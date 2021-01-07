#include "JaxMain.h"

namespace Jax
{
	void JaxMain::AddInitialPropertyFunction(FunctionProperty func)
	{
		if (!func)
		{
			return;
		}
		if (!sm_pInitialPropertyArray)
		{
			sm_pInitialPropertyArray = JAX_NEW JaxArray<FunctionProperty>;
		}
		sm_pInitialPropertyArray->AddElement(func);
	}


}
