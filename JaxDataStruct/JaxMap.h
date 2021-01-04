#pragma once
#include "JaxContainer.h"

namespace Jax
{
	template<typename KEY,typename VALUE,JaxMemManagerFun MMFun=JaxMemObject::GetMemManager>
	class JaxMap :public JaxContainer<MapElement<KEY,VALUE>,MMFun>
	{
	public:
		enum
		{
			DEFAULT_GROWBY=10
		};
		JaxMap(size_t growBy = DEFAULT_GROWBY);
		~JaxMap();

		void SetBufferNum(size_t bufferNum);
		void AddBufferNum(size_t bufferNum);
		void operator=(const JaxMap<KEY, VALUE, MMFun>& Map);

		FORCEINLINE size_t GetNum() const;
		FORCEINLINE size_t GetBufferNum() const;
		FORCEINLINE MapElement<KEY, VALUE>* GetBuffer() const;
		FORCEINLINE void SetGrowBy(size_t growBy);

		template<typename KEY1,typename VALUE1>
		void AddElement(const MapElement<KEY1, VALUE1>& Element);
		void AddElement(const KEY& Key, const VALUE& Value);

		template<typename KEY1,typename VALUE1,JaxMemManagerFun MMFun1>
		void AddElement(const JaxMap<KEY1, VALUE1, MMFun1>& Map, size_t begin, size_t end);

		MapElement<KEY, VALUE>& operator[](size_t i) const;
		void Clear();
		
		FORCEINLINE size_t GetSize() const;
		void Erase(size_t i);
		void Erase(size_t begin, size_t end);

		size_t Find(const KEY& key) const;

