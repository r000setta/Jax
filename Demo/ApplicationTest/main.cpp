#include <JaxApplication.h>
#include <JaxArray.h>
#include <stdio.h>

using namespace Jax;

int main()
{
	JaxArray<int> a;
	a.SetBufferNum(3);
	a[0] = 1;
	printf("%d", a[0]);
}