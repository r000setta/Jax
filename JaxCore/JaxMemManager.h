#pragma once
#include "JaxSystem.h"
#include "JaxSynchronize.h"
#include <Windows.h>
#include <new.h>

#define JAX_NEW new
#define JAX_DELETE delete
#define USE_STL_TYPE_TRAIT
#ifdef USE_STL_TYPE_TRAIT
#include <type_traits>
#endif // USE_STL_TYPE_TRAIT

namespace Jax
{
	class JAXCORE_API JaxMemManager
	{
	public:
		JaxMemManager() {}
		virtual ~JaxMemManager() = 0;
		virtual void* Allocate(size_t size, size_t alignment, bool isArray) = 0;
		virtual void Deallocate(char* addr, size_t alignment, bool isArray) = 0;
	};

	class JAXCORE_API JaxDebugMem :public JaxMemManager
	{
	public:
		JaxDebugMem();
		~JaxDebugMem();

		virtual void* Allocate(size_t size, size_t alignment, bool isArray) = 0;
		virtual void Deallocate(char* addr, size_t alignment, bool isArray) = 0;
		
	private:
		enum
		{
			BEGIN_MASK = 0xDEADC0DE,
			END_MASK = 0xDEADC0DE,
			RECORD_NUM = 32,
			CALLSTACK_NUM=32
		};

		static JaxCriticalSection sm_MemLock;
		class Block
		{
		public:
			Block()
			{
				for (size_t i = 0; i < CALLSTACK_NUM; ++i)
				{
					pAddr[i] = NULL;
				}
				m_pPrev = NULL;
				m_pNext = NULL;
			}
			void* pAddr[CALLSTACK_NUM];
			size_t m_uiStackInfoNum;
			size_t m_uiSize;
			bool m_bIsArray;
			bool m_bAlignment;
			Block* m_pPrev;
			Block* m_pNext;
		};
		size_t m_uiNumNewCalls;
		size_t m_uiNumDeleteCalls;
		Block* m_pHead;
		Block* m_pTail;
		size_t m_uiNumBlocks;
		size_t m_uiNumBytes;
		size_t m_uiMaxNumBytes;
		size_t m_uiMaxNumBlocks;
		size_t m_uiSizeRecord[RECORD_NUM];
		void InsertBlock(Block* pBlock);
		void RemoveBlock(Block* pBlock);
		
	};
}