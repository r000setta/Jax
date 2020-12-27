#pragma once
#include <stdio.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>
#include <sys/stat.h>
#include <atlsimpstr.h>

#pragma warning(disable:4251)
#pragma warning(disable:4595)
#pragma warning(disable:4091)

#ifdef JAXCORE_EXPORTS
#define JAXCORE_API __declspec(dllexport)
#else
#define JAXCORE_API __declspec(dllimport)
#endif

namespace Jax
{
#if WIN32
#define SYSTEM_BIT_WIDTH 32
#else if WIN64
#define SYSTEM_BIT_WIDTH 64
#endif
#if WIN32 || WIN64
#define WINDOWS
#endif

#define LOG_BUFFER_SIZE 65536

	class JAXCORE_API JaxSystem
	{
	public:
		static TCHAR sm_sLogBuffer[LOG_BUFFER_SIZE];
		static DWORD sm_dwMainThreadID;
	};
	FORCEINLINE bool JaxMemcpy(void* dest, const void* src, size_t count, size_t destSize = 0)
	{
		if (!destSize)
		{
			destSize = count;
		}
#ifdef WINDOWS
		return (memcpy_s(dest, destSize, src, count) == 0);
#else
		return false;
#endif // WINDOWS
	}

	FORCEINLINE size_t JaxStrlen(const TCHAR* str)
	{
#ifdef WINDOWS
		return (size_t)_tcslen(str);
#else
		return false;
#endif // WINDOWS
	}

	FORCEINLINE void JaxMemset(void* dest, int value, size_t size)
	{
#ifdef WINDOWS
		memset(dest, value, size);
#else
		return null;
#endif // WINDOWS
	}

	FORCEINLINE void JaxStrcat(TCHAR* dest, size_t count, const TCHAR* src)
	{
#ifdef WINDOWS
		_tcscat_s(dest, count, src);
#else
		return;
#endif
	}

	FORCEINLINE TCHAR* JaxStrtok(TCHAR* str, const TCHAR* delimiters, TCHAR** context)
	{
#ifdef WINDOWS
		return _tcstok_s(str, delimiters, context);
#else
		return NULL;
#endif // WINDOWS		
	}

	FORCEINLINE const TCHAR* JaxCsrChr(const TCHAR* string, int c)
	{
#ifdef WINDOWS
		return _tcsrchr(string, c);
#else
		return NULL;
#endif // WINDOWS

	}

	FORCEINLINE void JaxOutputDebugString(const TCHAR* format, ...)
	{
#ifdef WINDOWS
		char* pArgs;
		pArgs = (char*)&format + sizeof(format);
		_vstprintf_s(JaxSystem::sm_sLogBuffer, LOG_BUFFER_SIZE, format, pArgs);
		OutputDebugString(JaxSystem::sm_sLogBuffer);
#else
		return;
#endif
	}
}
