#pragma once
#include "JaxMath.h"
#include "JaxVector3.h"

namespace Jax
{
	class JAXMATH_API JaxVector4
	{
	public:
		union
		{
			JAXREAL m[4];
			struct
			{
				JAXREAL x, y, z, w;
			};
			struct
			{
				JAXREAL r, g, b, a;
			};
		};

		JaxVector4();
		JaxVector4(JAXREAL _x, JAXREAL _y, JAXREAL _z, JAXREAL _w = 1.0f);
		JaxVector4(const JaxVector3& v);
		JaxVector4(byte R, byte G, byte B, byte A = 255);

		FORCEINLINE void GetVector3(JaxVector3& v) const;
		FORCEINLINE JaxVector3 GetVector3() const;
		FORCEINLINE void Set(const JaxVector3& v);
		FORCEINLINE void Set(JAXREAL _x, JAXREAL _y, JAXREAL _z, JAXREAL _w = 1.0f);

		void operator+=(const JaxVector4& v);
		void operator-=(const JaxVector4& v);
		void operator*=(const JaxVector4& v);
		void operator/=(const JaxVector4& v);

		void operator*=(JAXREAL f);
		void operator/=(JAXREAL f);
		void operator+=(JAXREAL f);
		void operator-=(JAXREAL f);

		JaxVector4 operator+(JAXREAL f) const;
		JaxVector4 operator-(JAXREAL f) const;
		JaxVector4 operator*(JAXREAL f) const;
		JaxVector4 operator/(JAXREAL f) const;

		JaxVector4 operator+(const JaxVector4& v) const;
		JaxVector4 operator-(const JaxVector4& v) const;
		JaxVector4 operator*(const JaxVector4& v) const;
		JaxVector4 operator/(const JaxVector4& v) const;

		bool operator==(const JaxVector4& v) const;

		JAXREAL& operator[](size_t i);
		const JAXREAL& operator[](size_t i) const;

		DWORD GetDWARGB() const;
		DWORD GetDWRGBA() const;
		DWORD GetDWBGRA() const;
		DWORD GetDWABGR() const;

		void GetUCColor(byte& A, byte& R, byte& G, byte& B) const;

		void CreateFromARGB(DWORD ARGB);
		void CreateFromBGRA(DWORD BGRA);
		void CreateFromRGBA(DWORD RGBA);
		void CreateFromABGR(DWORD ABGR);
	};

	using JaxColorRGBA = JaxVector4;

	FORCEINLINE void JaxDWCOLORGetARGB(DWORD ARGB, byte& a, byte& r, byte& g, byte& b)
	{
		a = (ARGB >> 24) & 0xff;
		r = (ARGB >> 16) & 0xff;
		g = (ARGB >> 8) & 0xff;
		b = (ARGB) & 0xff;
	}

	FORCEINLINE void JaxDWCOLORGetBGRA(DWORD BGRA, byte& a, byte& r, byte& g, byte& b)
	{
		b = (BGRA >> 24) & 0xff;
		g = (BGRA >> 16) & 0xff;
		r = (BGRA >> 8) & 0xff;
		a = (BGRA) & 0xff;
	}

	FORCEINLINE void JaxDWCOLORGetRGBA(DWORD RGBA, byte& a, byte& r, byte& g, byte& b)
	{
		r = (RGBA >> 24) & 0xff;
		g = (RGBA >> 16) & 0xff;
		b = (RGBA >> 8) & 0xff;
		a = (RGBA) & 0xff;
	}

	FORCEINLINE void JaxDWCOLORGetABGR(DWORD ABGR, byte& a, byte& r, byte& g, byte& b)
	{
		a = (ABGR >> 24) & 0xff;
		b = (ABGR >> 16) & 0xff;
		g = (ABGR >> 8) & 0xff;
		r = (ABGR) & 0xff;
	}
}