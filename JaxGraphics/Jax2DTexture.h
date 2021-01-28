#pragma once
#include "JaxTexture.h"

namespace Jax
{
	class JaxRenderTarget;
	class JAXGRAPHIC_API Jax2DTexture :public JaxTexture
	{
		DECLARE_RTTI
	public:
		Jax2DTexture(size_t width, size_t height, size_t formatType, size_t mipLevel, bool isStatic);
		Jax2DTexture(size_t width, size_t height, size_t formatType, size_t mipLevel = 1);
		virtual ~Jax2DTexture();

		virtual size_t GetTexType() const
		{
			return TT_2D;
		}

		FORCEINLINE bool IsRenderTarget() const
		{
			return m_bRenderTarget;
		}

		virtual void SetMipLevel();
		bool SaveToFile(TCHAR* name);
		virtual void CreateRAMData();

		DECLARE_INITIAL

		bool m_bRtUsed;

	public:
		friend class JaxRenderer;
		friend class JaxRenderTarget;

		JaxRenderTarget* GetCurRenderTarget() const
		{
			return m_pCurRenderTarget;
		}

	protected:
		Jax2DTexture();
		bool m_bRenderTarget;
		class JaxRenderTarget* m_pCurRenderTarget;
	};

	DECLARE_PTR(Jax2DTexture);
	JAXTYPE_MARCO(Jax2DTexture);
}