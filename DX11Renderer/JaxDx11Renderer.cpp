#include "JaxDx11Renderer.h"

namespace Jax
{
	TCHAR JaxDX11Renderer::sm_cVertexShaderProgramVersion[] = _T("vs_5_0");
	TCHAR JaxDX11Renderer::sm_cPixelShaderProgramVersion[] = _T("ps_5_0");
	TCHAR JaxDX11Renderer::sm_cGeometryShaderProgramVersion[] = _T("gs_5_0");
	TCHAR JaxDX11Renderer::sm_cGDomainShaderProgramVersion[] = _T("ds_5_0");
	TCHAR JaxDX11Renderer::sm_cHullShaderProgramVersion[] = _T("hs_5_0");
	DWORD JaxDX11Renderer::sm_dwAlphaBlend[] =
	{
		D3D11_BLEND_ZERO,
		D3D11_BLEND_ONE,
		D3D11_BLEND_SRC_COLOR,
		D3D11_BLEND_INV_SRC_COLOR,
		D3D11_BLEND_SRC_ALPHA,
		D3D11_BLEND_INV_SRC_ALPHA,
		D3D11_BLEND_DEST_ALPHA,
		D3D11_BLEND_INV_DEST_ALPHA,
		D3D11_BLEND_DEST_COLOR,
		D3D11_BLEND_INV_DEST_COLOR
	};
	DWORD JaxDX11Renderer::sm_dwAlphaBlendOP[] =
	{
		D3D11_BLEND_OP_ADD,
		D3D11_BLEND_OP_SUBTRACT,
		D3D11_BLEND_OP_REV_SUBTRACT,
		D3D11_BLEND_OP_MIN,
		D3D11_BLEND_OP_MAX
	};
	DWORD JaxDX11Renderer::sm_dwCullType[] =
	{
		D3D11_CULL_NONE,
		D3D11_CULL_FRONT,
		D3D11_CULL_BACK
	};
	DWORD JaxDX11Renderer::sm_dwStencilOperation[] =
	{
		D3D11_STENCIL_OP_KEEP,
		D3D11_STENCIL_OP_ZERO,
		D3D11_STENCIL_OP_REPLACE,
		D3D11_STENCIL_OP_INCR,
		D3D11_STENCIL_OP_DECR,
		D3D11_STENCIL_OP_INVERT,
		D3D11_STENCIL_OP_INCR_SAT,
		D3D11_STENCIL_OP_DECR_SAT
	};
	DWORD JaxDX11Renderer::sm_dwCompare[] =
	{
		D3D11_COMPARISON_NEVER,
		D3D11_COMPARISON_LESS,
		D3D11_COMPARISON_EQUAL,
		D3D11_COMPARISON_LESS_EQUAL,
		D3D11_COMPARISON_GREATER,
		D3D11_COMPARISON_NOT_EQUAL,
		D3D11_COMPARISON_GREATER_EQUAL,
		D3D11_COMPARISON_ALWAYS
	};
	DWORD JaxDX11Renderer::sm_dwTextureFormatType[] =
	{
		DXGI_FORMAT_B8G8R8A8_UNORM,
		DXGI_FORMAT_D16_UNORM,
		DXGI_FORMAT_R24_UNORM_X8_TYPELESS,
		DXGI_FORMAT_D24_UNORM_S8_UINT,
		DXGI_FORMAT_R32G32B32A32_FLOAT,
		DXGI_FORMAT_R16G16B16A16_FLOAT,
		DXGI_FORMAT_R16G16_FLOAT,
		DXGI_FORMAT_R16_FLOAT,
		DXGI_FORMAT_R32_FLOAT,
		DXGI_FORMAT_UNKNOWN,
		DXGI_FORMAT_D24_UNORM_S8_UINT,
		DXGI_FORMAT_R32G32_FLOAT,
		DXGI_FORMAT_B5G6R5_UNORM,
		DXGI_FORMAT_A8_UNORM,
		DXGI_FORMAT_BC2_UNORM,
		DXGI_FORMAT_BC3_UNORM

	};
	DWORD JaxDX11Renderer::sm_dwSRGBTextureFormatType[] =
	{
		DXGI_FORMAT_B8G8R8A8_UNORM_SRGB,
		DXGI_FORMAT_UNKNOWN,
		DXGI_FORMAT_UNKNOWN,
		DXGI_FORMAT_UNKNOWN,
		DXGI_FORMAT_UNKNOWN,
		DXGI_FORMAT_UNKNOWN,
		DXGI_FORMAT_UNKNOWN,
		DXGI_FORMAT_UNKNOWN,
		DXGI_FORMAT_UNKNOWN,
		DXGI_FORMAT_UNKNOWN,
		DXGI_FORMAT_UNKNOWN,
		DXGI_FORMAT_UNKNOWN,
		DXGI_FORMAT_UNKNOWN,
		DXGI_FORMAT_UNKNOWN,
		DXGI_FORMAT_BC2_UNORM_SRGB,
		DXGI_FORMAT_BC3_UNORM_SRGB
	};
	DWORD JaxDX11Renderer::sm_dwTextureAddrType[] =
	{
		D3D11_TEXTURE_ADDRESS_CLAMP,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_MIRROR,
		D3D11_TEXTURE_ADDRESS_BORDER,
	};

