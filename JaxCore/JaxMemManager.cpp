#include "JaxMemManager.h"
#include "JaxSystem.h"
#include <DbgHelp.h>

namespace Jax
{
	JaxCriticalSection JaxDebugMem::sm_MemLock;

	typedef BOOL
	(WINAPI
		* tFMiniDumpWriteDump)
		(
			IN HANDLE hProcess,
			IN DWORD ProcessId,
			IN HANDLE hFile,
			IN MINIDUMP_TYPE DumpType,
			IN CONST PMINIDUMP_EXCEPTION_INFORMATION ExceptionParam, OPTIONAL
			IN CONST PMINIDUMP_USER_STREAM_INFORMATION UserStreamParam, OPTIONAL
			IN CONST PMINIDUMP_CALLBACK_INFORMATION CallbackParam OPTIONAL
			);

	typedef BOOL
	(WINAPI
		* tFSymInitialize)
		(
			IN HANDLE   hProcess,
			IN PSTR     UserSearchPath,
			IN BOOL     fInvadeProcess
			);

	typedef BOOL
	(WINAPI
		* tFStackWalk64)
		(
			DWORD                             MachineType,
			HANDLE                            hProcess,
			HANDLE                            hThread,
			LPSTACKFRAME64                    StackFrame,
			PVOID                             ContextRecord,
			PREAD_PROCESS_MEMORY_ROUTINE64    ReadMemoryRoutine,
			PFUNCTION_TABLE_ACCESS_ROUTINE64  FunctionTableAccessRoutine,
			PGET_MODULE_BASE_ROUTINE64        GetModuleBaseRoutine,
			PTRANSLATE_ADDRESS_ROUTINE64      TranslateAddress
			);

	typedef BOOL
	(WINAPI
		* tFSymFromAddr)
		(
			IN  HANDLE              hProcess,
			IN  DWORD64             Address,
			OUT PDWORD64            Displacement,
			IN OUT PSYMBOL_INFO     Symbol
			);

	typedef BOOL
	(WINAPI
		* tFSymGetLineFromAddr64)
		(
			IN  HANDLE                  hProcess,
			IN  DWORD64                 qwAddr,
			OUT PDWORD                  pdwDisplacement,
			OUT PIMAGEHLP_LINE64        Line64
			);

	typedef DWORD
	(WINAPI
		* tFSymGetOptions)
		(
			VOID
			);

	typedef DWORD
	(WINAPI
		* tFSymSetOptions)
		(
			IN DWORD   SymOptions
			);

	typedef PVOID
	(WINAPI
		* tFSymFunctionTableAccess64)
		(
			HANDLE  hProcess,
			DWORD64 AddrBase
			);

	typedef DWORD64
	(WINAPI
		* tFSymGetModuleBase64)
		(
			IN  HANDLE              hProcess,
			IN  DWORD64             qwAddr
			);

	static tFMiniDumpWriteDump fnMiniDumpWriteDump = NULL;
	static tFSymInitialize fnSymInitialize = NULL;
	static tFStackWalk64 fnStackWalk64 = NULL;
	static tFSymFromAddr fnSymFromAddr = NULL;
	static tFSymGetLineFromAddr64 fnSymGetLineFromAddr64 = NULL;
	static tFSymGetOptions fnSymGetOptions = NULL;
	static tFSymSetOptions fnSymSetOptions = NULL;
	static tFSymFunctionTableAccess64 fnSymFunctionTableAccess64 = NULL;
	static tFSymGetModuleBase64 fnSymGetModuleBase64 = NULL;

	static HMODULE s_DbgHelpLib = NULL;
	static HANDLE s_Process = NULL;

