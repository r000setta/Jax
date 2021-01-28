#include "JaxDepthStencilState.h"
#include "JaxResouceManager.h"
#include "JaxProperty.h"
namespace Jax
{
	IMPLEMENT_RTTI(JaxDepthStencilState,JaxBind)
	JaxPointer<JaxDepthStencilState> JaxDepthStencilState::Default;
	BEGIN_ADD_PROPERTY(JaxDepthStencilState,JaxBind)
	REGISTER_PROPERTY(m_DepthStencilDesc,DepthStencilDesc,JaxProperty::F_SAVE_LOAD_CLONE)
	END_ADD_PROPERTY
	IMPLEMENT_INITIAL_BEGIN(JaxDepthStencilState)
	ADD_INITIAL_FUNCTION_WITH_PRIORITY(InitialDefaultState)
	ADD_TERMINAL_FUNCTION_WITH_PRIORITY(TerminalDefaultState)
	IMPLEMENT_INITIAL_END

	bool JaxDepthStencilState::InitialDefaultState()
	{
		JaxDepthStencilDesc desc;
		Default = JaxResourceManager::CreateDepthStencilState(desc);
		if (!Default) return false;
		return true;
	}

	bool JaxDepthStencilState::TerminalDefaultState()
	{
		Default = NULL;
		return true;
	}

	JaxDepthStencilState::JaxDepthStencilState()
	{
		m_bIsStatic = 1;
	}

	bool JaxDepthStencilState::OnLoadResource(JaxResourceIdentifier*& id)
	{
		if (!m_pUser)
			return false;
		if(!m_pUser->OnLoad)
	}

	JaxDepthStencilState::~JaxDepthStencilState()
	{

	}

	IMPLEMENT_RTTI(JaxDepthStencilDesc,JaxObject)
	BEGIN_ADD_PROPERTY(JaxDepthStencilDesc,JaxObject)
	REGISTER_PROPERTY(m_bDepthEnable,DepthStencil,JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_bDepthWritable,DepthWritable,JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiDepthCompareMethod, DepthCompareMethod, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_bStencilEnable, StencilEnable, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiStencilCompareMethod, StencilCompareMethod, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiReference, Reference, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiMask, Mask, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiWriteMask, WriteMask, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiSPassZPassOP, SPassZPassOP, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiSPassZFailOP, SPassZFailOP, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiSFailZPassOP, SFailZPassOP, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiCCW_SPassZPassOP, CCW_SPassZPassOP, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiCCW_SPassZFailOP, CCW_SPassZFailOP, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiCCW_SFailZPassOP, CCW_SFailZPassOP, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_bTwoSideStencilMode, TwoSideStencilMode, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiCCW_StencilCompareMethod, CCW_StencilCompareMethod, JaxProperty::F_SAVE_LOAD_CLONE)
	END_ADD_PROPERTY
	IMPLEMENT_INITIAL_BEGIN(JaxDepthStencilDesc)
	IMPLEMENT_INITIAL_END
}
