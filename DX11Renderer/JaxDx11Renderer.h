#pragma once
#ifdef JAXDX11RENDERER_EXPORTS
#define JAXDX11RENDERER_API __declspec(dllexport)
#else
#define JAXDX11RENDERER_API __declspec(dllimport)
#endif 

#include <d3d11.h>
#include <dxgi.h>
#include <d3dcompiler.h>
#include "JaxRenderer.h"
#include "JaxResouceManager.h"

namespace Jax
{

#define JAXMAC_RELEASE(p) { if(p) { (p)->Release(); (p)=NULL; } }

	class JAXDX11RENDERER_API JaxDX11Renderer :public JaxRenderer
	{
		JaxDX11Renderer(HWND hMainWindow, size_t screenWidth, size_t screenHeight, bool isWindowed,
			size_t anisotropy, size_t multisample, ChildWindowInfo* childWindow, int numChildWindow);
		virtual ~JaxDX11Renderer();
		virtual int GetRendererType() const;
		virtual const TCHAR* GetRendererStringType();

	protected:
		static IDXGIFactory* sm_pDXGI;
		ID3D11Device* m_pDevice;
		ID3D11DeviceContext* m_pDeviceContext;
		IDXGIAdapter* m_pAdapter;
		IDXGIOutput* m_pAdapterOutput;
		IDXGISwapChain** m_pChain;
		IDXGISwapChain* m_pMainChain;
		DXGI_SWAP_CHAIN_DESC m_SwapChainDesc;

		ID3D11RenderTargetView* m_pMainRenderTargetView;
		ID3D11RenderTargetView** m_pChainRenderTargetView;

		static DWORD sm_dwAlphaBlend[];
		static DWORD sm_dwAlphaBlendOP[];
		static DWORD sm_dwCullType[];
		static DWORD sm_dwStencilOperation[];
		static DWORD sm_dwCompare[];
		static DWORD sm_dwTextureFormatType[];
		static DWORD sm_dwSRGBTextureFormatType[];

		static DWORD sm_dwTextureAddrType[];
		static DWORD sm_dwPrimitiveType[];
		static DWORD sm_dwDevTypes[];
		static DWORD sm_dwMultiSampleTypes[];
		static DWORD sm_dwLockFlag[];
		static DWORD sm_dwVertexFormatDateType[];
		static TCHAR* sm_dwVertexFormatClareType[];
		static TCHAR* sm_dwVertexFormatSemantics[];
		static unsigned int sm_uiVertexShaderProgramVersion;
		static unsigned int sm_uiPixelShaderProgramVersion;
		static TCHAR sm_cVertexShaderProgramVersion[];
		static TCHAR sm_cPixelShaderProgramVersion[];
		static TCHAR sm_cGeometryShaderProgramVersion[];
		static TCHAR sm_cGDomainShaderProgramVersion[];
		static TCHAR sm_cHullShaderProgramVersion[];
		
		DECLARE_PRIORITY
		DECLARE_INITIAL_ONLY

		static bool InitialDefaultState();
		static bool TerminalDefaultState();

	public:
		virtual void ClearBuffers(size_t clearFlag);
		virtual void ClearBackBuffer();
		virtual void ClearZBuffer();
		virtual void ClearStencilBuffer();
		virtual void ClearBuffers();

	};
}