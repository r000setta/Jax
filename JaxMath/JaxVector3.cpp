#include "JaxVector3.h"
#include "JaxMatrix3x3.h"
#include "JaxMatrix4x4.h"

namespace Jax
{
	const JaxVector3 JaxVector3::sm_Up = JaxVector3(0.0f, 1.0f, 0.0f);
	const JaxVector3 JaxVector3::sm_Right = JaxVector3(1.0f, 0.0f, 0.0f);
	const JaxVector3 JaxVector3::sm_Front = JaxVector3(0.0f, 0.0f, 1.0f);
	const JaxVector3 JaxVector3::sm_Zero = JaxVector3(0.0f, 0.0f, 0.0f);
	const JaxVector3 JaxVector3::sm_One = JaxVector3(1.0f, 1.0f, 1.0f);

	JaxVector3::JaxVector3()
	{
		x = 0;
		y = 0;
		z = 0;
	}

	JaxVector3::JaxVector3(JAXREAL _x, JAXREAL _y, JAXREAL _z) :x(_x), y(_y), z(_z) {}

	void JaxVector3::Set(JAXREAL _x, JAXREAL _y, JAXREAL _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	JAXREAL JaxVector3::GetLength() const
	{
		return (JAXREAL)sqrt(x * x + y * y + z * z);
	}

	JAXREAL JaxVector3::GetSqrtLength() const
	{
		return x * x + y * y + z * z;
	}

	void JaxVector3::Negate()
	{
		x = -x;
		y = -y;
		z = -z;
	}

	void JaxVector3::Normalize()
	{
		JAXREAL f = GetLength();
		if (f != 0.0f)
		{
			x /= f;
			y /= f;
			z /= f;
		}
	}

	void JaxVector3::Cross(const JaxVector3& v1, const JaxVector3& v2)
	{
		x = v1.y * v2.z - v1.z * v2.y;
		y = v1.z * v2.x - v1.x * v2.z;
		z = v1.x * v2.y - v1.y * v2.x;
	}

	JAXREAL JaxVector3::AngleWith(JaxVector3& v)
	{
		return (JAXREAL)acos(((*this).Dot(v)) / (this->GetLength() * v.GetLength()));
	}

	void JaxVector3::Create(const JaxVector3& v1, const JaxVector3& v2)
	{
		x = v2.x - v1.x;
		y = v2.y - v1.y;
		z = v2.z - v1.z;
	}
	JaxVector3 JaxVector3::ReflectDir(const JaxVector3& N) const
	{
		return N * Dot(N) * 2 + *this;
	}
	JaxVector3& JaxVector3::operator+=(const JaxVector3& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	JaxVector3& JaxVector3::operator-=(const JaxVector3& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	JaxVector3& JaxVector3::operator/=(const JaxVector3& v)
	{
		*this = JaxVector3(x / v.x, y / v.y, z / v.z);
		return *this;
	}

	JaxVector3& JaxVector3::operator*=(const JaxVector3& v)
	{
		*this = JaxVector3(x * v.x, y * v.y, z * v.z);
		return *this;
	}

	JaxVector3 JaxVector3::operator*(JAXREAL f) const
	{
		return JaxVector3(x * f, y * f, z * f);
	}

	JaxVector3 JaxVector3::operator+(JAXREAL f) const
	{
		return JaxVector3(x + f, y + f, z + f);
	}

	JaxVector3 JaxVector3::operator-(JAXREAL f) const
	{
		return JaxVector3(x - f, y - f, z - f);
	}

	JaxVector3 JaxVector3::operator/(JAXREAL f) const
	{
		return JaxVector3(x / f, y / f, z / f);
	}

	JaxVector3& JaxVector3::operator*=(JAXREAL f)
	{
		x *= f;
		y *= f;
		z *= f;
		return *this;
	}

	JaxVector3& JaxVector3::operator/=(JAXREAL f)
	{
		x /= f;
		y /= f;
		z /= f;
		return *this;
	}

	JaxVector3& JaxVector3::operator+=(JAXREAL f)
	{
		x += f;
		y += f;
		z += f;
		return *this;
	}

	JaxVector3& JaxVector3::operator-=(JAXREAL f)
	{
		x -= f;
		y -= f;
		z -= f;
		return *this;
	}

	JaxVector3 JaxVector3::operator+(const JaxVector3& v) const
	{
		return JaxVector3(x + v.x, y + v.y, z + v.z);
	}

	JaxVector3 JaxVector3::operator-(const JaxVector3& v) const
	{
		return JaxVector3(x - v.x, y - v.y, z - v.z);
	}

	JaxVector3 JaxVector3::operator*(const JaxVector3& v) const
	{
		return JaxVector3(x * v.x, y * v.y, z * v.z);
	}

	JaxVector3 JaxVector3::operator*(const JaxMatrix3x3& mat) const
	{
		JaxVector3 res;
		res.x = x * mat._00 + y * mat._10 + z * mat._20;
		res.y = x * mat._01 + y * mat._11 + z * mat._21;
		res.z = x * mat._02 + y * mat._12 + z * mat._22;
		return res;
	}

	JaxVector3 JaxVector3::operator*(const JaxMatrix4x4& mat) const
	{
		JaxVector3 res;
		res.x = x * mat._00 + y * mat._10 + z * mat._20 + mat._30;
		res.y = x * mat._01 + y * mat._11 + z * mat._21 + mat._31;
		res.z = x * mat._02 + y * mat._12 + z * mat._22 + mat._32;
		JAXREAL w = x * mat._03 + y * mat._13 + z * mat._23 + mat._33;

		res.x = res.x / w;
		res.y = res.y / w;
		res.z = res.z / w;
	}

	JAXREAL JaxVector3::Dot(const JaxVector3& v) const
	{
		return (v.x * x + v.y * y + v.z * z);
	}

	bool JaxVector3::operator==(const JaxVector3& v) const
	{
		for (size_t i = 0; i < 3; ++i)
		{
			if (ABS(m[i] - v.m[i]) > EPSILON_E4)
			{
				return false;
			}
		}
		return true;
	}

	bool JaxVector3::IsParallel(const JaxVector3& vector) const
	{
		JAXREAL t0, t1;
		bool tmp = false;
		t0 = x * vector.y;
		t1 = y * vector.x;

		if (ABS(t0 - t1) > EPSILON_E4)
		{
			tmp = true;
		}
		t0 = y * vector.z;
		t1 = z * vector.y;

		if (ABS(t0 - t1) > EPSILON_E4 && tmp)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	JaxVector3 JaxVector3::operator/(const JaxVector3& v) const
	{
		return JaxVector3(x / v.x, y / v.y, z / v.z);
	}

}




