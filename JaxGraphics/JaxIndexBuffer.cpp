#include "JaxIndexBuffer.h"
#include "JaxStream.h"
#include "JaxProperty.h"
namespace Jax
{
	IMPLEMENT_RTTI(JaxIndexBuffer,JaxBind)
	BEGIN_ADD_PROPERTY(JaxIndexBuffer,JaxBind)
	REGISTER_PROPERTY(m_pData,IndexData,JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiNum,Num,JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiDT,DataType,JaxProperty::F_SAVE_LOAD_CLONE)
	END_ADD_PROPERTY
	IMPLEMENT_INITIAL_BEGIN(JaxIndexBuffer)
	IMPLEMENT_INITIAL_END

	void* JaxIndexBuffer::Lock()
	{
		if (m_pLockData || !m_bIsStatic)
		{
			return nullptr;
		}
		if (m_pUser)
		{
			m_pLockData = m_pUser->Lock(this);
		}
		return m_pLockData;
	}

	JaxIndexBuffer::~JaxIndexBuffer()
	{
		ReleaseResource();
		m_pData = nullptr;
		m_pLockData = nullptr;
	}


	JaxIndexBuffer::JaxIndexBuffer() :
		m_pData(nullptr), m_uiNum(0), m_uiDT(JaxDataBuffer::DT_USHORT), m_pLockData(nullptr)
	{

	}

	JaxIndexBuffer::JaxIndexBuffer(size_t num, size_t DT)
	{
		JAX_ASSERT(num);
		JAX_ASSERT(DT == JaxDataBuffer::DT_USHORT || DT == JaxDataBuffer::DT_UINT);
		m_pData = nullptr;
		m_uiNum = num;
		m_uiDT = DT;
		m_pLockData = nullptr;
	}



	bool JaxIndexBuffer::SetData(JaxDataBuffer* pData)
	{
		if ((pData->GetDT() != JaxDataBuffer::DT_USHORT && pData->GetDT() != JaxDataBuffer::DT_UINT) || !pData->GetNum() || !pData->GetData())
		{
			return false;
		}
		m_pData = pData;
		m_uiNum = pData->GetNum();
		m_uiDT = pData->GetDT();
		return true;
	}

	void JaxIndexBuffer::UnLock()
	{
		if (!m - m_pLockData || m_bIsStatic)
		{
			return;
		}
		if (m_pUser)
		{
			m_pUser->UnLock(this);
		}
		m_pLockData = nullptr;
	}

	bool JaxIndexBuffer::LoadResource(JaxRenderer* render)
	{
		if (!JaxBind::LoadResource(render))
		{
			return false;
		}
		return true;
	}

	void JaxIndexBuffer::ClearInfo()
	{
		if (m_uiSwapChainNum == m_InfoArray.GetNum())
		{
			if (m_uiMemType == MT_VRAM)
			{
				m_pData = nullptr;
			}
		}
	}

	size_t JaxIndexBuffer::GetNum() const
	{
		return m_uiNum;
	}

	size_t JaxIndexBuffer::GetByteSize() const
	{
		return JaxDataBuffer::sm_uiDataTypeByte[m_uiDT] * m_uiNum;
	}

	bool JaxIndexBuffer::OnLoadResource(JaxResourceIdentifier*& id)
	{
		if (!m_pUser)
			return false;
		if (!m_pUser->OnLoadIBuffer(this, id))
			return false;
		return true;
	}

	bool JaxIndexBuffer::OnReleaseResource(JaxResourceIdentifier* id)
	{
		if (!m_pUser)
			return false;
		if (!m_pUser->OnReleaseIBuffer(id))
			return false;
		return true;
	}

}
