#pragma once
#include "JaxMath.h"
#include "JaxVector3.h"
#include "JaxSphere3.h"

namespace Jax
{
	class JAXMATH_API JaxLine3
	{
	protected:
		JaxVector3 m_Orig;
		JaxVector3 m_Dir;

	public:
		JaxLine3();
		JaxLine3(const JaxVector3& orig, const JaxVector3& dir);
		~JaxLine3();
		void Transform(const JaxLine3& line, const JaxMatrix4x4& mat);
	};
}