#pragma once
#include "JaxMemManager.h"
#include "JaxGraphic.h"
#include "JaxPointer.h"

namespace Jax
{
	class JAXGRAPHIC_API JaxReference
	{
	public:
		template<typename T>
		friend class JaxPointer;

		JaxReference();
		virtual ~JaxReference() = 0;
		
	public:
		int GetRef() const { return m_iReference; }

	protected:
		void IncreRef()
		{
			JaxLockedIncrement((long*)&m_iReference);
		}

		void DecreRef()
		{
			JaxLockedDecrement((long*)&m_iReference);
			if (!m_iReference)
				JAX_DELETE this;
		}
		int m_iReference;
	};
}