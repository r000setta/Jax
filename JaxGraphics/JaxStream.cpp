#include "JaxStream.h"

namespace Jax
{
	size_t JaxStream::sm_uiCurVersion = 0;
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

	bool JaxStream::WriteString(const JaxString& string)
	{
		size_t bufferLen = string.GetLength() * sizeof(TCHAR);
		if (!Write(&bufferLen, sizeof(size_t)))
		{
			return false;
		}
		if (!Write(string.GetBuffer(), bufferLen))
		{
			return false;
		}
		return true;
	}

	bool JaxStream::ReadString(JaxString& string)
	{
		size_t bufferSize = 0;
		size_t strLen = 0;
		if (!Read(&bufferSize, sizeof(size_t)))
		{
			return false;
		}
		if (!bufferSize)
		{
			return false;
		}

		TCHAR* pCh = JAX_NEW TCHAR[bufferSize];
		if (!Read(pCh, bufferSize))
		{
			JAXMAC_DELETEA(pCh);
			return false;
		}
		
		strLen = bufferSize;
		string.SetTCHARBufferNum(strLen);
		JaxMemcpy(string.GetBuffer(), pCh, bufferSize);

		JAXMAC_DELETEA(pCh);
		return true;
	}

	bool JaxStream::NewLoadFromBuffer(unsigned char* buffer, unsigned int size)
	{
		if (!buffer || !size)
		{
			return false;
		}

		m_pObjectArray.Clear();
		m_pLoadMap.Clear();
		m_pcCurBufPtr = NULL;
		m_uiBufferSize = 0;

		m_uiBufferSize = size;
		m_pcBuffer = buffer;

		m_pcCurBufPtr = m_pcBuffer;

		JaxArray<ObjectTable> objectTable;
		Read(&m_uiVersion, sizeof(size_t));

		size_t objectNum = 0;
		Read(&objectNum, sizeof(size_t));

		objectTable.SetBufferNum(objectNum);
		for (size_t i = 0; i < objectNum; ++i)
		{
			JaxObject* obj = NULL;
			if (!Read(&objectTable[i].m_pAddr, sizeof(JaxObject*)))
			{
				return false;
			}

			if (!ReadString(objectTable[i].m_RttiName))
			{
				return false;
			}
			if (!Read(&objectTable[i].m_uiObjectPropertySize, sizeof(size_t)))
			{
				return false;
			}
			if (!Read(&objectTable[i].m_uiObjectPropertyNum, sizeof(size_t)))
			{
				return false;
			}
		}

		JaxArray<size_t> tableID;
		for (size_t i = 0; i < objectNum; ++i)
		{

		}
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

			for (size_t j = 0; j < rtti.GetPropertyNum(); ++j)
			{
				JaxProperty* property = rtti.GetProperty(i);
				if (property->GetFlag() & JaxProperty::F_SAVE_LOAD)
				{
					objectTable[i].m_ObjectPropertyTable[j].m_uiOffset = m_uiBufferSize;
					m_uiArchivePropertySize = 0;
					property->Archive(*this, m_pObjectArray[i]);
					objectTable[i].m_ObjectPropertyTable[j].m_uiSize = m_uiArchivePropertySize;
					m_uiBufferSize += m_uiArchivePropertySize;
				}
			}
			objectTable[i].m_uiObjectPropertySize = m_uiBufferSize - objectTable[i].m_uiObjectPropertyTabeSize - objectTable[i].m_uiOffset;
		}

		JAXMAC_DELETE(m_pcBuffer);
		m_pcBuffer = JAX_NEW unsigned char[m_uiBufferSize];
		if (!m_pcBuffer)
		{
			return false;
		}
		m_pcCurBufPtr = m_pcBuffer;
		m_uiVersion = sm_uiCurVersion;
		Write(&m_uiVersion, sizeof(size_t));
		Write(&objectNum, sizeof(size_t));

		for (size_t i = 0; i < m_pObjectArray.GetNum(); ++i)
		{
			if (!Write(&objectTable[i].m_pAddr, sizeof(JaxObject*)))
			{
				JAXMAC_DELETEA(m_pcBuffer);
				return false;
			}

			if (!WriteString(objectTable[i].m_RttiName))
			{
				JAXMAC_DELETEA(m_pcBuffer);
				return false;
			}

			Write(&objectTable[i].m_uiObjectPropertySize, sizeof(size_t));
			Write(&objectTable[i].m_uiObjectPropertyNum, sizeof(size_t));
		}

		m_uiStreamFlag = AT_SAVE;
		for (size_t i = 0; i < m_pObjectArray.GetNum(); ++i)
		{
			JaxRtti& rtti = m_pObjectArray[i]->GetType();
			for (size_t j = 0; j < rtti.GetPropertyNum(); ++j)
			{
				JaxProperty* property = rtti.GetProperty(j);
				if (property->GetFlag() & JaxProperty::F_SAVE_LOAD)
				{
					Write(&objectTable[i].m_ObjectPropertyTable[j].m_uiNameID, sizeof(size_t));
					Write(&objectTable[i].m_ObjectPropertyTable[j].m_uiOffset, sizeof(size_t));
				}
			}
			for (size_t j = 0; j < rtti.GetPropertyNum(); ++j)
			{
				JaxProperty* property = rtti.GetProperty(j);
				if (property->GetFlag() & JaxProperty::F_SAVE_LOAD)
				{
					property->Archive(*this, m_pObjectArray[i]);
				}
			}
		}

		JaxFile* file = JAX_NEW JaxFile();
		if (!file)
		{
			JAXMAC_DELETEA(m_pcBuffer);
			return false;
		}

		if (!file->Open(fileName, JaxFile::OM_RB))
		{
			JAXMAC_DELETE(file);
			JAXMAC_DELETEA(m_pcBuffer);
			return false;
		}

		if (!file->Write(m_pcBuffer, m_uiBufferSize, 1))
		{
			JAXMAC_DELETE(file);
			JAXMAC_DELETEA(m_pcBuffer);
			return false;
		}

		if (!file->Write(m_pcBuffer, m_uiBufferSize, 1))
		{
			JAXMAC_DELETE(file);
			JAXMAC_DELETEA(m_pcBuffer);
			return false;
		}

		JAXMAC_DELETE(file);
		JAXMAC_DELETEA(m_pcBuffer);
		return true;
	}

	bool JaxStream::NewLoad(const TCHAR* const fileName)
	{
		JaxFile* file = JAX_NEW JaxFile();
		if (!file)
		{
			return false;
		}
		if (!file->Open(fileName, JaxFile::OM_RB))
		{
			JAXMAC_DELETE(file);
			return false;
		}

		size_t bufferSize = file->GetFileSize();
		unsigned char* buffer = JAX_NEW unsigned char[bufferSize];
		if (!buffer)
		{
			JAXMAC_DELETE(file);
			return false;
		}

		if (!file->Read(buffer, bufferSize, 1))
		{
			JAXMAC_DELETE(file);
			return false;
		}

		JAX_DELETE(file);
		

	}


}

