#include "JaxResource.h"
#include "JaxStream.h"

namespace Jax
{
	JaxString JaxResource::sm_FileSuffix[] =
	{
		_T("TEXTURE"),
		_T("")
	};

	JaxResource::JaxResource()
	{
		
	}

	JaxResource::~JaxResource()
	{
	}

	const JaxString& JaxResource::GetFileSuffix(size_t suffix)
	{
		if (suffix > RT_MAX)
			return sm_FileSuffix[RT_MAX];
		return sm_FileSuffix[suffix];
	}

	JaxResourceProxyBase::JaxResourceProxyBase()
	{
	}

	JaxResourceProxyBase::~JaxResourceProxyBase()
	{
	}
}

