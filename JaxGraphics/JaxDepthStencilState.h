#pragma once
#include "JaxBind.h"
namespace Jax
{
	class JaxStream;
	class JAXGRAPHIC_API JaxDepthStencilDesc :public JaxObject
	{
		DECLARE_RTTI
		DECLARE_INITIAL
		
	public:
		enum //Compare Method
		{
			CM_NEVER,
			CM_LESS,
			CM_EQUAL,
			CM_LESSEQUAL,
			CM_GREATER,
			CM_NOTEQUAL,
			CM_GREATEREQUAL,
			CM_ALWAYS,
			CM_MAX
		};

		enum //Operation Type
		{
			OT_KEEP,
			OT_ZERO,
			OT_REPLACE,
			OT_INCREMENT,
			OT_DECREMENT,
			OT_INVERT,
			OT_INCREMENT_STA,
			OT_DECREMENT_STA,
			OT_MAX
		};

		JaxDepthStencilDesc()
		{

		}

		~JaxDepthStencilDesc() {}
		bool m_bDepthEnable;
		bool m_bDepthWritable;
		byte m_uiDepthCompareMethod;
		bool m_bStencilEnable;
		byte m_uiStencilCompareMethod;
		byte m_uiReference;
		byte m_uiMask;
		byte m_uiWriteMask;
		byte m_uiSPassZPassOP;
		byte m_uiSPassZFailOP;
		byte m_uiSFailZPassOP;

		byte m_uiCCW_StencilCompareMethod;
		byte m_uiCCW_SPassZPassOP;
		byte m_uiCCW_SPassZFailOP;
		byte m_uiCCW_SFailZPassOP;
		bool m_bTwoSideStencilMode;

		void* GetCRC32Data(size_t& size) const
		{
			size = sizeof(JaxDepthStencilDesc) - sizeof(JaxObject);
			return (void*)&m_bDepthEnable;
		}
	};

	JAXTYPE_MARCO(JaxDepthStencilDesc);

	class JAXGRAPHIC_API JaxDepthStencilState :public JaxBind
	{
		DECLARE_RTTI

	public:
		virtual ~JaxDepthStencilState();

		static const JaxDepthStencilState* GetDefault()
		{
			return Default;
		}

		DECLARE_INITIAL

		static bool InitialDefaultState();
		static bool TerminalDefaultState();

		FORCEINLINE const JaxDepthStencilDesc& GetDepthStencilDesc() const
		{
			return m_DepthStencilDesc;
		}

		friend class JaxResourceManager;

	protected:
		JaxDepthStencilState();
		JaxDepthStencilDesc m_DepthStencilDesc;
		static JaxPointer<JaxDepthStencilState> Default;

		virtual bool OnLoadResource(JaxResourceIdentifier*& id);
		virtual bool OnReleaseResource(JaxResourceIdentifier* id);

	};

	DECLARE_PTR(JaxDepthStencilState)
	JAXTYPE_MARCO(JaxDepthStencilState)
}