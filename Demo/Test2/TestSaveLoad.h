#pragma once
#include "JaxObject.h"
#include "JaxName.h"

namespace Jax
{	
	class JaxTestSaveLoad :public JaxObject
	{
		DECLARE_RTTI
	public:
		//JaxTestSaveLoad() :m_Int(123), m_Name(_T("test")), m_TestString(_T("123")) {}
		JaxTestSaveLoad()
		{
			m_FixedFloatData = JAX_NEW JAXREAL[3];
		}
		~JaxTestSaveLoad() {}

		DECLARE_INITIAL

		static bool InitialDefaultState();
		static bool TerminalDefaultState();
	public:
		JaxArray<int> m_ArrayInt;
		//int m_Int;
		//JAXREAL* m_FloatData;
		JAXREAL* m_FixedFloatData;
		//size_t m_FloatDataNum;
		JaxString m_TestString;
		//JaxUsedName m_Name;
	};

	DECLARE_PTR(JaxTestSaveLoad)
	JAXTYPE_MARCO(JaxTestSaveLoad)
}