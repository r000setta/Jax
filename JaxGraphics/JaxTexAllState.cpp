#include "JaxTexAllState.h"
#include "Jax2DTexture.h"
#include "JaxResouceManager.h"
#include "JaxStream.h"
#include "JaxProperty.h"
namespace Jax
{
	IMPLEMENT_RTTI(JaxTexAllState, JaxObject);
	JaxTexAllStatePtr JaxTexAllState::Default;
	bool JaxTexAllState::sm_bIsEnableASYNLoader = true;
	BEGIN_ADD_PROPERTY(JaxTexAllState,JaxObject)
	REGISTER_PROPERTY(m_pTex,Tex,JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_SamplerDesc,SamplerDesc,JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_bSRGB,bSRGB,JaxProperty::F_SAVE_LOAD_CLONE)
	END_ADD_PROPERTY
	IMPLEMENT_INITIAL_BEGIN(JaxTexAllState,JaxObject)
	ADD_PRIORITY(Jax2DTexture)
	ADD_PRIORITY(JaxSamplerState)
	ADD_PRIORITY(JaxResourceManager)
	ADD_INITIAL_FUNCTION_WITH_PRIORITY(InitialDefaultState)
	ADD_TERMINAL_FUNCTION(TerminalDefaultState)
	IMPLEMENT_INITIAL_END

	void JaxTexAllState::SetSRGBEnable(bool enable)
	{
		m_bSRGB = enable;
		if (m_pTex)
		{
			m_pTex->m_bSRGB = m_bSRGB;
		}
	}

	JaxTexAllState::JaxTexAllState(JaxTexture* texture)
	{
		m_pTex = texture;
		m_pSamplerState = (JaxSamplerState*)JaxSamplerState::GetDefault();
		m_bSRGB = true;
		if (m_pTex)
		{
			m_pTex->m_bSRGB = m_bSRGB;
		}
	}

	JaxTexAllState::~JaxTexAllState()
	{
		m_pTex = nullptr;
		m_pSamplerState = nullptr;
	}

	JaxTexAllState::JaxTexAllState():m_pTex(nullptr),m_pSamplerState(nullptr),
		m_bSRGB(false)
	{
	}

	bool JaxTexAllState::InitialDefaultState()
	{
		JaxSamplerDesc desc;
		desc.m_uiMax = JaxSamplerDesc::FM_LINE;
		desc.m_uiMin = JaxSamplerDesc::FM_LINE;
		desc.m_uiMip = JaxSamplerDesc::FM_LINE;
		JaxSamplerStatePtr state = JaxResourceManager::CreateSamplerState(desc);
		JaxFileName fileName = JaxResourceManager::sm_TexturePath + _T("Default.bmp");
		Default = JaxResourceManager::Load2DTexture(fileName.GetBuffer(), state);
		if (!Default)
			return false;
		return true;
	}

	bool JaxTexAllState::TerminalDefaultState()
	{
		Default = nullptr;
		return true;
	}

	void JaxTexAllState::SetSRGBEnable(bool enable)
	{
		m_bSRGB = enable;
		if (m_pTex)
		{
			m_pTex->m_bSRGB = m_bSRGB;
		}
	}

	bool JaxTexAllState::PostLoad(void* data)
	{
		JaxObject::PostLoad(data);
		m_pSamplerState = JaxResourceManager::CreateSamplerState(m_SamplerDesc);
		if (m_pTex)
		{
			m_pTex->m_bSRGB = m_bSRGB;
		}
		return true;
	}

	bool JaxTexAllState::PostClone(JaxObject* src)
	{
		JaxObject::PostClone(src);
		m_pSamplerState = JaxResourceManager::CreateSamplerState(m_SamplerDesc);
		if (m_pTex)
		{
			m_pTex->m_bSRGB = m_bSRGB;
		}
		return true;
	}

}
