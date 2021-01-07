#include "JaxProperty.h"

namespace Jax
{
	JaxProperty::JaxProperty() :m_pRttiOwner(NULL),
		m_Name(NULL),m_uiElementOffset(0), m_uiFlag(0) {}

	JaxProperty::JaxProperty(JaxRtti& owner, const JaxUsedName& name, size_t elementOffset, size_t flag) : m_pRttiOwner(&owner),
		m_Name(name), m_uiElementOffset(elementOffset), m_uiFlag(flag) {}

	JaxProperty::~JaxProperty()
	{
	}

	void JaxProperty::SetOwner(JaxRtti& owner)
	{
		m_pRttiOwner = &owner;
	}

	size_t JaxProperty::GetFlag() const
	{
		return m_uiFlag;
	}

	void JaxProperty::SetFlag(size_t flag)
	{
		m_uiFlag = flag;
	}

	bool JaxProperty::Clone(JaxProperty* p)
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

	JaxFunction::~JaxFunction()
	{
		for (size_t i = 0; i < m_PropertyArray.GetNum(); ++i)
		{
			if (m_PropertyArray[i])
			{
				JAXMAC_DELETE(m_PropertyArray[i]);
			}
		}
		JAXMAC_DELETE(m_pReturnProperty);
	}

	bool JaxFunction::Clone(JaxFunction* f)
	{
		if ((f->GetRtti() == GetRtti() && GetRtti()))
		{
			m_Name = f->m_Name;
			m_uiFlag = f->m_uiFlag;
			for (size_t i = 0; i < m_PropertyArray.GetNum(); ++i)
			{
				JaxProperty* p = f->m_PropertyArray[i]->GetInstance();
				m_PropertyArray.AddElement(p);
				p->Clone(f->m_PropertyArray[i]);
			}
			return true;
		}
		return false;
	}
}