	JaxDebugMem::JaxDebugMem()
	{
		m_uiNumNewCalls = 0;
		m_uiNumDeleteCalls = 0;
		m_uiNumBlocks = 0;
		m_uiNumBytes = 0;
		m_uiMaxNumBytes = 0;
		m_uiMaxNumBlocks = 0;
		m_pHead = NULL;
		m_pTail = NULL;

		for (size_t i = 0; i < RECORD_NUM; ++i)
		{
			m_uiSizeRecord[i] = 0;
		}
	}

	JaxDebugMem::~JaxDebugMem()
	{
		InitDbgHelpLib();
		PrintInfo();
		FreeDbgHelpLib();
		FreeLeakMem();
	}

	void* JaxDebugMem::Allocate(size_t size, size_t alignment, bool isArray)
	{
		sm_MemLock.Lock();
		if (!size) {
			sm_MemLock.Unlock();
			return NULL;
		}
		m_uiNumNewCalls++;
		size_t extendedSize = sizeof(Block) + sizeof(size_t) + size + sizeof(size_t);
		char* pAddr = (char*)malloc(extendedSize);
		if (!pAddr) return NULL;
		Block* pBlock = (Block*)pAddr;
		pBlock->m_uiSize = size;
		pBlock->m_bIsArray = isArray;
		pBlock->m_bAlignment = (alignment > 0) ? true : false;
		pBlock->m_uiStackInfoNum = 0;

		DWORD _ebp, _esp;
		__asm mov _ebp, ebp;
		__asm mov _esp, esp;

		for (size_t idx = 0; idx < CALLSTACK_NUM; ++idx)
		{
			void* addr = (void*)ULongToPtr(*(((DWORD*)ULongToPtr(_ebp)) + 1));
			if (!addr)
			{
				break;
			}
			pBlock->pAddr[idx] = addr;
			pBlock->m_uiStackInfoNum++;
			_ebp = *(DWORD*)ULongToPtr(_ebp);
			if (_ebp == 0 || 0 != (_ebp & 0xFC000000) || _ebp < _esp)
				break;
		}

		InsertBlock(pBlock);

		pAddr += sizeof(Block);
		size_t* pBeginMask = (size_t*)(pAddr);
		*pBeginMask = BEGIN_MASK;
		pAddr += sizeof(size_t);
		size_t* pEndMask = (size_t*)(pAddr + size);
		*pEndMask = END_MASK;

		m_uiNumBlocks++;
		m_uiNumBytes += size;
		m_uiMaxNumBytes = max(m_uiMaxNumBytes, m_uiNumBytes);
		m_uiMaxNumBlocks = max(m_uiMaxNumBlocks, m_uiNumBlocks);
		sm_MemLock.Unlock();
		return (void*)pAddr;
	}

	void JaxDebugMem::Deallocate(char* pAddr, size_t alignment, bool isArray)
	{
		sm_MemLock.Lock();
		m_uiNumDeleteCalls++;
		if (!pAddr)
		{
			sm_MemLock.Unlock();
			return;
		}

		pAddr -= sizeof(size_t);
		size_t* pBeginMask = (size_t*)(pAddr);
		JAX_ASSERT(*pBeginMask == BEGIN_MASK);
		pAddr -= sizeof(Block);
		Block* pBlock = (Block*)pAddr;
		RemoveBlock(pBlock);
		JAX_ASSERT(pBlock->m_bIsArray = isArray);
		JAX_ASSERT(m_uiNumBlocks > 0 && m_uiNumBytes >= pBlock->m_uiSize);
		bool bAlignment = alignment > 0 ? true : false;
		JAX_ASSERT(pBlock->m_bAlignment == bAlignment);
		size_t* pEndMask = (size_t*)(pAddr + sizeof(Block) + sizeof(size_t) + pBlock->m_uiSize);
		JAX_ASSERT(*pEndMask == END_MASK);

		m_uiNumBlocks--;
		m_uiNumBytes -= pBlock->m_uiSize;

		free(pAddr);
		sm_MemLock.Unlock();
	}

