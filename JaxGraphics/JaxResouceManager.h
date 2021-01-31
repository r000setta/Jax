#pragma once
#include "JaxObject.h"
#include "JaxString.h"
#include "JaxArray.h"
#include "JaxMap.h"
#include "JaxName.h"
#include "JaxPriority.h"
#include "JaxVertexFormat.h"
#include "Jax2DTexture.h"
namespace Jax
{
	class JaxResourceControll
	{
	public:
		JaxResourceControll(unsigned int GCMaxTimeCount);
		virtual ~JaxResourceControll();
		virtual void GCResource();
	protected:
		JaxArray<unsigned int> m_TimeCount;
		unsigned int m_uiGCMaxTimeCount;
	};

	template<typename KEY,typename VALUE>
	class JaxResourceSet :public JaxResourceControll
	{
	protected:
		JaxMapOrder<KEY, VALUE> m_Resource;
	public:
		JaxResourceSet(unsigned int GCMaxTimeCount = 5000);
		~JaxResourceSet();

		VALUE CheckIsHaveTheResource(const KEY& key);
		bool AddResource(const KEY& key, VALUE object);
		bool DeleteResource(const KEY& key);

		unsigned int GetResourceNum();

		bool IsRealeseAll();
		void ClearAll();
		const MapElement<KEY, VALUE>* GetResource(unsigned int i);
	};

	class JaxName;
	class JaxTexture;
	class JaxTexAllState;
	class JaxVertexBuffer;
	DECLARE_PTR(JaxName)
	DECLARE_PTR(JaxTexAllState)

	DECLARE_PTR(JaxDepthStencilState)
	DECLARE_PTR(JaxRasterizeState)
	DECLARE_PTR(JaxBlendState)
	DECLARE_PTR(JaxSamplerState)

	class JaxBlendDesc;
	class JaxDepthStencilDesc;
	class JaxRasterizeDesc;
	class JaxSamplerDesc;

	class JAXGRAPHIC_API JaxResourceManager
	{
		DECLARE_PRIORITY

	public:
		JaxResourceManager();
		~JaxResourceManager();

#define GET_INNER_RESOURCE_SET(ResourceName) \
static JaxResourceSet<unsigned int,Jax##ResourceName##Ptr>& Get##ResourceName##Set() \
{ \
static JaxResourceSet<unsigned int,Jax##ResourceName##Ptr> s_##ResourceName##Set; \
return s_##ResourceName##Set; \
}

		GET_INNER_RESOURCE_SET(VertexFormat)
		GET_INNER_RESOURCE_SET(Name)
		GET_INNER_RESOURCE_SET(BlendState)
		GET_INNER_RESOURCE_SET(DepthStencilState)
		GET_INNER_RESOURCE_SET(RasterizeState)
		GET_INNER_RESOURCE_SET(BlendState)
		GET_INNER_RESOURCE_SET(SamplerState)


		static JaxName* CreateName(const TCHAR* pChar);
		static JaxName* CreateName(const JaxString& string);

		static JaxVertexFormat* LoadVeratexFormat(JaxVertexBuffer* vertexBuffer, JaxArray<JaxVertexFormat::VERTEXFORMAT_TYPE>* format = nullptr);

		static void CacheResource();

		static void AddGCObject(JaxObject* p)
		{

		}

		DECLARE_INITIAL_ONLY
		
		static JaxDepthStencilState* CreateDepthStencilState(const JaxDepthStencilDesc& desc);
		static JaxRasterizeState* CreateRasterizeState(const JaxRasterizeDesc& desc);
		static JaxBlendState* CreateBlendState(const JaxBlendDesc& desc);
		static JaxSamplerState* CreateSamplerState(const JaxSamplerDesc& desc);

		static JaxString sm_TexturePath;

		static JaxTexAllState* Load2DTexture(const TCHAR* fileName, JaxSamplerStatePtr state = NULL,
			size_t compressType = 0, bool isNormal = false, bool bSRGB = false);

		template<typename T>
		static bool GetNextMipData(const T* inData, size_t inDataWidth, size_t inDataHeight,
			T* outData, size_t channel);
		template<typename T>
		static bool GetNextMipData(const T* inData, size_t inDataWidth, size_t inDataHeight,
			size_t inDataLength, T* outData, size_t channel);

	protected:
		static JaxCriticalSection sm_NameCri;

	private:
		static bool InitialDefaultState();
		static bool TerminalDefaultState();
		
	public:
		static bool sm_bRenderThread;
	};

	template<typename KEY, typename VALUE>
	inline JaxResourceSet<KEY, VALUE>::JaxResourceSet(unsigned int GCMaxTimeCount):JaxResourceControll(GCMaxTimeCount)
	{
		m_Resource.Clear();
	}

	template<typename KEY, typename VALUE>
	inline JaxResourceSet<KEY, VALUE>::~JaxResourceSet()
	{
		m_Resource.Clear();
	}

	template<typename KEY, typename VALUE>
	inline VALUE JaxResourceSet<KEY, VALUE>::CheckIsHaveTheResource(const KEY& key)
	{
		size_t i = m_Resource.Find(key);
		if (i == m_Resource.GetNum())
		{
			return NULL;
		}
		m_TimeCount[i] = 0;
		return m_Resource[i].value; //
	}

