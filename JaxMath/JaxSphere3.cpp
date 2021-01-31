#include "JaxSphere3.h"

namespace Jax
{
	JaxSphere3::JaxSphere3() :m_Center(JaxVector3{ 0,0,0 }), m_fRadius(0.0f)
	{}

	JaxSphere3::~JaxSphere3()
	{
		m_fRadius = 0.0f;
	}

	JaxSphere3::JaxSphere3(const JaxVector3& center, JAXREAL radius) : m_Center(center), m_fRadius(radius)
	{
	}

	void JaxSphere3::Transform(const JaxSphere3& sphere, const JaxMatrix4x4& mat)
	{
		m_Center = sphere.m_Center * mat;
		JaxVector3 v0(1.0f, 0.0f, 0.0f), v1(0.0f, 0.1f, 0.0f), v2(0.0f, 0.0f, 1.0f);
		JaxVector3 tmp0 = sphere.m_Center + v0 * sphere.m_fRadius;
		JaxVector3 tmp1 = sphere.m_Center + v1 * sphere.m_fRadius;
		JaxVector3 tmp2 = sphere.m_Center + v2 * sphere.m_fRadius;

		tmp0 = tmp0 * mat;
		tmp0 = tmp1 * mat;
		tmp0 = tmp2 * mat;

		JAXREAL rtmp;
		m_fRadius = (tmp0 - m_Center).GetLength();
		rtmp = (tmp1 - m_Center).GetLength();
		if (m_fRadius < rtmp)
			m_fRadius = rtmp;
		rtmp = (tmp2 - m_Center).GetLength();
		if (m_fRadius < rtmp)
			m_fRadius = rtmp;
	}

	JAXREAL JaxSphere3::Distance(const JaxVector3& point, const JaxVector3& spherePoint) const
	{

	}
}
