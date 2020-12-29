#pragma once

#include "JaxSystem.h"
#include "JaxMemManager.h"
#include "JaxCommand.h"
#include "JaxTimer.h"
#include "JaxMath.h"

namespace Jax
{
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

		bool m_bIsActive;
		bool m_bIsRunning;
	};

	/*class JaxWindowApplication : public JaxApplication
	{
	public:
		JaxWindowApplication();
		virtual ~JaxWindowApplication();

	protected:
		virtual bool CreateRenderer();
	};*/

	class JaxConsoleApplication :public JaxApplication
	{
	public:
		JaxConsoleApplication();
		virtual ~JaxConsoleApplication();
	protected:
		virtual bool CreateRenderer();
		virtual bool CreateInput();

		virtual bool CreateAppWindow();

	public:
		virtual bool Main(int argc, char* argv[]);
	};
}