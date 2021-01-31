#pragma once
#include "JaxVector3.h"
#include "JaxMatrix3x3.h"
#include "JaxVector4.h"

namespace Jax
{
	class JaxLine3;
	class JaxSphere3;
	class JAXMATH_API JaxPlane3
	{
	protected:
		JaxVector3 m_N;
		JAXREAL m_fD;

	public:
		JaxPlane3();
		JaxPlane3(const JaxVector3& N, const JaxVector3& p);
		JaxPlane3(const JaxVector3& N, const JaxVector3& p1, const JaxVector3& p2);
		JaxPlane3(const JaxVector3 point[3]);
		JaxPlane3(const JaxVector3& N, JAXREAL fd);
		void Transform(const JaxPlane3& plane, const JaxMatrix4x4& mat);

		FORCEINLINE const JaxVector3& GetN() const
		{
			return m_N;
		}
		FORCEINLINE JaxVector3 GetPoint() const
		{
			if (ABS(m_N.z) < EPSILON_E4)
			{
				return JaxVector3(0.0f, 0.0f, 0.0f);
			}
			return JaxVector3(0.0f, 0.0f, -m_fD / m_N.z);
		}
		FORCEINLINE JAXREAL GetfD() const
		{
			return m_fD;
		}
		FORCEINLINE void Set(const JaxVector3& N, const JaxVector3& P)
		{
			m_N = N;
			m_N.Normalize();
			m_fD = -(m_N.Dot(P));
		}
		FORCEINLINE void Set(const JaxVector3& N, JAXREAL fd)
		{
			JAXREAL len = N.GetLength();
			m_N = N / len;
			m_fD = fd / len;
		}
		FORCEINLINE void Set(const JaxVector3& p0, const JaxVector3& p1, const JaxVector3& p2)
		{
			JaxVector3 edge1 = p1 - p0;
			JaxVector3 edge2 = p2 - p0;
			m_N.Cross(edge1, edge2);
			m_N.Normalize();
			m_fD = -(m_N.Dot(p0));
		}

		FORCEINLINE void Set(const JaxVector3 points[3])
		{
			Set(points[0], points[1], points[2]);
		}
		FORCEINLINE JaxPlane3 GetPlane() const
		{
			return *this;
		}
	};
}