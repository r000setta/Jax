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
		JaxStream();
		~JaxStream();

		bool Read(void* buffer, size_t size);
		bool Write(const void* buffer, size_t size);

		bool NewSave(const TCHAR* const fileName);
		bool NewLoad(const TCHAR* const fileName);
		
	private:
		unsigned char* m_pcCurBufPtr;
		unsigned char* m_pcBuffer;
		size_t m_uiBufferSize;
		JaxArray<JaxObject*> m_pObjectArray;
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