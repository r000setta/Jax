#pragma once
#include "JaxRtti.h"
#include "JaxSystem.h"
#include "JaxArray.h"
#include "JaxMap.h"

namespace Jax
{
	class JaxProperty
	{
	public:
		enum
		{
			PT_VALUE,
			PT_ENUM,
			PT_DATA,
			PT_ARRAY,
			PT_MAP,
			PT_MAX
		};

		enum
		{
			F_NONE=0x00,
			F_SAVE_LOAD=0x01,
			F_CLONE=0x02,
			F_COPY=0x04,
			F_SAVE_LOAD_COPY=0x05,
			F_REFLECT_NAME=0x08,
			F_MAX
		};

	};
}