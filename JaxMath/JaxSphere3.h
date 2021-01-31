#pragma once
#include "JaxVector3.h"

namespace Jax
{
	class JAXMATH_API JaxSphere3
	{
		JaxVector3 m_Center;
		JAXREAL m_fRadius;

		JaxSphere3();
		~JaxSphere3();
		JaxSphere3(const JaxVector3& center, JAXREAL radius);

		void Transform(const JaxSphere3& sphere, const JaxMatrix4x4& mat);

		FORCEINLINE void Set(const JaxVector3& center, JAXREAL radius)
		{
			m_Center = center;
			m_fRadius = radius;
		}

		JAXREAL Distance(const JaxVector3& point, const JaxVector3& spherePoint) const;
	};
}