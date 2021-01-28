#include "JaxRenderer.h"
#include "JaxTexture.h"
#include "Jax2DTexture.h"
#include "JaxBlendState.h"
#include "JaxSamplerState.h"
#include "JaxRasterizeState.h"
#include "JaxDepthStencilState.h"

namespace Jax
{

	JaxRenderer* JaxRenderer::sm_pRenderer = NULL;
	size_t JaxRenderer::sm_uiBytesPerPixel[SFT_MAX] =
	{
		4,
		2,
		4,
		4,
		16,
		8,
		4,
		2,
		4,
		4,
		4,
		8,
		2,
		1,
		16,
		16
	};
	size_t JaxRenderer::sm_uiChannelPerPixel[SFT_MAX] =
	{
		4,
		1,
		2,
		1,
		4,
		4,
		2,
		1,
		1,
		4,
		2,
		2,
		3,
		1,
		4,
		4
	};

	JaxRenderer::JaxRenderer()
	{
		m_pChildWindowInfo = NULL;
		m_ClearColor.Set(1.0f, 1.0f, 1.0f, 1.0f);
		m_fClearDepth = 1.0f;
		m_uiClearStencil = 0;

		m_iNumChildWindow = 0;
		m_iCurWindowID = -1;
		m_bIsRendering = false;
	}

	size_t JaxRenderer::GetBytesPerPixel(size_t formatType)
	{
		if (formatType >= SFT_MAX)
		{
			return 0;
		}
		return sm_uiBytesPerPixel[formatType];
	}

	size_t JaxRenderer::SetTexture(JaxTexture* texture, size_t i)
	{
		JAX_ASSERT(i < TEXLEVEL);
		if (!CheckIsTextureCanSet(texture))
		{
			return FRI_FAIL;
		}
		if (m_pPTex[i] == texture)
		{
			if (!texture)
			{
				return FRI_SAMESOURCE;
			}
			else if (texture && texture->GetSwapChainNum() == 1)
			{
				return FRI_SAMESOURCE;
			}
		}
		if (!texture)
		{

		}
		if (!LoadTexture(texture))
		{
			m_pPTex[i] = NULL;
			return FRI_FAIL;
		}

		m_pPTex[i] = texture;
		return true;
	}

	size_t JaxRenderer::SetVTexture(JaxTexture* texture, size_t i)
	{
		JAX_ASSERT(i < TEXLEVEL);
		if (!CheckIsTextureCanSet(texture))
		{
			return FRI_FAIL;
		}
		if (m_pVTex[i] == texture)
		{
			if (!texture)
			{
				return FRI_SAMESOURCE;
			}
			else if (texture && texture->GetSwapChainNum() == 1)
			{
				return FRI_SAMESOURCE;
			}
		}
		if (!texture)
		{

		}
		if (!LoadTexture(texture))
		{
			m_pVTex[i] = NULL;
			return FRI_FAIL;
		}

		m_pVTex[i] = texture;
		return true;
	}

	size_t JaxRenderer::SetGTexture(JaxTexture* texture, size_t i)
	{
		JAX_ASSERT(i < TEXLEVEL);
		if (!CheckIsTextureCanSet(texture))
		{
			return FRI_FAIL;
		}
		if (m_pGTex[i] == texture)
		{
			if (!texture)
			{
				return FRI_SAMESOURCE;
			}
			else if (texture && texture->GetSwapChainNum() == 1)
			{
				return FRI_SAMESOURCE;
			}
		}
		if (!texture)
		{

		}
		if (!LoadTexture(texture))
		{
			m_pGTex[i] = NULL;
			return FRI_FAIL;
		}

		m_pGTex[i] = texture;
		return true;
	}

	size_t JaxRenderer::SetDTexture(JaxTexture* texture, size_t i)
	{
		JAX_ASSERT(i < TEXLEVEL);
		if (!CheckIsTextureCanSet(texture))
		{
			return FRI_FAIL;
		}
		if (m_pDTex[i] == texture)
		{
			if (!texture)
			{
				return FRI_SAMESOURCE;
			}
			else if (texture && texture->GetSwapChainNum() == 1)
			{
				return FRI_SAMESOURCE;
			}
		}
		if (!texture)
		{

		}
		if (!LoadTexture(texture))
		{
			m_pDTex[i] = NULL;
			return FRI_FAIL;
		}

		m_pDTex[i] = texture;
		return true;
	}

	size_t JaxRenderer::SetHTexture(JaxTexture* texture, size_t i)
	{
		JAX_ASSERT(i < TEXLEVEL);
		if (!CheckIsTextureCanSet(texture))
		{
			return FRI_FAIL;
		}
		if (m_pHTex[i] == texture)
		{
			if (!texture)
			{
				return FRI_SAMESOURCE;
			}
			else if (texture && texture->GetSwapChainNum() == 1)
			{
				return FRI_SAMESOURCE;
			}
		}
		if (!texture)
		{

		}
		if (!LoadTexture(texture))
		{
			m_pHTex[i] = NULL;
			return FRI_FAIL;
		}

		m_pHTex[i] = texture;
		return true;
	}

