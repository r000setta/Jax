#pragma once
#include "JaxMath.h"
#include "JaxVector3.h"
#include "JaxVector4.h"

namespace Jax
{
	
	class JAXMATH_API JaxMatrix4x4
	{
	public:
		union
		{
			JAXREAL m[16];
			struct
			{
				JAXREAL _00, _01, _02, _03;
				JAXREAL _10, _11, _12, _13;
				JAXREAL _20, _21, _22, _23;
				JAXREAL _30, _31, _32, _33;
			};
			JAXREAL M[4][4];
		};

		JaxMatrix4x4();
		JaxMatrix4x4(JAXREAL m00, JAXREAL m01, JAXREAL m02, JAXREAL m03,
			JAXREAL m10, JAXREAL m11, JAXREAL m12, JAXREAL m13,
			JAXREAL m20, JAXREAL m21, JAXREAL m22, JAXREAL m23,
			JAXREAL m30, JAXREAL m31, JAXREAL m32, JAXREAL m33);

		JaxMatrix4x4 operator*(JAXREAL f) const;
		JaxMatrix4x4 operator+(JAXREAL f) const;
		JaxMatrix4x4 operator-(JAXREAL f) const;
		JaxMatrix4x4 operator+(const JaxMatrix4x4& mat) const;
		JaxMatrix4x4 operator-(const JaxMatrix4x4& mat) const;

		void operator*=(JAXREAL f);
		void operator+=(JAXREAL f);
		void operator-=(JAXREAL f);
		void operator+=(const JaxMatrix4x4& mat);
		void operator-=(const JaxMatrix4x4& mat);

		bool operator==(const JaxMatrix4x4& mat) const;

		FORCEINLINE void Identity();
		FORCEINLINE void SetZero();
	};
}