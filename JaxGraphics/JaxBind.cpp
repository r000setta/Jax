#include "JaxBind.h"
#include "JaxRenderer.h"
#include "JaxResouceManager.h"
#include "JaxStream.h"
#include "JaxProperty.h"
namespace Jax
{
	JaxArray<JaxBind*> JaxBind::sm_BindArray;
	JaxArray<JaxBind*> JaxBind::sm_DynamicTwoBindArray;

	IMPLEMENT_RTTI_NoCreateFun(JaxBind, JaxObject)
	IMPLEMENT_INITIAL_NO_CLASS_FACTORY_BEGIN(JaxBind)
	IMPLEMENT_INITIAL_NO_CLASS_FACTORY_END
	BEGIN_ADD_PROPERTY(JaxBind, JaxObject)
	REGISTER_PROPERTY(m_bIsStatic, IsStatic, JaxProperty::F_SAVE_LOAD_CLONE);
	REGISTER_PROPERTY(m_uiSwapChainNum, SwapChainNum, JaxProperty::F_SAVE_LOAD_CLONE);
	REGISTER_PROPERTY(m_uiLockFlag, LockFlag, JaxProperty::F_SAVE_LOAD_CLONE);
	REGISTER_PROPERTY(m_uiMemType, MemType, JaxProperty::F_SAVE_LOAD_CLONE);
	END_ADD_PROPERTY

	JaxBind::JaxBind(size_t memType)
	{
		m_InfoArray.Clear();
		m_bIsStatic = true;
		m_uiSwapChainNum = 1;
		m_uiLockFlag = LF_NOOVERWRITE;
		m_uiCurID = 0;
		m_pUser = NULL;
		m_uiMemType = memType;
		m_uiClearState = MCS_NONE;
		sm_BindArray.AddElement(this);
	}

	JaxBind::~JaxBind()
	{
		if (!m_bIsStatic && m_uiSwapChainNum == 2)
		{
			for (size_t i = 0; i < sm_DynamicTwoBindArray.GetNum(); ++i)
			{
				if (sm_DynamicTwoBindArray[i] == this)
				{
					sm_DynamicTwoBindArray.Erase(i);
					break;
				}
			}
		}

		for (size_t i = 0; i < sm_BindArray.GetNum(); ++i)
		{
			if (sm_BindArray[i] == this)
			{
				sm_BindArray.Erase(i);
				break;
			}
		}
	}

	size_t JaxBind::GetInfoQuantity() const
	{
		return m_InfoArray.GetNum();
	}

	void JaxBind::SetStatic(bool isStatic, bool mulThreadUse)
	{
		if (!m_bIsStatic && m_uiSwapChainNum == 2)
		{
			for (size_t i = 0; i < sm_DynamicTwoBindArray.GetNum(); ++i)
			{
				if (sm_DynamicTwoBindArray[i] == this)
				{
					sm_DynamicTwoBindArray.Erase(i);
					break;
				}
			}
		}
		m_bIsStatic = isStatic;
		if (m_bIsStatic)
		{
			m_uiSwapChainNum = 1;
		}
		else
		{
			if (JaxResourceManager::sm_bRenderThread && mulThreadUse &&JaxRenderer::sm_pRenderer->IsSupportMulBufferSwitch())
			{
				m_uiSwapChainNum = 2;
				sm_DynamicTwoBindArray.AddElement(this);
			}
			else
			{
				m_uiSwapChainNum = 1;
			}
		}
		m_uiCurID = 0;
	}

	void JaxBind::Exchange()
	{
		if (!m_bIsStatic && m_uiSwapChainNum == 2)
		{
			m_uiCurID = (m_uiCurID + 1) % m_uiSwapChainNum;
		}
	}

	JaxResourceIdentifier* JaxBind::GetIdentifier()
	{
		if (!m_InfoArray.GetNum())
		{
			return NULL;
		}
		JaxResourceIdentifier* id = m_InfoArray[m_uiCurID].ID;
		return id;
	}

	bool JaxBind::LoadResource(JaxRenderer* pRender)
	{
		if (!pRender) return false;
		if (m_uiMemType == MT_RAM)
		{
			return true;
		}
		if (m_uiSwapChainNum == m_InfoArray.GetNum())
		{
			return true;
		}
		else
		{
			m_pUser = pRender;
			for (size_t i = 0; i < m_uiSwapChainNum; ++i)
			{
				JaxResourceIdentifier* id = NULL;
				if (!OnLoadResource(id))
					return false;
				if (!id)
					return false;
				Bind(id);
			}
			if (!JaxResourceManager::sm_bRenderThread)
			{
				ClearInfo();
			}
			return false;
		}
	}

	bool JaxBind::ReleaseResource()
	{
		for (size_t i = 0; i < m_InfoArray.GetNum(); ++i)
		{
			INFO_TYPE& info = m_InfoArray[i];
			if (!OnReleaseResource(info.ID))
				return false;
		}
		m_InfoArray.Clear();
		return true;
	}
}