	DWORD JaxDX11Renderer::sm_dwPrimitiveType[] =
	{
		D3D11_PRIMITIVE_TOPOLOGY_POINTLIST,
		D3D11_PRIMITIVE_TOPOLOGY_LINELIST,
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
	};
	DWORD JaxDX11Renderer::sm_dwDevTypes[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_REFERENCE
	};
	DWORD JaxDX11Renderer::sm_dwMultiSampleTypes[] =
	{
		1 ,
		2 ,
		4 ,
		8 ,
		16
	};
	DWORD JaxDX11Renderer::sm_dwLockFlag[] =
	{
		D3D11_MAP_WRITE_NO_OVERWRITE,
		D3D11_MAP_WRITE_DISCARD,
		D3D11_MAP_READ
	};
	DWORD JaxDX11Renderer::sm_dwVertexFormatDateType[] =
	{
		DXGI_FORMAT_R32_FLOAT,
		DXGI_FORMAT_R32G32_FLOAT,
		DXGI_FORMAT_R32G32B32_FLOAT,
		DXGI_FORMAT_R32G32B32A32_FLOAT,

		DXGI_FORMAT_R16_UINT,
		DXGI_FORMAT_R32_UINT,

		DXGI_FORMAT_R8G8B8A8_UINT,
		DXGI_FORMAT_R8G8B8A8_UNORM,

		DXGI_FORMAT_R16G16_SINT,
		DXGI_FORMAT_R16G16_SNORM,
		DXGI_FORMAT_R16G16_UNORM,

		DXGI_FORMAT_R16G16B16A16_SINT,
		DXGI_FORMAT_R16G16B16A16_SNORM,
		DXGI_FORMAT_R16G16B16A16_UNORM,

		DXGI_FORMAT_R16G16_FLOAT,
		DXGI_FORMAT_R16G16B16A16_FLOAT,

		DXGI_FORMAT_R8G8B8A8_UNORM
	};
	TCHAR* JaxDX11Renderer::sm_dwVertexFormatClareType[] =
	{
		"float ",
		"float2 ",
		"float3 ",
		"float4 ",

		"uint ",
		"uint ",

		"uint4 ",
		"float4 ",

		"int2 ",
		"float2 ",
		"float2 ",

		"int4 ",
		"float4 ",
		"float4 ",

		"float2 ",
		"float4 ",

		"float4 "
	};
	TCHAR* JaxDX11Renderer::sm_dwVertexFormatSemantics[] =
	{
		"POSITION",
		"TEXCOORD",
		"NORMAL",
		"TANGENT",
		"BINORMAL",
		"PSIZE",
		"COLOR",
		"FOG",
		"SV_Depth",
		"BLENDWEIGHT",
		"BLENDINDICES"
	};

	IDXGIFactory* JaxDX11Renderer::sm_pDXGI = NULL;
	JaxDX11Renderer::JaxDX11Renderer(HWND hMainWindow, size_t screenWidth, size_t screenHeight, bool isWindowed, size_t anisotropy, size_t multisample, ChildWindowInfo* childWindow, int numChildWindow)
	{
		if (numChildWindow > 0 && childWindow && isWindowed)
		{
			m_pChildWindowInfo = JAX_NEW ChildWindowInfo[numChildWindow];
			JaxMemcpy(m_pChildWindowInfo, childWindow, sizeof(ChildWindowInfo) * numChildWindow);
			m_iNumChildWindow = numChildWindow;
		}
		else
		{
			m_iNumChildWindow = 0;
		}

		m_MainWindow = hMainWindow;
		m_bWindowed = isWindowed;
		m_uiScreenHeight = screenHeight;
		m_uiScreenWidth = screenWidth;
		m_uiCurRTHeight = screenHeight;
		m_uiCurRTWidth = screenWidth;

		HRESULT res = NULL;
		m_uinAdapter = 0;
		res = sm_pDXGI->EnumAdapters(m_uinAdapter, &m_pAdapter);
		JAX_ASSERT(SUCCEEDED(res));

		DXGI_ADAPTER_DESC adapterDesc;
		res = m_pAdapter->GetDesc(&adapterDesc);
		JAX_ASSERT(SUCCEEDED(res));
		res = m_pAdapter->EnumOutputs(0, &m_pAdapterOutput);
		JAX_ASSERT(SUCCEEDED(res));

		TCHAR name[128];
		JaxWcsToMbs(name, 128, adapterDesc.Description, 128);
		m_AdapterName = name;
		
		size_t deviceFlag = 0;
		deviceFlag |= D3D11_CREATE_DEVICE_SINGLETHREADED;
#ifdef DEBUG
		deviceFlag |= D3D11_CREATE_DEVICE_DEBUG;
#endif // DEBUG
		size_t numDriverTypes = ARRAYSIZE(sm_dwDevTypes);
		
		D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_11_1,
		};

		size_t numFeatureLevels = ARRAYSIZE(featureLevels);
		D3D_FEATURE_LEVEL outFeatureLevel;

		for (size_t i = 0; i < numDriverTypes; ++i)
		{
			res = D3D11CreateDevice(
				NULL,
				(D3D_DRIVER_TYPE)sm_dwDevTypes[i],
				NULL,
				deviceFlag,
				featureLevels,
				numFeatureLevels,
				D3D11_SDK_VERSION,
				&m_pDevice,
				&outFeatureLevel,
				&m_pDeviceContext);
			if (SUCCEEDED(res))
			{
				m_uiDevType = i;
				break;
			}
		}
		m_uiMaxMultisample = 0;
		size_t numMultisampleQualities = 0;
		for (size_t i = MS_MAX - 1; i >= MS_NONE; --i)
		{
			res = m_pDevice->CheckMultisampleQualityLevels((DXGI_FORMAT)sm_dwTextureFormatType[SFT_A8R8G8B8], 
				sm_dwMultiSampleTypes[i], &numMultisampleQualities);
			if (SUCCEEDED(res) && numMultisampleQualities > 0)
			{
				m_uiMaxMultisample = i;
				break;
			}
		}

		m_pMainChain = NULL;
	}
}