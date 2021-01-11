#pragma once
#include "JaxSynchronize.h"

namespace Jax
{
	template<typename T>
	class JaxPointer
	{
	public:
		JaxPointer(T* pObject = NULL);
		JaxPointer(const JaxPointer& pointer);
		~JaxPointer();

		T& operator*() const;
		T* operator->() const;

		JaxPointer& operator=(T* pObject);
		JaxPointer& operator=(const JaxPointer& reference);

		bool operator==(T* pObject) const;
		bool operator!=(T* pObject) const;
		bool operator==(const JaxPointer& reference) const;
		bool operator!=(const JaxPointer& reference) const;

		operator T* () const;

		FORCEINLINE T* GetObject() const
		{
			return m_pObject;
		}
		friend class JaxStream;
	private:
		T* m_pObject;
		FORCEINLINE void SetObject(T* pObject)
		{
			m_pObject = pObject;
		}
	};

	template<typename T>
	inline JaxPointer<T>::JaxPointer(T* pObject):m_pObject(pObject)
	{
		if (m_pObject)
		{
			m_pObject->IncreRef();
		}
	}

	template<typename T>
	inline JaxPointer<T>::JaxPointer(const JaxPointer& pointer):m_pObject(pointer.m_pObject)
	{
		if (m_pObject)
		{
			m_pObject->IncreRef();
		}
	}

	template<typename T>
	inline JaxPointer<T>::~JaxPointer()
	{
		if (m_pObject)
		{
			m_pObject = NULL;
		}
	}

	template<typename T>
	inline T& JaxPointer<T>::operator*() const
	{
		return *m_pObject;
	}

	template<typename T>
	inline T* JaxPointer<T>::operator->() const
	{
		return m_pObject;
	}

	template<typename T>
	inline JaxPointer<T>& JaxPointer<T>::operator=(T* pObject)
	{
		if (pObject != m_pObject)
		{
			if (pObject)
			{
				pObject->IncreRef();
			}
			if (m_pObject)
			{
				m_pObject->DecreRef();
			}
			m_pObject = pObject;
		}
		return *this;
	}

	template<typename T>
	inline JaxPointer<T>& JaxPointer<T>::operator=(const JaxPointer& reference)
	{
		if (m_pObject != reference.m_pObject)
		{
			if (reference.m_pObject)
			{
				reference.m_pObject->IncreRef();
			}
			if (m_pObject)
			{
				m_pObject->IncreRef();
			}
			m_pObject = reference.m_pObject;
		}
		return *this;
	}

	template<typename T>
	inline bool JaxPointer<T>::operator==(T* pObject) const
	{
		return m_pObject == pObject;
	}

	template<typename T>
	inline bool JaxPointer<T>::operator!=(T* pObject) const
	{
		return m_pObject != pObject;
	}

	template<typename T>
	inline bool JaxPointer<T>::operator==(const JaxPointer& reference) const
	{
		return m_pObject == reference.m_pObject;
	}

	template<typename T>
	inline bool JaxPointer<T>::operator!=(const JaxPointer& reference) const
	{
		return m_pObject != reference.m_pObject;
	}

	template<typename T>
	inline JaxPointer<T>::operator T* () const
	{
		return m_pObject;
	}

#define DECLARE_PTR(classname) \
class classname;\
typedef JaxPointer<classname> ##classname##Ptr;

}