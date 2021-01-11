#include "TestSaveLoad.h"
#include "JaxStream.h"
#include <iostream>

using namespace Jax;
using namespace std;

int main()
{
	JaxInitSystem();
	JaxInitMath();
	JaxMain::Initialize();

	JaxTestSaveLoadPtr testSaveLoad = JAX_NEW JaxTestSaveLoad();
	testSaveLoad->m_Name = _T("Test");
	JaxStream stream;
	stream.SetStreamFlag(JaxStream::AT_REGISTER);
	stream.ArchiveAll(testSaveLoad);
	stream.NewSave("testStream");

	JaxTestSaveLoadPtr test2 = NULL;
	stream.NewLoad("testStream");
	test2 = (JaxTestSaveLoad*)stream.GetObjectByRtti(JaxTestSaveLoad::sm_Type);

	cout << test2->m_Int << endl;

	JaxMain::Terminate();
}