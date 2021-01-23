#include "JaxMatrix4x4.h"

namespace Jax
{
	JaxMatrix4x4::JaxMatrix4x4()
	{
		Identity();
	}

	JaxMatrix4x4::JaxMatrix4x4(JAXREAL m00, JAXREAL m01, JAXREAL m02, JAXREAL m03, JAXREAL m10, JAXREAL m11, JAXREAL m12, JAXREAL m13, JAXREAL m20, JAXREAL m21, JAXREAL m22, JAXREAL m23, JAXREAL m30, JAXREAL m31, JAXREAL m32, JAXREAL m33)
	{
		_00 = m00; _01 = m01; _02 = m02; _03 = m03;
		_10 = m10; _11 = m11; _12 = m12; _13 = m13;
		_20 = m20; _21 = m21; _22 = m22; _23 = m23;
		_30 = m30; _31 = m31; _32 = m32; _33 = m33;
	}

	JaxMatrix4x4 JaxMatrix4x4::operator*(JAXREAL f) const
	{
		JaxMatrix4x4 tmp;
		for (size_t i = 0; i < 16; ++i) tmp.m[i] = m[i] * f;
		return tmp;
	}

	JaxMatrix4x4 JaxMatrix4x4::operator+(JAXREAL f) const
	{
		JaxMatrix4x4 tmp;
		for (size_t i = 0; i < 16; ++i) tmp.m[i] = m[i] + f;
		return tmp;
	}

	JaxMatrix4x4 JaxMatrix4x4::operator-(JAXREAL f) const
	{
		JaxMatrix4x4 tmp;
		for (size_t i = 0; i < 16; ++i) tmp.m[i] = m[i] - f;
		return tmp;
	}

	JaxMatrix4x4 JaxMatrix4x4::operator+(const JaxMatrix4x4& mat) const
	{
		JaxMatrix4x4 tmp;
		for (size_t i = 0; i < 16; ++i) tmp.m[i] = m[i] + mat.m[i];
		return tmp;
	}

	JaxMatrix4x4 JaxMatrix4x4::operator-(const JaxMatrix4x4& mat) const
	{
		JaxMatrix4x4 tmp;
		for (size_t i = 0; i < 16; ++i) tmp.m[i] = m[i] - mat.m[i];
		return tmp;
	}

	void JaxMatrix4x4::operator*=(JAXREAL f)
	{
		for (size_t i = 0; i < 16; ++i) m[i] *= f;
	}

	void JaxMatrix4x4::operator+=(JAXREAL f)
	{
		for (size_t i = 0; i < 16; ++i) m[i] += f;
	}

	void JaxMatrix4x4::operator-=(JAXREAL f)
	{
		for (size_t i = 0; i < 16; ++i) m[i] -= f;
	}

	void JaxMatrix4x4::operator+=(const JaxMatrix4x4& mat)
	{
		for (size_t i = 0; i < 16; ++i) m[i] += mat.m[i];
	}

	void JaxMatrix4x4::operator-=(const JaxMatrix4x4& mat)
	{
		for (size_t i = 0; i < 16; ++i) m[i] -= mat.m[i];
	}

	bool JaxMatrix4x4::operator==(const JaxMatrix4x4& mat) const
	{
		for (size_t i = 0; i < 16; ++i) {
			if (mat.m[i] != m[i]) return false;
		}
		return true;
	}

	void JaxMatrix4x4::Identity()
	{
		JaxMemset(m, 0, sizeof(JaxMatrix4x4));
		_00 = _10 = _20 = _30 = 1.0f;
	}

	void JaxMatrix4x4::SetZero()
	{
		JaxMemset(m, 0, sizeof(JaxMatrix4x4));
	}


}