		void Destory();
	protected:
		MapElement<KEY, VALUE>* m_pBuffer;
		size_t m_uiGrowBy;
		size_t m_uiCurUse;
		size_t m_uiBufferNum;
		size_t m_uiAllocNum;
	}
	;
	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	inline JaxMap<KEY, VALUE, MMFun>::JaxMap(size_t growBy)
	{
		m_uiGrowBy = growBy;
		m_pBuffer = NULL;
		m_uiCurUse = 0;
		m_uiBufferNum = 0;
		m_uiAllocNum = 0;
	}

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	inline JaxMap<KEY, VALUE, MMFun>::~JaxMap()
	{
		Delete(m_pBuffer, m_uiCurUse);
	}

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	inline void JaxMap<KEY, VALUE, MMFun>::SetBufferNum(size_t bufferNum)
	{
		if (!bufferNum)
		{
			Delete(m_pBuffer, m_uiCurUse);
			m_uiBufferNum = bufferNum;
		
			m_pBuffer = New(bufferNum);
			if (!m_pBuffer)
				return;
			m_uiCurUse = bufferNum;
			for (size_t i = 0; i < bufferNum; ++i)
			{
				JAX_NEW(m_pBuffer + i) MapElement<KEY, VALUE>();
			}
		}
	}

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	inline void JaxMap<KEY, VALUE, MMFun>::AddBufferNum(size_t bufferNum)
	{
		if (!bufferNum)
		{
			m_uiAllocNum++;
			m_uiGrowBy = m_uiAllocNum * m_uiGrowBy;

			MapElement<KEY, VALUE>* pBuffer = NULL;
			pBuffer = New(m_uiBufferNum + bufferNum);
			if (!pBuffer)
				return;
			if (m_pBuffer && m_uiCurUse)
			{
				for (size_t i = 0; i < m_uiCurUse; ++i)
				{
					JAX_NEW(pBuffer + i) MapElement<KEY, VALUE>(m_pBuffer[i]);
				}
			}
			Delete(m_pBuffer, m_uiCurUse);
			m_uiBufferNum += bufferNum;
			m_pBuffer = pBuffer;
		}
	}

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	inline void JaxMap<KEY, VALUE, MMFun>::operator=(const JaxMap<KEY, VALUE, MMFun>& map)
	{
		if (m_uiBufferNum >= map.GetNum())
		{
			Clear();
			m_uiCurUse = map.GetNum();
			MapElement<KEY, VALUE>* pBuffer = map.GetBuffer();
			for (size_t i = 0; i < m_uiCurUse; ++i)
			{
				JAX_NEW(m_pBuffer + i) MapElement<KEY, VALUE>(pBuffer[i]);
			}
		}
		else
		{
			Delete(m_pBuffer, m_uiCurUse);
			m_uiBufferNum = map.GetBufferNum();
			m_uiCurUse = map.GetNum();
			m_pBuffer = New(m_uiBufferNum);
			if (!m_pBuffer)
				return;
			MapElement<KEY, VALUE>* pBuffer = map.GetBuffer();
			for (size_t i = 0; i < m_uiCurUse; ++i)
			{
				JAX_NEW(m_pBuffer + i) MapElement<KEY, VALUE>(pBuffer[i]);
			}
		}
		return;
	}

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	inline size_t JaxMap<KEY, VALUE, MMFun>::GetNum() const
	{
		return m_uiCurUse;
	}

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	inline size_t JaxMap<KEY, VALUE, MMFun>::GetBufferNum() const
	{
		return m_uiBufferNum;
	}

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	inline MapElement<KEY, VALUE>* JaxMap<KEY, VALUE, MMFun>::GetBuffer() const
	{
		return m_pBuffer;
	}

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	inline void JaxMap<KEY, VALUE, MMFun>::SetGrowBy(size_t growBy)
	{
		m_uiGrowBy = growBy;
	}

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	inline void JaxMap<KEY, VALUE, MMFun>::AddElement(const KEY& Key, const VALUE& Value)
	{
		if (Find(Key) != m_uiCurUse)
		{
			return;
		}
		if (m_uiCurUse == m_uiBufferNum)
		{
			if (!m_uiGrowBy)
			{
				return;
			}
			AddBufferNum(m_uiGrowBy);
		}
		MapElement<KEY, VALUE> element(Key, Value);
		JAX_NEW(m_pBuffer + m_uiCurUse) MapElement<KEY, VALUE>(element);
		m_uiCurUse++;
	}

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	inline MapElement<KEY, VALUE>& JaxMap<KEY, VALUE, MMFun>::operator[](size_t i) const
	{
#ifdef DEBUG
		JAX_ASSERT(i < m_uiBufferNum);
#endif // DEBUG
		return m_pBuffer[i];
	}

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	inline void JaxMap<KEY, VALUE, MMFun>::Clear()
	{
		for (size_t i = 0; i < m_uiCurUse; ++i)
		{
			m_pBuffer[i].~MapElement<KEY, VALUE>();
		}
		m_uiCurUse = 0;
	}

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	inline size_t JaxMap<KEY, VALUE, MMFun>::GetSize() const
	{
		return sizeof(size_t) * 4 + sizeof(MapElement<KEY, VALUE>*) + sizeof(MapElement<KEY, VALUE>) * m_uiBufferNum;
	}

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	inline void JaxMap<KEY, VALUE, MMFun>::Erase(size_t i)
	{
		Erase(i, i);
	}

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	inline void JaxMap<KEY, VALUE, MMFun>::Erase(size_t begin, size_t end)
	{
		if (end >= m_uiCurUse)
		{
			return;
		}
		if (begin > end)
		{
			return;
		}
		size_t k;
		size_t moveNum = m_uiCurUse - end - 1;
		size_t moveIdx;
		for (size_t i = begin; i <= end; ++i)
		{
			m_pBuffer[i].~MapElement<KEY, VALUE>();
		}
		for (k = 0; k < moveNum; ++k)
		{
			moveIdx = end + k + 1;
			if (moveIdx < m_uiCurUse)
			{
				JAX_NEW(m_pBuffer + begin + k) MapElement<KEY, VALUE>(m_pBuffer[moveIdx]);
				m_pBuffer[moveIdx].~MapElement<KEY, VALUE>();
			}
		}
		m_uiCurUse -= ((end - begin) + 1);
	}

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	inline size_t JaxMap<KEY, VALUE, MMFun>::Find(const KEY& key) const
	{
		size_t i = 0;
		for (i = 0; i < m_uiCurUse; ++i)
		{
			if (m_pBuffer[i].Key == key)
			{
				break;
			}
		}
		return i;
	}

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	inline void JaxMap<KEY, VALUE, MMFun>::Destory()
	{
		Clear();
		Delete(m_pBuffer, m_uiCurUse);
	}


	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	template<typename KEY1, typename VALUE1>
	inline void JaxMap<KEY, VALUE, MMFun>::AddElement(const MapElement<KEY1, VALUE1>& Element)
	{
		if (Find(Element.key) != m_uiCurUse)
		{
			return;
		}
		if (m_uiCurUse == m_uiBufferNum)
		{
			if (!m_uiGrowBy)
			{
				return;
			}
			AddBufferNum(m_uiGrowBy);
		}
		JAX_NEW(m_pBuffer + m_uiCurUse) MapElement<KEY, VALUE>(Element);
		m_uiCurUse++;
	}

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	template<typename KEY1, typename VALUE1, JaxMemManagerFun MMFun1>
	inline void JaxMap<KEY, VALUE, MMFun>::AddElement(const JaxMap<KEY1, VALUE1, MMFun1>& Map, size_t begin, size_t end)
	{
		if (begin > end)
		{
			return;
		}
		if (end >= Map.GetNum())
		{
			end = Map.GetNum() - 1;
		}
		int addNum = end - begin + 1;
		int haveNum = m_uiBufferNum - m_uiCurUse;
		int needNum = haveNum - addNum;

		if (needNum < 0)
		{
			if (m_uiGrowBy)
			{
				needNum = -needNum;
				if ((size_t)needNum < m_uiGrowBy)
				{
					AddBufferNum(m_uiGrowBy);
				}
				else {
					AddBufferNum(needNum);
				}
			}
			else
			{
				addNum = haveNum;
			}
		}

		if (addNum == 1)
		{
			AddElement(Map[begin]);
		}
		else if (addNum == 2)
		{
			AddElement(Map[begin]);
			AddElement(Map[begin + 1]);
		}

		else
		{
			MapElement<KEY1, VALUE1>* pBuffer = Map.GetBuffer();
			for (size_t i = m_uiCurUse; i < addNum + m_uiCurUse; ++i)
			{
				JAX_NEW(m_pBuffer + i) MapElement<KEY1, VALUE1>(pBuffer[begin]);
				begin++;
			}
			m_uiCurUse++;
		}
	}


