#include "JaxTexture.h"
#include "JaxStream.h"
#include "JaxProperty.h"
namespace Jax
{
	IMPLEMENT_RTTI_NoCreateFun(JaxTexture,JaxBind)
	IMPLEMENT_INITIAL_NO_CLASS_FACTORY_BEGIN(JaxTexture)
	IMPLEMENT_INITIAL_NO_CLASS_FACTORY_END
	BEGIN_ADD_PROPERTY(JaxTexture,JaxBind)
	REGISTER_PROPERTY(m_uiFormatType, FormatType, JaxProperty::F_SAVE_LOAD_CLONE);
	REGISTER_PROPERTY(m_uiWidth, Width, JaxProperty::F_SAVE_LOAD_CLONE);
	REGISTER_PROPERTY(m_uiHeight, Height, JaxProperty::F_SAVE_LOAD_CLONE);
	REGISTER_PROPERTY(m_uiLength, Lenght, JaxProperty::F_SAVE_LOAD_CLONE);
	REGISTER_PROPERTY(m_uiMipLevel, MipLevel, JaxProperty::F_SAVE_LOAD_CLONE);
	REGISTER_PROPERTY_DATA(m_pBufferArray[0], m_BufferSize[0], BufferArray0);
	REGISTER_PROPERTY_DATA(m_pBufferArray[1], m_BufferSize[1], BufferArray1);
	REGISTER_PROPERTY_DATA(m_pBufferArray[2], m_BufferSize[2], BufferArray2);
	REGISTER_PROPERTY_DATA(m_pBufferArray[3], m_BufferSize[3], BufferArray3);
	REGISTER_PROPERTY_DATA(m_pBufferArray[4], m_BufferSize[4], BufferArray4);
	REGISTER_PROPERTY_DATA(m_pBufferArray[5], m_BufferSize[5], BufferArray5);
	REGISTER_PROPERTY_DATA(m_pBufferArray[6], m_BufferSize[6], BufferArray6);
	REGISTER_PROPERTY_DATA(m_pBufferArray[7], m_BufferSize[7], BufferArray7);
	REGISTER_PROPERTY_DATA(m_pBufferArray[8], m_BufferSize[8], BufferArray8);
	REGISTER_PROPERTY_DATA(m_pBufferArray[9], m_BufferSize[9], BufferArray9);
	REGISTER_PROPERTY_DATA(m_pBufferArray[10], m_BufferSize[10], BufferArray10);
	REGISTER_PROPERTY_DATA(m_pBufferArray[11], m_BufferSize[11], BufferArray11);
	REGISTER_PROPERTY_DATA(m_pBufferArray[12], m_BufferSize[12], BufferArray12);
	REGISTER_PROPERTY_DATA(m_pBufferArray[13], m_BufferSize[13], BufferArray13);
	END_ADD_PROPERTY

	JaxTexture::JaxTexture(size_t formatType, size_t width, size_t height, size_t length, size_t mipLevel, bool isStatic)
	{
		JAX_ASSERT(width && height);
		JAX_ASSERT(formatType < JaxRenderer::SFT_MAX);
		m_uiFormatType = formatType;
		m_uiHeight = height;
		m_uiWidth = width;
		m_uiLength = length;
		for (size_t i = 0; i < MAX_MIP_LEVEL; ++i)
		{
			for (size_t j = 0; j < 6; ++j)
			{
				m_pLockData[i][j] = NULL;
			}
		}
		for (size_t i = 0; i < MAX_MIP_LEVEL; ++i)
		{
			m_pBufferArray[i] = NULL;
			m_BufferSize[i] = 0;
		}
		m_bIsStatic = isStatic;
		m_uiMipLevel = mipLevel;
		m_bSRGB = false;
	}


	JaxTexture::JaxTexture(size_t formatType, size_t width, size_t height, size_t length, size_t mipLevel, bool isStatic)
	{
	}

	JaxTexture::JaxTexture()
	{
		for (size_t i = 0; i < MAX_MIP_LEVEL; ++i)
		{
			for (size_t j = 0; j < 6; ++j)
			{
				m_pLockData[i][j] = NULL;
			}
		}
		for (size_t i = 0; i < MAX_MIP_LEVEL; ++i)
		{
			m_pBufferArray[i] = NULL;
		}
		m_bSRGB = false;
	}

	JaxTexture::~JaxTexture()
	{
		ReleaseResource();
		for (size_t i = 0; i < MAX_MIP_LEVEL; ++i)
		{
			JAXMAC_DELETEA(m_pBufferArray[i]);
			m_BufferSize[i] = 0;
		}
	}


