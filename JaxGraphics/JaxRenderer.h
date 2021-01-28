#pragma once
#include "JaxVector2.h"
#include "JaxVector4.h"
#include "JaxGraphic.h"
#include "JaxString.h"
#include "JaxRenderState.h"
#include "JaxPointer.h"
#include "JaxSamplerState.h"
#include "JaxVertexFormat.h"
namespace Jax
{
	class JaxBind;
	class JaxResourceIdentifier;

	DECLARE_PTR(JaxTexture);
	DECLARE_PTR(JaxVertexFormat);

	typedef struct JAXDISPLAYMODE
	{
		UINT uiWidth;
		UINT uiHeight;
		UINT uiRefreshState;
		UINT uiBitFormat;
	}JaxDisplayMode, * JaxDisplayModePtr;

	class JAXGRAPHIC_API JaxRenderer
	{
	public:
		JaxRenderer();
		virtual ~JaxRenderer() = 0;

		friend class JaxTexture;
		friend class JaxBlendState;
		friend class JaxDepthStencilState;
		friend class JaxRasterizeState;
		friend class JaxSamplerState;
		friend class JaxVertexFormat;
		enum
		{
			RAT_NULL,
			RAT_OPENGL,
			RAT_DX11,
			RAT_DX12,
			RAT_SOFTWARE,
			RAT_MAX
		};

		enum //Function return info
		{
			FRI_FAIL,
			FRI_SUCCESS,
			FRI_SAMESOURCE
		};
		
		virtual int GetRendererType() const = 0;
		virtual const TCHAR* GetRendererStringType() const = 0;

		FORCEINLINE void SetClearColor(const JaxColorRGBA& color)
		{
			m_ClearColor = color;
		}

		FORCEINLINE const JaxColorRGBA& GetClearColor() const
		{
			return m_ClearColor;
		}

		FORCEINLINE void SetClearDepth(JAXREAL depth)
		{
			m_fClearDepth = depth;
		}

		FORCEINLINE JAXREAL GetClearDepth() const
		{
			return m_fClearDepth;
		}

		FORCEINLINE void SetClearStencil(size_t value)
		{
			m_uiClearStencil = value;
		}

		FORCEINLINE size_t GetClearStencil() const
		{
			return m_uiClearStencil;
		}

		enum
		{
			MS_NONE,
			MS_2,
			MS_4,
			MS_8,
			MS_16,
			MS_MAX,
		};

		enum	//Surface Format Type
		{
			SFT_A8R8G8B8,      //BGRA
			SFT_D16,
			SFT_D24X8,
			SFT_D32,
			SFT_A32B32G32R32F, //RGBA
			SFT_A16B16G16R16F, //RGBA
			SFT_G16R16F,
			SFT_R16F,
			SFT_R32F,
			SFT_DISCARD,
			SFT_D24S8,
			SFT_G32R32F,//RG
			SFT_R5G6B5,//BGR
			SFT_A8,
			SFT_DXT3,	//BC2
			SFT_DXT5,	//BC3
			SFT_MAX
		};

		enum
		{
			CF_NONE = 0,
			CF_COLOR = 1 << 0,
			CF_DEPTH = 1 << 1,
			CF_STENCIL = 1 << 2,
			CF_USE_MAX = CF_COLOR | CF_DEPTH | CF_STENCIL
		};

		virtual void ClearBuffers(size_t clearFlag) = 0;
		virtual void ClearBackBuffer() = 0;
		virtual void ClearZBuffer() = 0;
		virtual void ClearStencilBuffer() = 0;
		virtual void ClearBuffers() = 0;

		struct ChildWindowInfo
		{
			HWND m_Hwnd;
			size_t m_uiWidth;
			size_t m_uiHeight;
			bool m_bDepth;
		};

		virtual bool IsSupportMulBufferSwitch() const = 0;

		static size_t GetBytesPerPixel(size_t formatType);
		static size_t GetChannelPerPixel(size_t formatType);

		FORCEINLINE size_t GetScreenWidth() const;
		FORCEINLINE size_t GetScreenHeight() const;
		FORCEINLINE size_t GetDisplayFormat() const;
		FORCEINLINE size_t GetCurAnisotropy() const;
		FORCEINLINE size_t GetCurMultisample() const;
		FORCEINLINE size_t GetDepthStencilFormat() const;
		FORCEINLINE bool IsWindowed() const;
		FORCEINLINE size_t WindowNum() const;
		FORCEINLINE size_t GetMaxTextureWidth() const;
		FORCEINLINE size_t GetMaxTextureHeight() const;

		virtual size_t SetTexture(JaxTexture* texture, size_t i) = 0;
		virtual size_t SetVTexture(JaxTexture* texture, size_t i) = 0;
		virtual size_t SetGTexture(JaxTexture* texture, size_t i) = 0;
		virtual size_t SetDTexture(JaxTexture* texture, size_t i) = 0;
		virtual size_t SetHTexture(JaxTexture* texture, size_t i) = 0;

		bool CheckIsTextureCanSet(JaxTexture* texture);

		bool LoadBlendState(JaxBlendState* state);
		bool ReleaseBlendState(JaxBlendState* state);

		bool LoadDepthStencilState(JaxDepthStencilState* state);
		bool ReleaseDepthStencilState(JaxDepthStencilState* state);

		bool LoadRasterizeState(JaxRasterizeState* state);
		bool ReleaseRasterizeState(JaxRasterizeState* state);

