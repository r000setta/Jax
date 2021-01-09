#include "JaxObject.h"
#include "JaxStream.h"
#include "JaxProperty.h"
namespace Jax
{
	IMPLEMENT_RTTI_NoParent_NoCreateFun(JaxObject);
	JaxMapOrder<JaxUsedName, FactoryFunction> JaxObject::sm_ClassFactory;
	IMPLEMENT_INITIAL_NO_CLASS_FACTORY_BEGIN(JaxObject)
	IMPLEMENT_INITIAL_NO_CLASS_FACTORY_END
	BEGIN_ADD_PROPERTY_ROOT(JaxObject)
	END_ADD_PROPERTY

	JaxFastObjectManager::JaxFastObjectManager()
	{
		m_FreeTable.SetBufferNum(MAX_OBJECT_NUM);
		for (size_t i = 0; i < MAX_OBJECT_NUM; ++i)
		{
			m_FreeTable[i] = i;
			m_ObjectArray[i] = NULL;
		}
		m_ObjectArray[MAX_OBJECT_NUM] = NULL;
	}

	JaxFastObjectManager::~JaxFastObjectManager()
	{
	}
	size_t JaxFastObjectManager::AddObject(JaxObject* p)
	{
		JAX_ASSERT(m_FreeTable.GetNum() > 0);
		size_t id = m_FreeTable[m_FreeTable.GetNum() - 1];
		m_ObjectArray[id] = p;
		return id;
	}

	void JaxFastObjectManager::DeleteObject(JaxObject* p)
	{
		if (m_ObjectArray[p->m_uiObjectID])
		{
			m_FreeTable.AddElement(p->m_uiObjectID);
			m_ObjectArray[p->m_uiObjectID] = NULL;
			p->m_uiObjectID = MAX_OBJECT_FLAG;
		}
	}
	bool JaxFastObjectManager::IsClear()
	{
		return m_FreeTable.GetNum() == MAX_OBJECT_NUM;
	}
	size_t JaxFastObjectManager::GetObjectNum()
	{
		return MAX_OBJECT_NUM - m_FreeTable.GetNum();
	}

	JaxObject::~JaxObject()
	{
		GetObjectManager().DeleteObject(this);
	}

	JaxObject::JaxObject(const JaxObject& object)
	{
		m_uiFlag = object.m_uiFlag;
		m_uiObjectID = GetObjectManager().AddObject(this);
	}

	JaxObject& JaxObject::operator=(const JaxObject& object)
	{
		m_uiFlag = object.m_uiFlag;
		return *this;
	}

	JaxObject::JaxObject()
	{
		m_uiFlag = 0;
		m_uiObjectID = GetObjectManager().AddObject(this);
	}

	JaxObject* JaxObject::GetInstance(const JaxRtti& rtti)
	{
		//TODO
		return NULL;
	}

	bool JaxObject::BeforeSave(void* data)
	{
		return true;
	}

	bool JaxObject::PostSave(void* data)
	{
		return true;
	}

	bool JaxObject::PostLoad(void* data)
	{
		return true;
	}

	JaxObject* JaxObject::GetInstance(const JaxString& rttiName)
	{
		size_t i = sm_ClassFactory.Find(rttiName);
		if (i == sm_ClassFactory.GetNum())
		{
			return NULL;
		}
		JaxObject* object = sm_ClassFactory[i].value();
		//TODO:GC
		return object;
	}

	bool JaxObject::IsSameType(const JaxObject* pObject) const
	{
		return pObject && GetType().IsSameType(pObject->GetType());
	}

	bool JaxObject::IsDerived(const JaxObject* pObject) const
	{
		return pObject && GetType().IsDerived(pObject->GetType());
	}

	bool JaxObject::IsSameType(const JaxRtti& type) const
	{
		return GetType().IsSameType(type);
	}

	bool JaxObject::IsDerived(const JaxRtti& type) const
	{
		return GetType().IsDerived(type);
	}

	JaxObject* JaxObject::GetNoGCInstance(const JaxString& rttiName)
	{
		size_t i = sm_ClassFactory.Find(rttiName);
		if (i == sm_ClassFactory.GetNum())
		{
			return NULL;
		}
		JaxObject* object = sm_ClassFactory[i].value();
		return object;
	}
}

