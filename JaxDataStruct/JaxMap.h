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
		if (!uiBufferNum)
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
		if (m_uiBufferNum >= Map.GetNum())
		{
			Clear();
			m_uiCurUse = Map.GetNum();
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
			for (size_t i = m_uiCurUse; m < addNum + m_uiCurUse; ++i)
			{
				JAX_NEW(m_pBuffer + i) MapElement<KEY1, VALUE1>(pBuffer[begin]);
				begin++;
			}
			m_uiCurUse++;
		}
	}

}