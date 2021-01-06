#include "JaxRtti.h"
#include "JaxProperty.h"
namespace Jax
{
	JaxRtti::JaxRtti(const TCHAR* pRttiName, JaxRtti* pBase, CreateObjectFun COF) :m_cRttiName(pRttiName),m_pBase(pBase), m_CreateFun(COF) {}

	JaxRtti::~JaxRtti()
	{
		m_pBase = NULL;
	}

	JaxProperty* JaxRtti::GetProperty(size_t idx) const
	{
		if (idx >= m_PropertyArray.GetNum())
		{
			return NULL;
		}
		return m_PropertyArray[idx];
	}

	JaxProperty* JaxRtti::GetProperty(const JaxString& propertyName) const
	{
		for (size_t i = 0; i < m_PropertyArray.GetNum(); ++i)
		{
			if (m_PropertyArray[i]->GetName() == propertyName)
			{
				return m_PropertyArray[i];
			}
		}
		return NULL;
	}

	size_t JaxRtti::GetPropertyNum() const
	{
		return m_PropertyArray.GetNum();
	}

	void JaxRtti::AddProperty(JaxProperty* property)
	{
		if (property)
		{
			for (size_t i = 0; i < m_PropertyArray.GetNum(); ++i)
			{
				JAX_ASSERT(m_PropertyArray[i]->GetName() != property->GetName());
			}
			m_PropertyArray.AddElement(property);
		}
	}

	void JaxRtti::AddProperty(JaxRtti& rtti)
	{
		for (size_t i = 0; i < rtti.m_PropertyArray.GetNum(); ++i)
		{
			JaxProperty* property = rtti.m_PropertyArray[i];
			JaxProperty* newProperty = property->GetInstance();
			newProperty->Clone(property);
			newProperty->SetOwner(*this);
			m_PropertyArray.AddElement(newProperty);
		}
	}

	void JaxRtti::ClearProperty()
	{
		for (size_t i = 0; i < m_PropertyArray.GetNum(); ++i)
		{
			if (m_PropertyArray[i])
			{
				JAXMAC_DELETE(m_PropertyArray[i])
			}
		}
		m_PropertyArray.Clear();
	}

	bool JaxRtti::IsDerived(const JaxRtti& type) const
	{
		const JaxRtti* pTmp = this;
		while (!pTmp->IsSameType(type))
		{
			if (pTmp->m_pBase)
			{
				pTmp = pTmp->m_pBase;
			}
			else
			{
				return false;
			}
		}
		return true;
	}
}
