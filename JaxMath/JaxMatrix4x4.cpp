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

	void JaxMatrix4x4::TransposeOf(const JaxMatrix4x4& mat)
	{
		_00 = mat._00;
		_10 = mat._01;
		_20 = mat._02;
		_30 = mat._03;

		_01 = mat._10;
		_11 = mat._11;
		_21 = mat._12;
		_31 = mat._13;

		_02 = mat._20;
		_12 = mat._21;
		_22 = mat._22;
		_32 = mat._23;

		_03 = mat._30;
		_13 = mat._31;
		_23 = mat._32;
		_33 = mat._33;
	}

	void JaxMatrix4x4::InverseOf(const JaxMatrix4x4& mat)
	{
		JaxMatrix4x4 trans;
		JAXREAL tmp[12], det;
		trans.TransposeOf(mat);

		tmp[0] = trans._22 * trans._33;
		tmp[1] = trans._23 * trans._32;
		tmp[2] = trans._21 * trans._33;
		tmp[3] = trans._23 * trans._31;
		tmp[4] = trans._21 * trans._32;
		tmp[5] = trans._22 * trans._31;
		tmp[6] = trans._20 * trans._33;
		tmp[7] = trans._23 * trans._30;
		tmp[8] = trans._20 * trans._32;
		tmp[9] = trans._22 * trans._30;
		tmp[10] = trans._20 * trans._31;
		tmp[11] = trans._21 * trans._30;


		_00 = tmp[0] * trans._11 + tmp[3] * trans._12 + tmp[4] * trans._13;
		_00 -= tmp[1] * trans._11 + tmp[2] * trans._12 + tmp[5] * trans._13;
		_01 = tmp[1] * trans._10 + tmp[6] * trans._12 + tmp[9] * trans._13;
		_01 -= tmp[0] * trans._10 + tmp[7] * trans._12 + tmp[8] * trans._13;
		_02 = tmp[2] * trans._10 + tmp[7] * trans._11 + tmp[10] * trans._13;
		_02 -= tmp[3] * trans._10 + tmp[6] * trans._11 + tmp[11] * trans._13;
		_03 = tmp[5] * trans._10 + tmp[8] * trans._11 + tmp[11] * trans._12;
		_03 -= tmp[4] * trans._10 + tmp[9] * trans._11 + tmp[10] * trans._12;
		_10 = tmp[1] * trans._01 + tmp[2] * trans._02 + tmp[5] * trans._03;
		_10 -= tmp[0] * trans._01 + tmp[3] * trans._02 + tmp[4] * trans._03;
		_11 = tmp[0] * trans._00 + tmp[7] * trans._02 + tmp[8] * trans._03;
		_11 -= tmp[1] * trans._00 + tmp[6] * trans._02 + tmp[9] * trans._03;
		_12 = tmp[3] * trans._00 + tmp[6] * trans._01 + tmp[11] * trans._03;
		_12 -= tmp[2] * trans._00 + tmp[7] * trans._01 + tmp[10] * trans._03;
		_13 = tmp[4] * trans._00 + tmp[9] * trans._01 + tmp[10] * trans._02;
		_13 -= tmp[5] * trans._00 + tmp[8] * trans._01 + tmp[11] * trans._02;


		tmp[0] = trans._02 * trans._13;
		tmp[1] = trans._03 * trans._12;
		tmp[2] = trans._01 * trans._13;
		tmp[3] = trans._03 * trans._11;
		tmp[4] = trans._01 * trans._12;
		tmp[5] = trans._02 * trans._11;
		tmp[6] = trans._00 * trans._13;
		tmp[7] = trans._03 * trans._10;
		tmp[8] = trans._00 * trans._12;
		tmp[9] = trans._02 * trans._10;
		tmp[10] = trans._00 * trans._11;
		tmp[11] = trans._01 * trans._10;


		_20 = tmp[0] * trans._31 + tmp[3] * trans._32 + tmp[4] * trans._33;
		_20 -= tmp[1] * trans._31 + tmp[2] * trans._32 + tmp[5] * trans._33;
		_21 = tmp[1] * trans._30 + tmp[6] * trans._32 + tmp[9] * trans._33;
		_21 -= tmp[0] * trans._30 + tmp[7] * trans._32 + tmp[8] * trans._33;
		_22 = tmp[2] * trans._30 + tmp[7] * trans._31 + tmp[10] * trans._33;
		_22 -= tmp[3] * trans._30 + tmp[6] * trans._31 + tmp[11] * trans._33;
		_23 = tmp[5] * trans._30 + tmp[8] * trans._31 + tmp[11] * trans._32;
		_23 -= tmp[4] * trans._30 + tmp[9] * trans._31 + tmp[10] * trans._32;
		_30 = tmp[2] * trans._22 + tmp[5] * trans._23 + tmp[1] * trans._21;
		_30 -= tmp[4] * trans._23 + tmp[0] * trans._21 + tmp[3] * trans._22;
		_31 = tmp[8] * trans._23 + tmp[0] * trans._20 + tmp[7] * trans._22;
		_31 -= tmp[6] * trans._22 + tmp[9] * trans._23 + tmp[1] * trans._20;
		_32 = tmp[6] * trans._21 + tmp[11] * trans._23 + tmp[3] * trans._20;
		_32 -= tmp[10] * trans._23 + tmp[2] * trans._20 + tmp[7] * trans._21;
		_33 = tmp[10] * trans._22 + tmp[4] * trans._20 + tmp[9] * trans._21;
		_33 -= tmp[8] * trans._21 + tmp[11] * trans._22 + tmp[5] * trans._20;

		det = trans._00 * _00 + trans._01 * _01 + trans._02 * _02 + trans._03 * _03;

		det = 1 / det;

		_00 *= det;
		_01 *= det;
		_02 *= det;
		_03 *= det;

		_10 *= det;
		_11 *= det;
		_12 *= det;
		_13 *= det;

		_20 *= det;
		_21 *= det;
		_22 *= det;
		_23 *= det;

		_30 *= det;
		_31 *= det;
		_32 *= det;
		_33 *= det;

	}


}