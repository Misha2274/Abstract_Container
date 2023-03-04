#include <iostream>
#include "Containers.h"

using namespace std;

int main()
{
	ListQueue A(2, 5);
	AbstractContainer* B = &A;
	ListQueue C(A);
	ListQueue D;
	ListQueue E(D);
	E.PushBack(5);
	cout << E.Front() << '\n';
	C.PushBack(3);
	C.PushBack(3);
	C.PushBack(4);
	C.PushBack(1);
	cout << C.Size() << "\n";
	while (!C.IsEmpty())
	{
		cout << C.Front() << ' ';
		C.PopFront();
	}
	C = A;
	C.PushBack(3);
	C.PushBack(3);
	C.PopFront();
	C.PushBack(4);
	C.PushBack(1);
	C.PopFront();
	cout << '\n';
	while (!C.IsEmpty())
	{
		cout << C.Front() << ' ';
		C.PopFront();
	}
	return 0;
}