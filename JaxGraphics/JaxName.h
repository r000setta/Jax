#pragma once
#include "JaxReference.h"
#include "JaxPriority.h"
#include "JaxString.h"
#include "JaxCustomArchiveObject.h"

namespace Jax
{
#define DECLARE_INITIAL \
public:\
static bool RegisterMainFactory(); \
static bool InitialClassFactory(); \
static bool sm_bRegisterMainFactory; \
static bool InitialProperty(JaxRtti*); \
static bool TerminalProperty();

#define IMPLEMENT_INITIAL_BEGIN(classname) \
static bool gs_bStreamRegistered_##classname=classname::RegisterMainFactory(); \
bool classname::sm_bRegisterMainFactory=false; \
bool classname::InitialClassFactory() \
{ \
sm_ClassFactory.AddElement(sm_Type.GetName(),FactoryFunc);\
return true;\
}\
JaxObject* classname::FactoryFunc()\
{\
return JAX_NEW classname;\
}\
bool classname::RegisterFactory()\
{\
if(!sm_bRegisterMainFactory)\
{

#define IMPLEMENT_INITIAL_END \
sm_bRegisterMainFactory=true;\
}\
return sm_bRegisterMainFactory;\
}

#define DECLARE_INITIAL_ONLY\
public:\
static bool RegisterMainFactory();\
static bool sm_bRegisterMainFactory;

#define IMPLEMENT_INITIAL_ONLY_BEGIN(classname) \
static bool gs_bStreamRegistered_##classsname=classname::RegisterMainFactory();\
bool classname::sm_bRegisterMainFactory=false;\
bool classname::RegisterMainFactory() \
{\
if(!sm_bRegisterMainFactory)\
{\

#define IMPLEMENT_INITIAL_ONLY_END \
sm_bRegisterMainFactory=true;\
}\
return sm_bRegisterMainFactory;\
}

#define DECLARE_INITIAL_NO_CLASS_FACTORY\
public:\
static bool RegisterMainFactory();\
static bool sm_bRegisterMainFactory;\
static bool Initialproperty(JaxRtti* );\
static bool TerminalProperty();

#define IMPLEMENT_INITIAL_NO_CLASS_FACTORY_BEGIN(classname)\
static bool gs_bStreamRegistered_##classname=classname::RegisterMainFactory();\
bool classname::sm_bRegisterMainFactory=false;\
bool classname::RegisterMainFactory()\
{\
if(!sm_bRegisterMainFactory)\
{

#define IMPLEMENT_INITIAL_NO_CLASS_FACTORY_END \
sm_bRegisterMainFactory=true;\
}\
return sm_bRegisterMainFactory;\
}


	class JAXGRAPHIC_API JaxName :public JaxReference, public JaxMemObject
	{
	public:
		friend class JaxResourceManager;
		~JaxName();
		explicit JaxName(const TCHAR* pChar, size_t id);
		explicit JaxName(const JaxString& string, size_t id);

		FORCEINLINE const TCHAR* GetBuffer() const
		{
			return m_String.GetBuffer();
		}

		FORCEINLINE const JaxString& GetString() const
		{
			return m_String;
		}

		FORCEINLINE size_t GetLength() const
		{
			return m_String.GetLength();
		}

		FORCEINLINE size_t GetID() const
		{
			return m_uiID;
		}

	private:
		size_t m_uiID;
		JaxString m_String;
	};

	DECLARE_PTR(JaxName);

	class JaxStream;
	class JAXGRAPHIC_API JaxUsedName:public JaxCustomArchiveObject
	{
		DECLARE_PRIORITY
	public:
		~JaxUsedName();
		JaxUsedName() :m_pName(NULL) {}
		JaxUsedName(const TCHAR* pChar);
		JaxUsedName(const JaxString& string);

		void operator=(const JaxString& string);
		void operator=(const TCHAR* pChar);
		void operator=(const JaxUsedName& name);

		FORCEINLINE const TCHAR* GetBuffer() const
		{
			if (!m_pName)
			{
				return NULL;
			}
			return m_pName->GetBuffer();
		}

		FORCEINLINE const JaxString& GetString() const
		{
			if (!m_pName)
			{
				return JaxString::sm_StringNULL;
			}
			return m_pName->GetString();
		}

		FORCEINLINE size_t GetLength() const
		{
			if (!m_pName)
			{
				return 0;
			}
			return m_pName->GetLength();
		}

		FORCEINLINE size_t GetNameCode() const
		{
			if (!m_pName)
			{
				return 0;
			}
			return m_pName->GetID();
		}

		JAXGRAPHIC_API friend bool operator>(const JaxUsedName& name1, const JaxUsedName& name2);
		JAXGRAPHIC_API friend bool operator<(const JaxUsedName& name1, const JaxUsedName& name2);

		JAXGRAPHIC_API friend bool operator==(const JaxUsedName& name1, const JaxUsedName& name2);
		JAXGRAPHIC_API friend bool operator==(const JaxUsedName& name1, const JaxString& string);
		JAXGRAPHIC_API friend bool operator==(const JaxUsedName& name1, const TCHAR* pChar);

		JAXGRAPHIC_API friend bool operator!=(const JaxUsedName& name1, const JaxUsedName& name2);
		JAXGRAPHIC_API friend bool operator!=(const JaxUsedName& name1, const JaxString& string);
		JAXGRAPHIC_API friend bool operator!=(const JaxUsedName& name1, const TCHAR* pChar);

		virtual void Archive(JaxStream& stream);

	protected:
		JaxNamePtr m_pName;
	};
}