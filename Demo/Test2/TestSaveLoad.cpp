#include "TestSaveLoad.h"
#include "JaxProperty.h"
namespace Jax
{
	IMPLEMENT_RTTI(JaxTestObject,JaxObject)
	BEGIN_ADD_PROPERTY(JaxTestObject,JaxObject)
	REGISTER_PROPERTY(m_IntTest,TestInt,JaxProperty::F_SAVE_LOAD_CLONE)
	END_ADD_PROPERTY
	IMPLEMENT_INITIAL_BEGIN(JaxTestObject)
	ADD_INITIAL_FUNCTION_WITH_PRIORITY(InitialDefaultState)
	ADD_TERMINAL_FUNCTION(TerminalDefaultState)
	IMPLEMENT_INITIAL_END

	bool JaxTestObject::InitialDefaultState()
	{
		return true;
	}
	bool JaxTestObject::TerminalDefaultState()
	{
		return true;
	}

	IMPLEMENT_RTTI(JaxTestSaveLoad,JaxObject)
	BEGIN_ADD_PROPERTY(JaxTestSaveLoad,JaxObject)
	REGISTER_PROPERTY(m_Int,testInt,JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_Name,testName,JaxProperty::F_SAVE_LOAD_CLONE)
	END_ADD_PROPERTY
	IMPLEMENT_INITIAL_BEGIN(JaxTestSaveLoad)
	ADD_INITIAL_FUNCTION_WITH_PRIORITY(InitialDefaultState)
	ADD_TERMINAL_FUNCTION(TerminalDefaultState)
	IMPLEMENT_INITIAL_END

	bool JaxTestSaveLoad::InitialDefaultState()
	{
		return true;
	}

	bool JaxTestSaveLoad::TerminalDefaultState()
	{
		return true;
	}
}