	bool JaxTexture::LoadResource(JaxRenderer* render)
	{
		if (!JaxBind::LoadResource(render))
		{
			return false;
		}
		return true;
	}

	void* JaxTexture::Lock(size_t level, size_t face)
	{
		if (m_pLockData[level][face] || m_bIsStatic)
		{
			return NULL;
		}
		if (m_pUser)
		{
			m_pLockData[level][face] = m_pUser->Lock(this, level, face);
		}
		return m_pLockData[level][face];
	}

	void* JaxTexture::UnLock(size_t level, size_t face)
	{
		if (!m_pLockData[level][face] || m_bIsStatic)
		{
			return;
		}
		if (m_pUser)
		{
			m_pUser->UnLock(this, level, face);
		}
		m_pLockData[level][face] = NULL;
	}

	void JaxTexture::ClearInfo()
	{
		if (m_uiSwapChainNum == m_InfoArray.GetNum())
		{
			if (m_uiMemType == MT_VRAM)
			{
				for (size_t i = 0; i < MAX_MIP_LEVEL; ++i)
				{
					JAXMAC_DELETEA(m_pBufferArray[i]);
					m_BufferSize[i] = 0;
				}
			}
		}
	}

	void JaxTexture::ClearAllSlot()
	{
		for (size_t i = 0; i < 16; ++i)
		{
			if (m_VSTexSlot[i])
			{
				JaxRenderer::sm_pRenderer->SetVTexture(NULL, 1);
			}
		}
	}

	bool JaxTexture::HasAnySlot()
	{
		return m_VSTexSlot.HasValue() || m_PSTexSlot.HasValue() || m_GSTexSlot.HasValue()
			|| m_DSTexSlot.HasValue() || m_HSTexSlot.HasValue();
	}

	void JaxTexture::CreateRAMData()
	{
		for (size_t i = 0; i < m_uiMipLevel; ++i)
		{
			JAXMAC_DELETEA(m_pBufferArray[i]);
			m_BufferSize[i] = GetByteSize(i);
			if (m_BufferSize[i] == 0)
			{
				continue;
			}
			m_pBufferArray[i] = JAX_NEW byte[m_BufferSize[i]];
		}
	}

	bool JaxTexture::OnLoadResource(JaxResourceIdentifier*& id)
	{
		if (!m_pUser)
			return false;
		if (!m_pUser->OnLoadTexture(this, id))
			return false;
		return true;
	}

	bool JaxTexture::OnReleaseResource(JaxResourceIdentifier* id)
	{
		if (!m_pUser)
			return false;
		if (!m_pUser->OnReleaseTexture(id))
			return false;
		return true;
	}


	byte* JaxTexture::GetBuffer(size_t level, size_t i) const
	{
		if (IsCompress())
		{
			return NULL;
		}
		return m_pBufferArray[level] + i * JaxRenderer::GetBytesPerPixel(m_uiFormatType);
	}

	size_t JaxTexture::GetByteSize(size_t level) const
	{
		if (level > m_uiMipLevel)
		{
			return 0;
		}
		if (IsCompress())
		{

		}
		return JaxRenderer::GetBytesPerPixel(m_uiFormatType) * GetWidth(level) * GetHeight(level) * GetLength(level);
	}

	size_t JaxTexture::GetMemPitch(size_t level) const
	{
		if (level > m_uiMipLevel)
		{
			return 0;
		}
		if (IsCompress())
		{

		}
		return JaxRenderer::GetBytesPerPixel(m_uiFormatType) * GetWidth(level);
	}

	size_t JaxTexture::GetMemSlicePitch(size_t level) const
	{
		if (level > m_uiMipLevel)
		{
			return 0;
		}
		if (IsCompress())
		{

		}
		return JaxRenderer::GetBytesPerPixel(m_uiFormatType) * GetWidth(level) * GetHeight(level);
	}

	size_t JaxTexture::GetWidth(size_t level) const
	{
		if (level > m_uiMipLevel)
		{
			return 0;
		}
		size_t width = m_uiWidth >> level;
		if (!width) width = 1;
		return width;
	}

	size_t JaxTexture::GetHeight(size_t level) const
	{
		if (level > m_uiMipLevel)
		{
			return 0;
		}
		size_t height = m_uiHeight >> level;
		if (!height) height = 1;
		return height;
	}

	size_t JaxTexture::GetLength(size_t level) const
	{
		if (level > m_uiMipLevel)
		{
			return 0;
		}
		size_t length = m_uiLength >> level;
		if (!length) length = 1;
		return length;
	}

}