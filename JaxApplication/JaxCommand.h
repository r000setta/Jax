#pragma once
#include "JaxMath.h"
#include "JaxSystem.h"
#include "JaxString.h"
#include "JaxMap.h"

namespace Jax
{
	class JaxCommand :public JaxMemObject
	{
	public:
		JaxCommand(int argNums, TCHAR** args);
		JaxCommand(TCHAR* commandLine);
		JaxCommand() {}
		~JaxCommand();

		bool GetName(const TCHAR* name);
		bool GetInteger(const TCHAR* name, int& value);
		bool GetReal(const TCHAR* name, JAXREAL& value);
		bool GetString(const TCHAR* name, JaxString& value);

	protected:
		JaxMap<JaxString, JaxString> m_CommandMap;
	};
}