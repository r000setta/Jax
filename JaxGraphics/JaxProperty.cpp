#include "JaxProperty.h"

namespace Jax
{

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

