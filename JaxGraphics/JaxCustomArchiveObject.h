#pragma once
#include "JaxRtti.h"
#include "JaxType.h"
#include "JaxMap.h"

namespace Jax
{
	class JaxStream;
	class JAXGRAPHIC_API JaxCustomArchiveObject :public JaxMemObject
	{
	public:
		JaxCustomArchiveObject();
		virtual ~JaxCustomArchiveObject();
		virtual void Archive(JaxStream& stream) = 0;
	};

	CUSTOMTYPE_MARCO(JaxCustomArchiveObject)
}