	template<typename KEY, typename VALUE>
	inline bool JaxResourceSet<KEY, VALUE>::AddResource(const KEY& key, VALUE object)
	{
		if (!object)
		{
			return false;
		}
		m_Resource.AddElement(key, object);
		m_TimeCount.AddElement(0);
		return true;
	}

	template<typename KEY, typename VALUE>
	inline bool JaxResourceSet<KEY, VALUE>::DeleteResource(const KEY& key)
	{
		size_t i = m_Resource.Find(key);
		if (i == m_Resource.GetNum())
		{
			return NULL;
		}
		m_Resource.Erase(i);
		m_TimeCount.Erase(i);
		return true;
	}

	template<typename KEY, typename VALUE>
	inline unsigned int JaxResourceSet<KEY, VALUE>::GetResourceNum()
	{
		return m_Resource.GetNum();
	}

	template<typename KEY, typename VALUE>
	inline bool JaxResourceSet<KEY, VALUE>::IsRealeseAll()
	{
		return !m_Resource.GetNum();
	}

	template<typename KEY, typename VALUE>
	inline void JaxResourceSet<KEY, VALUE>::ClearAll()
	{
		m_Resource.Clear();
	}

	template<typename KEY, typename VALUE>
	inline const MapElement<KEY, VALUE>* JaxResourceSet<KEY, VALUE>::GetResource(unsigned int i)
	{
		JAX_ASSERT(i < m_Resource.GetNum());
		return &m_Resource[i];
	}

	template<typename T>
	inline bool JaxResourceManager::GetNextMipData(const T* inData, size_t inDataWidth, size_t inDataHeight, T* outData, size_t channel)
	{
		JAX_ASSERT(inData || outData);
		size_t outDataWidth = inDataWidth >> 1;
		if (!outDataWidth)
		{
			outDataWidth = 1;
		}
		size_t outDataHeight = inDataHeight >> 1;
		if (!outDataHeight)
		{
			outDataHeight = 1;
		}
		for (size_t i = 0; i < outDataWidth; ++i)
		{
			size_t row0 = i * 2;
			size_t row1 = i * 2 + 1;
			if (r1 >= inDataWidth)
			{
				r1 = inDataWidth - 1;
			}
			for (size_t j = 0; j < outDataHeight; ++j)
			{
				size_t col0 = j * 2;
				size_t col1 = j * 2 + 1;
				if (col1 >= inDataHeight)
				{
					col1 = inDataHeight - 1;
				}
				for (size_t k = 0; k < channel; ++k)
				{
					outData[(j+i*outDataHeight)*channel+k]=
						(T)((inData[(col0+row0*inDataHeight)*channel+k]+inData[(col1+col0*inDataHeight)*channel+k]
							+ inData[col0 + row1 * inDataHeight) * channel + k] + inData[(col1 + row1 * inDataHeight) * channel + k]) * 0.25f);
				}
			}
		}
		return true;
	}

	template<typename T>
	inline bool JaxResourceManager::GetNextMipData(const T* inData, size_t inDataWidth, size_t inDataHeight, size_t inDataLength, T* outData, size_t channel)
	{
		JAX_ASSERT(inData || outData);
		size_t outDataWidth = inDataWidth >> 1;
		if (!outDataWidth)
		{
			outDataWidth = 1;
		}
		size_t outDataHeight = inDataHeight >> 1;
		if (!outDataHeight)
		{
			outDataHeight = 1;
		}
		size_t outDataLength = inDataLength >> 1;
		if (!outDataLength)
		{
			outDataLength = 1;
		}
		for (size_t s = 0; s < outDataLength; ++s)
		{
			size_t len0 = s * 2;
			size_t len1 = s * 2 + 1;
			if (len1 >= outDataLength)
			{
				len1 = outDataLength - 1;
			}
			for (size_t i = 0; i < outDataWidth; ++i)
			{
				size_t row0 = i * 2;
				size_t row1 = i * 2 + 1;
				if (row1 >= inDataWidth)
				{
					row1 = inDataWidth - 1;
				}
				for (size_t j = 0; j < outDataHeight; ++j)
				{
					size_t col0 = j * 2;
					size_t col1 = j * 2 + 1;
					if (col1 >= inDataHeight)
					{
						col1 = inDataHeight - 1;
					}
					for (size_t k = 0; k < channel; ++k)
					{
						outData[(j + i * outDataHeight + s * outDataHeight * outDataWidth) * channel + k]
							= (T)((inData[(col0 + row0 * inDataHeight + len0 * inDataHeight * inDataWidth) * channel + k] +
								inData[(col1 + row0 * inDataHeight + len0 * inDataHeight * inDataWidth) * channel + k] +
								inData[(col0 + row1 * inDataHeight + len0 * inDataHeight * inDataWidth) * channel + k] +
								inData[(col1 + row1 * inDataHeight + len0 * inDataHeight * inDataWidth) * channel + k] +
								inData[(col0 + row0 * inDataHeight + len1 * inDataHeight * inDataWidth) * channel + k] +
								inData[(col1 + row0 * inDataHeight + len1 * inDataHeight * inDataWidth) * channel + k] +
								inData[(col0 + row1 * inDataHeight + len1 * inDataHeight * inDataWidth) * channel + k] +
								inData[(col1 + row1 * inDataHeight + len1 * inDataHeight * inDataWidth) * channel + k] +
								) * 0.125f);
					}
				}
			}
		}
		return true;
	}

}