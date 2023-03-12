#include <iostream>
#include "Containers.h"

using namespace std;

int main()
{
	ListQueue<int> A(2, 5);
	AbstractContainer<int>* B = &A;
	ListQueue<int> C(A);
	ListQueue<int> D;
	ListQueue<int> E(D);
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
	cout << "\n";
	LimitedArrayStack<int> a = LimitedArrayStack<int>(5, 5);
	LimitedArrayStack<int> a2 = move(a);
	while (!a.IsEmpty())
	{
		cout << a.Top() << " ";
		a.Pop();
	}
	cout << "\n";
	while (!a2.IsEmpty())
	{
		cout << a2.Top() << " ";
		a2.Pop();
	}
	cout << "\n";
	LimitedArrayQueue<int> b = LimitedArrayQueue<int>(5, 7);
	LimitedArrayQueue<int> b2 = move(b);
	while (!b.IsEmpty())
	{
		cout << b.Front() << " ";
		b.PopFront();
	}
	cout << "\n";
	while (!b2.IsEmpty())
	{
		cout << b2.Front() << " ";
		b2.PopFront();
	}
	cout << "\n";
	UnlimitedArrayStack<int> c = UnlimitedArrayStack<int>(5, 8);
	UnlimitedArrayStack<int> c2 = move(c);
	while (!c.IsEmpty())
	{
		cout << c.Top() << " ";
		c.Pop();
	}
	cout << "\n";
	while (!c2.IsEmpty())
	{
		cout << c2.Top() << " ";
		c2.Pop();
	}
	cout << "\n";
	ListStack<int> d = ListStack<int>(5, 9);
	ListStack<int> d2 = move(d);
	while (!d.IsEmpty())
	{
		cout << d.Top() << " ";
		d.Pop();
	}
	cout << "\n";
	while (!d2.IsEmpty())
	{
		cout << d2.Top() << " ";
		d2.Pop();
	}
	cout << "\n";
	ListQueue<int> e = ListQueue<int>(5, 6);
	ListQueue<int> e2 = move(e);
	while (!e.IsEmpty())
	{
		cout << e.Front() << " ";
		e.PopFront();
	}
	cout << "\n";
	while (!e2.IsEmpty())
	{
		cout << e2.Front() << " ";
		e2.PopFront();
	}
	cout << "\n";
	ListQueue<float> P(2, 5.5);
	AbstractContainer<float>* R = &P;
	ListQueue<float> T(P);
	T.PushBack(30.54);
	T.PushBack(3.545);
	T.PushBack(4.5555);
	T.PushBack(1.1);
	cout << T.Size() << "\n";
	while (!T.IsEmpty())
	{
		cout << T.Front() << ' ';
		T.PopFront();
	}
	return 0;
}