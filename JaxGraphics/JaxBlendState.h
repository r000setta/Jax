#pragma once
#include "JaxBind.h"
namespace Jax
{
	class JaxStream;
	class JAXGRAPHIC_API JaxBlendDesc :public JaxObject
	{
		DECLARE_RTTI
		DECLARE_INITIAL

	public:
		enum
		{
			MAX_RENDER_TARGET_NUM = 8
		};

		enum
		{
			BP_ZERO,
			BP_ONE,
			BP_SRCCOLOR,
			BP_INVSRCCOLOR,
			BP_SRCALPHA,
			BP_INVSRCALPHA,
			BP_DESTALPHA,
			BP_INVDESTALPHA,
			BP_DESTCOLOR,
			BP_INVDESTCOLOR,
			BP_MAX
		};

		enum
		{
			BO_ADD,
			BO_SUBTRACT,
			BO_REVSUBTRACT,
			BO_MIN_SRC_DEST,
			BO_MAX_SRC_DEST,
			BO_MAX
		};

		enum
		{
			WM_NONE = 0,
			WM_ALPHA = BIT(0),
			WM_RED = BIT(1),
			WM_GREEN = BIT(2),
			WM_BLUE = BIT(3),
			WM_ALL = 0x0F
		};

		JaxBlendDesc()
		{
			bAlphaToCoverageEnable = false;
			bIndependentBlendEnable = false;
			for (size_t i = 0; i, MAX_RENDER_TARGET_NUM; ++i)
			{
				bBlendEnable[i] = false;
				ucSrcBlend[i] = BP_ONE;
				ucDestBlend[i] = BP_ZERO;
				ucBlendOp[i] = BO_ADD;
				bAlphaBlendEnable[i] = false;
				ucSrcBlendAlpha[i] = BP_ONE;
				ucDestBlendAlpha[i] = BP_ZERO;
				ucBlendOpAlpha[i] = BO_ADD;
				ucWriteMask[i] = WM_ALL;
			}
		}

		~JaxBlendDesc() {}
		bool bAlphaToCoverageEnable;
		bool bIndependentBlendEnable;
		bool bBlendEnable[MAX_RENDER_TARGET_NUM];
		byte ucSrcBlend[MAX_RENDER_TARGET_NUM];
		byte ucDestBlend[MAX_RENDER_TARGET_NUM];
		byte ucBlendOp[MAX_RENDER_TARGET_NUM];

		bool bAlphaBlendEnable[MAX_RENDER_TARGET_NUM];
		byte ucSrcBlendAlpha[MAX_RENDER_TARGET_NUM];
		byte ucDestBlendAlpha[MAX_RENDER_TARGET_NUM];
		byte ucBlendOpAlpha[MAX_RENDER_TARGET_NUM];
		byte ucWriteMask[MAX_RENDER_TARGET_NUM];

		bool IsBlendUsed(size_t channel=0) const
		{
			return (bBlendEnable[channel] || bAlphaBlendEnable[channel]);
		}

		void* GetCRC32Data(size_t& size) const
		{
			size = sizeof(JaxBlendDesc) - sizeof(JaxObject);
			return (void*)&bAlphaToCoverageEnable;
		}

	};
	JAXTYPE_MARCO(JaxBlendDesc)

	class JAXGRAPHIC_API JaxBlendState :public JaxBind
	{
		DECLARE_RTTI
	public:
		virtual ~JaxBlendState();
	protected:
		JaxBlendState();
		JaxBlendDesc m_BlendDesc;
		static JaxPointer<JaxBlendState> Default;
	public:
		static const JaxBlendState* GetDefault()
		{
			return Default;
		}

		DECLARE_INITIAL
		static bool InitialDefaultState();
		static bool TerminalDefaultState();

		FORCEINLINE const JaxBlendDesc& GetBlendDesc() const
		{
			return m_BlendDesc;
		}
		friend class JaxResourceManager;
	};

	DECLARE_PTR(JaxBlendState)
	JAXTYPE_MARCO(JaxBlendState)
}