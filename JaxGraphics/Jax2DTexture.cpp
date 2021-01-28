#include "Jax2DTexture.h"
#include "JaxRenderTarget.h"
#include "JaxProperty.h"
namespace Jax
{
	IMPLEMENT_RTTI(Jax2DTexture,JaxTexture)
	BEGIN_ADD_PROPERTY(Jax2DTexture,JaxTexture)
	END_ADD_PROPERTY
	IMPLEMENT_INITIAL_BEGIN(Jax2DTexture)
	IMPLEMENT_INITIAL_END


	Jax2DTexture::Jax2DTexture(size_t width, size_t height, size_t formatType, size_t mipLevel, bool isStatic)
	{
		SetMipLevel();
		m_bRenderTarget = true;
		m_bRtUsed = false;
		m_pCurRenderTarget = NULL;
	}

	Jax2DTexture::Jax2DTexture(size_t width, size_t height, size_t formatType, size_t mipLevel)
	{
		m_bRenderTarget = true;
		m_bRtUsed = false;
		m_pCurRenderTarget = NULL;
	}

	Jax2DTexture::~Jax2DTexture()
	{

	}

	void Jax2DTexture::SetMipLevel()
	{
		if (m_uiMipLevel == 1)
		{
			return;
		}
		JAX_ASSERT(m_uiWidth && m_uiHeight);
		if (!IsTwoPower(m_uiWidth) || !IsTwoPower(m_uiHeight))
		{
			m_uiMipLevel = 1;
		}
		size_t widthLevel;
		size_t width = m_uiWidth;
		__asm bsr eax, width
		__asm mov widthLevel, eax

		size_t heightLevel;
		size_t height = m_uiHeight;
		__asm bsr eax, height;
		__asm mov heightLevel, eax

		size_t curLevel = Max(widthLevel, heightLevel) + 1;
		if (!m_uiMipLevel || curLevel < m_uiMipLevel)
		{
			m_uiMipLevel = curLevel;
		}
	}

	bool Jax2DTexture::SaveToFile(TCHAR* name)
	{
		if (!m_uiHeight || !m_uiWidth)
		{
			return false;
		}
		size_t heightSize = GetByteSize(0);
		if (!heightSize) return false;
		BITMAPFILEHEADER fileHeader;
		fileHeader.bfType = 0x4D42;
		fileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + heightSize;
		fileHeader.bfReserved1 = 0;
		fileHeader.bfReserved2 = 0;
		fileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

		BITMAPINFOHEADER infoHeader;
		infoHeader.biSize = sizeof(BITMAPINFOHEADER);
		infoHeader.biWidth = m_uiWidth;
		infoHeader.biHeight = m_uiHeight;
		infoHeader.biPlanes = 1;
		infoHeader.biBitCount = 32;
		infoHeader.biCompression = 0;
		infoHeader.biSizeImage = heightSize;
		infoHeader.biXPelsPerMeter = 0;
		infoHeader.biYPelsPerMeter = 0;
		infoHeader.biClrUsed = 0;
		infoHeader.biClrImportant = 0;

		byte* bufferTmp = NULL, *buffer = NULL;
		bufferTmp = JAX_NEW byte[heightSize];
		buffer = GetBuffer(0);
		if (!bufferTmp) return false;
		size_t bytesPerLine = m_uiWidth * 4;
		for (size_t i = 0; i < m_uiHeight; ++i)
		{
			JaxMemcpy(&bufferTmp[((m_bIsStatic-1)-i)*bytesPerLine],
				&buffer[i * bytesPerLine], bytesPerLine);
		}
		JaxFile* file = JAX_NEW JaxFile();
		if (!file) return false;
		if (file->Open(name, JaxFile::OM_WB))
		{
			JAX_DELETE(file);
			return false;
		}
		file->Write(&fileHeader, sizeof(BITMAPFILEHEADER), 1);
		file->Write(&fileHeader, sizeof(BITMAPINFOHEADER), 1);
		file->Write(bufferTmp, heightSize, 1);
		JAXMAC_DELETEA(bufferTmp);
		JAXMAC_DELETE(file);
		return true;
	}

	void Jax2DTexture::CreateRAMData()
	{
		if (m_bRenderTarget)
		{
			return;
		}
		JaxTexture::CreateRAMData();
	}

	Jax2DTexture::Jax2DTexture()
	{
		m_bRenderTarget = false;
	}

}
