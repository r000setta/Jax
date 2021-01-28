#include "JaxRasterizeState.h"
#include "JaxResouceManager.h"
#include "JaxProperty.h"

namespace Jax
{
	IMPLEMENT_RTTI(JaxRasterizeState, JaxBind)
	JaxRasterizeStatePtr JaxRasterizeState::Default;
	JaxRasterizeStatePtr JaxRasterizeState::ScissorEnable;
	BEGIN_ADD_PROPERTY(JaxRasterizeState,JaxBind)
	REGISTER_PROPERTY(m_RasterizeDesc,RasterizeDesc,JaxProperty::F_SAVE_LOAD_CLONE)
	END_ADD_PROPERTY
	IMPLEMENT_INITIAL_BEGIN(JaxRasterizeState)
	ADD_INITIAL_FUNCTION_WITH_PRIORITY(InitialDefaultState)
	ADD_TERMINAL_FUNCTION(TerminalDefaultState)
	IMPLEMENT_INITIAL_END

	bool JaxRasterizeState::InitialDefaultState()
	{
		JaxRasterizeDesc desc;
		Default = JaxResourceManager::CreateRasterizeState(desc);
		if (!Default) return false;
		desc.m_bScissorTestEnable = true;
		ScissorEnable = JaxResourceManager::CreateRasterizeState(desc);
		if (!ScissorEnable) return false;
		return true;
	}


	bool JaxRasterizeState::TerminalDefaultState()
	{
		Default = NULL;
		ScissorEnable = NULL;
		return false;
	}

	JaxRasterizeState::JaxRasterizeState()
	{
		m_bIsStatic = true;
	}

	JaxRasterizeState::~JaxRasterizeState()
	{

	}

	IMPLEMENT_RTTI(JaxRasterizeDesc,JaxObject)
	BEGIN_ADD_PROPERTY(JaxRasterizeDesc,JaxObject)
	REGISTER_PROPERTY(m_bWireEnable, WireEnable, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiCullType, CullType, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_bClipPlaneEnable, ClipPlaneEnable, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_bScissorTestEnable, ScissorTestEnable, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_fDepthBias, DepthBias, JaxProperty::F_SAVE_LOAD_CLONE)
	END_ADD_PROPERTY
	IMPLEMENT_INITIAL_BEGIN(JaxRasterizeDesc)
	IMPLEMENT_INITIAL_END

}