		bool LoadSamplerState(JaxSamplerState* state);
		bool ReleaseSamplerState(JaxSamplerState* state);

		bool LoadTexture(JaxTexture* texture);
		bool ReleaseTexture(JaxTexture* texture);

		virtual size_t SetBlendState(JaxBlendState* state, bool forceSet = false) = 0;
		virtual size_t SetDepthStencilState(JaxDepthStencilState* state, bool forceSet = false) = 0;
		virtual size_t SetRasterizeState(JaxRasterizeState* state, bool forceSet = false) = 0;

		virtual size_t SetSamplerState(JaxSamplerState* state, size_t i, bool forceSet = false) = 0;
		virtual size_t SetVSamplerState(JaxSamplerState* state, size_t i, bool forceSet = false) = 0;
		virtual size_t SetGSamplerState(JaxSamplerState* state, size_t i, bool forceSet = false) = 0;
		virtual size_t SetDSamplerState(JaxSamplerState* state, size_t i, bool forceSet = false) = 0;
		virtual size_t SetHSamplerState(JaxSamplerState* state, size_t i, bool forceSet = false) = 0;

		virtual bool OnLoadTexture(JaxTexture* texture, JaxResourceIdentifier*& id) = 0;
		virtual bool OnReleaseTexture(JaxResourceIdentifier* id) = 0;

		virtual bool OnLoadBlendState(JaxBlendState* state, JaxResourceIdentifier*& id) = 0;
		virtual bool OnReleaseBlendState(JaxResourceIdentifier* id) = 0;

		virtual bool OnLoadDepthStencilState(JaxDepthStencilState* state, JaxResourceIdentifier*& id) = 0;
		virtual bool OnReleaseDepthStencilState(JaxResourceIdentifier* id) = 0;

		virtual bool OnLoadRasterizeState(JaxRasterizeState* state, JaxResourceIdentifier*& id) = 0;
		virtual bool OnReleaseRasterizeState(JaxResourceIdentifier* id) = 0;

		virtual bool OnLoadSamplerState(JaxSamplerState* state, JaxResourceIdentifier*& id) = 0;
		virtual bool OnReleaseSamplerState(JaxResourceIdentifier* id) = 0;

		virtual bool OnLoadVBufferFormat(JaxVertexFormat* format, JaxResourceIdentifier*& id) = 0;
		virtual bool OnReleaseVBufferFormat(JaxResourceIdentifier* id) = 0;

		virtual size_t SetVertexFormat(JaxVertexFormat* format) = 0;

		virtual void* Lock(JaxTexture* texture, size_t level, size_t face) = 0;
		virtual void UnLock(JaxTexture* texture, size_t level, size_t face) = 0;

		bool SetDefaultValue();
		bool ReleaseDefaultValue();
	protected:
		HWND m_MainWindow;
		ChildWindowInfo* m_pChildWindowInfo;
		int m_iNumChildWindow;
		int m_iCurWindowID;
		bool m_bIsRendering;

		JaxColorRGBA m_ClearColor;
		JAXREAL m_fClearDepth;
		size_t m_uiClearStencil;

		JaxVertexFormat* m_pVertexFormat;

		size_t m_uinAdapter;
		size_t m_uiDevType;
		JaxString m_AdapterName;
		UINT m_uiScreenWidth;
		UINT m_uiScreenHeight;
		UINT m_uiCurRTWidth;
		UINT m_uiCurRTHeight;
		UINT m_uiCurMultisample;
		UINT m_uiMaxMultisample;
		bool m_bWindowed;
		UINT m_uiDisplayFormat;
		UINT m_uiBufferFormat;
		UINT m_uiDepthStencilFormat;
		UINT m_uiCurRTMultisample;
		DWORD m_dwMultsampleQuality;
		UINT m_uiCurAnisotropy;

		UINT m_uiMaxUseClipPlane;
		UINT m_uiMaxTexture;
		UINT m_uiMaxVTexture;
		UINT m_uiMaxGTexture;
		UINT m_uiMaxDTexture;
		UINT m_uiMaxHTexture;
		UINT m_uiMaxAnisotropy;
		UINT m_uiMaxRTNum;

		UINT m_uiMaxTextureWidth;
		UINT m_uiMaxTextureHeight;

		static size_t sm_uiBytesPerPixel[SFT_MAX];
		static size_t sm_uiChannelPerPixel[SFT_MAX];

		JaxTexture* m_pVTex[TEXLEVEL];
		JaxSamplerState* m_pVSamplerState[TEXLEVEL];

		JaxTexture* m_pPTex[TEXLEVEL];
		JaxSamplerState* m_pPSamplerState[TEXLEVEL];

		JaxTexture* m_pGTex[TEXLEVEL];
		JaxSamplerState* m_pGSamplerState[TEXLEVEL];

		JaxTexture* m_pHTex[TEXLEVEL];
		JaxSamplerState* m_pHSamplerState[TEXLEVEL];

		JaxTexture* m_pDTex[TEXLEVEL];
		JaxSamplerState* m_pDSamplerState[TEXLEVEL];

		JaxBlendState* m_pBlendState;
		JaxDepthStencilState* m_pDepthStencilState;
		JaxRasterizeState* m_pRasterizeState;
		bool m_bClipPlaneEnable;
		bool m_bScissorRectEnable;
	public:
		static JaxRenderer* sm_pRenderer;

	};
}