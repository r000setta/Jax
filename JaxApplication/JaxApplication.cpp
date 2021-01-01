#include "JaxApplication.h"

namespace Jax
{
	JaxApplication* JaxApplication::sm_pApplication = NULL;
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

	bool JaxApplication::OnDraw()
	{
		return true;
	}

	void JaxApplication::OnMove(int xPos, int yPos)
	{
	}

	void JaxApplication::OnReSize(int width, int height)
	{
	}

	void JaxApplication::OnKeyDown(unsigned int key)
	{
	}

	void JaxApplication::OnKeyUp(unsigned int key)
	{
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

	JaxWindowApplication::JaxWindowApplication()
	{
		m_hInst = NULL;
		m_MainHwnd = NULL;
	}

	JaxWindowApplication::~JaxWindowApplication()
	{
	}

	bool JaxWindowApplication::CreateRenderer()
	{
		JaxApplication::CreateRenderer();
		return true;
	}

	bool JaxWindowApplication::CreateInput()
	{
		return true;
	}

	bool JaxWindowApplication::CreateAppWindow()
	{
		WNDCLASSEX wndClass;
		HWND hWnd = NULL;

		wndClass.cbSize = sizeof(wndClass);
		wndClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
		wndClass.lpfnWndProc = JaxWindowApplication::MsgProc;
		wndClass.cbClsExtra = 0;
		wndClass.cbWndExtra = 0;
		wndClass.hInstance = m_hInst;
		wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW);
		wndClass.lpszMenuName = NULL;
		wndClass.lpszClassName = m_WindowClassName.GetBuffer();
		wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		if (RegisterClassExW(&wndClass) == NULL)
		{
			return false;
		}

		if (!(hWnd = CreateWindowEx(NULL, m_WindowClassName.GetBuffer(),
			m_Tile.GetBuffer(),
			m_dwWindowStyle,
			0,
			0,
			m_uiScreenWidth,m_uiScreenHeight,NULL,NULL,m_hInst,NULL)))
		{
			return false;
		}

		m_MainHwnd = hWnd;

		if (m_bIsWindowed)
		{
			RECT windowRect = { 0,0,m_uiScreenWidth,m_uiScreenHeight };
			AdjustWindowRect(&windowRect, m_dwWindowStyle, GetMenu(m_MainHwnd) != NULL);
			int newWidth = windowRect.right - windowRect.left;
			int newHeight = windowRect.bottom - windowRect.top;
			MoveWindow(m_MainHwnd,
				0,
				0,
				newWidth,
				newHeight,
				TRUE);
		}

		return true;
	}

	LRESULT WINAPI JaxWindowApplication::MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (!JaxApplication::sm_pApplication)
		{
			return DefWindowProc(hWnd, msg, wParam, lParam);
		}
		switch (msg)
		{
		case WM_KILLFOCUS:
		{
			JaxWindowApplication::sm_pApplication->m_bIsActive = false;
			break;
		}
		case WM_SETFOCUS:
		{
			JaxWindowApplication::sm_pApplication->m_bIsActive = true;
			break;
		}
		case WM_ACTIVATE:
		{
			JaxWindowApplication::sm_pApplication->m_bIsActive = (bool)(wParam);
			break;
		}
		case WM_MOVE:
		{
			int xPos = (int)(LOWORD(lParam));
			int yPos = (int)(HIWORD(lParam));
			JaxApplication::sm_pApplication->OnMove(xPos, yPos);
			break;
		}
		case WM_SIZE:
		{
			int width = (int)(LOWORD(lParam));
			int height = (int)(HIWORD(lParam));
			JaxApplication::sm_pApplication->OnReSize(width, height);
			break;
		}
		case WM_DESTROY:
		{
			JaxApplication::sm_pApplication->m_bIsRunning = false;
			PostQuitMessage(0);
			return 1;
		}
		default:
			break;
		}
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}

}

