#pragma once
#include "JaxTexture.h"
#include "JaxResource.h"
#include "JaxSamplerState.h"

namespace Jax
{
	class JaxStream;
	class JAXGRAPHIC_API JaxTexAllState :public JaxObject, public JaxResource
	{
		DECLARE_RTTI;

	public:
		JaxTexAllState(JaxTexture* texture);
		virtual ~JaxTexAllState();
		JaxTexAllState();
		virtual size_t GetResourceType() const
		{
			return RT_TEXTURE;
		}

		DECLARE_INITIAL;

		static bool InitialDefaultState();
		static bool TerminalDefaultState();

		JaxTexturePtr m_pTex;

	protected:
		JaxSamplerDesc m_SamplerDesc;
		JaxSamplerStatePtr m_pSamplerState;
		bool m_bSRGB;
		static JaxTexAllStatePtr Default;

	public:
		friend class JaxRenderer;
		FORCEINLINE bool GetSRGB() const
		{
			return m_bSRGB;
		}

		void SetSRGBEnable(bool enable);
		static const JaxTexAllState* GetDefault()
		{
			return Default;
		}

		void SetSamplerState(JaxSamplerState* state)
		{
			if (state)
			{
				state = (JaxSamplerState*)JaxSamplerState::GetDefault();
			}
			if (state != m_pSamplerState)
			{
				m_pSamplerState = state;
				m_SamplerDesc = state->GetSamplerDesc();
			}
		}

		const JaxSamplerState* GetSamplerState() const
		{
			return m_pSamplerState;
		}

		static bool sm_bIsEnableASYNLoader;
		virtual bool PostLoad(void* data = NULL);
		virtual bool PostClone(JaxObject* src);
	};

	DECLARE_PTR(JaxTexAllState);
	DECLARE_PROXY(JaxTexAllState);
	JAXTYPE_MARCO(JaxTexAllState);
}