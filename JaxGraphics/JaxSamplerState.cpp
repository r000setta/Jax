#include "JaxSamplerState.h"
#include "JaxResouceManager.h"
#include "JaxStream.h"
#include "JaxProperty.h"

namespace Jax
{
	IMPLEMENT_RTTI(JaxSamplerState, JaxBind)
	JaxPointer<JaxSamplerState> JaxSamplerState::Default;
	JaxPointer<JaxSamplerState> JaxSamplerState::DoubleLine;
	JaxPointer<JaxSamplerState> JaxSamplerState::TriLine;
	JaxPointer<JaxSamplerState> JaxSamplerState::ShadowMapSampler;
	JaxPointer<JaxSamplerState> JaxSamplerState::BorderARGB0Sampler;
	JaxPointer<JaxSamplerState> JaxSamplerState::LightFunctionSampler;
	BEGIN_ADD_PROPERTY(JaxSamplerState,JaxBind)
	REGISTER_PROPERTY(m_SamplerDesc,SamplerDesc,JaxProperty::F_SAVE_LOAD_CLONE)
	END_ADD_PROPERTY
	IMPLEMENT_INITIAL_BEGIN(JaxSamplerState)
	ADD_INITIAL_FUNCTION_WITH_PRIORITY(InitialDefaultState)
	ADD_TERMINAL_FUNCTION(TerminalDefaultState)
	IMPLEMENT_INITIAL_END

	bool JaxSamplerState::InitialClassFactory()
	{
		JaxSamplerDesc desc;
		Default=JaxResourceManager::CreateSampl
	}

	bool JaxSamplerState::TerminalDefaultState()
	{
		Default = NULL;
		DoubleLine = NULL;
		TriLine = NULL;
		ShadowMapSampler = NULL;
		BorderARGB0Sampler = NULL;
		LightFunctionSampler = NULL;
	}

	IMPLEMENT_RTTI(JaxSamplerDesc,JaxObject)
	BEGIN_ADD_PROPERTY(JaxSamplerDesc,JaxObject)
	REGISTER_PROPERTY(m_uiMax, Max, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiMin, Min, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiMip, Mip, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiMipLevel, MipLevel, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiAniLevel, AniLevel, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiCoordU, CoordU, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiCoordV, CoordV, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiCoordW, CoordW, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_BorderColor, BorderColor, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_MipLODBias, MipLODBias, JaxProperty::F_SAVE_LOAD_CLONE)
	END_ADD_PROPERTY
	IMPLEMENT_INITIAL_BEGIN(JaxSamplerDesc)
	IMPLEMENT_INITIAL_END
}