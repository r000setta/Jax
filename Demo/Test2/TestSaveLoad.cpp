#include "TestSaveLoad.h"
#include "JaxProperty.h"
namespace Jax
{
	IMPLEMENT_RTTI(JaxTestSaveLoad,JaxObject)
	BEGIN_ADD_PROPERTY(JaxTestSaveLoad,JaxObject)
	//REGISTER_PROPERTY(m_Int,testInt,JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_ArrayInt,TestArray,JaxProperty::F_SAVE_LOAD_CLONE)
	//REGISTER_PROPERTY(m_TestString,TestString,JaxProperty::F_SAVE_LOAD_CLONE)
	//REGISTER_PROPERTY_DATA(m_FloatData,m_FloatDataNum,TestDataBuffer)
	REGISTER_PROPERTY_FIXED_DATA(m_FixedFloatData,3,FixedFloatData,false)
	//REGISTER_PROPERTY(m_Name,testName,JaxProperty::F_SAVE_LOAD_CLONE)
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