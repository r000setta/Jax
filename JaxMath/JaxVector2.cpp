#include "JaxVector2.h"

namespace Jax
{
	void JaxVector2::operator+=(const JaxVector2& v)
	{
		x += v.x;
		y += v.y;
	}

	void JaxVector2::operator-=(const JaxVector2& v)
	{
		x -= v.x;
		y -= v.y;
	}

	void JaxVector2::operator*=(JAXREAL f)
	{
		x *= f;
		y *= f;
	}

	void JaxVector2::operator-=(JAXREAL f)
	{
		x -= f;
		y -= f;
	}

	void JaxVector2::operator+=(JAXREAL f)
	{
		x += f;
		y += f;
	}

	void JaxVector2::operator/=(JAXREAL f)
	{
		x /= f;
		y /= f;
	}

	JAXREAL JaxVector2::operator*(const JaxVector2& v) const
	{
		return v.x * x + v.y * y;
	}

	bool JaxVector2::operator==(const JaxVector2& v) const
	{
		for (size_t i = 0; i < 2; ++i)
		{
			if (ABS(m[i] - v.m[i]) > EPSILON_E4)
			{
				return false;
			}
		}
		return true;
	}

	JaxVector2 JaxVector2::operator*(JAXREAL f) const
	{
		return JaxVector2(x*f,y*f);
	}

	JaxVector2 JaxVector2::operator/(JAXREAL f) const
	{
		return JaxVector2(x/f,y/f);
	}

	JaxVector2 JaxVector2::operator+(JAXREAL f) const
	{
		return JaxVector2(x + f, y + f);
	}

	JaxVector2 JaxVector2::operator-(JAXREAL f) const
	{
		return JaxVector2(x - f, y - f);
	}

	JaxVector2 JaxVector2::operator+(const JaxVector2& v) const
	{
		return JaxVector2(x + v.x, y + v.y);
	}

	JaxVector2 JaxVector2::operator-(const JaxVector2& v) const
	{
		return JaxVector2(x - v.x, y - v.y);
	}

	void JaxVector2::Normalize()
	{
		JAXREAL f = (JAXREAL)sqrt(x * x + y * y);
		if (f != 0.0f)
		{
			x /= f, y /= f;
		}
	}
}
