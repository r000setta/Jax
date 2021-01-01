#include "JaxRtti.h"

namespace Jax
{
	JaxRtti::JaxRtti(const TCHAR* pRttiName, JaxRtti* pBase, CreateObjectFun COF) :m_cRttiName(pRttiName),m_pBase(pBase), m_CreateFun(COF) {}

	JaxRtti::~JaxRtti()
	{
		m_pBase = NULL;
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
