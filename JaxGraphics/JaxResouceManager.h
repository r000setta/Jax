#pragma once
#include "JaxObject.h"
#include "JaxString.h"
#include "JaxArray.h"
#include "JaxMap.h"
#include "JaxName.h"
#include "JaxPriority.h"

namespace Jax
{
	class JaxResourceControll
	{
	public:
		JaxResourceControll(unsigned int GCMaxTimeCount);
		virtual ~JaxResourceControll();
		virtual void GCResource();
	protected:
		JaxArray<unsigned int> m_TimeCount;
		unsigned int m_uiGCMaxTimeCount;
	};

	template<typename KEY,typename VALUE>
	class JaxResourceSet :public JaxResourceControll
	{
	protected:
		JaxMapOrder<KEY, VALUE> m_Resource;
	public:
		JaxResourceSet(unsigned int GCMaxTimeCount = 5000);
		~JaxResourceSet();

		VALUE CheckIsHaveTheResource(const KEY& key);
		bool AddResource(const KEY& key, VALUE object);
		bool DeleteResource(const KEY& key);

		unsigned int GetResourceNum();

		bool IsRealeseAll();
		void ClearAll();
		const MapElement<KEY, VALUE>* GetResource(unsigned int i);
	};

	class JAXGRAPHIC_API JaxResourceManager
	{
		DECLARE_PRIORITY

	public:
		JaxResourceManager();
		~JaxResourceManager();

#define GET_INNER_RESOURCE_SET(ResourceName) \
static JaxResourceSet<unsigned int,Jax##ResourceName##Ptr>& Get##ResourceName##Set() \
{ \
static JaxResourceSet<unsigned int,Jax##ResourceName##Ptr> s_##ResourceName##Set; \
return s_##ResourceName##Set; \
}

		GET_INNER_RESOURCE_SET(Name);

		static JaxName* CreateName(const TCHAR* pChar);
		static JaxName* CreateName(const JaxString& string);

	protected:
		static JaxCriticalSection sm_NameCri;
	};

	template<typename KEY, typename VALUE>
	inline JaxResourceSet<KEY, VALUE>::JaxResourceSet(unsigned int GCMaxTimeCount):JaxResourceControll(GCMaxTimeCount)
	{
		m_Resource.Clear();
	}

	template<typename KEY, typename VALUE>
	inline JaxResourceSet<KEY, VALUE>::~JaxResourceSet()
	{
		m_Resource.Clear();
	}

	template<typename KEY, typename VALUE>
	inline VALUE JaxResourceSet<KEY, VALUE>::CheckIsHaveTheResource(const KEY& key)
	{
		size_t i = m_Resource.Find(key);
		if (i == m_Resource.GetNum())
		{
			return NULL;
		}
		m_TimeCount[i] = 0;
		return m_Resource[i].value; //
	}

	template<typename KEY, typename VALUE>
	inline bool JaxResourceSet<KEY, VALUE>::AddResource(const KEY& key, VALUE object)
	{
		if (!object)
		{
			return false;
		}
		m_Resource.AddElememt(key, object);
		m_TimeCount.AddElement(0);
		return true;
	}

	template<typename KEY, typename VALUE>
	inline bool JaxResourceSet<KEY, VALUE>::DeleteResource(const KEY& key)
	{
		size_t i = m_Resource.Find(key);
		if (i == m_Resource.GetNum())
		{
			return NULL;
		}
		m_Resource.Erase(i);
		m_TimeCount.Erase(i);
		return true;
	}

	template<typename KEY, typename VALUE>
	inline unsigned int JaxResourceSet<KEY, VALUE>::GetResourceNum()
	{
		return m_Resource.GetNum();
	}

	template<typename KEY, typename VALUE>
	inline bool JaxResourceSet<KEY, VALUE>::IsRealeseAll()
	{
		return !m_Resource.GetNum();
	}

	template<typename KEY, typename VALUE>
	inline void JaxResourceSet<KEY, VALUE>::ClearAll()
	{
		m_Resource.Clear();
	}

	template<typename KEY, typename VALUE>
	inline const MapElement<KEY, VALUE>* JaxResourceSet<KEY, VALUE>::GetResource(unsigned int i)
	{
		JAX_ASSERT(i < m_Resource.GetNum());
		return &m_Resource[i];
	}


}