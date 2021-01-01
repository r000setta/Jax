#include "JaxPriority.h"

namespace Jax
{
	JaxPriority::JaxPriority()
	{
		m_uiPriorityNum = 0;
	}

	JaxPriority::JaxPriority(size_t priorityNum)
	{
		m_uiPriorityNum = priorityNum;
	}

	JaxPriority::~JaxPriority()
	{
		m_pPriorityThanList.Clear();
	}

	size_t JaxPriority::GetPriorityNum()
	{
		CheckPriorityNum();
		return m_uiPriorityNum;
	}

	JaxPriority& JaxPriority::operator=(JaxPriority& r)
	{
		r.CheckPriorityNum();
		m_uiPriorityNum = r.m_uiPriorityNum;
		m_pPriorityThanList.Clear();
		m_pPriorityThanList = r.m_pPriorityThanList;
		return *this;
	}

	bool JaxPriority::operator==(JaxPriority& r)
	{
		r.CheckPriorityNum();
		CheckPriorityNum();
		return m_uiPriorityNum == r.m_uiPriorityNum;
	}

	bool JaxPriority::operator!=(JaxPriority& r)
	{
		r.CheckPriorityNum();
		CheckPriorityNum();
		return m_uiPriorityNum != r.m_uiPriorityNum;
	}

	bool JaxPriority::operator>(JaxPriority& r)
	{
		r.CheckPriorityNum();
		CheckPriorityNum();
		return m_uiPriorityNum > r.m_uiPriorityNum;
	}

	bool JaxPriority::operator<(JaxPriority& r)
	{
		r.CheckPriorityNum();
		CheckPriorityNum();
		return m_uiPriorityNum < r.m_uiPriorityNum;
	}

	bool JaxPriority::operator>=(JaxPriority& r)
	{
		r.CheckPriorityNum();
		CheckPriorityNum();
		return m_uiPriorityNum >= r.m_uiPriorityNum;
	}

	bool JaxPriority::operator<=(JaxPriority& r)
	{
		r.CheckPriorityNum();
		CheckPriorityNum();
		return m_uiPriorityNum <= r.m_uiPriorityNum;
	}

	bool JaxPriority::CheckIsCircle(const JaxPriority* checked) const
	{
		if (!checked)
		{
			return false;
		}
		for (size_t i = 0; i < m_pPriorityThanList.GetNum(); ++i)
		{
			if (checked == m_pPriorityThanList[i])
			{
				return true;
			}
			else
			{
				return m_pPriorityThanList[i]->CheckIsCircle(checked);
			}
		}
		return false;
	}

	size_t JaxPriority::CheckPriorityNum()
	{
		if (m_uiPriorityNum || !m_pPriorityThanList.GetNum())
			return m_uiPriorityNum;
		else
		{
			size_t Max = 0;
			for (size_t i = 0; i < m_pPriorityThanList.GetNum(); ++i)
			{
				if (Max < m_pPriorityThanList[i]->CheckPriorityNum())
				{
					Max = m_pPriorityThanList[i]->m_uiPriorityNum;
				}
			}
			m_uiPriorityNum = Max + 1;
			return m_uiPriorityNum;
		}
	}
}

