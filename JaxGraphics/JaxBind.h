#pragma once
#include "JaxObject.h"
#include "JaxRenderer.h"
#include "JaxResouceManager.h"
namespace Jax
{
	class JAXGRAPHIC_API JaxResourceIdentifier
	{
	public:
		virtual ~JaxResourceIdentifier() {}
	protected:
		JaxResourceIdentifier() {}
	};

	class JaxStream;
	class JAXGRAPHIC_API JaxBind :public JaxObject
	{
		DECLARE_RTTI;
		DECLARE_INITIAL_NO_CLASS_FACTORY;
	public:

		enum //LOCK_FLAG
		{
			LF_NOOVERWRITE,
			LF_DISCARD,
			LF_READONLY,
			LF_MAX
		};

		enum //Mem Type
		{
			MT_BOTH,
			MT_RAM,
			MT_VRAM,
			MT_MAX
		};

		enum
		{
			MCS_NONE,
			MCS_READY,
			MCS_DONE,
			MCS_MAX
		};

		JaxBind(size_t memType = MT_BOTH);
		virtual ~JaxBind() = 0;
		size_t GetInfoQuantity() const;

		bool IsStatic() const { return m_bIsStatic; }
		void SetStatic(bool isStatic, bool mulThreadUse = false);
		static JaxArray<JaxBind*> sm_DynamicTwoBindArray;
		static JaxArray<JaxBind*> sm_BindArray;
		void Exchange();
		JaxResourceIdentifier* GetIdentifier();

		virtual bool LoadResource(JaxRenderer* pRender);
		virtual bool ReleaseResource();

		virtual size_t GetByteSize() const;

		FORCEINLINE void SetLockFlag(size_t flag)
		{
			if (flag > LF_MAX)
			{
				flag = LF_NOOVERWRITE;
			}
			m_uiFlag = flag;
		}

		FORCEINLINE size_t GetLockFlag() const
		{
			return m_uiLockFlag;
		}

		FORCEINLINE void SetMemType(size_t memType)
		{
			if (memType < MT_MAX)
			{
				m_uiMemType = memType;
			}
		}

		FORCEINLINE size_t GetMemType() const
		{
			return m_uiMemType;
		}

		FORCEINLINE size_t GetSwapChainNum() const
		{
			return m_uiSwapChainNum;
		}

	protected:
		virtual void ClearInfo() {}
		friend class JaxRenderer;

		void Bind(JaxResourceIdentifier* id);

		struct INFO_TYPE
		{
			INFO_TYPE() :ID(NULL) {}
			~INFO_TYPE() {}
			JaxResourceIdentifier* ID;
		};

		JaxArray<INFO_TYPE> m_InfoArray;
		size_t m_uiSwapChainNum;
		size_t m_uiCurID;
		bool m_bIsStatic;
		JaxRenderer* m_pUser;
		size_t m_uiLockFlag;
		size_t m_uiMemType;
		size_t m_uiClearState;

		virtual bool OnLoadResource(JaxResourceIdentifier*& id) = 0;
		virtual bool OnReleaseResource(JaxResourceIdentifier* id) = 0;

	};

	DECLARE_PTR(JaxBind);
	JAXTYPE_MARCO(JaxBind);
}