#include "JaxProperty.h"

namespace Jax
{
	JaxProperty::JaxProperty() :m_pRttiOwner(NULL),
		m_Name(NULL),m_uiElementOffset(0), m_uiFlag(0) {}

	JaxProperty::JaxProperty(JaxRtti& owner, const JaxString& name, size_t elementOffset, size_t flag) : m_pRttiOwner(&owner),
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


}

