#include <JaxMemManager.h>
#include <JaxVector3.h>
#include <iostream>
using namespace Jax;
using namespace std;
int main()
{
	JaxVector3 v1{ 1,2,3 };
	JaxVector3 v2{ 1,2,3 };
	auto v3 = v1 + v2;
	cout << v3.x << ' ' << v3.y << ' ' << v3.z << endl;
	cout << v1.Dot(v2) << endl;
}