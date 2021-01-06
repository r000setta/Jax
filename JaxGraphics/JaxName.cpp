#include "JaxName.h"
#include "JaxStream.h"
#include "JaxResouceManager.h"

namespace Jax
{
	JaxName::~JaxName()
	{
		m_uiID = 0;
		m_String.Clear();
	}

	JaxName::JaxName(const TCHAR* pChar, size_t id)
	{
		JAX_ASSERT(pChar);
		m_uiID = id;
		m_String.Clear();
		m_String = pChar;
	}

	JaxName::JaxName(const JaxString& string, size_t id)
	{
		m_uiID = id;
		m_String.Clear();
		m_String = string;
	}


	JaxUsedName::~JaxUsedName()
	{
		m_pName = NULL;
	}

	JaxUsedName::JaxUsedName(const TCHAR* pChar)
	{
		m_pName = JaxResourceManager::CreateName(pChar);
	}

	JaxUsedName::JaxUsedName(const JaxString& string)
	{
		m_pName = JaxResourceManager::CreateName(string);
	}

	void JaxUsedName::operator=(const JaxString& string)
	{
		m_pName = JaxResourceManager::CreateName(string);
	}

	void JaxUsedName::operator=(const TCHAR* pChar)
	{
		m_pName = JaxResourceManager::CreateName(pChar);
	}

	void JaxUsedName::operator=(const JaxUsedName& name)
	{
		m_pName = name.m_pName;
	}

	bool operator>(const JaxUsedName& name1, const JaxUsedName& name2)
	{
		if (!name1.m_pName && !name2.m_pName)
		{
			return false;
		}
		else if (name1.m_pName && !name2.m_pName)
		{
			return true;
		}
		else if (!name1.m_pName && name2.m_pName)
		{
			return false;
		}
		return name1.m_pName->GetID() > name2.m_pName->GetID();
	}

	bool operator<(const JaxUsedName& name1, const JaxUsedName& name2)
	{
		if (!name1.m_pName && !name2.m_pName)
		{
			return false;
		}
		else if (name1.m_pName && !name2.m_pName)
		{
			return false;
		}
		else if (!name1.m_pName && name2.m_pName)
		{
			return true;
		}
		return name1.m_pName->GetID() < name2.m_pName->GetID();
	}

	bool operator==(const JaxUsedName& name1, const JaxUsedName& name2)
	{
		if (!name1.m_pName && !name2.m_pName)
		{
			return true;
		}
		else if (!name1.m_pName || !name2.m_pName)
		{
			return false;
		}
		return name1.m_pName->GetID() == name2.m_pName->GetID();
	}

	bool operator==(const JaxUsedName& name1, const JaxString& string)
	{
		if (!name1.m_pName)
		{
			return false;
		}
		return name1.m_pName->GetString() == string;
	}

	bool operator==(const JaxUsedName& name1, const TCHAR* pChar)
	{
		if (!name1.m_pName&&!pChar)
		{
			return true;
		}
		else if (!name1.m_pName || !pChar)
		{
			return false;
		}
		return name1.m_pName->GetString() == pChar;
	}

	bool operator!=(const JaxUsedName& name1, const JaxUsedName& name2)
	{
		if (!name1.m_pName && !name2.m_pName)
		{
			return false;
		}
		else if (!name1.m_pName || !name2.m_pName)
		{
			return true;
		}
		return name1.m_pName->GetID() != name2.m_pName->GetID();
	}

	bool operator!=(const JaxUsedName& name1, const JaxString& string)
	{
		if (!name1.m_pName)
		{
			return true;
		}
		return name1.m_pName->GetString() != string;
	}

	bool operator!=(const JaxUsedName& name1, const TCHAR* pChar)
	{
		if (!name1.m_pName && !pChar)
		{
			return false;
		}
		else if (!name1.m_pName || !pChar)
		{
			return true;
		}
		return name1.m_pName->GetString() != pChar;
	}

	void JaxUsedName::Archive(JaxStream& stream)
	{
		if (stream.GetStreamFlag() == JaxStream::AT_LOAD)
		{
			JaxString string;
			stream.ReadString(string);
			if (string == JaxString::sm_StringNULL)
			{
				m_pName = NULL;
			}
			else
			{
				m_pName = JaxResourceManager::CreateName(string);
			}
		}
		else if (stream.GetStreamFlag() == JaxStream::AT_SAVE)
		{
			if (m_pName)
			{
				stream.WriteString(m_pName->GetString());
			}
			else
			{
				stream.WriteString(JaxString::sm_StringNULL);
			}
		}
	}

}
