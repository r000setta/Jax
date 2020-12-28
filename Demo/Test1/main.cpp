#include <JaxMemManager.h>
using namespace Jax;
void Fun()
{
	char* k = JAX_NEW char[15];
}
int main()
{
	int* a = JAX_NEW int;
	*a = 5;
	Fun();
}