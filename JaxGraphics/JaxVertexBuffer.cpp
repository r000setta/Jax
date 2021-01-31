#include "JaxVertexBuffer.h"
#include "JaxStream.h"
#include "JaxResouceManager.h"
#include "JaxProperty.h"

namespace Jax
{
	IMPLEMENT_RTTI(JaxVertexBuffer,JaxBind)
	BEGIN_ADD_PROPERTY(JaxVertexBuffer,JaxBind)
	REGISTER_PROPERTY(m_pData[0], PositionData, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_pData[1], TextureData, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_pData[2], NormalData, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_pData[3], TangetData, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_pData[4], BinormalData, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_pData[5], PSizeData, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_pData[6], ColorData, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_pData[7], FogData, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_pData[8], DepthData, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_pData[9], BlendWeightData, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_pData[10], BlendIndicesData, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiVertexNum, VertexNum, JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiOneVertexSize, OneVertexSize, JaxProperty::F_SAVE_LOAD_CLONE)
	END_ADD_PROPERTY
	IMPLEMENT_INITIAL_BEGIN(JaxVertexBuffer)
	IMPLEMENT_INITIAL_END

	JaxVertexBuffer::JaxVertexBuffer(JaxArray<JaxVertexFormat::VERTEXFORMAT_TYPE>& format, size_t num)
		:m_pVertexFormat(nullptr),m_uiOneVertexSize(0),m_uiVertexNum(num),m_pLockData(nullptr)
	{
		JAX_ASSERT(format.GetNum() && num);
		for (size_t i = 0; i < format.GetNum(); ++i)
		{
			m_uiOneVertexSize += JaxDataBuffer::sm_uiDataTypeByte[format[i].dataType];
		}
		m_pVertexFormat = JaxResourceManager::LoadVeratexFormat(this, &format);
		JAX_ASSERT(m_pVertexFormat);
	}

	JaxVertexBuffer::JaxVertexBuffer(bool bIsStatic)
		:m_uiVertexNum(0),m_pVertexFormat(nullptr),
		m_uiOneVertexSize(0),m_pLockData(nullptr)
	{
		for (size_t i = 0; i < JaxVertexFormat::VF_MAX; ++i)
		{
			m_pData[i].Clear();
		}
		m_bIsStatic = bIsStatic;
	}

	JaxVertexBuffer::~JaxVertexBuffer()
	{
		ReleaseResource();
		for (size_t i = 0; i < JaxVertexFormat::VF_MAX; ++i)
		{
			m_pData[i].Clear();
		}
		m_pVertexFormat = nullptr;
		m_pLockData = nullptr;
	}

	bool JaxVertexBuffer::SetData(JaxDataBuffer* data, size_t vf)
	{
		if (!data || m_pVertexFormat || vf >= JaxVertexFormat::VF_MAX)
		{
			return false;
		}

		if (!data->GetData())
			return false;
		if (vf == JaxVertexFormat::VF_POSITION)
		{
			m_pData[vf].AddElement(data);
		}
		else if (vf == JaxVertexFormat::VF_NORMAL)
		{
			m_pData[vf].AddElement(data);
		}
		else if (vf == JaxVertexFormat::VF_PSIZE)
		{
			if (!m_pData[vf].GetNum())
				m_pData[vf].AddElement(data);
			else
				return false;
		}
		else if (vf == JaxVertexFormat::VF_COLOR)
		{
			if (!m_pData[vf].GetNum() < 2)
				m_pData[vf].AddElement(data);
			else
				return false;
		}
		else if (vf == JaxVertexFormat::VF_BLENDWEIGHT)
		{
			if (!m_pData[vf].GetNum())
				m_pData[vf].AddElement(data);
			else
				return false;
		}
		else if (vf == JaxVertexFormat::VF_BLENDINDICES)
		{
			if (!m_pData[vf].GetNum())
				m_pData[vf].AddElement(data);
			else
				return false;
		}
		else if (vf == JaxVertexFormat::VF_BINORMAL)
		{
			if (!m_pData[vf].GetNum())
				m_pData[vf].AddElement(data);
			else
				return false;
		}
		else if (vf == JaxVertexFormat::VF_TANGENT)
		{
			if (!m_pData[vf].GetNum())
				m_pData[vf].AddElement(data);
			else
				return false;
		}
		else if (vf == JaxVertexFormat::VF_FOG)
		{
			if (!m_pData[vf].GetNum())
				m_pData[vf].AddElement(data);
			else
				return false;
		}
		else if (vf == JaxVertexFormat::VF_DEPTH)
		{
			if (!m_pData[vf].GetNum())
				m_pData[vf].AddElement(data);
			else
				return false;
		}
		else if (vf == JaxVertexFormat::VF_TEXCOORD)
		{
			m_pData[vf].AddElement(data);
		}
		else
		{
			return false;
		}

		if (!m_uiVertexNum)
		{
			m_uiVertexNum = data->GetNum();
		}
		else
		{
			if (m_uiVertexNum != data->GetNum())
			{
				return false;
			}
		}
		m_uiOneVertexSize += data->GetStride();
		return true;
	}

	JaxVertexBuffer::JaxVertexBuffer()
		:m_uiVertexNum(0), m_pVertexFormat(nullptr),
		m_uiOneVertexSize(0), m_pLockData(nullptr)
	{
		for (size_t i = 0; i < JaxVertexFormat::VF_MAX; ++i)
		{
			m_pData[i].Clear();
		}
		m_bIsStatic = false;
	}
	

}

