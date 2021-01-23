#pragma once
#include "JaxMath.h"

namespace Jax
{
	class JaxMatrix3x3;
	class JAXMATH_API JaxVector3
	{
	public:
		union
		{
			JAXREAL m[3];
			struct
			{
				JAXREAL x, y, z;
			};
		};

		JaxVector3();
		JaxVector3(JAXREAL _x, JAXREAL _y, JAXREAL _z);

		FORCEINLINE void Set(JAXREAL _x, JAXREAL _y, JAXREAL _z);
		FORCEINLINE JAXREAL GetLength() const;
		FORCEINLINE JAXREAL GetSqrtLength() const;
		FORCEINLINE void Negate();
		FORCEINLINE void Normalize();
		FORCEINLINE void Cross(const JaxVector3& v1, const JaxVector3& v2);

		JAXREAL AngleWith(JaxVector3& v);
		void Create(const JaxVector3& v1, const JaxVector3& v2);

		JaxVector3 ReflectDir(const JaxVector3& N) const;

		JaxVector3& operator+=(const JaxVector3& v);
		JaxVector3& operator-=(const JaxVector3& v);
		JaxVector3& operator/=(const JaxVector3& v);
		JaxVector3& operator*=(const JaxVector3& v);

		JaxVector3 operator+(JAXREAL f) const;
		JaxVector3 operator-(JAXREAL f) const;
		JaxVector3 operator*(JAXREAL f) const;
		JaxVector3 operator/(JAXREAL f) const;

		JaxVector3& operator*=(JAXREAL f);
		JaxVector3& operator/=(JAXREAL f);
		JaxVector3& operator+=(JAXREAL f);
		JaxVector3& operator-=(JAXREAL f);

		JaxVector3 operator+(const JaxVector3& v) const;
		JaxVector3 operator-(const JaxVector3& v) const;
		JaxVector3 operator/(const JaxVector3& v) const;
		JaxVector3 operator*(const JaxVector3& v) const;

		JaxVector3 operator*(const JaxMatrix3x3& mat) const;

		JAXREAL Dot(const JaxVector3& v) const;
		bool operator==(const JaxVector3& v) const;

		bool IsParallel(const JaxVector3& vector) const;

		const static JaxVector3 sm_Up;
		const static JaxVector3 sm_Right;
		const static JaxVector3 sm_Front;
		const static JaxVector3 sm_Zero;
		const static JaxVector3 sm_One;
	};
}