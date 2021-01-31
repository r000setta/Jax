#pragma once
#include "JaxVector3.h"
#include "JaxMatrix4x4.h"
#include "JaxMatrix3x3.h"
#include "JaxPlane3.h"

namespace Jax
{
	class JaxRenderer;
	struct JaxViewPort
	{
		JAXREAL xmin;
		JAXREAL ymin;
		JAXREAL zmin;
		JAXREAL xmax;
		JAXREAL ymax;
		JAXREAL zmax;
		bool bChangeAspect;
		
		void Reset()
		{
			xmin = 0.0f;
			ymin = 0.0f;
			xmax = 1.0f;
			ymax = 1.0f;
			zmin = 0.0f;
			zmax = 1.0f;
			bChangeAspect = false;
		}

		JaxViewPort()
		{
			Reset();
		}
	};

	class JaxStream;
	class JAXGRAPHIC_API JaxCamera
	{

	};
}