	bool JaxRenderer::CheckIsTextureCanSet(JaxTexture* texture)
	{
		if (!texture)
		{
			return true;
		}
		if (texture->GetTexType() == JaxTexture::TT_2D)
		{
			if (((Jax2DTexture*)texture)->IsRenderTarget())
			{
				if (((Jax2DTexture*)texture)->m_bRtUsed == true)
				{
					return false;
				}
				else
				{
					return true;
				}
			}
		}
	}

	bool JaxRenderer::LoadBlendState(JaxBlendState* state)
	{
		if (!state) return false;
		state->LoadResource(this);
		return true;
	}

	bool JaxRenderer::ReleaseBlendState(JaxBlendState* state)
	{
		if (!state) return false;
		state->ReleaseResource();
		return true;
	}

	bool JaxRenderer::LoadDepthStencilState(JaxDepthStencilState* state)
	{
		if (!state) return false;
		state->LoadResource(this);
		return true;
	}

	bool JaxRenderer::ReleaseDepthStencilState(JaxDepthStencilState* state)
	{
		if (!state) return false;
		state->ReleaseResource();
		return true;
	}

	bool JaxRenderer::LoadRasterizeState(JaxRasterizeState* state)
	{
		if (!state) return false;
		state->LoadResource(this);
		return true;
	}

	bool JaxRenderer::ReleaseRasterizeState(JaxRasterizeState* state)
	{
		if (!state) return false;
		state->ReleaseResource();
		return true;
	}

	bool JaxRenderer::LoadSamplerState(JaxSamplerState* state)
	{
		if (!state) return false;
		state->LoadResource(this);
		return true;
	}

	bool JaxRenderer::ReleaseSamplerState(JaxSamplerState* state)
	{
		if (!state) return false;
		state->ReleaseResource();
		return true;
	}

	bool JaxRenderer::LoadTexture(JaxTexture* texture)
	{
		if (!texture) return false;
		return texture->LoadResource(this);
	}

	bool JaxRenderer::ReleaseTexture(JaxTexture* texture)
	{
		if (!texture) return false;
		return texture->ReleaseResource();
	}

	size_t JaxRenderer::SetBlendState(JaxBlendState* state, bool forceSet)
	{
		if (!state)
		{
			state = (JaxBlendState*)JaxBlendState::GetDefault();
		}
		if (!m_pBlendState)
		{
			m_pBlendState = (JaxBlendState*)JaxBlendState::GetDefault();
		}
		if (m_pBlendState == state && !forceSet)
		{
			return FRI_SAMESOURCE;
		}
		if (!LoadBlendState(state))
		{
			return FRI_FAIL;
		}
		return FRI_SUCCESS;
	}

	size_t JaxRenderer::SetDepthStencilState(JaxDepthStencilState* state, bool forceSet)
	{
		if (!state)
		{
			state = (JaxDepthStencilState*)JaxDepthStencilState::GetDefault();
		}
		if (!m_pDepthStencilState)
		{
			m_pDepthStencilState = (JaxDepthStencilState*)JaxDepthStencilState::GetDefault();
		}
		if (m_pDepthStencilState == state && !forceSet)
		{
			return FRI_SAMESOURCE;
		}
		if (!LoadDepthStencilState(state))
		{
			return FRI_FAIL;
		}
		return FRI_SUCCESS;
	}

	size_t JaxRenderer::SetRasterizeState(JaxRasterizeState* state, bool forceSet)
	{
		if (!state)
		{
			state = (JaxRasterizeState*)JaxRasterizeState::GetDefault();
		}
		if (!m_pRasterizeState)
		{
			m_pRasterizeState = (JaxRasterizeState*)JaxRasterizeState::GetDefault();
		}
		if (m_pRasterizeState == state && !forceSet)
		{
			return FRI_SAMESOURCE;
		}
		if (!LoadRasterizeState(state))
		{
			return FRI_FAIL;
		}
		return FRI_SUCCESS;
	}

	size_t JaxRenderer::SetSamplerState(JaxSamplerState* state, size_t i, bool forceSet)
	{
		if (!state)
		{
			state = (JaxSamplerState*)JaxSamplerState::GetDefault();
		}
		if (!m_pPSamplerState[i])
		{
			m_pPSamplerState[i] = (JaxSamplerState*)JaxSamplerState::GetDefault();
		}
		if (m_pPSamplerState[i] == state && forceSet == false)
		{
			return FRI_SAMESOURCE;
		}
		if (!LoadSamplerState(state))
		{
			return FRI_FAIL;
		}
		return FRI_SUCCESS;
	}

