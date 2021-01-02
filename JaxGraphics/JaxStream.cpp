#include "JaxStream.h"

namespace Jax
{
	JaxStream::JaxStream() :m_pcBuffer(NULL), m_pcCurBufPtr(NULL) 
	{
		m_pObjectArray.Clear();
	}

	JaxStream::~JaxStream()
	{
		m_pObjectArray.Clear();
		m_pcCurBufPtr = NULL;
	}

	bool JaxStream::Read(void* buffer, size_t size)
	{
		if (!buffer || !m_pcBuffer)
			return false;
		if (size_t(m_pcCurBufPtr + size - m_pcBuffer) > m_uiBufferSize)
			return false;
		JaxMemcpy(buffer, m_pcCurBufPtr, size);
		m_pcCurBufPtr += size;
		return true;
	}

	bool JaxStream::Write(const void* buffer, size_t size)
	{
		if (!buffer || !m_pcBuffer)
			return false;
		if (size_t(m_pcCurBufPtr + size - m_pcBuffer) > m_uiBufferSize)
			return false;
		JaxMemcpy(m_pcCurBufPtr, buffer, size);
		m_pcCurBufPtr += size;
		return true;
	}

	bool JaxStream::NewSave(const TCHAR* const fileName)
	{
		size_t objectNum = m_pObjectArray.GetNum();
		m_uiBufferSize = 0;

		m_uiBufferSize += sizeof(size_t); //version
		m_uiBufferSize += sizeof(size_t); //Object nums

		JaxArray<ObjectTable> objectTable;
		objectTable.SetBufferNum(objectNum);

		for (size_t i = 0; i < m_pObjectArray.GetNum(); ++i)
		{
			m_uiBufferSize += sizeof(JaxObject*);
			objectTable[i].m_pAddr = m_pObjectArray[i];

			m_uiBufferSize += m_pObjectArray[i]->GetType().GetName().GetLength();
			objectTable[i].m_RttiName = m_pObjectArray[i]->GetType().GetName();

			//object property size
			m_uiBufferSize += sizeof(size_t);
			//object property num
			m_uiBufferSize += sizeof(size_t);
		}

		size_t objectContentAddr = m_uiBufferSize;
		
		for (size_t i = 0; i < m_pObjectArray.GetNum(); ++i)
		{
			objectTable[i].m_uiOffset = m_uiBufferSize;

			JaxRtti& rtti = m_pObjectArray[i]->GetType();
			objectTable[i].m_ObjectPropertyTable.SetBufferNum(rtti.GetPropertyNum());

			objectTable[i].m_uiObjectPropertyNum = 0;
			for (size_t j = 0; j < rtti.GetPropertyNum(); ++j)
			{
				JaxProperty* property = rtti.GetProperty(i);
				
				if (property->GetFlag() & JaxProperty::F_SAVE_LOAD)
				{
					m_uiBufferSize += sizeof(size_t);
					objectTable[i].m_ObjectPropertyTable[j].m_PropertyName = property->GetName();
					objectTable[i].m_ObjectPropertyTable[j].m_uiNameID = property->GetName().GetLength();
					
					m_uiBufferSize += sizeof(size_t);
					objectTable[i].m_uiObjectPropertyNum++;
				}
			}
			objectTable[i].m_uiObjectPropertyTabeSize = m_uiBufferSize - objectTable[i].m_uiOffset;
		}
	}


}