	void JaxDebugMem::InsertBlock(Block* pBlock)
	{
		if (m_pTail)
		{
			pBlock->m_pPrev = m_pTail;
			pBlock->m_pNext = NULL;
			m_pTail->m_pNext = pBlock;
			m_pTail = pBlock;
		}
		else
		{
			pBlock->m_pPrev = NULL;
			pBlock->m_pNext = NULL;
			m_pHead = pBlock;
			m_pTail = pBlock;
		}
	}

	void JaxDebugMem::RemoveBlock(Block* pBlock)
	{
		if (pBlock->m_pPrev)
		{
			pBlock->m_pPrev->m_pNext = pBlock->m_pNext;
		}
		else
		{
			m_pHead = pBlock->m_pNext;
		}

		if (pBlock->m_pNext)
		{
			pBlock->m_pNext->m_pPrev = pBlock->m_pPrev;
		}
		else
		{
			m_pTail = pBlock->m_pPrev;
		}
	}

	bool JaxDebugMem::GetFileAndLine(const void* pAddress, TCHAR szFile[MAX_PATH], int& line)
	{
		IMAGEHLP_LINE64 Line;
		Line.SizeOfStruct = sizeof(Line);
		JaxMemset(&Line, 0, sizeof(Line));
		DWORD Offset = 0;
		return true;
		if (fnSymGetLineFromAddr64(s_Process, (DWORD64)pAddress, &Offset, &Line))
		{
#ifdef _UNICODE

#else
			JaxStrCopy(szFile, MAX_PATH, Line.FileName);
#endif
			line = Line.LineNumber;
			return true;
		}
		else
		{
			DWORD error = GetLastError();
			return false;
		}
	}

