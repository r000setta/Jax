#include "JaxDataBuffer.h"
#include "JaxMath.h"
#include "JaxVector3.h"
#include "JaxVector2.h"
#include "JaxVector4.h"
#include "JaxStream.h"
#include "JaxProperty.h"
namespace Jax
{
	IMPLEMENT_RTTI(JaxDataBuffer,JaxObject)
	BEGIN_ADD_PROPERTY(JaxDataBuffer,JaxObject)
	REGISTER_PROPERTY(m_uiNum,Num,JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_uiDT,DataType,JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY_DATA(m_pData,m_uiSize,Data)
	END_ADD_PROPERTY
	IMPLEMENT_INITIAL_BEGIN(JaxDataBuffer)
	IMPLEMENT_INITIAL_END

	size_t JaxDataBuffer::sm_uiDataTypeByte[]=
	{
		4,
		8,
		12,
		16,

		2,
		4,

		4,
		4,

		4,
		4,
		4,

		8,
		8,
		8,

		4,
		8,

		4
	};

	size_t JaxDataBuffer::sm_uiDataTypeChannel[] =
	{
		1,
		2,
		3,
		4,

		1,
		1,

		4,
		4,

		2,
		2,
		2,

		4,
		4,
		4,

		2,
		4,

		4
	};

	JaxDataBuffer::~JaxDataBuffer()
	{
		JAXMAC_DELETEA(m_pData);
	}

	JaxDataBuffer::JaxDataBuffer() :
		m_uiDT(DT_MAXNUM), m_uiNum(0), m_pData(nullptr)
	{

	}

	bool JaxDataBuffer::SetData(const void* data, size_t num, size_t DT)
	{
		if (DT >= DT_MAXNUM || !data || !num)
			return false;
		m_uiDT = DT;
		m_uiNum = num;
		JAXMAC_DELETEA(m_pData);

		m_pData = JAX_NEW byte[GetSize()];
		if (!m_pData)
			return false;
		JaxMemcpy(m_pData, data, GetSize());
		m_uiSize = GetSize();
		return true;
	}

	bool JaxDataBuffer::AddData(const void* data, size_t num, size_t DT)
	{
		
	}
}
