#include "JaxCommand.h"

namespace Jax
{
	JaxCommand::JaxCommand(int argNums, TCHAR** args)
	{
		for (int i = 0; i < argNums; ++i)
		{
			JaxString command(args[i]);
			JaxString value;
			if (value.GetString(command, '=', 1, false))
			{
				JaxString key;
				key.GetString(command, '=', 1);
				m_CommandMap.AddElement(key, value);
			}
			else
			{
				m_CommandMap.AddElement(command, value);
			}
		}
	}

	JaxCommand::JaxCommand(TCHAR* commandLine)
	{
		if (!commandLine)
		{
			return;
		}
		
		TCHAR* nextToken = NULL;
		TCHAR* token = JaxStrtok(commandLine, _T(" "), &nextToken);
		while (token)
		{
			JaxString command(token);
			JaxString value;
			if (command.GetString(value, '=', 1, false))
			{
				JaxString key;
				command.GetString(key, '=', 1);
				m_CommandMap.AddElement(key, value);
			}
			else
			{
				m_CommandMap.AddElement(command, value);
			}
			token = JaxStrtok(NULL, _T(" "), &nextToken);
		}
	}

	JaxCommand::~JaxCommand()
	{
	}

	bool JaxCommand::GetName(const TCHAR* name)
	{
		if (m_CommandMap.Find(name) != m_CommandMap.GetNum())
		{
			return true;
		}
		return false;
	}
	bool JaxCommand::GetInteger(const TCHAR* name, int& value)
	{
		size_t i = m_CommandMap.Find(name);
		if (i != m_CommandMap.GetNum())
		{
			value = StringToInt(m_CommandMap[i].value);
			return true;
		}
		return false;
	}
	bool JaxCommand::GetReal(const TCHAR* name, JAXREAL& value)
	{
		size_t i = m_CommandMap.Find(name);
		if (i != m_CommandMap.GetNum())
		{
			value = StringToReal(m_CommandMap[i].value);
			return true;
		}
		return false;
	}

	bool JaxCommand::GetString(const TCHAR* name, JaxString& value)
	{
		size_t i = m_CommandMap.Find(name);
		if (i != m_CommandMap.GetNum())
		{
			value = m_CommandMap[i].value;
			return true;
		}
		return false;
	}


}
