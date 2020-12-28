template<typename T, JaxMemManagerFun MMFun>
 JaxArray<T, MMFun>::JaxArray(size_t growBy)
{
	m_uiGrowBy = growBy;
	m_pBuffer = NULL;
	m_uiCurUse = 0;
	m_uiBufferNum = 0;
	m_uiAllocNum = 0;
}

template<typename T, JaxMemManagerFun MMFun>
 JaxArray<T, MMFun>::~JaxArray()
{
	Delete(m_pBuffer, m_uiCurUse);
	m_uiBufferNum = 0;
	m_uiCurUse = 0;
	m_uiAllocNum = 0;
}

template<typename T, JaxMemManagerFun MMFun>
 JaxArray<T, MMFun>::JaxArray(const JaxArray& Array)
{
	m_uiGrowBy = Array.m_uiGrowBy;
	m_pBuffer = NULL;
	m_uiCurUse = 0;
	m_uiBufferNum = 0;
	m_uiAllocNum = 0;
	*this = Array;
}

template<typename T, JaxMemManagerFun MMFun>
 void JaxArray<T, MMFun>::SetBufferNum(size_t bufferNum)
{
	if (bufferNum)
	{
		Delete(m_pBuffer, m_uiCurUse);
		m_uiBufferNum = bufferNum;
		m_pBuffer = this->New(bufferNum);
		if (!m_pBuffer)
			return;
		m_uiCurUse = m_uiBufferNum;
		for (size_t i = 0; i < m_uiBufferNum; ++i)
		{
			JAX_NEW(m_pBuffer + i) T();
		}
	}
}

template<typename T, JaxMemManagerFun MMFun>
 void JaxArray<T, MMFun>::AddBufferNum(size_t bufferNum)
{
	if (bufferNum)
	{
		m_uiAllocNum++;
		m_uiGrowBy = m_uiAllocNum * m_uiGrowBy;

		T* pBuffer = NULL;
		pBuffer = this->New(m_uiBufferNum * bufferNum);
		if (!pBuffer)
			return;
		if (pBuffer && m_uiCurUse)
		{
			for (size_t i = 0; i < m_uiCurUse; ++i)
			{
				JAX_NEW(pBuffer + i) T(m_pBuffer[i]);
			}
		}

		Delete(m_pBuffer, m_uiCurUse);
		m_uiBufferNum = m_uiBufferNum + bufferNum;
		m_pBuffer = pBuffer;
	}
}

template<typename T, JaxMemManagerFun MMFun>
 void JaxArray<T, MMFun>::operator=(const JaxArray<T, MMFun>& Array)
{
	if (m_uiBufferNum >= Array.GetNum())
	{
		Clear();
		m_uiCurUse = Array.GetNum();
		T* pBuffer = Array.GetBuffer();
		for (size_t i = 0; i < m_uiCurUse; ++i)
		{
			JAX_NEW(m_pBuffer + i) T(pBuffer[i]);
		}
	}
	else
	{
		Delete(m_pBuffer, m_uiCurUse);
		m_uiBufferNum = Array.GetBufferNum();
		m_uiCurUse = Array.GetNum();
		m_pBuffer = this->New(m_uiBufferNum);
		if (!m_pBuffer)
			return;
		T* pBuufer = Array.GetBuffer();
		for (size_t i = 0; i < m_uiCurUse; ++i)
		{
			JAX_NEW(m_pBuffer + i) T(pBuufer[i]);
		}
	}
	return;
}

template<typename T, JaxMemManagerFun MMFun>
 size_t JaxArray<T, MMFun>::GetNum() const
{
	return m_uiCurUse;
}

template<typename T, JaxMemManagerFun MMFun>
 size_t JaxArray<T, MMFun>::GetBufferNum() const
{
	return m_uiBufferNum;
}

template<typename T, JaxMemManagerFun MMFun>
 T* JaxArray<T, MMFun>::GetBuffer() const
{
	return m_pBuffer;
}

template<typename T, JaxMemManagerFun MMFun>
 void JaxArray<T, MMFun>::SetGrowBy(size_t growBy)
{
	m_uiGrowBy = growBy;
}

template<typename T, JaxMemManagerFun MMFun>
 void JaxArray<T, MMFun>::AddElement(const T& element)
{
	if (m_uiCurUse == m_uiBufferNum)
	{
		if (!m_uiGrowBy)
		{
			return;
		}
		AddBufferNum(m_uiGrowBy);
	}
	JAX_NEW(m_pBuffer + m_uiCurUse) T(element);
	m_uiCurUse++;
}


template<typename T, JaxMemManagerFun MMFun>
 T& JaxArray<T, MMFun>::operator[](size_t i) const
{
#ifdef _DEBUG
	JAX_ASSERT(i < m_uiBufferNum);
#endif // _DEBUG
	return m_pBuffer[i];
}

