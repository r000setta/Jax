#include "JaxApplication.h"

namespace Jax
{
	JaxApplication::JaxApplication()
	{
		m_iUpdateThreadNum = 0;
	}

	JaxApplication::~JaxApplication() {}


	bool JaxApplication::CreateAppWindow()
	{
		return true;
	}

	bool JaxApplication::CreateRenderer()
	{
		return true;
	}

	bool JaxApplication::ReleaseRenderer()
	{
		return true;
	}

	bool JaxApplication::CreateInput()
	{
		return true;
	}

	bool JaxApplication::ReleaseInput()
	{
		return true;
	}

	bool JaxApplication::CreateTimer()
	{
		if (!JaxTimer::sm_pTimer)
		{
			JaxTimer* pTimer = JAX_NEW JaxTimer();
			if (!pTimer)
			{
				return false;
			}
		}
		JaxRandInit(JaxTimer::sm_pTimer->GetRandSeed());
		return true;
	}

	bool JaxApplication::ReleaseTimer()
	{
		JAXMAC_DELETE(JaxTimer::sm_pTimer);
		return true;
	}

	bool JaxApplication::Run()
	{
		double time = 0.0f;
		double fps = 0.0f;
		double detTime = 0.0f;
		return true;
	}

	bool JaxApplication::CreateEngine()
	{
		if (!CreateRenderer())
		{
			return false;
		}
		if (!CreateInput())
		{
			return false;
		}
		return true;
	}

	bool JaxApplication::ReleaseEngine()
	{
		if (!ReleaseInput())
		{
			return false;
		}
		if (!ReleaseRenderer())
		{
			return false;
		}
		return true;
	}

	bool JaxApplication::Main(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow)
	{
		return false;
	}

	bool JaxApplication::Main(int argc, char* argv[])
	{
		return false;
	}

	JaxConsoleApplication::JaxConsoleApplication()
	{
	}

	JaxConsoleApplication::~JaxConsoleApplication()
	{
	}

	bool JaxConsoleApplication::CreateRenderer()
	{
		return true;
	}

	bool JaxConsoleApplication::CreateInput()
	{
		return true;
	}

	bool JaxConsoleApplication::CreateAppWindow()
	{
		return true;
	}

	bool JaxConsoleApplication::Main(int argc, char* argv[])
	{
		m_bIsRunning = true;
		m_bIsActive = false;
		if (!CreateTimer())
		{
			return false;
		}
		if (!CreateAppWindow())
		{
			return false;
		}
		if (!CreateEngine())
		{
			return false;
		}
		bool error = false;
		while (m_bIsRunning)
		{
			if (m_bIsActive)
			{
				if (!Run())
				{
					m_bIsRunning = false;
					error = true;
				}
			}
		}
		if (!ReleaseEngine())
		{
			error = true;
		}
		if (!ReleaseTimer())
		{
			error = true;
		}
		return !error;
	}

}