	bool JaxDebugMem::InitDbgHelpLib()
	{
		TCHAR dbgName[MAX_PATH];
		GetModuleFileName(NULL, dbgName, MAX_PATH);
		TCHAR* p = (TCHAR*)JaxCsrChr(dbgName, _T('\\'));
		if (p) *p = NULL;
		JaxStrcat(dbgName, MAX_PATH, _T("\\dbghelp.dll"));

		s_DbgHelpLib = LoadLibrary(dbgName);
		if (s_DbgHelpLib == NULL)
		{
			s_DbgHelpLib = LoadLibrary(_T("dbghelp.dll"));
			if (s_DbgHelpLib == NULL)
			{
				return false;
			}
		}

		fnMiniDumpWriteDump = (tFMiniDumpWriteDump)GetProcAddress(s_DbgHelpLib, "MiniDumpWriteDump");
		fnSymInitialize = (tFSymInitialize)GetProcAddress(s_DbgHelpLib, "SymInitialize");
		fnStackWalk64 = (tFStackWalk64)GetProcAddress(s_DbgHelpLib, "StackWalk64");
		fnSymFromAddr = (tFSymFromAddr)GetProcAddress(s_DbgHelpLib, "SymFromAddr");
		fnSymGetLineFromAddr64 = (tFSymGetLineFromAddr64)GetProcAddress(s_DbgHelpLib, "SymGetLineFromAddr64");
		fnSymGetOptions = (tFSymGetOptions)GetProcAddress(s_DbgHelpLib, "SymGetOptions");
		fnSymSetOptions = (tFSymSetOptions)GetProcAddress(s_DbgHelpLib, "SymSetOptions");
		fnSymFunctionTableAccess64 = (tFSymFunctionTableAccess64)GetProcAddress(s_DbgHelpLib, "SymFunctionTableAccess64");
		fnSymGetModuleBase64 = (tFSymGetModuleBase64)GetProcAddress(s_DbgHelpLib, "SymGetModuleBase64");

		if (fnMiniDumpWriteDump &&
			fnSymInitialize &&
			fnStackWalk64 &&
			fnSymFromAddr &&
			fnSymGetLineFromAddr64 &&
			fnSymGetOptions &&
			fnSymSetOptions &&
			fnSymFunctionTableAccess64 &&
			fnSymGetModuleBase64)
		{
			DWORD ProcessID = GetCurrentProcessId();
			s_Process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessID);
			fnSymInitialize(s_Process, (PSTR)".", TRUE);
			return true;
		}
		return false;
	}

	void JaxDebugMem::FreeDbgHelpLib()
	{
		if (s_DbgHelpLib != NULL)
		{
			FreeLibrary(s_DbgHelpLib);
			CloseHandle(s_Process);
			s_Process = NULL;
			s_DbgHelpLib = NULL;
		}

		fnMiniDumpWriteDump = NULL;
		fnSymInitialize = NULL;
		fnStackWalk64 = NULL;
		fnSymFromAddr = NULL;
		fnSymGetLineFromAddr64 = NULL;
		fnSymGetOptions = NULL;
		fnSymSetOptions = NULL;
		fnSymFunctionTableAccess64 = NULL;
		fnSymGetModuleBase64 = NULL;
	}

	void JaxDebugMem::FreeLeakMem()
	{
		Block* pBlock = m_pHead;
		while (pBlock)
		{
			Block* tmp = pBlock;
			pBlock = pBlock->m_pNext;
			free((void*)tmp);
		}
	}

	void JaxDebugMem::PrintInfo()
	{
		JaxOutputDebugString(_T("#########################  begin print leak mem  ######################\n"));
		JaxOutputDebugString(_T("Max Byte Num: %d\n"), m_uiMaxNumBytes);
		JaxOutputDebugString(_T("Max Block Num: %d\n"), m_uiNumBlocks);
		JaxOutputDebugString(_T("Total Size: %d\n"), m_uiNumBytes);
		JaxOutputDebugString(_T("Block Num: %d\n"), m_uiNumBlocks);
		JaxOutputDebugString(_T("New Call: %d\n"), m_uiNumNewCalls);
		JaxOutputDebugString(_T("Delete Call: %d\n"), m_uiNumDeleteCalls);
		
		if (m_pHead)
		{
			JaxOutputDebugString(_T("Memory Leak:\n"));
		}
		else
		{
			JaxOutputDebugString(_T("No Memory Leak"));
		}

		Block* pBlock = m_pHead;
		static size_t leakNum = 0;
		while (pBlock)
		{
			leakNum++;
			JaxOutputDebugString(_T("$$$$$$$$$$$$$$$$  Leak %d  $$$$$$$$$$$$$$$$$\n"), leakNum);
			JaxOutputDebugString(_T("Size: %d\n"), pBlock->m_uiSize);
			JaxOutputDebugString(_T("Is Array: %d\n"), pBlock->m_bIsArray);

			TCHAR file[MAX_PATH];
			int line;
			for (size_t i = 0; i < pBlock->m_uiStackInfoNum; ++i)
			{
				if (!GetFileAndLine(pBlock->pAddr[i], file, line))
				{
					break;
				}
				JaxOutputDebugString(_T("%s(%d)\n"), file, line);
			}
			JaxOutputDebugString(_T("$$$$$$$$$$$$$$$$  Leak %d  $$$$$$$$$$$$$$$$$\n"), leakNum);
			pBlock = pBlock->m_pNext;
		}
		JaxOutputDebugString(_T("Leak block total num: %d\n"), leakNum);
		JaxOutputDebugString(_T("#########################  end print leak mem  ######################\n"));
	}

	JaxMemObject::JaxMemObject()
	{
#ifdef USE_CUSTOM_NEW
		GetMemManager();
#endif
	}

	JaxMemManager& Jax::JaxMemObject::GetMemManager()
	{
#ifdef _DEBUG
		static JaxDebugMem g_MemManager;
#endif // _DEBUG
		return g_MemManager;
	}
	JaxMemManager::JaxMemManager()
	{
	}
	JaxMemManager::~JaxMemManager()
	{
	}
}
