#pragma once
#include "JaxName.h"
#include "JaxObject.h"

namespace Jax
{
	class JaxStream;
	class JAXGRAPHIC_API JaxResource
	{
	public:
		enum //Resource Type
		{
			RT_TEXTURE,
			RT_MAX
		};

		JaxResource();
		virtual ~JaxResource() = 0;
		FORCEINLINE const JaxUsedName& GetResourceName() const
		{
			return m_ResourceName;
		}

		FORCEINLINE void SetResourceName(const JaxUsedName& name)
		{
			m_ResourceName = name;
		}

		virtual size_t GetResourceType() const = 0;
		static const JaxString& GetFileSuffix(size_t suffix);
	protected:
		JaxUsedName m_ResourceName;
		static JaxString sm_FileSuffix[];
	};

	class JAXGRAPHIC_API JaxResourceProxyBase :public JaxReference, public JaxMemObject
	{
	public:
		JaxResourceProxyBase();
		virtual ~JaxResourceProxyBase() = 0;
		virtual bool IsEnableASYNLoad() = 0;
		virtual bool IsLoaded() = 0;
		virtual const JaxUsedName& GetResourceName() = 0;
		virtual size_t GetResourceType() = 0;

		void LoadEvent()
		{
			for (size_t i = 0; i < m_LoadedEventObject.GetNum(); ++i)
			{
				m_LoadedEventObject[i].key->LoadEvent(this, m_LoadedEventObject[i].value);
			}
			m_LoadedEventObject.Destory();
		}

		void AddLoadEventObject(JaxObject* object, int data = 0)
		{
			if (!object) return;
			if (m_bIsLoaded == false)
			{
				m_LoadedEventObject.AddElement(object, data);
			}
			else
			{
				object->LoadEvent(this);
			}
		}
	protected:
		JaxMap<JaxObjectPtr, int> m_LoadedEventObject;
		bool m_bIsLoaded;
		JaxUsedName m_ResourceName;

		void Loaded()
		{
			m_bIsLoaded = true;
			LoadEvent();
		}

		void SetResourceName(const JaxUsedName& name)
		{
			m_ResourceName = name;
		}
	};
	DECLARE_PTR(JaxResourceProxyBase);

	template<typename T>
	class JaxResourceProxy :public JaxResourceProxyBase
	{
	public:
		JaxResourceProxy();
		virtual ~JaxResourceProxy();
		T* GetResource();
		virtual const JaxUsedName& GetResourceName();
		friend class JaxResourceManager;
		virtual bool IsLoaded();
		virtual bool IsEnableASYNLoad();
		virtual size_t GetResourceType();
		void SetNewResource(JaxPointer<T> resource);
		static JaxResourceProxy<T>* Create(T* resource);

	protected:
		JaxPointer<T> m_pResource;
		JaxPointer<T> m_pPreResource;
	};

	template<typename T>
	inline JaxResourceProxy<T>::JaxResourceProxy()
	{
		m_bIsLoaded = false;
		m_pPreResource = (T*)T::GetDefault();
		m_pResource = NULL;
	}

	template<typename T>
	inline JaxResourceProxy<T>::~JaxResourceProxy()
	{
		m_pPreResource = NULL;
		m_pResource = NULL;
	}

	template<typename T>
	inline T* JaxResourceProxy<T>::GetResource()
	{
		if (m_bIsLoaded)
		{
			return m_pResource;
		}
		else
		{
			return m_pPreResource;
		}
	}

	template<typename T>
	inline const JaxUsedName& JaxResourceProxy<T>::GetResourceName()
	{
		return m_ResourceName;
	}

	template<typename T>
	inline bool JaxResourceProxy<T>::IsLoaded()
	{
		return m_bIsLoaded;
	}

	template<typename T>
	inline bool JaxResourceProxy<T>::IsEnableASYNLoad()
	{
		return false;
	}

	template<typename T>
	inline size_t JaxResourceProxy<T>::GetResourceType()
	{
		return GetResource()->GetResourceType();
	}

	template<typename T>
	inline void JaxResourceProxy<T>::SetNewResource(JaxPointer<T> resource)
	{
		m_pResource = resource;
		m_pResource->SetResourceName(m_ResourceName);
	}

	template<typename T>
	inline JaxResourceProxy<T>* JaxResourceProxy<T>::Create(T* resource)
	{
		JaxResourceProxy<T>* proxy = JAX_NEW JaxResource<T>();
		proxy->SetResourceName(resource->GetResouceName());
		proxy->SetNewResource(resource);
		proxy->Loaded();
		return proxy;
	}

#define DECLARE_PROXY(className) \
typedef JaxResourceProxy<className> ##className##R; \
typedef JaxPointer<JaxResourceProxy<className>> ##className##RPtr;
}