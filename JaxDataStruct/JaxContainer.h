#pragma once
#include "JaxMemManager.h"
#ifdef JAXDATASTRUCT_EXPORTS
#define JAXDATASTRUCT_API __declspec(dllexport)
#else
#define JAXDATASTRUCT_API __declspec(dllimport)
#endif

namespace Jax
{
	template<typename KEY,typename VALUE>
	class MapElement :public JaxMemObject
	{
	public:
		KEY key;
		VALUE value;
		void operator=(const MapElement<KEY, VALUE>& Element)
		{
			key = Element.key;
			value = Element.value;
		}

		MapElement() {}
		MapElement(const MapElement<KEY, VALUE>& Element)
		{
			key = Element.key;
			value = Element.value;
		}
		MapElement(const KEY& _key, const VALUE& _value)
		{
			key = _key;
			value = _value;
		}
		~MapElement() {}
	};

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