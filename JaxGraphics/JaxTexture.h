#pragma once
#include "JaxBind.h"
#include "JaxRenderer.h"
#include "JaxBitArray.h"
namespace Jax
{
	class JaxStream;
	class JAXGRAPHIC_API JaxTexture :public JaxBind
	{
		DECLARE_RTTI
		DECLARE_INITIAL_NO_CLASS_FACTORY

	public:
		enum
		{
			MAX_MIP_LEVEL = 20
		};

		enum //Tex Type
		{
			TT_1D,
			TT_2D,
			TT_3D,
			TT_CUBE,
			TT_MAX
		};

	protected:
		JaxTexture(size_t formatType, size_t width, size_t height, size_t length,
			size_t mipLevel, bool isStatic = true);
		JaxTexture();

	public:
		virtual ~JaxTexture() = 0;
		virtual size_t GetTexType() const = 0;
		virtual void SetMipLevel() = 0;

		FORCEINLINE size_t GetFormatType() const
		{
			return m_uiFormatType;
		}

		FORCEINLINE size_t GetBytePerPixel() const
		{
			return JaxRenderer::GetBytesPerPixel(m_uiFormatType);
		}

		FORCEINLINE size_t GetChannelPerPixel() const
		{
			return JaxRenderer::GetChannelPerPixel(m_uiFormatType);
		}

		FORCEINLINE byte* GetBuffer(size_t level) const
		{
			return m_pBufferArray[level];
		}

		byte* GetBuffer(size_t level, size_t i) const;
		virtual size_t GetByteSize(size_t level) const;
		virtual size_t GetMemPitch(size_t level) const;
		virtual size_t GetMemSlicePitch(size_t level) const;

		size_t GetWidth(size_t level) const;
		size_t GetHeight(size_t level) const;
		size_t GetLength(size_t level) const;

		FORCEINLINE size_t GetMipLevel() const
		{
			return m_uiMipLevel;
		}

		FORCEINLINE bool IsCompress() const
		{
			if (m_uiFormatType == JaxRenderer::SFT_DXT3 || m_uiFormatType == JaxRenderer::SFT_DXT5)
			{
				return true;
			}
			return false;
		}

		bool m_bSRGB;
		virtual bool LoadResource(JaxRenderer* render);
		void* Lock(size_t level = 0, size_t face = 0);
		void* UnLock(size_t level = 0, size_t face = 0);

		FORCEINLINE void* GetLockDataPtr(size_t level = 0, size_t face = 0) const
		{
			JAX_ASSERT(level < GetMipLevel() && face < 6);
			return m_pLockData[level][face];
		}

		virtual void ClearInfo();

		JaxBit<unsigned short> m_VSTexSlot;
		JaxBit<unsigned short> m_PSTexSlot;
		JaxBit<unsigned short> m_GSTexSlot;
		JaxBit<unsigned short> m_DSTexSlot;
		JaxBit<unsigned short> m_HSTexSlot;
		void ClearAllSlot();
		bool HasAnySlot();

		virtual void CreateRAMData();

		FORCEINLINE bool IsCompress() const
		{
			if (m_uiFormatType == JaxRenderer::SFT_DXT3 || m_uiFormatType == JaxRenderer::SFT_DXT5)
			{
				return true;
			}
			return false;
		}

		FORCEINLINE bool IsHasAlpha() const
		{
			if (m_uiFormatType == JaxRenderer::SFT_A8R8G8B8 ||
				m_uiFormatType == JaxRenderer::SFT_A16B16G16R16F
				|| m_uiFormatType == JaxRenderer::SFT_A32B32G32R32F
				|| m_uiFormatType == JaxRenderer::SFT_DXT3 || m_uiFormatType == JaxRenderer::SFT_DXT5)
			{
				return true;
			}
			return false;
		}

	protected:
		byte* m_pBufferArray[MAX_MIP_LEVEL];
		size_t m_BufferSize[MAX_MIP_LEVEL];
		size_t m_uiFormatType;
		size_t m_uiWidth;
		size_t m_uiHeight;
		size_t m_uiMipLevel;
		size_t m_uiLength;

		size_t m_uiMipLevel;

		void* m_pLockData[MAX_MIP_LEVEL][6];
		
		virtual bool OnLoadResource(JaxResourceIdentifier*& id);
		virtual bool OnReleaseResource(JaxResourceIdentifier* id);
	};

	DECLARE_PTR(JaxTexture)
	JAXTYPE_MARCO(JaxTexture)
}