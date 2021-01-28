#pragma once
#include "JaxSystem.h"
#include "JaxMemManager.h"
#include "JaxFile.h"

namespace Jax
{
	class JAXCORE_API JaxImage
	{
	public:
		enum
		{
			IF_BMP,
			IF_TGA,
			IF_MAX
		};

		static TCHAR sm_ImageFormat[IF_MAX][10];
		JaxImage();
		virtual ~JaxImage() = 0;
		virtual bool Load(const TCHAR* fileName) = 0;
		virtual bool LoadFromBuffer(byte* buffer, size_t size) = 0;
		virtual const byte* GetPixel(size_t x, size_t y) const = 0;
		FORCEINLINE size_t GetBPP() const
		{
			return m_uiBPP;
		}

		FORCEINLINE size_t GetWidth() const
		{
			return m_uiWidth;
		}

		FORCEINLINE size_t GetHeight() const
		{
			return m_uiHeight;
		}

		FORCEINLINE const byte* GetImage() const
		{
			return m_pImageData;
		}

		FORCEINLINE size_t GetImageDataSize() const
		{
			return m_uiDataSize;
		}

		FORCEINLINE byte* GetPalette() const
		{
			return m_pPalette;
		}

	protected:
		size_t m_uiWidth;
		size_t m_uiHeight;
		size_t m_uiBPP;
		byte* m_pImageData;
		size_t m_uiDataSize;
		byte* m_pData;
		byte* m_pPalette;
	};

	class JAXCORE_API JaxBMPImage :public JaxImage
	{
	public:
		JaxBMPImage();
		~JaxBMPImage();
		virtual bool Load(const TCHAR* fileName);
		virtual bool LoadFromBuffer(byte* buffer, size_t size);
		virtual const byte* GetPixel(size_t x, size_t y) const;

	private:
		size_t m_uiEnc;
		size_t m_uiPlanes;
		size_t m_uiImgOffset;

		bool GetFile(const TCHAR* fileName);
		bool ReadBmpHeader();
		bool LoadBmpRaw();
		bool LoadBmpRLE8();
		bool LoadBmpPalette();
		void FlipImg();
	};
}

