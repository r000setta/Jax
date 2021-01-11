#pragma once
#include "JaxRtti.h"
#include "JaxPointer.h"
#include "JaxArray.h"
#include "JaxMap.h"
#include "JaxFile.h"
#include "JaxObject.h"
#include "JaxType.h"
#include "JaxCustomArchiveObject.h"

namespace Jax
{
	DECLARE_PTR(JaxObject);

	template<typename T>
	void Copy(T& dest, T& src, JaxMap<JaxObject*, JaxObject*>& cloneMap);

	template<typename T,JaxMemManagerFun MMFun>
	void Copy(JaxArray<T, MMFun>& dest, JaxArray<T, MMFun>& src, JaxMap<JaxObject*, JaxObject*>& cloneMap);

	template<typename KEY,typename VALUE,JaxMemManagerFun MMFun>
	void Copy(JaxMap<KEY, VALUE, MMFun>& dest, JaxMap<KEY, VALUE, MMFun>& src, JaxMap<JaxObject*, JaxObject*>& cloneMap);

	class JAXGRAPHIC_API JaxStream
	{
	public:
		enum
		{
			AT_SAVE,
			AT_LOAD,
			AT_LINK,
			AT_REGISTER,
			AT_SIZE,
			AT_POSTLOAD,
			AT_OBJECT_COLLECT_GC,
			AT_CLEAR_OBJECT_PROPERTY_GC,
			AT_LOAD_OBJECT_COLLECT_GC,
		};

		template<typename T>
		void Archive(T& obj)
		{
			if (m_uiStreamFlag == AT_LOAD)
			{
				if (TIsJaxResourceProxyPointType<T>::Value)
				{

				}
				else if (TIsJaxPointerType<T>::Value)
				{
					JaxObject* tmp = *(JaxObject**)(void*)&obj;
					ReadObjectPtr(tmp);
				}
				else if (TIsJaxType<T>::Value)
				{
					JaxObject* key = (JaxObject*)&obj;
					JaxObject* value = NULL;
					ReadObjectPtr(value);
					m_pJaxTypeLoadMap.AddElement(key, value);
				}
				else if (TIsJaxSmartPointerType<T>::Value)
				{
					JaxObjectPtr& tmp = *(JaxObjectPtr*)(void*)&obj;
					ReadObjectPtr(tmp);
				}
				else if (TIsJaxStringType<T>::Value)
				{
					JaxString& tmp = *(JaxString*)(void*)&obj;
					ReadString(tmp);
				}
				else if (TIsCustomType<T>::Value)
				{
					JaxCustomArchiveObject* tmp = (JaxCustomArchiveObject*)(void*)&obj;
					if (tmp)
					{
						tmp->Archive(*this);
					}
				}
				else
				{
					Read((void*)&obj, sizeof(T));
				}
			}
		}

		JaxStream();
		~JaxStream();

		bool Read(void* buffer, size_t size);
		bool Write(const void* buffer, size_t size);
		bool WriteString(const JaxString& string);
		bool ReadString(JaxString& string);

		bool NewLoadFromBuffer(unsigned char* buffer, unsigned int size);

		bool NewSave(const TCHAR* const fileName);
		bool NewLoad(const TCHAR* const fileName);

		bool ArchiveAll(JaxObject* object);

		static int GetStrDistUse(const JaxString& str);
		static int GetStrDistUse(const TCHAR* pCh);

		bool RegisterObject(JaxObject* object);

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

		template<typename T>
		bool ReadObjectPtr(T* &object);

		template<typename T>
		bool ReadObjectPtr(JaxPointer<T>& pointer);

		const JaxObject* GetObjectByRtti(const JaxRtti& rtti);

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
		JaxMap<JaxObject*, JaxObject*> m_pJaxTypeLoadMap;
	};
	template<typename T>
	inline bool JaxStream::ReadObjectPtr(T* &object)
	{
		if (!Read(&object, sizeof(T*)))
			return false;
		return true;
	}

	template<typename T>
	inline bool JaxStream::ReadObjectPtr(JaxPointer<T>& pointer)
	{
		T* p = NULL;
		if (!Read(&p, sizeof(T*)))
			return false;
		pointer.SetObject(p);
		return true;
	}

	template<typename T>
	void Copy(T& dest, T& src, JaxMap<JaxObject*, JaxObject*>& cloneMap)
	{
		if (TIsJaxResourceType<T>::Value)
		{
			dest = src;
		}
		else if (TIsJaxPointerType<T>::Value)
		{
			JaxObject*& tmpSrc = *(JaxObject**)(void*)&src;
			JaxObject*& tmpDest = *(JaxObject**)(void*)&dest;
			tmpDest = JaxObject::_CloneCreateObject(tmpSrc, cloneMap);
		}
		else if (TIsJaxType<T>::Value)
		{
			JaxObject* tmpSrc = (JaxObject*)&src;
			JaxObject* tmpDest = (JaxObject*)&dest;
			JaxObject::_CloneObject(tmpSrc, tmpDest, cloneMap);
		}
		else if (TIsJaxSmartPointerType<T>::Value)
		{
			JaxObjectPtr& tmpSrc = *(JaxObjectPtr*)(void*)&src;
			JaxObjectPtr& tmpDest = *(JaxObjectPtr*)(void*)&dest;
			tmpDest = JaxObject::_CloneCreateObject(tmpSrc, cloneMap);
		}
		else if (TIsCustomType<T>::Value)
		{
			JaxCustomArchiveObject*& tmpSrc = *(JaxCustomArchiveObject**)(void*)&src;
			JaxCustomArchiveObject*& tmpDest = *(JaxCustomArchiveObject**)(void*)&dest;
			tmpDest->CopyFrom(tmpSrc, cloneMap);
		}
		else
		{
			dest = src;
		}
	}

	template<typename T, JaxMemManagerFun MMFun>
	void Copy(JaxArray<T, MMFun>& dest, JaxArray<T, MMFun>& src, JaxMap<JaxObject*, JaxObject*>& cloneMap)
	{
		dest.Clear();
		dest.SetBufferNum(src.GetNum());
		for (size_t i = 0; i < src.GetNum(); ++i)
		{
			Copy(dest[i], src[i], cloneMap);
		}
	}

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	void Copy(JaxMap<KEY, VALUE, MMFun>& dest, JaxMap<KEY, VALUE, MMFun>& src, JaxMap<JaxObject*, JaxObject*>& cloneMap)
	{
		dest.Clear();
		dest.SetBufferNum(src.GetNum());
		for (size_t i = 0; i < src.GetNum(); ++i)
		{
			MapElement<KEY, VALUE>& eleSrc = src[i];
			MapElement<KEY, VALUE>& eleDest = dest[i];
			Copy(eleDest.key, eleDest.key, cloneMap);
			Copy(eleDest.value, eleDest.value, cloneMap);
		}
	}
}