#include "JaxResouceManager.h"
#include "JaxDepthStencilState.h"
#include "JaxRasterizeState.h"
#include "JaxBlendState.h"
#include "JaxSamplerState.h"
#include "JaxImage.h"
#include "JaxTexAllState.h"
#include "JaxVertexBuffer.h"
namespace Jax
{

	JaxCriticalSection JaxResourceManager::sm_NameCri;

	JaxString JaxResourceManager::sm_TexturePath;
	JaxResourceManager::~JaxResourceManager()
	{

	}

	JaxName* JaxResourceManager::CreateName(const TCHAR* pChar)
	{
		if (!pChar)
		{
			return NULL;
		}
		sm_NameCri.Lock();
		size_t crcCode = CRC32Compute(pChar, JaxStrlen(pChar));
		JaxName* name = JaxResourceManager::GetNameSet().CheckIsHaveTheResource(crcCode);
		if (!name)
		{
			name = JAX_NEW JaxName(pChar, crcCode);
			if (!name)
			{
				sm_NameCri.Unlock();
				return NULL;
			}
			JaxResourceManager::GetNameSet().AddResource(name->GetID(), name);
		}
		sm_NameCri.Unlock();
		return name;
	}

	JaxName* JaxResourceManager::CreateName(const JaxString& string)
	{
		sm_NameCri.Unlock();
		size_t crcCode = CRC32Compute(string.GetBuffer(), string.GetLength());
		JaxName* name = JaxResourceManager::GetNameSet().CheckIsHaveTheResource(crcCode);
		if (!name)
		{
			name = JAX_NEW JaxName(string, crcCode);
			if (!name)
			{
				sm_NameCri.Unlock();
				return NULL;
			}
			JaxResourceManager::GetNameSet().AddResource(name->GetID(), name);
		}
		sm_NameCri.Unlock();
		return name;
	}

	JaxVertexFormat* JaxResourceManager::LoadVeratexFormat(JaxVertexBuffer* vertexBuffer, JaxArray<JaxVertexFormat::VERTEXFORMAT_TYPE>* format)
	{
		if (!vertexBuffer && !format)
			return nullptr;
		if (vertexBuffer)
		{
			if (vertexBuffer->m_pVertexFormat)
				return vertexBuffer->m_pVertexFormat;
		}
		JaxArray<JaxVertexFormat::VERTEXFORMAT_TYPE> formatArray;
		if (!format)
		{
			if (!vertexBuffer->GetVertexFormat(formatArray))
				return nullptr;
			format = &formatArray;
		}
		else
		{
			if (!format->GetNum())
				return nullptr;
		}
		size_t vertexFormatCode = CRC32Compute(format->GetBuffer(), sizeof(JaxVertexFormat::VERTEXFORMAT_TYPE) * format->GetNum());
		JaxVertexFormat* vertexFormat = (JaxVertexFormat*)JaxResourceManager::GetVertexFormatSet().CheckIsHaveTheResource(vertexFormatCode);
		if (vertexFormat)
		{
			if (vertexBuffer)
			{
				vertexBuffer->m_pVertexFormat = vertexFormat;
			}
			return vertexFormat;
		}
		vertexFormat = JAX_NEW JaxVertexFormat();
		JaxResourceManager::GetVertexFormatSet().AddResource(vertexFormatCode, vertexFormat);
		if (vertexBuffer)
		{
			vertexBuffer->m_pVertexFormat = vertexFormat;
		}
		vertexFormat->m_FormatArray = *format;
		vertexFormat->m_uiVertexFormatCode = vertexFormatCode;
		vertexFormat->LoadResource(JaxRenderer::sm_pRenderer);
		return vertexFormat;
	}

	void JaxResourceManager::CacheResource()
	{
	}

	JaxDepthStencilState* JaxResourceManager::CreateDepthStencilState(const JaxDepthStencilDesc& desc)
	{
		size_t size = 0;
		void* pData = desc.GetCRC32Data(size);
		size_t hashCode = CRC32Compute(pData, size);

		JaxDepthStencilState* state = (JaxDepthStencilState*)JaxResourceManager::GetDepthStencilStateSet().CheckIsHaveTheResource(hashCode);
		if (state) return state;
		state = JAX_NEW JaxDepthStencilState();
		state->m_DepthStencilDesc = desc;
		JaxResourceManager::GetDepthStencilStateSet().AddResource(hashCode, state);
		return state;
	}

	JaxRasterizeState* JaxResourceManager::CreateRasterizeState(const JaxRasterizeDesc& desc)
	{
		size_t size = 0;
		void* pData = desc.GetCRC32Data(size);
		size_t hashCode = CRC32Compute(pData, size);

		JaxRasterizeState* state = (JaxRasterizeState*)JaxResourceManager::GetRasterizeStateSet().CheckIsHaveTheResource(hashCode);
		if (state) return state;
		state = JAX_NEW JaxRasterizeState();
		state->m_RasterizeDesc = desc;
		JaxResourceManager::GetRasterizeStateSet().AddResource(hashCode, state);
		return state;
	}

