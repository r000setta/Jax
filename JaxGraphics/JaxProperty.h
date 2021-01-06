#pragma once
#include "JaxRtti.h"
#include "JaxStream.h"
#include "JaxSystem.h"
#include "JaxArray.h"
#include "JaxMap.h"
#include "JaxName.h"

namespace Jax
{
	class JaxProperty
	{
	public:
		enum
		{
			PT_VALUE,
			PT_ENUM,
			PT_DATA,
			PT_ARRAY,
			PT_MAP,
			PT_MAX
		};

		enum
		{
			F_NONE=0x00,
			F_SAVE_LOAD=0x01,
			F_CLONE=0x02,
			F_SAVE_LOAD_CLONE=0x03,
			F_COPY=0x04,
			F_SAVE_LOAD_COPY=0x05,
			F_REFLECT_NAME=0x08,
			F_NO_USE_GC=0x10,
			F_MAX
		};

		JaxProperty();
		JaxProperty(JaxRtti& owner,const JaxUsedName& name, size_t elementOffset, size_t flag);

		virtual ~JaxProperty();

		virtual size_t GetPropertyType() const = 0;

		FORCEINLINE JaxRtti* GetRtti() const
		{
			return m_pRttiOwner;
		}

		FORCEINLINE const JaxUsedName& GetName() const
		{
			return m_Name;
		}

		virtual void* GetValueAddress(void* pObj) const
		{
			return (void*)(((unsigned char*)pObj) + m_uiElementOffset);
		}

		virtual bool Archive(JaxStream& stream, void* pObj) = 0;

		virtual JaxProperty* GetInstance() = 0;
		virtual void CloneData(void* src, void* dest, JaxMap<JaxObject*, JaxObject*>& cloneMap) = 0;

		void SetOwner(JaxRtti& owner);
		size_t GetFlag() const;
		void SetFlag(size_t flag);

		virtual bool Clone(JaxProperty* p);

	protected:
		JaxRtti* m_pRttiOwner;
		JaxUsedName m_Name;
		size_t m_uiFlag;
		size_t m_uiElementOffset;
	};

	template<typename T,typename NumType>
	class JaxDataProperty :public JaxProperty
	{
	public:
		JaxDataProperty(JaxRtti& owner, const JaxUsedName& Name, size_t elementOffset, size_t dataNum, bool dynamic)
			:JaxProperty(owner, name, elementOffset, F_SAVE_LOAD_CLONE | F_NO_USE_GC)
		{
			m_uiDataNum = dataNum;
			m_bDynamicCreate = dynamic;
		}

		JaxDataProperty() {}
		
		virtual size_t GetPropertyType() const
		{
			return PT_DATA;
		}

		virtual JaxProperty* GetInstance()
		{
			return JAX_NEW JaxDataProperty<T, NumType>();
		}

		virtual void CloneData(void* src, void* dest, JaxMap<JaxObject*, JaxObject*>& cloneMap);

		virtual bool Clone(JaxProperty* p);

		virtual bool Archive(JaxStream& stream, void* pObj);

	protected:
		bool m_bDynamicCreate;
		size_t m_uiDataNum;
		size_t m_uiNumElementOffset;
	};

	template<typename T, typename NumType>
	inline void JaxDataProperty<T, NumType>::CloneData(void* src, void* dest, JaxMap<JaxObject*, JaxObject*>& cloneMap)
	{
		T* srcAddress = *(T**)GetValueAddress(src);
		if (m_uiDataNum > 0)
		{
			T** tmp = (T**)GetValueAddress(dest);
			if (m_bDynamicCreate)
			{
				*tmp = JAX_NEW T[m_uiDataNum];
				JaxMemcpy((void*)(*tmp), (void*)srcAddress, m_uiDataNum * sizeof(T));
			}
			else
			{
				JaxMemcpy((void*)(*tmp), (void*)srcAddress, m_uiDataNum * sizeof(T));
			}
		}
		else
		{
			T** tmp = (T**)GetValueAddress(dest);
			void* srcOffset = (void*)(((unsigned char*)src) + m_uiNumElementOffset);
			void* destOffset = (void*)(((unsigned char*)dest) + m_uiNumElementOffset);
			*(NumType)destOffset = *(NumType*)srcOffset;
			NumType num = *(NumType*)srcOffset;
			*tmp = JAX_NEW T[num];
			JaxMemcpy((void*)*(tmp), (void*)srcAddress, num * sizeof(T));
		}
	}

	template<typename T, typename NumType>
	inline bool JaxDataProperty<T, NumType>::Clone(JaxProperty* p)
	{
		JaxDataProperty<T, NumType>* tmp = (JaxDataProperty<T, NumType>*)p;
		if (!JaxProperty::Clone(tmp))
		{
			return false;
		}
		m_bDynamicCreate = tmp->m_bDynamicCreate;
		m_uiDataNum = tmp->m_uiDataNum;
		m_uiNumElementOffset = tmp->m_uiNumElementOffset;
		return true;
	}

	template<typename T, typename NumType>
	inline bool JaxDataProperty<T, NumType>::Archive(JaxStream& stream, void* pObj)
	{
		size_t streamFlag = stream.GetStreamFlag();
		if (streamFlag == JaxStream::AT_SAVE)
		{
			T* valueAddress = *(T**)GetValueAddress(pObj);
			if (m_uiDataNum > 0)
			{
				stream.Write(valueAddress, m_uiDataNum * sizeof(T));
			}
			else
			{
				void* numOffset = (void*)(((unsigned char*)pObj) + m_uiElementOffset);
				NumType num = *(NumType*)numOffset;
				stream.Write(numOffset, sizeof(NumType));
				stream.Write(valueAddress, num * sizeof(T));
			}
		}
		else if (streamFlag == JaxStream::AT_LOAD)
		{
			T** tmp = (T**)GetValueAddress(obj);
			if (m_uiDataNum > 0)
			{
				if (m_bDynamicCreate)
				{
					*tmp = JAX_NEW T[m_uiDataNum];
					stream.Read((void*)(*tmp), m_uiDataNum * sizeof(T));
				}
				else
				{
					stream.Read((void*)*(tmp), m_uiDataNum * sizeof(T));
				}
			}
			else
			{
				void* numOffset = (void*)(((unsigned char*)obj) + m_uiElementOffset);
				stream.Read(numOffset, sizeof(NumType));
				NumType num = *(NumType*)numOffset;
				*tmp = JAX_NEW T[num];
				stream.Read((void*)(*tmp), num * sizeof(T));
			}
		}
		return true;
	}

}