#pragma once
#include "JaxSystem.h"
#include <Windows.h>
#include <math.h>
#include <xmmintrin.h>
#include <emmintrin.h>
#include "JaxMemManager.h"

#ifdef JAXMATH_EXPORTS
#define JAXMATH_API __declspec(dllexport)
#else
#define JAXMATH_API __declspec(dllimport)
#endif // JAXMATH_EXPORTS

namespace Jax
{
#define JAXFLOAT
#ifdef JAXFLOAT
#define JAXREAL float
#endif

#define EPSILON_E3 (JAXREAL)(1E-3)
#define EPSILON_E4 (JAXREAL)(1E-4)
#define EPSILON_E5 (JAXREAL)(1E-5)
#define EPSILON_E6 (JAXREAL)(1E-6)

#define JAXFRONT 0
#define JAXBACK 1
#define JAXON 2

#define JAXCLIPPED 3
#define JAXCULLED 4
#define JAXVISIBLE 5

#define JAXINTERSECT 3
#define JAXOUT 4
#define JAXIN 5
#define JAXNOINTERSECT 6

#define JAXPI 3.14159265f

	FORCEINLINE JAXREAL RadianToAngle(JAXREAL radian)
	{
		return (radian * 180.0f) / JAXPI;
	}

	FORCEINLINE JAXREAL AngleToRadian(JAXREAL angle)
	{
		return (angle * JAXPI) / 180.0f;
	}

	FORCEINLINE bool IsTwoPower(unsigned int n)
	{
		return !(n & (n - 1));
	}

}
