#pragma once
#include "JaxString.h"
#include "JaxGraphic.h"
#include "JaxMemManager.h"
#include "JaxArray.h"
#include "JaxPriority.h"

namespace Jax
{
	class JaxObject;
	typedef JaxObject* (*CreateObjectFun)();

#define DECLARE_RTTI \
public:\
virtual JaxRtti& GetType() const { return sm_Type; } \
static JaxRtti sm_Type;\
static JaxPriority sm_Priority;

#define IMPLEMENT_RTTI(classname,baseclassname) \
JaxRtti classname:sm_Type(_T(#classname),&baseclassname::sm_Type,classname::FactoryFunc);\
IMPLEMENT_PRIORITY(classname)

#define IMPLEMENT_RTTI_NoCreateFun(classname,baseclassname)\
JaxRtti classname::sm_Type(_T(#classname),&baseclassname::sm_Type,NULL);\
IMPLEMENT_PRIORITY(classname)

#define IMPLEMENT_RTTI_NoParent(classname)\
JaxRtti classname::sm_Type(_T(#classname),NULL,classname::FactoryFunc);\
IMPLEMENT_PRIORITY(classname)

#define IMPLEMENT_RTTI_NoParent_NoCreateFun(classname) \
JaxRtti classname::sm_Type(_T(#classname),NULL,NULL);\
IMPLEMENT_PRIORITY(classname)

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

		bool IsDerived(const JaxRtti& Type) const;

	private:
		JaxString m_cRttiName;
		JaxRtti* m_pBase;
		CreateObjectFun m_CreateFun;
	};
}