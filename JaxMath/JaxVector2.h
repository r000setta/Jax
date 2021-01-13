#pragma once
#include "JaxMath.h"

namespace Jax
{
	class JAXMATH_API JaxVector2
	{
	public:
		union
		{
			JAXREAL m[2];
			struct
			{
				JAXREAL x, y;
			};
		};

		JaxVector2() :x(0), y(0) {}
		JaxVector2(JAXREAL _x, JAXREAL _y) :x(_x), y(_y) {}

		FORCEINLINE void Set(JAXREAL _x, JAXREAL _y)
		{
			x = _x;
			y = _y;
		}

		void operator+=(const JaxVector2& v);
		void operator-=(const JaxVector2& v);

		void operator*=(JAXREAL f);
		void operator-=(JAXREAL f);
		void operator+=(JAXREAL f);
		void operator/=(JAXREAL f);

		JAXREAL operator*(const JaxVector2& v) const;

		bool operator==(const JaxVector2& v) const;

		JaxVector2 operator*(JAXREAL f) const;
		JaxVector2 operator/(JAXREAL f) const;
		JaxVector2 operator+(JAXREAL f) const;
		JaxVector2 operator-(JAXREAL f) const;

		JaxVector2 operator+(const JaxVector2& v) const;
		JaxVector2 operator-(const JaxVector2& v) const;

		void Normalize();
	};
}