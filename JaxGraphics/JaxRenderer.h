#pragma once
#include "JaxVector2.h"
#include "JaxVector4.h"
#include "JaxGraphic.h"

namespace Jax
{
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

		enum
		{
			RAT_NULL,
			RAT_OPENGL,
			RAT_DX11,
			RAT_DX12,
			RAT_SOFTWARE,
			RAT_MAX
		};
		
		virtual int GetRendererType() const = 0;
		virtual const TCHAR* GetRendererStringType() const = 0;

		FORCEINLINE void SetClearColor(const JaxColorRGBA& color);
		FORCEINLINE const JaxColorRGBA& GetClearColor() const;
		FORCEINLINE void SetClearDepth(JAXREAL depth);
		FORCEINLINE JAXREAL GetClearDepth() const;
		FORCEINLINE void SetClearStencil(size_t value);
		FORCEINLINE size_t GetClearStencil() const;

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

	protected:
		HWND m_MainWindow;
		ChildWindowInfo* m_pChildWindowInfo;
		int m_iNumChildWindow;
		int m_iCurWindowID;
		bool m_bIsRendering;

		JaxColorRGBA m_ClearColor;
		JAXREAL m_fClearDepth;
		size_t m_uiClearStencil;

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

	public:
		static JaxRenderer* sm_pRenderer;

	};
}