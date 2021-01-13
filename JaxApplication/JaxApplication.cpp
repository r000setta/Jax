#include "JaxApplication.h"
#include "JaxInput.h"
namespace Jax
{
#ifdef WINDOWS
	int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
	{
		JaxInitSystem();
		JaxInitMath();
		JaxMain::Initialize();
		if (JaxApplication::sm_pApplication)
		{
			if (!JaxApplication::sm_pApplication->Main(hInstance, lpCmdLine, nCmdShow))
			{
				return false;
			}
		}
		JaxMain::Terminate();
		return true;
	}
#endif // WINDOWS

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
		return true;
	}

	bool JaxApplication::Main(int argc, char* argv[])
	{
		return false;
	}

	bool JaxApplication::PreInitial()
	{
		m_uiScreenWidth = 1024;
		m_uiScreenWidth = 768;
		m_uiAnisotropy = 1;
		m_uiMultisample = 0;

		return true;
	}

	bool JaxApplication::OnInitial()
	{
		return true;
	}

	bool JaxApplication::OnTerminal()
	{
		return true;
	}

	bool JaxApplication::PostUpdate()
	{
		return true;
	}

	bool JaxApplication::PreUpdate()
	{
		return true;
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

	void JaxApplication::OnLButtonDown(int xPos, int yPos)
	{

	}

	void JaxApplication::OnLButtonUp(int xPos, int yPos)
	{
	}

	void JaxApplication::OnRButtonDown(int xPos, int yPos)
	{
	}

	void JaxApplication::OnRButtonUp(int xPos, int yPos)
	{
	}

	void JaxApplication::OnMButtonDown(int xPos, int yPos)
	{
	}

	void JaxApplication::OnMButtonUp(int xPos, int yPos)
	{
	}

	void JaxApplication::OnMouseMove(int xPos, int yPos)
	{
	}

	void JaxApplication::OnMouseWheel(int xPos, int yPos, int zDet)
	{
	}

	void JaxApplication::ChangeScreenSize(size_t width, size_t height, bool isWindow, bool isMaxScreen)
	{

	}

	void JaxApplication::InputMsgProc(size_t inputType, size_t event, size_t key, int x, int y, int z)
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

	bool JaxWindowApplication::Main(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow)
	{
		m_pCommand = JAX_NEW JaxCommand(lpCmdLine);
		m_hInst = hInstance;
		m_bIsRunning = true;
		m_bIsActive = false;
		if (!CreateTimer())
		{
			return false;
		}

		if (!PreInitial())
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

		if (!OnInitial())
		{
			return false;
		}

		MSG msg;
		bool error = false;
		while (m_bIsRunning)
		{
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (m_bIsActive)
			{
				if (!Run())
				{
					m_bIsRunning = false;
					error = true;
				}
			}
		}
		if (!OnTerminal())
		{
			error = true;
		}
		if (!ReleaseEngine())
		{
			error = true;
		}
		if (!ReleaseTimer())
		{
			error = true;
		}

		JAXMAC_DELETE(m_pCommand);
		UnregisterClass(m_WindowClassName.GetBuffer(), m_hInst);
		return !error;
	}

	bool JaxWindowApplication::PreInitial()
	{
		JaxApplication::PreInitial();
		m_uiRenderAPIType = 1;
		m_uiScreenWidth = 1024;
		m_uiScreenHeight = 768;
		m_bIsWindowed = true;
		m_uiAnisotropy = 1;
		m_uiMultisample = 0;
		m_Tile = _T("Demo");
		m_WindowClassName = _T("Test");
		m_uiInputAPIType = JaxInput::IAT_WINDOWS;
		m_dwWindowStyle = WS_OVERLAPPEDWINDOW & (~WS_OVERLAPPED) | WS_VISIBLE;
		m_dwFullScreenStyle = WS_POPUP | WS_SYSMENU | WS_VISIBLE;
		return true;
	}

	void JaxWindowApplication::ChangeScreenSize(size_t width, size_t height, bool isWindow, bool isMaxScreen)
	{
		JaxApplication::ChangeScreenSize(width, height, isWindow, isMaxScreen);
		if (isWindow)
		{
			if (isMaxScreen)
			{
				RECT rect = { 0,0,m_uiScreenWidth,m_uiScreenHeight };
				AdjustWindowRect(&rect, m_dwFullScreenStyle, GetMenu(m_MainHwnd) != NULL);
				SetWindowLong(m_MainHwnd, GWL_STYLE, m_dwFullScreenStyle);
				SetWindowPos(m_MainHwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_FRAMECHANGED);
				MoveWindow(m_MainHwnd,
					0,
					0,
					GetSystemMetrics(SM_CXSCREEN),
					GetSystemMetrics(SM_CYSCREEN),
					TRUE);
			}
			else
			{
				RECT rect = { 0,0,m_uiScreenWidth,m_uiScreenHeight };
				AdjustWindowRect(&rect, m_dwFullScreenStyle, GetMenu(m_MainHwnd) != NULL);
				SetWindowLong(m_MainHwnd, GWL_STYLE, m_dwFullScreenStyle);
				size_t newWidth = rect.right - rect.left;
				size_t newHeight = rect.bottom - rect.top;
				MoveWindow(m_MainHwnd,
					0,
					0,
					newWidth,
					newHeight,
					TRUE);
			}
		}
	}

	bool JaxWindowApplication::CreateRenderer()
	{
		JaxApplication::CreateRenderer();
		return true;
	}

	bool JaxWindowApplication::CreateInput()
	{
		if (JaxInput::sm_pInput)
		{
			if (JaxInput::sm_pInput->GetInputAPIType() == m_uiInputAPIType)
			{
				return true;
			}
			else
			{
				if (m_uiInputAPIType == JaxInput::IAT_DX)
				{
					return false;
				}
			}
		}
		else
		{

		}
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

		if (RegisterClassEx(&wndClass) == NULL)
		{
			return false;
		}

		if (!(hWnd = CreateWindowEx(NULL, m_WindowClassName.GetBuffer(),
			m_Tile.GetBuffer(),
			m_dwWindowStyle,
			0,
			0,
			m_uiScreenWidth, m_uiScreenHeight, NULL, NULL, m_hInst, NULL)))
			return 0;

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

	bool JaxWindowApplication::CreateOPGL()
	{
		return false;
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

