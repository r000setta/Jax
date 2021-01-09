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

	class JaxTestSaveLoad :public JaxObject
	{
		DECLARE_RTTI
	public:
		JaxTestSaveLoad() :m_Int(10) {}
		~JaxTestSaveLoad() {}

		DECLARE_INITIAL
		int m_Int;
	public:
		static bool InitialDefaultState();
		static bool TerminalDefaultState();
	};

	DECLARE_PTR(JaxTestSaveLoad);
	JAXTYPE_MARCO(JaxTestSaveLoad);
}