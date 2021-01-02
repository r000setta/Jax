#include <JaxMemManager.h>
#include <JaxVector3.h>
#include <iostream>
#include <string>
#include <JaxString.h>
#include <stdio.h>
#include <JaxObject.h>

using namespace Jax;
using namespace std;

class A :public JaxReference
{
	DECLARE_RTTI

public:
	bool IsSameType(A* pObject) const;
	bool IsDerived(A* pObject) const;

	void getname() {}
};

IMPLEMENT_RTTI_NoParent_NoCreateFun(A)

bool A::IsSameType(A* pObject) const
{
	return pObject && GetType().IsSameType(pObject->GetType());
}

class B :public A
{
	DECLARE_RTTI
};

IMPLEMENT_RTTI_NoCreateFun(B, A)

class C :public A
{
	DECLARE_RTTI
};

IMPLEMENT_RTTI_NoCreateFun(C,A)

template<typename T>
T* StaticCast(A* obj)
{
	return (T*)obj;
}

template<typename T>
const T* StaticCast(const A* obj)
{
	return (const T*)obj;
}

template<typename T>
T* DynamicCast(A* obj)
{
	return obj && obj->IsDerived(T::sm_Type) ? (T*)obj : NULL;
}

template<typename T>
const T* DynamicCast(const A* obj)
{
	return obj && obj->IsDerived(T::sm_Type) ? (const T*)obj : NULL;
}

int main()
{
	A* p1 = JAX_NEW A();
	A* p2 = JAX_NEW B();
	A* p3 = JAX_NEW C();
	cout << boolalpha;
	cout << p2->IsDerived(p1) << endl;
	cout << p3->IsDerived(p1) << endl;
	cout << p3->IsDerived(p2) << endl;

	cout << (char*)A::sm_Type.GetName().GetBuffer() << endl;
	printf("%ls\n", A::sm_Type.GetName().GetBuffer());

	JAXMAC_DELETE(p1);
	JAXMAC_DELETE(p2);
	JAXMAC_DELETE(p3);

	JaxArray<A*> a;
	a.SetBufferNum(10);
	a[0] = p1;
	a[0]->getname();
}

bool A::IsDerived(A* pObject) const
{
	return pObject && GetType().IsDerived(pObject->GetType());
}
