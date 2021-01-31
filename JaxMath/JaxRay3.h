#pragma once
#include "JaxLine3.h"

namespace Jax
{
	class JAXMATH_API JaxRay3 :public JaxLine3
	{
		JaxRay3();
		JaxRay3(const JaxVector3& orig, const JaxVector3& dir);
		~JaxRay3();

		void Transform(const JaxRay3& ray, const JaxMatrix4x4& mat);
	};
}