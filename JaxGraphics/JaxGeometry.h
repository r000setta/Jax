#pragma once
#include "JaxSpatial.h"
#include "JaxArray.h"

namespace Jax
{
	class JaxStream;

	class JAXGRAPHIC_API JaxGeometry :public JaxSpatial
	{
		DECLARE_RTTI
		DECLARE_INITIAL

	public:
		enum // Update Geometry Renturn Information
		{
			UGRI_FAIL,
			UGRI_CONTINUE,
			UGRI_END,
			UGRI_MAX
		};

		enum // Geometry Use Type
		{
			GUT_NORMAL,
			GUT_SHADOW_VOLUME,
			GUT_MAX
		};

		JaxGeometry();
		virtual ~JaxGeometry();
	};
}