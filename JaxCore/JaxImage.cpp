#include "JaxImage.h"

namespace Jax
{
	TCHAR JaxImage::sm_ImageFormat[IF_MAX][10] =
	{
		_T("bmp"),
		_T("tga")
	};

	JaxImage::JaxImage()
	{
		m_pData = NULL;
		m_uiWidth = 0;
		m_uiHeight = 0;
		m_uiBPP = 0;
		m_uiDataSize = 0;
		m_pImageData = NULL;
		m_pPalette = NULL;
	}

	JaxImage::~JaxImage()
	{
		JAXMAC_DELETEA(m_pImageData);
		JAXMAC_DELETEA(m_pData);
		JAXMAC_DELETEA(m_pPalette);
	}

	JaxBMPImage::JaxBMPImage()
	{
		m_uiPlanes = 0;
		m_uiEnc = 0;
	}

	JaxBMPImage::~JaxBMPImage()
	{
	}

	bool JaxBMPImage::Load(const TCHAR* fileName)
	{
		JAXMAC_DELETEA(m_pImageData);
		JAXMAC_DELETEA(m_pData);
		JAXMAC_DELETEA(m_pPalette);
		if (!GetFile(fileName))
		{
			return false;
		}
		if (!ReadBmpHeader())
		{
			return false;
		}
		switch (m_uiEnc)
		{
		case 0:
			if (!LoadBmpRaw())
				return false;
			break;
		case 1:
			if (!LoadBmpRLE8())
				return false;
			break;
		default:
			return false;
		}

		FlipImg();
		if (!LoadBmpPalette())
			return false;
		JAXMAC_DELETEA(m_pData);
		return true;
	}

	bool JaxBMPImage::LoadFromBuffer(byte* buffer, size_t size)
	{
		if (!buffer)
		{
			return false;
		}
		JAXMAC_DELETEA(m_pImageData);
		JAXMAC_DELETEA(m_pPalette);
		m_pData = buffer;
		if (!ReadBmpHeader())
			return false;
		switch (m_uiEnc)
		{
		case 0:
			if (!LoadBmpRaw())
				return false;
			break;
		case 1:
			if (!LoadBmpRLE8())
				return false;
			break;
		default:
			return false;
		}
		FlipImg();
		if (!LoadBmpPalette())
			return false;
		m_pData = NULL;
		return true;
	}

	const byte* JaxBMPImage::GetPixel(size_t x, size_t y) const
	{
		if (x < 0) x = 0;
		if (x >= m_uiWidth) x = m_uiWidth - 1;
		if (y < 0) y = 0;
		if (y >= m_uiHeight) y = m_uiHeight - 1;

		int bpp = m_uiBPP / 8;
		int loc = (y * m_uiWidth + x) * bpp;
		return m_pImageData + loc;
	}

	bool JaxBMPImage::GetFile(const TCHAR* fileName)
	{
		JaxFile imgFile;
		imgFile.Open(fileName, JaxFile::OM_RB);
		if (!imgFile.GetFileSize())
		{
			return false;
		}
		m_pData = JAX_NEW byte[imgFile.GetFileSize()];
		if (!m_pData)
		{
			return false;
		}
		imgFile.Read(m_pData, imgFile.GetFileSize(), 1);
		return true;
	}

	bool JaxBMPImage::ReadBmpHeader()
	{
		int info;
		if (m_pData[0x0] != 'B' || m_pData[0x1] != 'M')
			return false;
		JaxMemcpy(&m_uiImgOffset, &m_pData[0xA], 4);
		JaxMemcpy(&info, &m_pData[0xE], 4);
		if (info != 0x28)
			return false;
		JaxMemcpy(&m_uiWidth, &m_pData[0x12], 4);
		JaxMemcpy(&m_uiHeight, &m_pData[0x16], 4);
		JaxMemcpy(&m_uiPlanes, &m_pData[0x1A], 2);
		JaxMemcpy(&m_uiBPP, &m_pData[0x1C], 2);
		JaxMemcpy(&m_uiEnc, &m_pData[0x1E], 4);

		m_uiDataSize = (m_uiWidth * m_uiHeight * (m_uiBPP >> 3));
		return true;
	}

	bool JaxBMPImage::LoadBmpRaw()
	{
		m_pImageData = JAX_NEW byte[m_uiDataSize];
		if (!m_pImageData)
			return false;
		JaxMemcpy(m_pImageData, &m_pData[m_uiImgOffset], m_uiDataSize);
		return true;
	}

	bool JaxBMPImage::LoadBmpRLE8()
	{

	}
	bool JaxBMPImage::LoadBmpPalette()
	{
		return false;
	}

	void JaxBMPImage::FlipImg()
	{
		byte tmp;
		byte* line1, *line2;
		size_t len, idx;

		len = m_uiWidth * (m_uiBPP / 8);
		line1 = m_pImageData;
		line2 = &m_pImageData[len * (m_uiHeight - 1)];

		for (; line1 < line2; line2 -= (len * 2))
		{
			for (idx = 0; idx != len; line1++, line2++, idx++)
			{
				tmp = *line1;
				*line1 = *line2;
				*line2 = tmp;
			}
		}
	}
}

