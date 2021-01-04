#pragma once
#include "JaxRtti.h"
#include "JaxPointer.h"
#include "JaxArray.h"
#include "JaxMap.h"
#include "JaxFile.h"
#include "JaxObject.h"

namespace Jax
{
	class JAXGRAPHIC_API JaxStream
	{
	public:
		enum
		{
			AT_SAVE,
			AT_LOAD,
		};
		JaxStream();
		~JaxStream();
		void f() {}

		bool Read(void* buffer, size_t size);
		bool Write(const void* buffer, size_t size);
		bool WriteString(const JaxString& string);
		bool ReadString(JaxString& string);

		bool NewLoadFromBuffer(unsigned char* buffer, unsigned int size);

		bool NewSave(const TCHAR* const fileName);
		bool NewLoad(const TCHAR* const fileName);

		size_t GetStreamFlag() const
		{
			return m_uiStreamFlag;
		}

		void SetStreamFlag(size_t streamFlag)
		{
			m_uiStreamFlag = streamFlag;
		}

		void AddBufferSize(size_t size)
		{
			m_uiArchivePropertySize += size;
		}


	protected:
		size_t m_uiStreamFlag;
		size_t m_uiArchivePropertySize;
	private:
		unsigned char* m_pcCurBufPtr;
		unsigned char* m_pcBuffer;
		static size_t sm_uiCurVersion;
		size_t m_uiBufferSize;
		size_t m_uiVersion;
		JaxArray<JaxObject*> m_pObjectArray;
		JaxMap<JaxObject*, JaxObject*> m_pLoadMap;
	};

	struct ObjectPropertyTable
	{
		ObjectPropertyTable() :m_uiOffset(0),
			m_uiSize(0), m_uiNameID(0) {}

		JaxString m_PropertyName;
		size_t m_uiOffset;
		size_t m_uiSize;
		size_t m_uiNameID;
	};

	struct ObjectTable
	{
		ObjectTable() :m_pAddr(NULL), m_uiOffset(0), m_uiObjectPropertyNum(0) {}

		JaxObject* m_pAddr;
		JaxString m_RttiName;
		size_t m_uiOffset;
		size_t m_uiObjectPropertySize;
		size_t m_uiObjectPropertyNum;
		size_t m_uiObjectPropertyTabeSize;
		JaxArray<ObjectPropertyTable> m_ObjectPropertyTable;
	};
}