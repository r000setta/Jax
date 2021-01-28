#pragma once
#include "JaxBind.h"
#include "JaxVector4.h"

namespace Jax
{
	class JaxStream;
	class JAXGRAPHIC_API JaxSamplerDesc :public JaxObject
	{
		DECLARE_RTTI
		DECLARE_INITIAL

	public:
		enum //Coordinate Mode
		{
			CM_CLAMP,
			CM_WRAP,
			CM_MIRROR,
			CM_BORDER,
			CM_MAX
		};

		enum //Filter Mode
		{
			FM_NONE,
			FM_POINT,
			FM_LINE,
			FM_ANISOTROPIC,
			FM_MAX
		};

		JaxSamplerDesc()
		{
			m_uiMax = FM_POINT;
			m_uiMax = FM_POINT;
			m_uiMip = FM_NONE;
			m_uiMipLevel = 0;
			m_uiAniLevel = 1;
			m_uiCoordU = CM_WRAP;
			m_uiCoordV = CM_WRAP;
			m_uiCoordW = CM_WRAP;
			m_BorderColor = JaxColorRGBA(0.0f, 0.0f, 0.0f, 0.0f);
			m_MipLODBias = 0.0f;
		}

		~JaxSamplerDesc()
		{

		}

		byte m_uiMax;
		byte m_uiMin;
		byte m_uiMip;
		byte m_uiMipLevel;
		byte m_uiAniLevel;

		byte m_uiCoordU;
		byte m_uiCoordV;
		byte m_uiCoordW;
		JAXREAL m_MipLODBias;
		JaxColorRGBA m_BorderColor;

		void* GetCRC32Data(size_t& size) const
		{
			size = sizeof(JaxSamplerDesc) - sizeof(JaxObject);
			return (void*)&m_uiMax;
		}
	};

	JAXTYPE_MARCO(JaxSamplerDesc);

	class JAXGRAPHIC_API JaxSamplerState :public JaxBind
	{
		DECLARE_RTTI
	public:
		virtual ~JaxSamplerState();

		DECLARE_INITIAL
		static bool InitialDefaultState();
		static bool TerminalDefaultState();

		const JaxSamplerDesc& GetSamplerDesc() const
		{
			return m_SamplerDesc;
		}

		static const JaxSamplerState* GetDefault()
		{
			return Default;
		}
		static const JaxSamplerState* GetTriLine()
		{
			return TriLine;
		}
		static const JaxSamplerState* GetDoubleLine()
		{
			return DoubleLine;
		}
		static const JaxSamplerState* GetShadowMapSampler()
		{
			return ShadowMapSampler;
		}
		static const JaxSamplerState* GetBorderARGB0Sampler()
		{
			return BorderARGB0Sampler;
		}
		static const JaxSamplerState* GetLightFunctionSampler()
		{
			return LightFunctionSampler;
		}

		friend class JaxResourceManager;

	protected:
		JaxSamplerState();
		JaxSamplerDesc m_SamplerDesc;
		static JaxPointer<JaxSamplerState> Default;
		static JaxPointer<JaxSamplerState> TriLine;
		static JaxPointer<JaxSamplerState> DoubleLine;
		static JaxPointer<JaxSamplerState> ShadowMapSampler;
		static JaxPointer<JaxSamplerState> BorderARGB0Sampler;
		static JaxPointer<JaxSamplerState> LightFunctionSampler;

		virtual bool OnLoadResource(JaxResourceIdentifier*& id);
		virtual bool OnReleaseResource(JaxResourceIdentifier* id);
	};

	DECLARE_PTR(JaxSamplerState);
	JAXTYPE_MARCO(JaxSamplerState);
}