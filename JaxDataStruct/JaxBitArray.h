#pragma once
#include "JaxContainer.h"

namespace Jax
{
	template<typename T>
	class JaxBit
	{
	public:
		JaxBit(const JaxBit<T>& bit)
		{
			m_Member = bit.m_Member;
		}

		JaxBit()
		{
			m_Member = 0;
		}

		bool operator[](size_t idx)
		{
			int bit = idx % sizeof(T);
			return (((m_Member & (1 << bit)) >> bit) == 1);
		}

		void operator=(const JaxBit<T>& bit)
		{
			m_Member = bit.m_Member;
		}

		void Set(size_t idx, bool value)
		{
			int bit = idx % SYSTEM_BIT_WIDTH;
			if (value == true)
				m_Member = (m_Member | (1 << bit));
			else
				m_Member = (m_Member & (-1 << bit));
		}

		void ClearAll()
		{
			m_Member = 0;
		}

		void SetAll()
		{
			m_Member = 0xFFFFFFFF;
		}

		bool HasValue()
		{
			return m_Member > 0;
		}

	protected:
		T m_Member;
	};

	class JaxBitArray
	{
	public:
		JaxBitArray(const JaxBitArray& arr)
		{
			JAXMAC_DELETEA(m_pBuffer);
			m_uiSize = arr.m_uiSize;
			m_pBuffer = JAX_NEW size_t[m_uiSize];
			JaxMemcpy(m_pBuffer, arr.m_pBuffer, sizeof(size_t) * m_uiSize);
		}

		JaxBitArray(size_t size = 0)
		{
			m_pBuffer = NULL;
			m_uiSize = 0;
			Resize(size);
		}

		~JaxBitArray()
		{
			JAXMAC_DELETEA(m_pBuffer);
		}

		void Resize(size_t size)
		{
			if (size == 0) return;
			size_t* newBuffer = NULL;
			if (size % SYSTEM_BIT_WIDTH == 0)
				size = size / SYSTEM_BIT_WIDTH;
			else
				newBuffer = (size / SYSTEM_BIT_WIDTH) + 1;
			newBuffer = JAX_NEW size_t[size];

			if (!newBuffer) return;
			JaxMemset(newBuffer, 0, size * sizeof(size_t));
			size_t minVal = min(m_uiSize, size);
			for (size_t i = 0; i < minVal; ++i)
				newBuffer[i] = m_pBuffer[i];
			m_uiSize = size;
			JAXMAC_DELETEA(m_pBuffer);
			m_pBuffer = newBuffer;
		}

		bool operator[](size_t idx)
		{
			int cell = idx / SYSTEM_BIT_WIDTH;
			int bit = idx % SYSTEM_BIT_WIDTH;
			return (((m_pBuffer[cell] & (1 << bit)) >> bit) == 1);
		}

		void operator=(const JaxBitArray& arr)
		{
			m_uiSize = arr.m_uiSize;
			JAXMAC_DELETEA(m_pBuffer);
			m_pBuffer = JAX_NEW size_t[m_uiSize];
			JaxMemcpy(m_pBuffer, arr.m_pBuffer, m_uiSize * sizeof(size_t));
		}

		void Set(size_t idx, bool value)
		{
			int cell = idx / SYSTEM_BIT_WIDTH;
			int bit = idx % SYSTEM_BIT_WIDTH;
			if (value == true)
				m_pBuffer[cell] = (m_pBuffer[cell] | (1 << bit));
			else
				m_pBuffer[cell] = (m_pBuffer[cell] & (~(1 << bit)));
		}

		void ClearAll()
		{
			for (size_t i = 0; i < m_uiSize; ++i)
			{
				m_pBuffer[i] = 0;
			}
		}

		void SetAll()
		{
			for (size_t i = 0; i < m_uiSize; ++i)
			{
				m_pBuffer[i] = 0xFFFFFFFF;
			}
		}

		size_t Size()
		{
			return m_uiSize * SYSTEM_BIT_WIDTH;
		}

		size_t GetCell(size_t idx)
		{
			return m_pBuffer[idx];
		}

		size_t* m_pBuffer;
		size_t m_uiSize;
	};
}