#pragma once
#include "JaxRtti.h"
#include "JaxStream.h"
#include "JaxSystem.h"
#include "JaxArray.h"
#include "JaxMap.h"
#include "JaxName.h"

namespace Jax
{

#define REGISTER_PROPERTY(varName,reflectName,flag) \
{ \
activeProperty=PropertyCreator::GetAutoPropertyCreator(dummy->varName).CreateProperty( \
	_T(#reflectName),*rtti,(size_t)((char*)&(dummy->varName)-(char*)dummy),flag); \
rtti->AddProperty(activeProperty);\
}

#define BEGIN_ADD_PROPERTY(classname,baseclassname) \
bool classname::TerminalProperty() \
{ \
sm_Type.ClearProperty(); \
return true; \
} \
bool classname::InitialProperty(JaxRtti* rtti) \
{ \
classname* dummy=NULL; \
JaxProperty* activeProperty=NULL; \
JaxRtti* rttiTmp=rtti; \
if(!rtti)\
{ \
rtti=&sm_Type; \
} \
baseclassname::InitialProperty(rtti);

#define END_ADD_PROPERTY \
return true; \
}

#define NO_PROPERTY(classname) \
bool classname::InitialProperty(JaxRtti* ) \
{ \
return true; \
} \
bool classname::TerminalProperty() \
{ \
sm_Type.ClearProperty(); \
return true; \
}

#define BEGIN_ADD_PROPERTY_ROOT(classname) \
bool classname::TerminalProperty() \
{ \
sm_Type.ClearProperty();\
return true; \
} \
bool classname::InitialProperty(JaxRtti* rtti) \
{ \
classname* dummy=NULL; \
JaxProperty* activeProperty=NULL; \
if(!rtti) \
{ \
rtti=&sm_Type; \
}

	class JaxFunction;
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

		JaxProperty()
		{
			m_pRttiOwner = NULL;
			m_pFunctionOwner = NULL;
			m_uiFlag = 0;
			m_uiElementOffset = 0;
		}

		JaxProperty(JaxRtti& owner, const JaxUsedName& name, size_t elementOffset, size_t flag)
			:m_pRttiOwner(&owner)
		{
			m_Name = name;
			m_uiElementOffset = elementOffset;
			m_uiFlag = flag;
			m_pFunctionOwner = NULL;
		}

		JaxProperty(JaxFunction& owner, const JaxUsedName& name, size_t elementOffset, size_t flag)
			:m_pFunctionOwner(&owner)
		{
			m_Name = name;
			m_uiElementOffset = elementOffset;
			m_uiFlag = flag;
			m_pRttiOwner = NULL;
		}

		virtual ~JaxProperty()
		{

		}

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
		virtual bool Clone(JaxProperty* p)
		{
			if ((p->GetRtti() == GetRtti()))
			{
				m_Name = p->m_Name;
				m_uiFlag = p->m_uiFlag;
				m_uiElementOffset = p->m_uiElementOffset;
				return true;
			}
			return false;
		}
		virtual void CopyData(void* src, void* dest) = 0;

		void SetOwner(JaxRtti& owner);
		size_t GetFlag() const;
		void SetFlag(size_t flag);


	protected:
		JaxRtti* m_pRttiOwner;
		JaxFunction* m_pFunctionOwner;
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

	template<typename T>
	class JaxValueBaseProperty :public JaxProperty
	{
	public:
		JaxValueBaseProperty()
		{

		}

		JaxValueBaseProperty(JaxRtti& owner, const JaxUsedName& name, size_t offset, size_t flag, bool range = false, T high = T(), T low = T(), T fStep = T())
			:JaxProperty(owner, name, offset, flag)
		{
			m_LowValue = low;
			m_HighValue = high;
			m_fStep = fStep;
			m_bRange = range;
		}

		JaxValueBaseProperty(JaxFunction& owner, const JaxUsedName& name, size_t offset, size_t flag, bool range = false, T high = T(), T low = T(), T fStep = T())
			:JaxProperty(owner, name, offset, flag)
		{
			m_LowValue = low;
			m_HighValue = high;
			m_fStep = fStep;
			m_bRange = range;
		}

		virtual ~JaxValueBaseProperty() {}

		virtual bool Clone(JaxProperty* p)
		{
			JaxValueBaseProperty<T>* tmp = (JaxValueBaseProperty<T>*)p;
			if (!JaxProperty::Clone(tmp))
				return false;
			m_LowValue = tmp->m_LowValue;
			m_HighValue = tmp->m_HighValue;
			return true;
		}

	protected:
		T m_LowValue;
		T m_HighValue;
		T m_fStep;
		bool m_bRange;
	};

	template<typename T>
	class JaxValueProperty :public JaxValueBaseProperty<T>
	{
	public:
		JaxValueProperty() {}
		JaxValueProperty(JaxRtti& owner, const JaxUsedName& name, size_t offset, size_t flag, bool range = false, T high = T(), T low = T(), T fStep = T())
			:JaxValueBaseProperty(owner, name, offset, flag, range, high, low, fStep)
		{

		}

		JaxValueProperty(JaxFunction& owner, const JaxUsedName& name, size_t offset, size_t flag, bool range = false, T high = T(), T low = T(), T fStep = T())
			:JaxValueBaseProperty(owner, name, offset, flag, range, high, low, fStep)
		{

		}

		virtual ~JaxValueProperty() {}
		virtual size_t GetPropertyType() const
		{
			return PT_VALUE;
		}

		virtual bool SetValue(void* obj, T& src)
		{
			if (src > m_HighValue || src < m_LowValue) return false;
			*(T*)(((unsigned char*)obj) + m_uiElementOffset) = src;
			return true;
		}

		virtual bool GetValue(void* obj, T& dest) const
		{
			dest = *(T*)(((unsigned char*)obj) + m_uiElementOffset);
			return true;
		}

		virtual bool GetValue(const void* obj, T& dest) const
		{
			dest = *(const T*)(((const char*)obj) + m_uiElementOffset);
			return true;
		}

		virtual T& Value(void* obj) const
		{
			return *(T*)(((const char*)obj) + m_uiElementOffset);
		}

		virtual bool Archive(JaxStream& stream, void* obj)
		{
			stream.Archive(Value(obj));
			return true;
		}

		virtual void CloneData(void* src, void* dest, JaxMap<JaxObject*, JaxObject*>& cloneMap)
		{
			Copy(Value(dest), Value(src), cloneMap);
		}

		virtual void CopyData(void* src, void* dest)
		{
			Value(dest) = Value(src);
		}

		virtual JaxProperty* GetInstance()
		{
			return JAX_NEW JaxValueProperty<T>();
		}
	};

	template<typename T,typename NumType>
	struct DataPropertyCreator
	{
		JaxProperty* CreateProperty(const JaxUsedName& name, JaxRtti& owner, size_t offset, size_t numOffset);
		JaxProperty* CreateFunctionProperty(const JaxUsedName& name, JaxRtti& owner, size_t offset, size_t numOffset);
		JaxProperty* CreateProperty(const JaxUsedName& name, JaxRtti& owner, size_t offset, size_t dataNum, bool dynamicCreate);
	};

	template<typename T>
	struct AutoPropertyCreator
	{
		JaxProperty* CreateProperty(const JaxUsedName& name, JaxRtti& owner, size_t offset, size_t flag);
		JaxProperty* CreateFunctionProperty(const JaxUsedName& name, JaxFunction& owner, size_t offset, size_t flag);
		JaxProperty* CreateProperty(const JaxUsedName& name, JaxRtti& owner, size_t offset, T high, T low, JAXREAL fstep, size_t flag);
	};

	class PropertyCreator
	{
	public:
		template<typename ValueType>
		static AutoPropertyCreator<ValueType>& GetAutoPropertyCreator(ValueType& valueType)
		{
			static AutoPropertyCreator<ValueType> apc;
			return apc;
		};
	};

	using FunctionTemplatePtr = void(*)(JaxObject* p, JaxFunction* pFun, void* para, void* ret);
	class JaxFunction
	{
	public:
		enum
		{
			F_DEFAULT=0x00,
			F_CLIENT=0x01,
			F_MAX
		};

		JaxFunction() :m_pReturnProperty(NULL), objectFun(NULL) {}
		~JaxFunction();

		JaxFunction(JaxRtti& owner, const JaxUsedName& name, size_t flag) :m_pOwner(&owner)
		{
			m_Name = name;
			m_uiFlag = flag;
			m_pReturnProperty = NULL;
			objectFun = NULL;
		}

		FORCEINLINE JaxRtti* GetRtti() const
		{
			return m_pOwner;
		}

		FORCEINLINE const JaxUsedName& GetName() const
		{
			return m_Name;
		}

		virtual bool Clone(JaxFunction* f);

		virtual JaxFunction* GetInstance()
		{
			return JAX_NEW JaxFunction();
		}

		void SetOwner(JaxRtti& owner)
		{
			m_pOwner = &owner;
		}

		size_t GetFlag() const
		{
			return m_uiFlag;
		}

		void AddProperty(JaxProperty* p)
		{
			m_PropertyArray.AddElement(p);
		}

		JaxProperty* GetProperty(size_t i)
		{
			return m_PropertyArray[i];
		}

		void SetReturnType(JaxProperty* p)
		{
			m_pReturnProperty = p;
		}

		bool IsReturnVoid()
		{
			return !m_pReturnProperty;
		}

		void SetTotalSize(size_t totalSize)
		{
			m_uiTotalSize = totalSize;
		}

		bool IsSame(JaxFunction* p)
		{
			if (m_pOwner != p->m_pOwner
				|| m_Name != p->m_Name
				|| m_uiTotalSize != p->m_uiTotalSize
				|| m_PropertyArray.GetNum() != p->m_PropertyArray.GetNum())
			{
				return false;
			}
			return true;
		}

		FunctionTemplatePtr objectFun;
	protected:
		JaxRtti* m_pOwner;
		JaxUsedName m_Name;
		size_t m_uiFlag;
		JaxArray<JaxProperty*> m_PropertyArray;
		JaxProperty* m_pReturnProperty;
		size_t m_uiTotalSize;
	};

	template<typename T, typename NumType>
	inline JaxProperty* DataPropertyCreator<T, NumType>::CreateProperty(const JaxUsedName& name, JaxRtti& owner, size_t offset, size_t numOffset)
	{
		return JAX_NEW JaxDataProperty<T, NumType>(owner, name, offset, numOffset);
	}

	template<typename T, typename NumType>
	inline JaxProperty* DataPropertyCreator<T, NumType>::CreateProperty(const JaxUsedName& name, JaxRtti& owner, size_t offset, size_t dataNum, bool dynamicCreate)
	{
		return JAX_NEW JaxDataProperty<T, NumType>(owner, name, offset, dataNum, dynamicCreate);
	}

	template<typename T, typename NumType>
	inline JaxProperty* DataPropertyCreator<T, NumType>::CreateFunctionProperty(const JaxUsedName& name, JaxRtti& owner, size_t offset, size_t numOffset)
	{
		return JAX_NEW JaxDataProperty<T, NumType>(owner, name, offset, numOffset);
	}

	template<typename T>
	inline JaxProperty* AutoPropertyCreator<T>::CreateProperty(const JaxUsedName& name, JaxRtti& owner, size_t offset, size_t flag)
	{
		if (!(TIsJaxPointerType<T>::Value || TIsJaxSmartPointerType<T>::Value || TIsCustomType<T>::Value || TIsJaxType<T>::Value))
		{
			flag |= JaxProperty::F_NO_USE_GC;
		}
		return JAX_NEW JaxValueProperty<T>(owner, name, offset, flag);
	}

	template<typename T>
	inline JaxProperty* AutoPropertyCreator<T>::CreateFunctionProperty(const JaxUsedName& name, JaxFunction& owner, size_t offset, size_t flag)
	{
		return JAX_NEW JaxValueProperty<T>(owner, name, offset, flag);
	}

	template<typename T>
	inline JaxProperty* AutoPropertyCreator<T>::CreateProperty(const JaxUsedName& name, JaxRtti& owner, size_t offset, T high, T low, JAXREAL fstep, size_t flag)
	{
		if (!(TIsJaxPointerType<T>::Value || TIsJaxSmartPointerType<T>::Value || TIsCustomType<T>::Value || TIsJaxType<T>::Value))
		{
			flag |= JaxProperty::F_NO_USE_GC;
		}
		return JAX_NEW JaxValueProperty<T>(owner, name, offset, flag, true, high, low, fstep);
	}
}