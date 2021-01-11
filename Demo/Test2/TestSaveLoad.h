#pragma once
#include "JaxObject.h"
#include "JaxName.h"

namespace Jax
{
	struct TestStruct
	{
		int m_Int;
		JAXREAL m_Float;
		TestStruct()
		{
			m_Float = 4.0f;
			m_Int = 1;
		}
	};

	class JaxTestObject :public JaxObject
	{
		DECLARE_RTTI;
	public:
		JaxTestObject() :m_IntTest(10), m_TestFloat(1.3f) {}
		~JaxTestObject() {}

		DECLARE_INITIAL

		static bool InitialDefaultState();
		static bool TerminalDefaultState();
		int m_IntTest;
		JAXREAL m_TestFloat;
	};

	DECLARE_PTR(JaxTestObject);
	JAXTYPE_MARCO(JaxTestObject);
	
	class JaxTestSaveLoad :public JaxObject
	{
		DECLARE_RTTI
	public:
		JaxTestSaveLoad() :m_Int(11) {}
		~JaxTestSaveLoad() {}

		DECLARE_INITIAL

		static bool InitialDefaultState();
		static bool TerminalDefaultState();
	public:
		int m_Int;
		JaxUsedName m_Name;
	};

	DECLARE_PTR(JaxTestSaveLoad)
	JAXTYPE_MARCO(JaxTestSaveLoad)

}