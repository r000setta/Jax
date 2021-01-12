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

#define REGISTER_PROPERTY_RANGE(varName,reflectName,high,low,step,flag) \
{ \
activeProperty=PropertyCreator::GetAutoPropertyCreator(dummy->varName).CreateProperty( \
_T(#reflectName),*rtti,(size_t)((char*)&(dummy->varName)-(char*)dummy),high,low,step,flag); \
rtti->AddProperty(activeProperty); \
}

#define REGISTER_PROPERTY_DATA(varName,varNumName,reflectName) \
{ \
activeProperty=PropertyCreator::GetAutoPropertyCreator(dummy->varName,dummy->varNumName).CreateProperty( \
_T(#reflectName),*rtti,(size_t)((char*)&(dummy->varName)-(char*)dummy),(size_t)((char*)&(dummy->varNumName)-(char*)dummy)); \
rtti->AddProperty(activeProperty); \
}

#define REGISTER_PROPERTY_FIXED_DATA(varName,Num,reflectName,isDynamicCreate) \
{ \
size_t numType=0; \
activeProperty=PropertyCreator::GetAutoPropertyCreator(dummy->varName,numType).CreateProperty( \
_T(#reflectName),*rtti,(size_t)((char*)&(dummy->varName)-(char*)dummy),Num,isDynamicCreate); \
rtti->AddProperty(activeProperty); \
}

#define REGISTER_ENUM_PROPERTY(varName,enumName,reflectName,flag) \
{ \
activeProperty=PropertyCreator::CreateEnumProperty( \
dummy->varName,_T(#reflectName),_T(#enumName),*rtti,(size_t)((char*)&(dummy->varName)-(char*)dummy),flag); \
rtti->AddProperty(activeProperty); \
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

	template<typename T>
	class JaxEnumProperty :public JaxProperty
	{
	public:
		JaxEnumProperty()
		{
			JAX_ASSERT(sizeof(T) == 4);
		}

		JaxEnumProperty(JaxRtti& owner, const JaxUsedName& name, const JaxUsedName& enumName, size_t offset, size_t flag)
			:JaxProperty(owner,name,offset,flag)
		{
			JAX_ASSERT(sizeof(T) == 4);
			m_EnumName = enumName;
		}

		JaxEnumProperty(JaxFunction& owner, const JaxUsedName& name, const JaxUsedName& enumName, size_t offset, size_t flag)
			:JaxProperty(owner, name, offset, flag)
		{
			JAX_ASSERT(sizeof(T) == 4);
			m_EnumName = enumName;
		}

		virtual ~JaxEnumProperty()
		{

		}

		virtual bool Clone(JaxProperty* p)
		{
			JaxEnumProperty* tmp = (JaxEnumProperty*)p;
			if (!JaxProperty::Clone(tmp))
				return false;
			m_EnumName = tmp->m_EnumName;
			return true;
		}

		virtual bool SetValue(void* obj, size_t& src) const
		{
			*(size_t)(((unsigned char*)obj) + m_uiElementOffset) = src;
			return true;
		}

		virtual bool GetValue(void* obj, size_t& dest) const
		{
			dest = *(size_t*)(((unsigned char*)obj) + m_uiElementOffset);
			return true;
		}

		virtual bool GetValue(const void* obj, size_t& dest) const
		{
			dest = *(const size_t*)(((const char*)obj) + m_uiElementOffset);
			return true;
		}

		virtual size_t& Value(void* obj) const
		{
			return *(size_t*)(((const char*)obj) + m_uiElementOffset);
		}

		virtual bool Archive(JaxStream& stream, void* obj)
		{
			stream.Archive(Value(obj));
			return true;
		}

		virtual void CloneData(void* src, void* dest, JaxMap<JaxObject*, JaxObject*> cloneMap)
		{
			Value(dest) = Value(src);
		}

		virtual void CopyData(void* src, void* dest)
		{
			Value(dest) = Value(src);
		}

		virtual JaxProperty* GetInstance()
		{
			return JAX_NEW JaxEnumProperty();
		}

		JaxUsedName& GetEnumName()
		{
			return m_EnumName;
		}

		virtual size_t GetPropertyType() const
		{
			return PT_ENUM;
		}

	protected:
		JaxUsedName m_EnumName;
	};

	template<typename T,typename NumType>
	class JaxDataProperty :public JaxProperty
	{
	public:
		JaxDataProperty(JaxRtti& owner, const JaxUsedName& name, size_t elementOffset, size_t dataNum, bool dynamic)
			:JaxProperty(owner, name, elementOffset, F_SAVE_LOAD_CLONE | F_NO_USE_GC)
		{
			m_uiDataNum = dataNum;
			m_bDynamicCreate = dynamic;
		}

		JaxDataProperty(JaxFunction& owner, const JaxUsedName& name, size_t elementOffset, size_t dataNum, bool dynamic)
			:JaxProperty(owner, name, elementOffset, dataNum, dynamic)
		{
			m_uiDataNum = dataNum;
			m_bDynamicCreate = m_bDynamicCreate;
		}

		JaxDataProperty() {}

		JaxDataProperty(JaxRtti& owner, const JaxUsedName& name, size_t elementOffset, size_t numElementOffset)
			:JaxProperty(owner, name, elementOffset, F_SAVE_LOAD_CLONE | F_NO_USE_GC)
		{
			m_uiDataNum = 0;
			m_bDynamicCreate = true;
			m_uiNumElementOffset = numElementOffset;
		}
		
		virtual size_t GetPropertyType() const
		{
			return PT_DATA;
		}

		virtual JaxProperty* GetInstance()
		{
			return JAX_NEW JaxDataProperty<T, NumType>();
		}

		virtual void CopyData(void* src, void* dest)
		{
			return;
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
			*(NumType*)destOffset = *(NumType*)srcOffset;
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
	inline bool JaxDataProperty<T, NumType>::Archive(JaxStream& stream, void* obj)
	{
		size_t streamFlag = stream.GetStreamFlag();
		if (streamFlag == JaxStream::AT_SAVE)
		{
			T* valueAddress = *(T**)GetValueAddress(obj);
			if (m_uiDataNum > 0)
			{
				stream.Write(valueAddress, m_uiDataNum * sizeof(T));
			}
			else
			{
				void* numOffset = (void*)(((unsigned char*)obj) + m_uiNumElementOffset);
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
				void* numOffset = (void*)(((unsigned char*)obj) + m_uiNumElementOffset);
				stream.Read(numOffset, sizeof(NumType));
				NumType num = *(NumType*)numOffset;
				*tmp = JAX_NEW T[num];
				stream.Read((void*)(*tmp), num * sizeof(T));
			}
		}
		else if (streamFlag == JaxStream::AT_SIZE)
		{
			if (m_uiDataNum > 0)
			{
				stream.AddBufferSize(m_uiDataNum * sizeof(T));
			}
			else
			{
				void* numOffset = (void*)(((unsigned char*)obj) + m_uiNumElementOffset);
				NumType num = *(NumType*)numOffset;
				stream.AddBufferSize(sizeof(NumType));
				stream.AddBufferSize(num * sizeof(T));
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

	template<typename ArrayType,typename T>
	class JaxArrayProperty :public JaxValueBaseProperty<T>
	{
	public:
		JaxArrayProperty() {}
		JaxArrayProperty(JaxRtti& owner, const JaxUsedName& name, size_t offset, size_t flag, bool range = false, T high = T(), T low = T(), T fStep = T())
			:JaxValueBaseProperty(owner, name, offset, flag, range, high, low, fStep)
		{

		}

		JaxArrayProperty(JaxFunction& owner, const JaxUsedName& name, size_t offset, size_t flag, bool range = false, T high = T(), T low = T(), T fStep = T())
			:JaxValueBaseProperty(owner, name, offset, flag, range, high, low, fStep)
		{

		}

		virtual ~JaxArrayProperty()
		{

		}

		virtual size_t GetPropertyType() const
		{
			return PT_ARRAY;
		}

		FORCEINLINE ArrayType& GetContainer(void* obj) const
		{
			return (*(ArrayType*)(((unsigned char*)obj) + m_uiElementOffset));
		}

		FORCEINLINE bool AddElement(void* obj,T& src)
		{
			GetContainer(obj).AddElement(src);
			return true;
		}

		FORCEINLINE bool Erase(void* obj, size_t idx)
		{
			GetContainer(obj).Erase(idx);
		}

		virtual bool SetValue(void* obj, size_t idx, T& src) const
		{
			if (src > m_HighValue || src < m_LowValue)
			{
				return false;
			}
			GetContainer(obj)[idx] = src;
			return true;
		}

		virtual bool GetValue(void* obj, size_t idx, T& dest) const
		{
			dest = GetContainer(obj)[idx];
			return true;
		}

		virtual bool Archive(JaxStream& stream, void* obj)
		{
			stream.Archive(GetContainer(obj));
			return true;
		}

		virtual void CloneData(void* src, void* dest, JaxMap<JaxObject*, JaxObject*>& cloneMap)
		{
			Copy(GetContainer(dest), GetContainer(src), cloneMap);
		}

		virtual void CopyData(void* src, void* dest)
		{
			GetContainer(dest) = GetContainer(src);
		}

		virtual JaxProperty* GetInstance()
		{
			return JAX_NEW JaxArrayProperty<ArrayType, T>();
		}
	};

	template<typename MapType,typename KEY,typename VALUE>
	class JaxMapProperty :public JaxValueBaseProperty<VALUE>
	{
	public:
		JaxMapProperty() {}
		JaxMapProperty(JaxRtti& owner, const JaxUsedName& name, size_t offset, size_t flag, bool range = false, VALUE high = VALUE(), VALUE low = VALUE(), VALUE fStep = VALUE())
			:JaxValueBaseProperty(owner, name, offset, flag, range, high, low, fStep)
		{

		}

		JaxMapProperty(JaxFunction& owner, const JaxUsedName& name, size_t offset, size_t flag, bool range = false, VALUE high = VALUE(), VALUE low = T(), VALUE fStep = VALUE())
			:JaxValueBaseProperty(owner, name, offset, flag, range, high, low, fStep)
		{

		}

		virtual ~JaxMapProperty()
		{

		}

		virtual size_t GetPropertyType() const
		{
			return PT_MAP;
		}

		FORCEINLINE MapType& GetContainer(void* obj) const
		{
			return (*MapType*)(((unsigned char*)obj) + m_uiElementOffset);
		}

		FORCEINLINE bool AddElement(void* obj, MapElement<KEY, VALUE>& src)
		{
			GetContainer(obj).AddElement(src);
			return true;
		}

		FORCEINLINE bool Erase(void* obj, size_t idx)
		{
			GetContainer(obj).Erase(i);
		}

		virtual bool SetValue(void* obj, size_t idx, KEY& key, VALUE& value) const
		{
			if (value > m_HighValue || value < m_LowValue)
			{
				return false;
			}
			MapElement<KEY, VALUE> tmp(key, value);
			GetContainer(obj)[idx] = tmp;
			return true;
		}

		virtual bool GetValue(void* obj, size_t idx, MapElement<KEY, VALUE>& dest) const
		{
			dest = GetContainer(obj)[idx];
			return true;
		}

		virtual bool Archive(JaxStream& stream, void* obj)
		{
			stream.Archive(GetContainer(obj));
			return true;
		}

		virtual void CloneData(void* src, void* dest, JaxMap<JaxObject, JaxObject*>& cloneMap)
		{
			Copy(GetContainer(dest), GetContainer(src), cloneMap);
		}

		virtual void CopyData(void* src, void* dest)
		{
			GetContainer(dest) = GetContainer(src);
		}

		virtual JaxProperty* GetInstance()
		{
			return JAX_NEW JaxMapProperty<MapType, KEY, VALUE>();
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

	template<typename T,JaxMemManagerFun MMFun>
	struct AutoPropertyCreator<JaxArray<T, MMFun>>
	{
		JaxProperty* CreateProperty(const JaxUsedName& name, JaxRtti& owner, size_t offset, size_t flag)
		{
			if (!(TIsJaxPointerType<T>::Value || TIsJaxSmartPointerType<T>::Value || TIsCustomType<T>::Value || TIsJaxType<T>::Value || ValueBase<T>::NeedsConstructor))
			{
				flag |= JaxProperty::F_NO_USE_GC;
			}
			return JAX_NEW JaxArrayProperty<JaxArray<T, MMFun>, T>(owner, name, offset, flag);
		}

		JaxProperty* CreateFunctionProperty(const JaxUsedName& name, JaxFunction& owner, size_t offset, size_t flag)
		{
			return JAX_NEW JaxArrayProperty<JaxArray<T, MMFun>, T>(owner, name, offset, flag);
		}

		JaxProperty* CreateProperty(const JaxUsedName& name, JaxRtti& owner, size_t offset, T high, T low, JAXREAL fstep, size_t flag)
		{
			if (!(TIsJaxPointerType<T>::Value || TIsJaxSmartPointerType<T>::Value || TIsCustomType<T>::Value || TIsJaxType<T>::Value || ValueBase<T>::NeedsConstructor))
			{
				flag |= JaxProperty::F_NO_USE_GC;
			}
			return JAX_NEW JaxArrayProperty<JaxArray<T, MMFun>, T>(owner, name, offset, flag, high, low, fstep);
		}
	};

	template<typename KEY,typename VALUE, JaxMemManagerFun MMFun>
	struct AutoPropertyCreator<JaxMap<KEY,VALUE,MMFun>>
	{
		JaxProperty* CreateProperty(const JaxUsedName& name, JaxRtti& owner, size_t offset, size_t flag)
		{
			return JAX_NEW JaxMapProperty<JaxMap<KEY, VALUE, MMFun>, KEY, VALUE>(owner, name, offset, flag);
		}

		JaxProperty* CreateFunctionProperty(const JaxUsedName& name, JaxFunction& owner, size_t offset, size_t flag)
		{
			return JAX_NEW JaxMapProperty<JaxMap<KEY, VALUE, MMFun>, KEY, VALUE>(owner, name, offset, flag);
		}

		JaxProperty* CreateProperty(const JaxUsedName& name, JaxRtti& owner, size_t offset, VALUE high, VALUE low, JAXREAL fstep, size_t flag)
		{
			return JAX_NEW JaxMapProperty<JaxMap<KEY, VALUE, MMFun>, KEY, VALUE>(owner, name, offset, flag, high, low, fstep);
		}
	};

	template<typename KEY, typename VALUE, JaxMemManagerFun MMFun>
	struct AutoPropertyCreator<JaxMapOrder<KEY, VALUE, MMFun>>
	{
		JaxProperty* CreateProperty(const JaxUsedName& name, JaxRtti& owner, size_t offset, size_t flag)
		{
			return JAX_NEW JaxMapProperty<JaxMapOrder<KEY, VALUE, MMFun>, KEY, VALUE>(owner, name, offset, flag);
		}

		JaxProperty* CreateFunctionProperty(const JaxUsedName& name, JaxFunction& owner, size_t offset, size_t flag)
		{
			return JAX_NEW JaxMapProperty<JaxMapOrder<KEY, VALUE, MMFun>, KEY, VALUE>(owner, name, offset, flag);
		}

		JaxProperty* CreateProperty(const JaxUsedName& name, JaxRtti& owner, size_t offset, VALUE high, VALUE low, JAXREAL fstep, size_t flag)
		{
			return JAX_NEW JaxMapProperty<JaxMapOrder<KEY, VALUE, MMFun>, KEY, VALUE>(owner, name, offset, flag, high, low, fstep);
		}
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

		template<typename ValueType,typename NumType>
		static DataPropertyCreator<ValueType, NumType>& GetAutoPropertyCreator(ValueType*& valueType,NumType& numType)
		{
			static DataPropertyCreator<ValueType, NumType> apc;
			return apc;
		}

		template<typename ValueType>
		static JaxProperty* CreateEnumProperty(ValueType& valueType, const JaxUsedName& name, const JaxUsedName& enumName, JaxRtti& owner, size_t offset, size_t flag)
		{
			return JAX_NEW JaxEnumProperty<ValueType>(owner, name, enumName, offset, flag | JaxProperty::F_NO_USE_GC);
		}
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