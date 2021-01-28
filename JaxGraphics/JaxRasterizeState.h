#pragma once
#include "JaxBind.h"

namespace Jax
{
	class JaxStream;
	class JAXGRAPHIC_API JaxRasterizeDesc :public JaxObject
	{
		DECLARE_RTTI
		DECLARE_INITIAL

	public:
		enum //Cull Type
		{
			CT_NONE,
			CT_CW,
			CT_CCW,
			CT_MAX
		};

		JaxRasterizeDesc()
		{
			m_bWireEnable = false;
			m_uiCullType = CT_CCW;
			m_bClipPlaneEnable = false;
			m_bScissorTestEnable = false;
			m_fDepthBias = 0.0f;
		}

		~JaxRasterizeDesc() {}
		bool m_bWireEnable;
		byte m_uiCullType;
		bool m_bClipPlaneEnable;
		bool m_bScissorTestEnable;
		JAXREAL m_fDepthBias;
		
		void* GetCRC32Data(size_t& size) const
		{
			size = sizeof(JaxRasterizeDesc) - sizeof(JaxObject);
			return (void*)&m_bWireEnable;
		}

	};

	JAXTYPE_MARCO(JaxRasterizeDesc)

	class JAXGRAPHIC_API JaxRasterizeState :public JaxBind
	{
		DECLARE_RTTI
	public:
		virtual ~JaxRasterizeState();
		static const JaxRasterizeState* GetDefault()
		{
			return Default;
		}

		static const JaxRasterizeState* GetScissorEnable()
		{
			return ScissorEnable;
		}

		DECLARE_INITIAL

		static bool InitialDefaultState();
		static bool TerminalDefaultState();

		FORCEINLINE const JaxRasterizeDesc& GetRasterizeDesc() const
		{
			return m_RasterizeDesc;
		}
		friend class JaxResourceManager;

	protected:
		JaxRasterizeState();
		JaxRasterizeDesc m_RasterizeDesc;
		static JaxRasterizeStatePtr Default;
		static JaxRasterizeStatePtr ScissorEnable;

	};
}