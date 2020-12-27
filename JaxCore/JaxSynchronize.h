#pragma once
#include "JaxSystem.h"

namespace Jax
{
	class JAXCORE_API JaxSynchronize
	{
	public:
		JaxSynchronize() {}
		virtual ~JaxSynchronize() {}
		
		virtual void* GetHandle() = 0;
		
	};

	class JAXCORE_API JaxCriticalSection
	{
		CRITICAL_SECTION CriticalSection;
	public:
		FORCEINLINE JaxCriticalSection()
		{
			InitializeCriticalSection(&CriticalSection);
			SetCriticalSectionSpinCount(&CriticalSection, 4000);
		}

		FORCEINLINE ~JaxCriticalSection()
		{
			DeleteCriticalSection(&CriticalSection);
		}

		FORCEINLINE void Lock()
		{
			EnterCriticalSection(&CriticalSection);
		}

		FORCEINLINE void Unlock()
		{
			LeaveCriticalSection(&CriticalSection);
		}
	};
}