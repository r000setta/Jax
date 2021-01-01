#pragma once

#include "JaxSystem.h"
#include "JaxMemManager.h"
#include "JaxCommand.h"
#include "JaxTimer.h"
#include "JaxMath.h"
#include "JaxArray.h"

namespace Jax
{

//#define DECLARE_APPLICATION(classname) \
//public:\
//static bool RegisterMainFactory();\
//private:\
//static bool InitialApplication();\
//static bool TerminalApplication();\
//static bool sm_bRegisterMainFactory();

	class JaxApplication :public JaxMemObject
	{
	public:
		JaxApplication();
		virtual ~JaxApplication();
		static JaxApplication* sm_pApplication;

	protected:
		JaxCommand* m_pCommand;
		unsigned int m_uiRenderAPIType;
		unsigned int m_uiScreenWidth;
		unsigned int m_uiScreenHeight;
		unsigned int m_uiMultisample;
		unsigned int m_uiAnisotropy;
		unsigned int m_iUpdateThreadNum;

		virtual bool CreateAppWindow();

		virtual bool CreateRenderer();
		virtual bool ReleaseRenderer();

		virtual bool CreateInput();
		virtual bool ReleaseInput();

		virtual bool CreateTimer();
		virtual bool ReleaseTimer();

		virtual bool Run();

		virtual bool CreateEngine();
		virtual bool ReleaseEngine();
	public:
		virtual bool Main(HINSTANCE hInstance, LPSTR lpCmdLine, int nCmdShow);
		virtual bool Main(int argc, char* argv[]);

		virtual bool OnDraw();
		virtual void OnMove(int xPos,int yPos);
		virtual void OnReSize(int width, int height);
		virtual void OnKeyDown(unsigned int key);
		virtual void OnKeyUp(unsigned int key);

		bool m_bIsActive;
		bool m_bIsRunning;
	};

#ifdef WINDOWS

	class JaxWindowApplication : public JaxApplication
	{
	public:
		JaxWindowApplication();
		virtual ~JaxWindowApplication();

	protected:
		virtual bool CreateRenderer();
		virtual bool CreateInput();

		virtual bool CreateAppWindow();

		static LRESULT WINAPI MsgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

		JaxString m_Tile;
		JaxString m_WindowClassName;
		unsigned int m_uiInputAPIType;

		DWORD m_dwWindowStyle;
		DWORD m_dwFullScreenStyle;
		bool m_bIsWindowed;
		HWND m_MainHwnd;
		HINSTANCE m_hInst;
	};

#endif

	class JaxConsoleApplication :public JaxApplication
	{
	public:
		JaxConsoleApplication();
		virtual ~JaxConsoleApplication();
	protected:
		virtual bool CreateRenderer();
		virtual bool CreateInput();

		
	public:
		virtual bool Main(int argc, char* argv[]);
	};
}