#include "JaxVector4.h"
#include "JaxMatrix4x4.h"

namespace Jax
{
	JaxVector4::JaxVector4()
	{
		x = 0, y = 0, z = 0, w = 1.0f;
	}

	JaxVector4::JaxVector4(JAXREAL _x, JAXREAL _y, JAXREAL _z, JAXREAL _w)
	{
		x = _x, y = _y, z = _z, w = _w;
	}

	JaxVector4::JaxVector4(const JaxVector3& v)
	{
		Set(v);
	}

	JaxVector4::JaxVector4(byte R, byte G, byte B, byte A)
	{
		r = (R * (JAXREAL)1.0) / 255;
		g = (G * (JAXREAL)1.0) / 255;
		b = (B * (JAXREAL)1.0) / 255;
		r = (A * (JAXREAL)1.0) / 255;
	}

	void JaxVector4::GetVector3(JaxVector3& v) const
	{
		v.x = x;
		v.y = y;
		v.z = z;
	}

	JaxVector3 JaxVector4::GetVector3() const
	{
		return JaxVector3(x,y,z);
	}

	void JaxVector4::Set(const JaxVector3& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = 1.0f;
	}

	void JaxVector4::Set(JAXREAL _x, JAXREAL _y, JAXREAL _z, JAXREAL _w)
	{
		x = _x;
		y = _y;
		z = _z;
		w = _w;
	}

	JaxVector4 JaxVector4::operator*(const JaxMatrix4x4& m) const
	{
		JaxVector4 res;

		res.x = x * m._00 + y * m._10 + z * m._20 + w * m._30;
		res.y = x * m._01 + y * m._11 + z * m._21 + w * m._31;
		res.z = x * m._02 + y * m._12 + z * m._22 + w * m._32;
		res.w = x * m._03 + y * m._13 + z * m._23 + w * m._33;

		return res;
	}

	void JaxVector4::operator+=(const JaxVector4& v)
	{
		for (byte i = 0; i < 4; ++i) m[i] += v.m[i];
	}

	void JaxVector4::operator-=(const JaxVector4& v)
	{
		for (byte i = 0; i < 4; ++i) m[i] -= v.m[i];
	}

	void JaxVector4::operator*=(const JaxVector4& v)
	{
		for (byte i = 0; i < 4; ++i) m[i] *= v.m[i];
	}

	void JaxVector4::operator/=(const JaxVector4& v)
	{
		for (byte i = 0; i < 4; ++i) m[i] /= v.m[i];
	}

	void JaxVector4::operator*=(JAXREAL f)
	{
		for (byte i = 0; i < 4; ++i) m[i] *= f;
	}

	void JaxVector4::operator/=(JAXREAL f)
	{
		for (byte i = 0; i < 4; ++i) m[i] /= f;
	}

	void JaxVector4::operator+=(JAXREAL f)
	{
		for (byte i = 0; i < 4; ++i) m[i] += f;
	}

	void JaxVector4::operator-=(JAXREAL f)
	{
		for (byte i = 0; i < 4; ++i) m[i] -= f;
	}

	JaxVector4 JaxVector4::operator+(JAXREAL f) const
	{
		return JaxVector4(x + f, y + f, z + f, w + f);
	}

	JaxVector4 JaxVector4::operator-(JAXREAL f) const
	{
		return JaxVector4(x - f, y - f, z - f, w - f);
	}

	JaxVector4 JaxVector4::operator/(JAXREAL f) const
	{
		return JaxVector4(x / f, y / f, z / f, w / f);
	}

	JaxVector4 JaxVector4::operator*(JAXREAL f) const
	{
		return JaxVector4(x * f, y * f, z * f, w * f);
	}

	JaxVector4 JaxVector4::operator+(const JaxVector4& v) const
	{
		return JaxVector4(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	JaxVector4 JaxVector4::operator-(const JaxVector4& v) const
	{
		return JaxVector4(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	JaxVector4 JaxVector4::operator*(const JaxVector4& v) const
	{
		return JaxVector4(x * v.x, y * v.y, z * v.z, w * v.w);
	}

	JaxVector4 JaxVector4::operator/(const JaxVector4& v) const
	{
		return JaxVector4(x / v.x, y / v.y, z / v.z, w / v.w);
	}

	bool JaxVector4::operator==(const JaxVector4& v) const
	{
		for (byte i = 0; i < 4; ++i) {
			if (v.m[i] != m[i]) {
				return false;
			}
		}
		return true;
	}

	JAXREAL& JaxVector4::operator[](size_t i)
	{
		return m[i];
	}

	const JAXREAL& JaxVector4::operator[](size_t i) const
	{
		return m[i];
	}

	DWORD JaxVector4::GetDWARGB() const
	{
		byte R, G, B, A;
		GetUCColor(A, R, G, B);
		return (DWORD)(((((A) & 0xff) << 24) | (((R) & 0xff) << 16) | (((G) & 0xff) << 8) | ((B) & 0xff)));
	}

	DWORD JaxVector4::GetDWRGBA() const
	{
		byte R, G, B, A;
		GetUCColor(A, R, G, B);
		return (DWORD)(((((R) & 0xff) << 24) | (((G) & 0xff) << 16) | (((B) & 0xff) << 8) | ((A) & 0xff)));
	}

	DWORD JaxVector4::GetDWBGRA() const
	{
		byte R, G, B, A;
		GetUCColor(A, R, G, B);
		return ((DWORD)((((B) & 0xff) << 24) | (((G) & 0xff) << 16) | (((R) & 0xff) << 8) | ((A) & 0xff)));
	}

	DWORD JaxVector4::GetDWABGR() const
	{
		byte R, G, B, A;
		GetUCColor(A, R, G, B);
		return ((DWORD)((((A) & 0xff) << 24) | (((B) & 0xff) << 16) | (((G) & 0xff) << 8) | ((R) & 0xff)));
	}


	void JaxVector4::GetUCColor(byte& A, byte& R, byte& G, byte& B) const
	{
		A = (byte)(a * 255);
		R = (byte)(r * 255);
		G = (byte)(g * 255);
		B = (byte)(b * 255);
	}

	void JaxVector4::CreateFromARGB(DWORD ARGB)
	{
		byte a, r, g, b;
		JaxDWCOLORGetARGB(ARGB, a, r, g, b);
		*this = JaxVector4(r, g, b, a);
	}

	void JaxVector4::CreateFromBGRA(DWORD BGRA)
	{
		byte a, r, g, b;
		JaxDWCOLORGetBGRA(BGRA, a, r, g, b);
		*this = JaxVector4(r, g, b, a);
	}

	void JaxVector4::CreateFromRGBA(DWORD RGBA)
	{
		byte a, r, g, b;
		JaxDWCOLORGetRGBA(RGBA, a, r, g, b);
		*this = JaxVector4(r, g, b, a);
	}

	void JaxVector4::CreateFromABGR(DWORD ABGR)
	{
		byte a, r, g, b;
		JaxDWCOLORGetABGR(ABGR, a, r, g, b);
		*this = JaxVector4(r, g, b, a);
	}

}