	size_t JaxRenderer::SetVSamplerState(JaxSamplerState* state, size_t i, bool forceSet)
	{
		if (!state)
		{
			state = (JaxSamplerState*)JaxSamplerState::GetDefault();
		}
		if (!m_pVSamplerState[i])
		{
			m_pVSamplerState[i] = (JaxSamplerState*)JaxSamplerState::GetDefault();
		}
		if (m_pVSamplerState[i] == state && forceSet == false)
		{
			return FRI_SAMESOURCE;
		}
		if (!LoadSamplerState(state))
		{
			return FRI_FAIL;
		}
		return FRI_SUCCESS;
	}

	size_t JaxRenderer::SetGSamplerState(JaxSamplerState* state, size_t i, bool forceSet)
	{
		if (!state)
		{
			state = (JaxSamplerState*)JaxSamplerState::GetDefault();
		}
		if (!m_pGSamplerState[i])
		{
			m_pGSamplerState[i] = (JaxSamplerState*)JaxSamplerState::GetDefault();
		}
		if (m_pGSamplerState[i] == state && forceSet == false)
		{
			return FRI_SAMESOURCE;
		}
		if (!LoadSamplerState(state))
		{
			return FRI_FAIL;
		}
		return FRI_SUCCESS;
	}

	size_t JaxRenderer::SetDSamplerState(JaxSamplerState* state, size_t i, bool forceSet)
	{
		if (!state)
		{
			state = (JaxSamplerState*)JaxSamplerState::GetDefault();
		}
		if (!m_pDSamplerState[i])
		{
			m_pDSamplerState[i] = (JaxSamplerState*)JaxSamplerState::GetDefault();
		}
		if (m_pDSamplerState[i] == state && forceSet == false)
		{
			return FRI_SAMESOURCE;
		}
		if (!LoadSamplerState(state))
		{
			return FRI_FAIL;
		}
		return FRI_SUCCESS;
	}

	size_t JaxRenderer::SetHSamplerState(JaxSamplerState* state, size_t i, bool forceSet)
	{
		if (!state)
		{
			state = (JaxSamplerState*)JaxSamplerState::GetDefault();
		}
		if (!m_pHSamplerState[i])
		{
			m_pHSamplerState[i] = (JaxSamplerState*)JaxSamplerState::GetDefault();
		}
		if (m_pHSamplerState[i] == state && forceSet == false)
		{
			return FRI_SAMESOURCE;
		}
		if (!LoadSamplerState(state))
		{
			return FRI_FAIL;
		}
		return FRI_SUCCESS;
	}

	size_t JaxRenderer::SetVertexFormat(JaxVertexFormat* format)
	{
		if (m_pVertexFormat == format)
			return FRI_SAMESOURCE;
		m_pVertexFormat = format;
		if (!format)
			return FRI_FAIL;
		return FRI_SUCCESS;
	}

	bool JaxRenderer::SetDefaultValue()
	{
		JAX_ASSERT(m_uiMaxTexture);
		for (size_t i = 0; i < m_uiMaxTexture; ++i)
		{
			m_pPTex[i] = NULL;
			m_pPSamplerState[i] = (JaxSamplerState*)JaxSamplerState::GetDefault();
			SetSamplerState(NULL, i, true);
		}
		JAX_ASSERT(m_uiMaxTexture);
		for (size_t i = 0; i < m_uiMaxTexture; ++i)
		{
			m_pVTex[i] = NULL;
			m_pVSamplerState[i] = (JaxSamplerState*)JaxSamplerState::GetDefault();
			SetVSamplerState(NULL, i, true);
		}

		for (size_t i = 0; i < m_uiMaxTexture; ++i)
		{
			m_pGTex[i] = NULL;
			m_pGSamplerState[i] = (JaxSamplerState*)JaxSamplerState::GetDefault();
			SetGSamplerState(NULL, i, true);
		}

		for (size_t i = 0; i < m_uiMaxTexture; ++i)
		{
			m_pDTex[i] = NULL;
			m_pDSamplerState[i] = (JaxSamplerState*)JaxSamplerState::GetDefault();
			SetDSamplerState(NULL, i, true);
		}

		for (size_t i = 0; i < m_uiMaxTexture; ++i)
		{
			m_pHTex[i] = NULL;
			m_pHSamplerState[i] = (JaxSamplerState*)JaxSamplerState::GetDefault();
			SetHSamplerState(NULL, i, true);
		}
		m_pBlendState = (JaxBlendState*)JaxBlendState::GetDefault();
		m_pDepthStencilState = (JaxDepthStencilState*)JaxDepthStencilState::GetDefault();
		m_pRasterizeState = (JaxRasterizeState*)JaxRasterizeState::GetDefault();
		SetDepthStencilState(NULL, true);
		SetBlendState(NULL, true);
		SetRasterizeState(NULL, true);
		m_bClipPlaneEnable = false;
		m_bScissorRectEnable = false;

		SetTexture(JaxTE)
	}

}
