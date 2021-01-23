#include "JaxMatrix3x3.h"

namespace Jax
{
	JaxMatrix3x3::JaxMatrix3x3()
	{
		Identity();
	}

	JaxMatrix3x3::JaxMatrix3x3(JAXREAL m00, JAXREAL m01, JAXREAL m02, JAXREAL m10, JAXREAL m11, JAXREAL m12, JAXREAL m20, JAXREAL m21, JAXREAL m22)
	{
		_00 = m00; _01 = m01; _02 = m02;
		_10 = m10; _11 = m11; _12 = m12;
		_20 = m20; _21 = m21; _22 = m22;
	}

	JaxMatrix3x3 JaxMatrix3x3::operator*(JAXREAL f) const
	{
		JaxMatrix3x3 tmp;
		for (size_t i = 0; i < 8; ++i) tmp.m[i] = m[i] * f;
		return tmp;
	}

	JaxMatrix3x3 JaxMatrix3x3::operator+(JAXREAL f) const
	{
		JaxMatrix3x3 tmp;
		for (size_t i = 0; i < 8; ++i) tmp.m[i] = m[i] + f;
		return tmp;
	}

	JaxMatrix3x3 JaxMatrix3x3::operator-(JAXREAL f) const
	{
		JaxMatrix3x3 tmp;
		for (size_t i = 0; i < 8; ++i) tmp.m[i] = m[i] - f;
		return tmp;
	}

	JaxMatrix3x3 JaxMatrix3x3::operator-(const JaxMatrix3x3& mat) const
	{
		JaxMatrix3x3 tmp;
		for (size_t i = 0; i < 8; ++i) tmp.m[i] = m[i] - mat.m[i];
		return tmp;
	}

	JaxMatrix3x3 JaxMatrix3x3::operator+(const JaxMatrix3x3& mat) const
	{
		JaxMatrix3x3 tmp;
		for (size_t i = 0; i < 8; ++i) tmp.m[i] = m[i] + mat.m[i];
		return tmp;
	}

	void JaxMatrix3x3::operator*=(JAXREAL f)
	{
		for (size_t i = 0; i < 8; ++i) m[i] *= f;
	}

	void JaxMatrix3x3::operator-=(JAXREAL f)
	{
		for (size_t i = 0; i < 8; ++i) m[i] -= f;
	}

	void JaxMatrix3x3::operator-=(const JaxMatrix3x3& mat)
	{
		for (size_t i = 0; i < 8; ++i) m[i] -= mat.m[i];
	}

	void JaxMatrix3x3::operator+=(const JaxMatrix3x3& mat)
	{
		for (size_t i = 0; i < 8; ++i) m[i] += mat.m[i];
	}

	bool JaxMatrix3x3::operator==(const JaxMatrix3x3& mat)
	{
		for (size_t i = 0; i < 8; ++i)
		{
			if (mat.m[i] != m[i]) return false;
		}
		return true;
	}

	JaxMatrix3x3 JaxMatrix3x3::operator*(const JaxMatrix3x3& mat) const
	{
		JaxMatrix3x3 res;
		for (byte i = 0; i < 3; ++i) {
			for (byte j = 0; j < 3; ++j) {
				for (byte k = 0; k < 3; ++k) {
					res.M[i][j] += M[i][k] * mat.M[k][j];
				}
			}
		}
		return res;
	}

	JaxVector3 JaxMatrix3x3::operator*(const JaxVector3& vec) const
	{
		return vec * (*this);
	}

	void JaxMatrix3x3::operator+=(JAXREAL f)
	{
		for (size_t i = 0; i < 8; ++i) m[i] += f;
	}

	void JaxMatrix3x3::Identity()
	{
		JaxMemset(m, 0, sizeof(JaxMatrix3x3));
		_00 = _11 = _22 = 1.0f;
	}

	void JaxMatrix3x3::Transpose(const JaxMatrix3x3& mat)
	{
		_00 = mat._00;
		_10 = mat._01;
		_20 = mat._02;

		_01 = mat._10;
		_11 = mat._11;
		_12 = mat._21;

		_02 = mat._20;
		_12 = mat._21;
		_22 = mat._22;
	}


}