	template<typename KEY, typename VALUE,JaxMemManagerFun MMFun=JaxMemObject::GetMemManager>
	class JaxMapOrder :public JaxMap<KEY, VALUE, MMFun>
	{
	public:
		JaxMapOrder(size_t growBy = DEFAULT_GROWBY);
		~JaxMapOrder();

		template<typename KEY1,typename VALUE1>
		void AddElement(const MapElememt<KEY1, VALUE1>& element);

		void AddElememt(const KEY& key, const VALUE& value);
		size_t Find(const KEY& key);

	protected:
		template<typename KEY1,typename VALUE1>
		size_t Process(size_t idx0, size_t idx1, const MapElement<KEY1, VALUE1>& element);

		size_t FindElement(size_t idx0, size_t idx1, const KEY& key) const;
	};

	template<typename KEY, typename VALUE,JaxMemManagerFun MMFun>
	inline JaxMapOrder<KEY,VALUE, MMFun>::JaxMapOrder(size_t growBy)
	{
	}

	template<typename KEY, typename VALUE,JaxMemManagerFun MMFun>
	inline JaxMapOrder<KEY,VALUE,MMFun>::~JaxMapOrder()
	{
	}

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	inline void JaxMapOrder<KEY, VALUE, MMFun>::AddElememt(const KEY& key, const VALUE& value)
	{
		MapElement<KEY, VALUE> element{ key,value };
		AddElement(element);
	}

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	inline size_t JaxMapOrder<KEY, VALUE, MMFun>::Find(const KEY& key)
	{
		if (m_uiCurUse)
		{
			if (m_pBuffer[0].key > key)
			{
				return m_uiCurUse;
			}
			else if (key > m_pBuffer[m_uiCurUse - 1].key)
			{
				return m_uiCurUse;
			}
			else
			{
				return FindElement(0, m_uiCurUse - 1, key);
			}
		}
		else
		{
			return m_uiCurUse;
		}
	}

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	inline size_t JaxMapOrder<KEY, VALUE, MMFun>::FindElement(size_t idx0, size_t idx1, const KEY& key) const
	{
		if (idx0 == idx1)
		{
			if (m_pBuffer[idx0].key == key)
			{
				return idx0;
			}
			else
			{
				return m_uiCurUse;
			}
		}
		else if (idx1 - idx0 == 1)
		{
			if (m_pBuffer[idx0].key == key)
			{
				return idx0;
			}
			else if (m_pBuffer[idx1].key == key)
			{
				return idx1;
			}
			else
			{
				return m_uiCurUse;
			}
		}
		else
		{
			size_t idx = (idx0 + idx1) >> 1;
			if (m_pBuffer[idx].key == key)
			{
				return idx;
			}
			else if (m_pBuffer[idx].key > key)
			{
				return FindElement(idx0, idx, key);
			}
			else
			{
				return FindElement(idx, idx1, key);
			}
		}
	}

