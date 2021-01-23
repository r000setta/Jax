#pragma once
#include "JaxVector3.h"

namespace Jax
{
	class JAXMATH_API JaxMatrix3x3
	{
	public:
		union
		{
			JAXREAL m[9];
			struct
			{
				JAXREAL _00, _01, _02;
				JAXREAL _10, _11, _12;
				JAXREAL _20, _21, _22;
			};
			JAXREAL M[3][3];
		};

		JaxMatrix3x3();
		JaxMatrix3x3(JAXREAL m00, JAXREAL m01, JAXREAL m02,
			JAXREAL m10, JAXREAL m11, JAXREAL m12,
			JAXREAL m20, JAXREAL m21, JAXREAL m22);
		
		JaxMatrix3x3 operator*(JAXREAL f) const;
		JaxMatrix3x3 operator+(JAXREAL f) const;
		JaxMatrix3x3 operator-(JAXREAL f) const;
		JaxMatrix3x3 operator-(const JaxMatrix3x3 &mat) const;
		JaxMatrix3x3 operator+(const JaxMatrix3x3 &mat) const;

		void operator*=(JAXREAL f);
		void operator+=(JAXREAL f);
		void operator-=(JAXREAL f);
		void operator-=(const JaxMatrix3x3& mat);
		void operator+=(const JaxMatrix3x3& mat);

		bool operator==(const JaxMatrix3x3& mat);

		FORCEINLINE JaxMatrix3x3 operator*(const JaxMatrix3x3& mat) const;
		FORCEINLINE JaxVector3 operator*(const JaxVector3& vec) const;

		FORCEINLINE void Identity();
		FORCEINLINE void Transpose(const JaxMatrix3x3& mat);
	};
}