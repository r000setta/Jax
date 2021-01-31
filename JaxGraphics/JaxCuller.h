#pragma once
#include "JaxPlane3.h"
#include "JaxObject.h"
#include "JaxSphere3.h"

namespace Jax
{
	class JaxSpatial;
	class JaxCamera;
	class JaxRenderContext
	{
	public:
		JaxRenderContext();

		static JaxRenderContext sm_RenderContextNull;
	};
}