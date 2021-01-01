#include <VSMemManager.h>
#include <VSArray.h>
using namespace VSEngine2;
class MyClass
{
public:
	MyClass();
	~MyClass();

	int i;
};

MyClass::MyClass()
{
	i = 0;
}

MyClass::~MyClass()
{
	i = 2;
}

int main()
{
	VSArray<MyClass> k1;
	k1.SetBufferNum(3);
	k1[0].i = 3;
	k1.AddBufferNum(5);

}