	template<typename KEY,typename VALUE, JaxMemManagerFun MMFun>
	template<typename KEY1, typename VALUE1>
	inline void JaxMapOrder<KEY,VALUE,MMFun>::AddElement(const MapElememt<KEY1, VALUE1>& element)
	{
		if (Find(element.key) != m_uiCurUse)
		{
			return;
		}

		if (m_uiCurUse == m_uiBufferNum)
		{
			if (!m_uiGrowBy)
			{
				return;
			}
			AddBufferNum(m_uiGrowBy);
		}

		size_t idx;
		if (m_uiCurUse == 0)
		{
			idx = 0;
		}
		else if (m_uiCurUse == 1)
		{
			if (m_pBuffer[0].key > element.key)
			{
				idx = 0;
			}
			else
			{
				idx = 1;
			}
		}
		else if (m_pBuffer[0].key > element.key)
		{
			idx = 0;
		}
		else if (element.key > m_pBuffer[m_uiCurUse - 1].key)
		{
			idx = m_uiCurUse;
		}
		else
		{
			idx = Process(0, m_uiCurUse - 1, element);
		}
		if (m_uiCurUse == idx)
		{
			JAX_NEW(m_pBuffer + idx) MapElememt<KEY, VALUE>(element);
		}
		else
		{
			JAX_NEW(m_pBuffer + m_uiCurUse) MapElememt<KEY, VALUE>(m_pBuffer[m_uiCurUse - 1]);
			for (size_t i = m_uiCurUse - 2; i >= idx; --i)
			{
				m_pBuffer[i + 1] = m_pBuffer[i];
			}
			m_pBuffer[idx] = element;
		}
		m_uiCurUse++;
	}

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	template<typename KEY1, typename VALUE1>
	inline size_t JaxMapOrder<KEY, VALUE, MMFun>::Process(size_t idx0, size_t idx1, const MapElement<KEY1, VALUE1>& element)
	{
		if (idx0 == idx1)
		{
			return idx0;
		}
		else if (idx1 - idx0 == 1)
		{
			return idx1;
		}
		else
		{
			size_t idx = (idx0 + idx + 1) >> 1;
			if (m_pBuffer[idx].key == element.key)
			{
				return idx;
			}
			else if (m_pBuffer[idx].key > element.key)
			{
				return Process(idx0, idx, element);
			}
			else
			{
				return Process(idx, idx1, element);
			}
		}
	}


}