	JaxBlendState* JaxResourceManager::CreateBlendState(const JaxBlendDesc& desc)
	{
		size_t size = 0;
		void* pData = desc.GetCRC32Data(size);
		size_t hashCode = CRC32Compute(pData, size);

		JaxBlendState* state = (JaxBlendState*)JaxResourceManager::GetBlendStateSet().CheckIsHaveTheResource(hashCode);
		if (state) return state;
		state = JAX_NEW JaxBlendState();
		state->m_BlendDesc = desc;
		JaxResourceManager::GetBlendStateSet().AddResource(hashCode, state);
		return state;
	}

	JaxSamplerState* JaxResourceManager::CreateSamplerState(const JaxSamplerDesc& desc)
	{
		size_t size = 0;
		void* data = desc.GetCRC32Data(size);
		size_t hashCode = CRC32Compute(data, size);
		
		JaxSamplerState* state = (JaxSamplerState*)JaxResourceManager::GetSamplerStateSet().CheckIsHaveTheResource(hashCode);
		if (state)
		{
			return state;
		}
		state = JAX_NEW JaxSamplerState();
		state->m_SamplerDesc = desc;
		JaxResourceManager::GetSamplerStateSet().AddResource(hashCode, state);
		return state;
	}

	JaxTexAllState* JaxResourceManager::Load2DTexture(const TCHAR* fileName, JaxSamplerStatePtr state, size_t compressType, bool isNormal, bool bSRGB)
	{
		if (!fileName)
		{
			return NULL;
		}
		JaxFileName name = fileName;
		JaxString ext;
		if (!name.GetExtension(ext))
		{
			return NULL;
		}
		JaxTexAllState* texAllState = NULL;
		JaxImage* img = NULL;
		if (ext == JaxImage::sm_ImageFormat[JaxImage::IF_BMP])
		{
			img = JAX_NEW JaxBMPImage();
		}
		else
		{
			return NULL;
		}
		if (!img->Load(name.GetBuffer()))
		{
			JAXMAC_DELETE(img);
			return nullptr;
		}
		size_t width = img->GetWidth();
		size_t height = img->GetHeight();
		if (!width || !height)
		{
			JAXMAC_DELETE(img);
			return nullptr;
		}
		if (!IsTwoPower(width) || !IsTwoPower(height))
		{
			JAXMAC_DELETE(img);
			return nullptr;
		}
		Jax2DTexture* texture = JAX_NEW Jax2DTexture(width, height, JaxRenderer::SFT_A8R8G8B8, 0, 1);
		if (!texture)
		{
			JAXMAC_DELETE(img);
			return nullptr;
		}
		texture->CreateRAMData();
		for (size_t cy = 0; cy < height; cy++) {
			for (size_t cx = 0; cx < width; cx++) {
				unsigned idx = cy * width + cx;
				byte* buffer = texture->GetBuffer(0, idx);
				const byte* imgBuffer = img->GetPixel(cx, cy);
				if (img->GetBPP() == 8)
				{
					buffer[0] = imgBuffer[0];
					buffer[1] = imgBuffer[0];
					buffer[2] = imgBuffer[0];
					buffer[3] = 255;
				}
				else if (img->GetBPP() == 24)
				{
					buffer[0] = imgBuffer[0];
					buffer[1] = imgBuffer[1];
					buffer[2] = imgBuffer[2];
					buffer[3] = 255;
				}
				else if (img->GetBPP() == 32)
				{
					buffer[0] = imgBuffer[0];
					buffer[1] = imgBuffer[1];
					buffer[2] = imgBuffer[2];
					buffer[3] = imgBuffer[3];
				}
			}
		}

		byte* last = texture->GetBuffer(0);
		for (size_t i = 1; i < texture->GetMipLevel(); ++i)
		{
			byte* now = texture->GetBuffer(i);
			if (JaxResourceManager::GetNextMipData(last, texture->GetWidth(i - 1), texture->GetHeight(i - 1), now, texture->GetChannelPerPixel()))
			{
				JAXMAC_DELETE(texture);
				JAXMAC_DELETE(img);
				return nullptr;
			}
			last = texture->GetBuffer(i);
		}
		if (img)
		{
			JAXMAC_DELETE(img);
		}
		texAllState = JAX_NEW JaxTexAllState(texture);
		if (state)
		{
			texAllState->SetSamplerState(state);
		}
		texAllState->SetSRGBEnable(bSRGB);
		return texAllState;
	}

	bool JaxResourceManager::sm_bRenderThread = false;

	IMPLEMENT_PRIORITY(JaxResourceManager)
	IMPLEMENT_INITIAL_ONLY_BEGIN(JaxResourceManager);
	ADD_INITIAL_FUNCTION_WITH_PRIORITY(InitialDefaultState)
	ADD_TERMINAL_FUNCTION(TerminalDefaultState)
	IMPLEMENT_INITIAL_ONLY_END

	bool JaxResourceManager::InitialDefaultState()
	{
		return true;
	}

	bool JaxResourceManager::TerminalDefaultState()
	{
		return true;
	}

	JaxResourceControll::JaxResourceControll(unsigned int GCMaxTimeCount)
	{
		m_uiGCMaxTimeCount = GCMaxTimeCount;
	}

	JaxResourceControll::~JaxResourceControll()
	{
	}

	void JaxResourceControll::GCResource()
	{

	}

}