template<typename T, JaxMemManagerFun MMFun>
 void JaxArray<T, MMFun>::Clear()
{
	if (m_uiCurUse == 0)
		return;
	if (ValueBase<T>::NeedsDestructor)
	{
		for (size_t i = 0; i < m_uiCurUse; ++i)
		{
			m_pBuffer[i].~T();
		}
	}
	m_uiCurUse = 0;
}

template<typename T, JaxMemManagerFun MMFun>
 size_t JaxArray<T, MMFun>::GetSize() const
{
	return size_t();
}

template<typename T, JaxMemManagerFun MMFun>
 void JaxArray<T, MMFun>::Erase(size_t i)
{
	if (i < m_uiCurUse)
	{
		Erase(i, i);
	}
}

template<typename T, JaxMemManagerFun MMFun>
 void JaxArray<T, MMFun>::Erase(size_t begin, size_t end)
{
	if (end >= m_uiCurUse)
	{
		end = m_uiCurUse - 1;
	}
	if (begin > end)
	{
		return;
	}
	size_t k;
	size_t moveNum = m_uiCurUse - 1 - end;
	size_t moveIdx;
	if (ValueBase<T>::NeedsDestructor)
	{
		for (size_t i = begin; i <= end; ++i)
		{
			m_pBuffer[i].~T();
		}
	}
	for (k = 0; k < moveNum; ++k)
	{
		moveIdx = end + k + 1;
		if (moveIdx < m_uiCurUse)
		{
			JAX_NEW(m_pBuffer + begin + k) T(m_pBuffer[moveIdx]);
			if (ValueBase<T>::NeedsDestructor)
			{
				m_pBuffer[moveIdx].~T();
			}
		}
	}
	m_uiCurUse -= ((end - begin) + 1);
}

template<typename T, JaxMemManagerFun MMFun>
 void JaxArray<T, MMFun>::Sort(size_t begin, size_t end)
{
	if (end >= m_uiCurUse)
	{
		end = m_uiCurUse - 1;
	}
	if (begin >= end)
	{
		return;
	}

	//ц╟ещ
	for (size_t i = begin; i < end; ++i) {
		for (size_t j = begin; j < end - begin - i; ++j) {
			if (m_pBuffer[j] > m_pBuffer[j + 1])
			{
				swap(m_pBuffer[i], m_pBuffer[j + 1]);
			}
		}
	}
}

template<typename T, JaxMemManagerFun MMFun>
 void JaxArray<T, MMFun>::Destory()
{
	Clear();
	Delete(m_pBuffer, m_uiCurUse);
}

template<typename T, JaxMemManagerFun MMFun>
 size_t JaxArray<T, MMFun>::FindElement(const T& element)
{
	for (size_t i = 0; i < m_uiCurUse; ++i)
	{
		if (m_pBuffer[i] == element)
		{
			return i;
		}
	}
	return m_uiCurUse;
}

template<typename T, JaxMemManagerFun MMFun>
template<typename N, JaxMemManagerFun MMFunN>
 void JaxArray<T, MMFun>::AddElement(const JaxArray<N, MMFunN>& Array, size_t begin, size_t end)
{
	if (begin > end)
	{
		return;
	}
	if (end >= Array.GetNum())
	{
		end = Array.GetNum() - 1;
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
				AddBufferNum(m_uiGrowBy);
			else
				AddBufferNum(needNum);
		}
		else
		{
			addNum = haveNum;
		}
	}
	if (addNum == 1)
	{
		AddElement(Array[begin]);
	}
	else if (addNum == 2)
	{
		AddElement(Array[begin]);
		AddElement(Array[begin + 1]);
	}
	else
	{
		N* pBuffer = Array.GetBuffer();
		for (size_t i = m_uiCurUse; i < (size_t)addNum + m_uiCurUse; ++i)
		{
			JAX_NEW(m_pBuffer + i) T(pBuffer[begin]);
			begin++;
		}
		m_uiCurUse += addNum;
	}
}

template<typename T, JaxMemManagerFun MMFun>
template<typename N>
 void JaxArray<T, MMFun>::Sort(size_t begin, size_t end, N Compare)
{
	if (end >= m_uiCurUse)
	{
		end = m_uiCurUse - 1;
	}
	if (begin >= end)
	{
		return;
	}

	for (size_t i = begin; i < end; ++i)
	{
		for (size_t j = begin; j < end - begin - i; ++j)
		{
			if (Compare(m_pBuffer[j], m_pBuffer[j + 1]) == 0)
			{
				swap(m_pBuffer[i], m_pBuffer[j + 1]);
			}
		}
	}
}