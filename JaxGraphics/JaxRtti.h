#pragma once
#include "JaxString.h"
#include "JaxGraphic.h"
#include "JaxMemManager.h"
#include "JaxArray.h"

namespace Jax
{
	class JaxObject;
	typedef JaxObject* (*CreateObjectFun)();
	class JaxProperty;

#define DECLARE_RTTI \
public: \
virtual JaxRtti& GetType() const { return sm_Type; } \
static JaxRtti sm_Type; \
static JaxPriority sm_Priority;

#define IMPLEMENT_RTTI(classname,baseclassname) \
JaxRtti classname:sm_Type(_T(#classname),&baseclassname::sm_Type,classname::FactoryFunc);\
JaxPriority classname::sm_Priority;

#define IMPLEMENT_RTTI_NoCreateFun(classname,baseclassname)\
JaxRtti classname::sm_Type(_T(#classname),&baseclassname::sm_Type,NULL);\
JaxPriority classname::sm_Priority;

#define IMPLEMENT_RTTI_NoParent(classname)\
JaxRtti classname::sm_Type(_T(#classname),NULL,classname::FactoryFunc);\
JaxPriority classname::sm_Priority;

#define IMPLEMENT_RTTI_NoParent_NoCreateFun(classname) \
JaxRtti classname::sm_Type(_T(#classname),NULL,NULL); \
JaxPriority classname::sm_Priority;

	class JAXGRAPHIC_API JaxRtti :public JaxMemObject
	{
	public:
		JaxRtti(const TCHAR* pRttiName, JaxRtti* pBase, CreateObjectFun COF);
		~JaxRtti();

		FORCEINLINE const JaxString& GetName() const
		{
			return m_cRttiName;
		}

		FORCEINLINE bool IsSameType(const JaxRtti& Type) const
		{
			return &Type == this;
		}

		FORCEINLINE JaxRtti* GetBase() const
		{
			return m_pBase;
		}

		JaxProperty* GetProperty(size_t idx) const;
		JaxProperty* GetProperty(const JaxString& propertyName) const;
		size_t GetPropertyNum() const;
		void AddProperty(JaxProperty* property);
		void AddProperty(JaxRtti& rtti);
		void ClearProperty();

		bool IsDerived(const JaxRtti& Type) const;

	private:
		JaxString m_cRttiName;
		JaxRtti* m_pBase;
		JaxArray<JaxProperty *> m_PropertyArray;
		CreateObjectFun m_CreateFun;
	};
}