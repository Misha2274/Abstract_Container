#pragma once

#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

template <typename T>
class AbstractContainer
{

public:

	virtual int Size() const = 0;
	virtual bool IsEmpty() const = 0;

};

template <typename T>
class AbstractStack : public AbstractContainer<T>
{

public:

	virtual void Push(const T value) = 0;
	virtual void Pop() = 0;
	virtual T Top() const = 0;
	virtual T& Top() = 0;

};

template <typename T>
class LimitedArrayStack : public AbstractStack<T>
{

	int capacity_;
	int size_;
	T* arr_;

	LimitedArrayStack();

public:

	LimitedArrayStack(const int size);
	LimitedArrayStack(const int size, const T value);
	LimitedArrayStack(const LimitedArrayStack& other);
	LimitedArrayStack(LimitedArrayStack&& other) noexcept;
	LimitedArrayStack& operator= (const LimitedArrayStack& other);
	LimitedArrayStack& operator= (LimitedArrayStack&& other) noexcept;
	~LimitedArrayStack();
	bool IsEmpty() const override;
	int Size() const override;
	void Resize(int size);
	void Push(const T value) override;
	void Pop() override;
	T Top() const override;
	T& Top() override;

};

template <typename T>
class UnlimitedArrayStack : public AbstractStack<T>
{

	vector<T> arr_;

public:

	UnlimitedArrayStack();
	UnlimitedArrayStack(const int size);
	UnlimitedArrayStack(const int size, const T value);
	UnlimitedArrayStack(const UnlimitedArrayStack& other);
	UnlimitedArrayStack(UnlimitedArrayStack&& other) noexcept;
	UnlimitedArrayStack& operator= (const UnlimitedArrayStack& other);
	UnlimitedArrayStack& operator= (UnlimitedArrayStack&& other) noexcept;
	~UnlimitedArrayStack();
	bool IsEmpty() const override;
	int Size() const override;
	void Resize(int size);
	void Push(const T value) override;
	void Pop() override;
	T Top() const override;
	T& Top() override;

};

template <typename T>
struct ForwardNode
{

	T data;
	ForwardNode* next;
	ForwardNode();
	ForwardNode(const T value);

};

template <typename T>
class ListStack : public AbstractStack<T>
{

	ForwardNode<T>* head_;

public:

	ListStack();
	ListStack(int size);
	ListStack(int size, T value);
	ListStack(const ListStack& other);
	ListStack(ListStack&& other) noexcept;
	ListStack& operator= (const ListStack& other);
	ListStack& operator= (ListStack&& other) noexcept;
	~ListStack();
	bool IsEmpty() const override;
	int Size() const override;
	void Push(const T value) override;
	void Pop() override;
	T Top() const override;
	T& Top() override;
};

template <typename T>
class AbstractQueue : public AbstractContainer<T>
{

public:

	virtual void PushBack(const T value) = 0;
	virtual void PopFront() = 0;
	virtual T Front() const = 0;
	virtual T& Front() = 0;

};

template <typename T>
class LimitedArrayQueue : public AbstractQueue<T>
{

	vector<T> arr_;
	int capacity_;
	int size_;
	int shift_;
	LimitedArrayQueue();

public:

	LimitedArrayQueue(const int size);
	LimitedArrayQueue(const int size, const T value);
	LimitedArrayQueue(const LimitedArrayQueue& other);
	LimitedArrayQueue(LimitedArrayQueue&& other) noexcept;
	LimitedArrayQueue& operator= (const LimitedArrayQueue& other);
	LimitedArrayQueue& operator= (LimitedArrayQueue&& other) noexcept;
	~LimitedArrayQueue();
	bool IsEmpty() const override;
	int Size() const override;
	void Resize(int size);
	void Reserve(int size);
	void PushBack(const T value) override;
	void PopFront() override;
	T Front() const override;
	T& Front() override;

};

template <typename T>
struct Node
{

	T data;
	Node* next, * previous;
	Node();
	Node(const T value);

};

template <typename T>
class ListQueue : public AbstractQueue<T>
{

	Node<T>* head_, * tail_;

public:

	ListQueue();
	ListQueue(int size);
	ListQueue(int size, T value);
	ListQueue(const ListQueue& other);
	ListQueue(ListQueue&& other) noexcept;
	ListQueue& operator= (const ListQueue& other);
	ListQueue& operator= (ListQueue&& other) noexcept;
	~ListQueue();
	bool IsEmpty() const override;
	int Size() const override;
	void PushBack(const T value) override;
	void PopFront() override;
	T Front() const override;
	T& Front() override;

};