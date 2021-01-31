#pragma once

#include <d3d11.h>
#include "JaxBind.h"
#include "JaxDx11Renderer.h"

namespace Jax
{
	class JAXDX11RENDERER_API JaxSamplerStateID :public JaxResourceIdentifier
	{
	public:
		ID3D11SamplerState* m_pSamplerState;
		JaxSamplerStateID() :m_pSamplerState(nullptr) {}
		virtual ~JaxSamplerStateID()
		{
			JAXMAC_RELEASE(m_pSamplerState);
		}
	};

	class JAXDX11RENDERER_API JaxBlendStateID :public JaxResourceIdentifier
	{
	public:
		ID3D11BlendState* m_pBlendState;
		JaxBlendStateID() :m_pBlendState(nullptr) {}
		virtual ~JaxBlendStateID()
		{
			JAXMAC_RELEASE(m_pBlendState);
		}
	};

	class JAXDX11RENDERER_API JaxRasterStateID :public JaxResourceIdentifier
	{
	public:
		ID3D11RasterizerState* m_pRasterState;
		JaxRasterStateID() :m_pRasterState(nullptr) {}
		virtual ~JaxRasterStateID()
		{
			JAXMAC_RELEASE(m_pRasterState);
		}
	};

	class JAXDX11RENDERER_API JaxDepthStencilStateID :public JaxResourceIdentifier
	{
	public:
		ID3D11DepthStencilState* m_pDepthStencilState;
		JaxDepthStencilStateID() :m_pDepthStencilState(nullptr) {}
		virtual ~JaxDepthStencilStateID()
		{
			JAXMAC_RELEASE(m_pDepthStencilState);
		}
	};

	class JAXDX11RENDERER_API JaxRenderTargetID :public JaxResourceIdentifier
	{
	public:
		JaxRenderTargetID() :
			m_pSaveRenderTarget(nullptr), m_pSaveDepthStencilBuffer(nullptr),
			m_pRenderTarget(nullptr), m_pTextureSurface(nullptr), m_pStagTexture(nullptr)
		{}

		~JaxRenderTargetID()
		{
			JAXMAC_RELEASE(m_pRenderTarget);
			JAXMAC_RELEASE(m_pTextureSurface);
			JAXMAC_RELEASE(m_pStagTexture);
			m_pOldTexture = nullptr;
			m_pSaveRenderTarget = nullptr;
			m_pSaveDepthStencilBuffer = nullptr;
		}

		ID3D11Resource* m_pOldTexture;
		ID3D11Resource* m_pTextureSurface;
		ID3D11RenderTargetView* m_pRenderTarget;
		ID3D11RenderTargetView* m_pSaveRenderTarget;
		ID3D11RenderTargetView* m_pSaveDepthStencilBuffer;
		ID3D11Resource* m_pStagTexture;
	};

	class JAXDX11RENDERER_API JaxTextureID :public JaxResourceIdentifier
	{
	public:
		ID3D11Resource* m_pTexture;
		ID3D11ShaderResourceView* m_pShaderResourceView;

		JaxTextureID() :m_pTexture(nullptr), m_pShaderResourceView(nullptr)
		{}

		virtual ~JaxTextureID()
		{
			JAXMAC_RELEASE(m_pShaderResourceView);
			JAXMAC_RELEASE(m_pTexture);
		}
	};

	class JAXDX11RENDERER_API JaxDepthStencilID :public JaxResourceIdentifier
	{
	public:
		ID3D11Resource* m_pTexture;
		ID3D11DepthStencilView* m_pDepthStencilBuffer;
		ID3D11DepthStencilView* m_pSaveDepthStencilBuffer;

		JaxDepthStencilID() :
			m_pTexture(nullptr), m_pDepthStencilBuffer(nullptr), m_pSaveDepthStencilBuffer(nullptr)
		{}

		~JaxDepthStencilID()
		{
			JAXMAC_RELEASE(m_pDepthStencilBuffer);
			JAXMAC_RELEASE(m_pTexture);
			m_pSaveDepthStencilBuffer = nullptr;
		}
	};

	class JAXDX11RENDERER_API JaxVBufferID :public JaxResourceIdentifier
	{
	public:
		ID3D11Buffer* m_pVertexBuffer;

		JaxVBufferID() :m_pVertexBuffer(nullptr)
		{}

		virtual ~JaxVBufferID()
		{
			JAXMAC_RELEASE(m_pVertexBuffer);
		}
	};

	class JAXDX11RENDERER_API JaxVBufferFormatID :public JaxResourceIdentifier
	{
	public:
		ID3D11InputLayout* m_pDeclaration;

		JaxVBufferFormatID() :m_pDeclaration(nullptr)
		{}

		virtual ~JaxVBufferFormatID()
		{
			JAXMAC_RELEASE(m_pDeclaration);
		}
	};

	class JAXDX11RENDERER_API JaxIBufferID :public JaxResourceIdentifier
	{
	public:
		ID3D11Buffer* m_IndexBuffer;
		JaxIBufferID() :m_IndexBuffer(nullptr)
		{}

		virtual ~JaxIBufferID()
		{
			JAXMAC_RELEASE(m_IndexBuffer);
		}
	};
}