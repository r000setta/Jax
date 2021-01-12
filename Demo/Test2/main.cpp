#include "TestSaveLoad.h"
#include "JaxStream.h"
#include <iostream>

using namespace Jax;
using namespace std;

void TestSaveLoadFun()
{
	JaxTestSaveLoadPtr testSaveLoad = JAX_NEW JaxTestSaveLoad();

	testSaveLoad->m_ArrayInt.AddElement(0);
	testSaveLoad->m_ArrayInt.AddElement(1);
	testSaveLoad->m_ArrayInt.AddElement(2);
	testSaveLoad->m_ArrayInt.AddElement(3);

	/*testSaveLoad->m_Int = 321;
	testSaveLoad->m_TestString = _T("testString");
	testSaveLoad->m_FloatDataNum = 4;
	testSaveLoad->m_FloatData = JAX_NEW JAXREAL[4];
	testSaveLoad->m_FloatData[0] = 0.1f;
	testSaveLoad->m_FloatData[1] = 0.2f;
	testSaveLoad->m_FloatData[2] = 0.3f;
	testSaveLoad->m_FloatData[3] = 0.4f;
	*/

	//testSaveLoad->m_FixedFloatData = JAX_NEW JAXREAL[3];
	testSaveLoad->m_FixedFloatData[0] = 1.0f;
	testSaveLoad->m_FixedFloatData[1] = 2.0f;
	testSaveLoad->m_FixedFloatData[2] = 3.0f;

	JaxStream stream;
	JaxStream stream2;
	stream.SetStreamFlag(JaxStream::AT_REGISTER);
	stream.ArchiveAll(testSaveLoad);
	stream.NewSave("testStream2");

	JaxTestSaveLoadPtr test2 = NULL;
	stream2.NewLoad("testStream2");
	test2 = (JaxTestSaveLoad*)stream2.GetObjectByRtti(JaxTestSaveLoad::sm_Type);

	cout << "Array Test:" << endl;
	cout << test2->m_ArrayInt[0] << endl;
	cout << test2->m_ArrayInt[1] << endl;
	cout << test2->m_ArrayInt[2] << endl;
	cout << test2->m_ArrayInt[3] << endl;

	//cout << test2->m_Int << endl;
	/*cout << (char*)test2->m_TestString.GetBuffer() << endl;
	cout << test2->m_FloatData[0] << endl;
	cout << test2->m_FloatData[1] << endl;
	cout << test2->m_FloatData[2] << endl;
	cout << test2->m_FloatData[3] << endl;
	cout << test2->m_FloatDataNum << endl;*/

	cout << "Fixed Data Test:" << endl;
	cout << test2->m_FixedFloatData[0] << endl;
	cout << test2->m_FixedFloatData[1] << endl;
	cout << test2->m_FixedFloatData[2] << endl;
}

int main()
{
	JaxInitSystem();
	JaxInitMath();
	JaxMain::Initialize();

	JaxMain::Terminate();
}