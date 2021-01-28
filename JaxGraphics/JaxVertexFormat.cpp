#include "JaxVertexFormat.h"
#include "JaxStream.h"
#include "JaxProperty.h"

namespace Jax
{
	IMPLEMENT_RTTI(JaxVertexFormat,JaxBind)
	BEGIN_ADD_PROPERTY(JaxVertexFormat,JaxBind)
	REGISTER_PROPERTY(m_uiVertexFormatCode,VertexFormatCode,JaxProperty::F_SAVE_LOAD_CLONE)
	REGISTER_PROPERTY(m_FormatArray,FormatArray,JaxProperty::F_SAVE_LOAD_CLONE)
	END_ADD_PROPERTY
	IMPLEMENT_INITIAL_BEGIN(JaxVertexFormat)
	IMPLEMENT_INITIAL_END

	JaxVertexFormat::~JaxVertexFormat()
	{
		ReleaseResource();
	}

	JaxVertexFormat::JaxVertexFormat()
	{
		m_bIsStatic = true;
	}
	bool JaxVertexFormat::OnLoadResource(JaxResourceIdentifier*& id)
	{
		if (!m_pUser)
			return false;
		if (!m_pUser->OnLoadVBufferFormat(this, id))
		{
			return false;
		}
		return true;
	}

	bool JaxVertexFormat::OnReleaseResource(JaxResourceIdentifier* id)
	{
		if (!m_pUser)
		{
			return false;
		}
		if (!m_pUser->OnReleaseVBufferFormat(id))
		{
			return false;
		}
		return true;
	}

}

