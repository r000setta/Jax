#pragma once
#include "JaxMemManager.h"
#ifdef JAXDATASTRUCT_EXPORTS
#define JAXDATASTRUCT_API __declspec(dllexport)
#else
#define JAXDATASTRUCT_API __declspec(dllimport)
#endif

namespace Jax
{
	template<typename T,JaxMemManagerFun MMFun=JaxMemObject::GetMemManager>
	class JaxContainer :public JaxMemObject
	{
	protected:
		T* New(size_t size)
		{
			if (!size)
			{
				return NULL;
			}
#ifdef USE_CUSTOM_NEW
			T* pPtr = (T*)MMFun().Allocate(size * sizeof(T), 0, true);
			JAX_ASSERT(pPtr);
			if (!pPtr)
			{
				return NULL;
			}
#else
			T* pPtr = (T*)malloc(sizeof(T) * size);
			JAX_ASSERT(pPtr);
			if (!pPtr)
			{
				return NULL;
			}
#endif // USE_CUSTOM_NEW
			return pPtr;
		}

		void Delete(T*& pPtr, size_t size)
		{
			if (!pPtr)
			{
				return;
			}
#ifdef USE_CUSTOM_NEW
			if (size > 0)
			{
				if (ValueBase<T>::NeedsDestructor)
				{
					for (size_t i = 0; i < size; ++i)
					{
						(pPtr + i)->~T();
					}
				}
			}
			MMFun().Deallocate((char*)pPtr, 0, true);
			pPtr = NULL;
#else
			free(pPtr);
			pPtr = NULL;
#endif // USE_CUSTOM_NEW

		}
	};
}