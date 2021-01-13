#include <JaxApplication.h>
#include <JaxInput.h>

using namespace Jax;

class JaxDemoWindowApplication :public JaxWindowApplication
{
	DECLARE_APPLICATION(JaxDemoWindowApplication);

public:
	JaxDemoWindowApplication() {}
	~JaxDemoWindowApplication() {}
	virtual bool PreInitial();
	virtual bool OnInitial();
	virtual bool OnTerminal();
	virtual bool PostUpdate();
	virtual bool PreUpdate();
	virtual bool OnDraw();
	virtual void OnMove(int xPos, int yPos);
	virtual void OnReSize(int iWidth, int iHeight);
	virtual void OnKeyDown(unsigned int uiKey);
	virtual void OnKeyUp(unsigned int uiKey);
	virtual void OnLButtonDown(int xPos, int yPos);
	virtual void OnLButtonUp(int xPos, int yPos);
	virtual void OnRButtonDown(int xPos, int yPos);
	virtual void OnRButtonUp(int xPos, int yPos);
	virtual void OnMButtonDown(int xPos, int yPos);
	virtual void OnMButtonUp(int xPos, int yPos);
	virtual void OnMouseMove(int xPos, int yPos);
	virtual void OnMouseWheel(int xPos, int yPos, int zDet);
};

IMPLEMENT_APPLICATION(JaxDemoWindowApplication);

bool JaxDemoWindowApplication::PreInitial()
{
	JaxWindowApplication::PreInitial();
	return true;
}

bool JaxDemoWindowApplication::OnInitial()
{
	JaxWindowApplication::OnInitial();
	return true;
}

bool JaxDemoWindowApplication::OnTerminal()
{
	JaxWindowApplication::OnTerminal();
	return true;
}

bool JaxDemoWindowApplication::PostUpdate()
{
	JaxWindowApplication::PostUpdate();
	return true;
}

bool JaxDemoWindowApplication::PreUpdate()
{
	JaxWindowApplication::PreUpdate();
	return true;
}

bool JaxDemoWindowApplication::OnDraw()
{
	JaxWindowApplication::OnDraw();
	return true;
}

void JaxDemoWindowApplication::OnMove(int xPos, int yPos)
{
}

void JaxDemoWindowApplication::OnReSize(int iWidth, int iHeight)
{
}

void JaxDemoWindowApplication::OnKeyDown(unsigned int uiKey)
{
	JaxApplication::OnKeyDown(uiKey);
	if (uiKey == JaxInput::BK_F1)
	{
		ChangeScreenSize(800, 600, true, false);
	}
	JaxOutputDebugString("Key Down\n");
}

void JaxDemoWindowApplication::OnKeyUp(unsigned int uiKey)
{
	JaxApplication::OnKeyUp(uiKey);
	JaxOutputDebugString("Key Up\n");
}

void JaxDemoWindowApplication::OnLButtonDown(int xPos, int yPos)
{
	JaxOutputDebugString("LButton Down\n");
}

void JaxDemoWindowApplication::OnLButtonUp(int xPos, int yPos)
{
	JaxOutputDebugString("LButton Up\n");
}

void JaxDemoWindowApplication::OnRButtonDown(int xPos, int yPos)
{
	JaxOutputDebugString("RButton Down\n");
}

void JaxDemoWindowApplication::OnRButtonUp(int xPos, int yPos)
{
	JaxOutputDebugString("RButton Up\n");
}

void JaxDemoWindowApplication::OnMButtonDown(int xPos, int yPos)
{
	JaxOutputDebugString("MButton Down\n");
}

void JaxDemoWindowApplication::OnMButtonUp(int xPos, int yPos)
{
	JaxOutputDebugString("MButton Up\n");
}

void JaxDemoWindowApplication::OnMouseMove(int xPos, int yPos)
{
	JaxOutputDebugString("Mouse Move\n");
}

void JaxDemoWindowApplication::OnMouseWheel(int xPos, int yPos, int zDet)
{
	JaxOutputDebugString("Mouse Wheel\n");
}


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