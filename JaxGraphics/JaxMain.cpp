#include "JaxMain.h"
#include "JaxResouceManager.h"
namespace Jax
{
	JaxArray<JaxMain::Element>* JaxMain::sm_pInitialArray = NULL;
	JaxArray<JaxMain::Element>* JaxMain::sm_pTerminalArray = NULL;
	JaxArray<FunctionProperty>* JaxMain::sm_pInitialPropertyArray = NULL;
	JaxArray<Function>* JaxMain::sm_pTerminalProperyArray = NULL;
	size_t JaxMain::sm_uiInitialObject = 0;
	size_t JaxMain::sm_uiTerminalObject = 0;
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

	void JaxMain::AddTerminalPropertyFunction(Function func)
	{
		if (!func)
		{
			return;
		}
		if (!sm_pTerminalProperyArray)
		{
			sm_pTerminalProperyArray = JAX_NEW JaxArray<Function>;
		}
		sm_pTerminalProperyArray->AddElement(func);
	}

	void JaxMain::AddInitialFunction(Function func)
	{
		AddInitialFunction(func, NULL);
	}

	void JaxMain::AddInitialFunction(Function func, JaxPriority* priority)
	{
		if (!func)
		{
			return;
		}
		if (!sm_pInitialArray)
		{
			sm_pInitialArray = JAX_NEW JaxArray<Element>;
		}
		Element e{ func,priority };
		sm_pInitialArray->AddElement(e);
	}

	bool JaxMain::Initialize()
	{
		for (size_t i = 0; i < sm_pInitialPropertyArray->GetNum(); ++i)
		{
			if (!(*((*sm_pInitialPropertyArray)[i]))(NULL))
			{
				return false;
			}
		}
		sm_pInitialArray->Sort(0, sm_pInitialArray->GetNum() - 1, PriorityCompare());
		for (size_t i = 0; i < sm_pInitialArray->GetNum(); ++i)
		{
			if (!(*((*sm_pInitialArray)[i].func))())
			{
				return false;
			}
		}
		
		sm_pInitialArray->Clear();
		JAXMAC_DELETE(sm_pInitialArray);
		sm_uiInitialObject = JaxObject::GetObjectManager().GetObjectNum();
		sm_pInitialPropertyArray->Clear();
		JAXMAC_DELETE(sm_pInitialPropertyArray);
		return true;
	}

	void JaxMain::AddTerminalFunction(Function func)
	{
		AddTerminalFunction(func, NULL);
	}

	void JaxMain::AddTerminalFunction(Function func, JaxPriority* priority)
	{
		if (!func)
		{
			return;
		}
		if (!sm_pTerminalArray)
		{
			sm_pTerminalArray = JAX_NEW JaxArray<Element>;
		}
		Element e{ func,priority };
		sm_pTerminalArray->AddElement(e);
	}

	bool JaxMain::Terminate()
	{
		JaxResourceManager::CacheResource();
		sm_pTerminalArray->Sort(0, sm_pTerminalArray->GetNum(), PriorityCompare());
		sm_uiTerminalObject = JaxObject::GetObjectManager().GetObjectNum();

		for (int i = sm_pTerminalArray->GetNum() - 1; i >= 0; --i)
		{
			if (!(*((*sm_pTerminalArray)[i].func))())
			{
				return false;
			}
		}
		sm_pTerminalArray->Clear();
		JAXMAC_DELETE(sm_pTerminalArray);
		sm_uiTerminalObject = JaxObject::GetObjectManager().GetObjectNum();
		//JAX_ASSERT(sm_uiTerminalObject==0)
		return true;
	}
}
