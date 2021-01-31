#include "JaxPlane3.h"
#include "JaxMath.h"
#include "JaxLine3.h"
#include "JaxMatrix4x4.h"

namespace Jax
{
	JaxPlane3::JaxPlane3()
		:m_N(JaxVector3{ 0,0,0 }), m_fD(0.0f)
	{}

	JaxPlane3::JaxPlane3(const JaxVector3 & N, const JaxVector3 & p)
	{
		Set(N, p);
	}

	JaxPlane3::JaxPlane3(const JaxVector3& N, const JaxVector3& p1, const JaxVector3& p2)
	{
		Set(N, p1, p2);
	}

	JaxPlane3::JaxPlane3(const JaxVector3 point[3])
	{
		Set(point);
	}

	JaxPlane3::JaxPlane3(const JaxVector3& N, JAXREAL fd)
	{
		Set(N, fd);
	}

	void JaxPlane3::Transform(const JaxPlane3& plane, const JaxMatrix4x4& mat)
	{
		JaxVector4 tmp(m_N.x, m_N.y, m_N.z, m_fD);
		JaxMatrix4x4 inv;
		inv.InverseOf(mat);
		JaxMatrix4x4 transpose;
		transpose.TransposeOf(inv);
		JaxVector4 res = tmp * transpose;

		Set(JaxVector3(res.x, res.y, res.z), res.w);
	}


}

