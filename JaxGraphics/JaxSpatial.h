#pragma once
#include "JaxObject.h"
#include "JaxResource.h"

namespace Jax
{
	class JaxStream;

	class JAXGRAPHIC_API JaxSpatial :public JaxObject
	{
		DECLARE_RTTI
		DECLARE_INITIAL_NO_CLASS_FACTORY

	protected:
		friend class JaxNode;
		bool m_bIsVisibleUpdate;

	public:
		virtual ~JaxSpatial() = 0;
		virtual void ComputeVisibleSet()
	};
}