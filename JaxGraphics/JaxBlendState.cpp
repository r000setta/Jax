#include "JaxBlendState.h"
#include "JaxResouceManager.h"
#include "JaxProperty.h"

namespace Jax
{
	IMPLEMENT_RTTI(JaxBlendState, JaxBind)
	JaxPointer<JaxBlendState> JaxBlendState::Default;
	BEGIN_ADD_PROPERTY(JaxBlendState,JaxBind)
	REGISTER_PROPERTY(m_BlendDesc,BlendDesc,JaxProperty::F_SAVE_LOAD_CLONE)
	END_ADD_PROPERTY
	IMPLEMENT_INITIAL_BEGIN(JaxBlendState)
	ADD_INITIAL_FUNCTION_WITH_PRIORITY(InitialDefaultState)
	ADD_TERMINAL_FUNCTION(TerminalDefaultState)
	IMPLEMENT_INITIAL_END

	JaxBlendState::JaxBlendState()
	{
		m_bIsStatic = true;
	}

	JaxBlendState::~JaxBlendState()
	{

	}

	bool JaxBlendState::InitialDefaultState()
	{
		JaxBlendDesc desc;
		Default = JaxResourceManager::CreateBlendState(desc);
		if (!Default) return false;
		return true;
	}

	bool JaxBlendState::TerminalDefaultState()
	{
		Default = NULL;
		return true;
	}

	IMPLEMENT_RTTI(JaxBlendDesc,JaxObject)
	BEGIN_ADD_PROPERTY(JaxBlendDesc,JaxObject)
	REGISTER_PROPERTY(bBlendEnable[0], BlendEnable0, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucSrcBlend[0], SrcBlend0, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucDestBlend[0], DestBlend0, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucBlendOp[0], BlendOp0, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(bAlphaBlendEnable[0], AlphaBlendEnable0, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucSrcBlendAlpha[0], SrcBlendAlpha0, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucDestBlendAlpha[0], DestBlendAlpha0, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucBlendOpAlpha[0], BlendOpAlpha0, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucWriteMask[0], WriteMask0, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(bBlendEnable[1], BlendEnable1, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucSrcBlend[1], SrcBlend1, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucDestBlend[1], DestBlend1, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucBlendOp[1], BlendOp1, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(bAlphaBlendEnable[1], AlphaBlendEnable1, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucSrcBlendAlpha[1], SrcBlendAlpha1, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucDestBlendAlpha[1], DestBlendAlpha1, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucBlendOpAlpha[1], BlendOpAlpha1, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucWriteMask[1], WriteMask1, JaxProperty::F_SAVE_LOAD_CLONE)

	REGISTER_PROPERTY(bBlendEnable[2], BlendEnable2, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucSrcBlend[2], SrcBlend2, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucDestBlend[2], DestBlend2, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucBlendOp[2], BlendOp2, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(bAlphaBlendEnable[2], AlphaBlendEnable2, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucSrcBlendAlpha[2], SrcBlendAlpha2, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucDestBlendAlpha[2], DestBlendAlpha2, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucBlendOpAlpha[2], BlendOpAlpha2, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucWriteMask[2], WriteMask2, JaxProperty::F_SAVE_LOAD_CLONE)

	REGISTER_PROPERTY(bBlendEnable[3], BlendEnable3, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucSrcBlend[3], SrcBlend3, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucDestBlend[3], DestBlend3, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucBlendOp[3], BlendOp3, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(bAlphaBlendEnable[3], AlphaBlendEnable3, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucSrcBlendAlpha[3], SrcBlendAlpha3, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucDestBlendAlpha[3], DestBlendAlpha3, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucBlendOpAlpha[3], BlendOpAlpha3, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucWriteMask[3], WriteMask3, JaxProperty::F_SAVE_LOAD_CLONE)

	REGISTER_PROPERTY(bBlendEnable[4], BlendEnable4, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucSrcBlend[4], SrcBlend4, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucDestBlend[4], DestBlend4, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucBlendOp[4], BlendOp4, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(bAlphaBlendEnable[4], AlphaBlendEnable4, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucSrcBlendAlpha[4], SrcBlendAlpha4, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucDestBlendAlpha[4], DestBlendAlpha4, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucBlendOpAlpha[4], BlendOpAlpha4, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucWriteMask[4], WriteMask4, JaxProperty::F_SAVE_LOAD_CLONE)

	REGISTER_PROPERTY(bBlendEnable[5], BlendEnable5, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucSrcBlend[5], SrcBlend5, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucDestBlend[5], DestBlend5, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucBlendOp[5], BlendOp5, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(bAlphaBlendEnable[5], AlphaBlendEnable5, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucSrcBlendAlpha[5], SrcBlendAlpha5, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucDestBlendAlpha[5], DestBlendAlpha5, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucBlendOpAlpha[5], BlendOpAlpha5, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucWriteMask[5], WriteMask5, JaxProperty::F_SAVE_LOAD_CLONE)

	REGISTER_PROPERTY(bBlendEnable[6], BlendEnable6, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucSrcBlend[6], SrcBlend6, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucDestBlend[6], DestBlend6, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucBlendOp[6], BlendOp6, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(bAlphaBlendEnable[6], AlphaBlendEnable6, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucSrcBlendAlpha[6], SrcBlendAlpha6, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucDestBlendAlpha[6], DestBlendAlpha6, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucBlendOpAlpha[6], BlendOpAlpha6, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucWriteMask[6], WriteMask6, JaxProperty::F_SAVE_LOAD_CLONE)

	REGISTER_PROPERTY(bBlendEnable[7], BlendEnable7, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucSrcBlend[7], SrcBlend7, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucDestBlend[7], DestBlend7, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucBlendOp[7], BlendOp7, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(bAlphaBlendEnable[7], AlphaBlendEnable7, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucSrcBlendAlpha[7], SrcBlendAlpha7, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucDestBlendAlpha[7], DestBlendAlpha7, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucBlendOpAlpha[7], BlendOpAlpha7, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(ucWriteMask[7], WriteMask7, JaxProperty::F_SAVE_LOAD_CLONE)

	REGISTER_PROPERTY(bAlphaToCoverageEnable, AlphaToCoverageEnable, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(bIndependentBlendEnable, IndependentBlendEnable, JaxProperty::F_SAVE_LOAD_CLONE)

	END_ADD_PROPERTY
	IMPLEMENT_INITIAL_BEGIN(JaxBlendDesc)
	IMPLEMENT_INITIAL_END
}

