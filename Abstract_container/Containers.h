#pragma once

#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

class AbstractContainer
{

public:

	virtual int Size() const = 0;
	virtual bool IsEmpty() const = 0;

};

class AbstractStack : public AbstractContainer
{

public:

	virtual void Push(const int value) = 0;
	virtual void Pop() = 0;
	virtual int Top() const = 0;
	virtual int& Top() = 0;

};

class LimitedArrayStack : public AbstractStack
{

	int capacity_;
	int size_;
	int* arr_;

	LimitedArrayStack();

public:

	LimitedArrayStack(const int size);
	LimitedArrayStack(const int size, const int value);
	LimitedArrayStack(const LimitedArrayStack& other);
	LimitedArrayStack(LimitedArrayStack&& other) noexcept;
	LimitedArrayStack& operator= (const LimitedArrayStack& other);
	LimitedArrayStack& operator= (LimitedArrayStack&& other) noexcept;
	~LimitedArrayStack();
	bool IsEmpty() const override;
	int Size() const override;
	void Resize(int size);
	void Push(const int value) override;
	void Pop() override;
	int Top() const override;
	int& Top() override;

};

class UnlimitedArrayStack : public AbstractStack
{

	vector<int> arr_;

public:

	UnlimitedArrayStack();
	UnlimitedArrayStack(const int size);
	UnlimitedArrayStack(const int size, const int value);
	UnlimitedArrayStack(const UnlimitedArrayStack& other);
	UnlimitedArrayStack(UnlimitedArrayStack&& other) noexcept;
	UnlimitedArrayStack& operator= (const UnlimitedArrayStack& other);
	UnlimitedArrayStack& operator= (UnlimitedArrayStack&& other) noexcept;
	~UnlimitedArrayStack();
	bool IsEmpty() const override;
	int Size() const override;
	void Resize(int size);
	void Push(const int value) override;
	void Pop() override;
	int Top() const override;
	int& Top() override;

};

struct ForwardNode
{

	int data;
	ForwardNode* next;
	ForwardNode();
	ForwardNode(const int value);

};

class ListStack : public AbstractStack
{

	ForwardNode* head_;

public:

	ListStack();
	ListStack(int size);
	ListStack(int size, int value);
	ListStack(const ListStack& other);
	ListStack(ListStack&& other) noexcept;
	ListStack& operator= (const ListStack& other);
	ListStack& operator= (ListStack&& other) noexcept;
	~ListStack();
	bool IsEmpty() const override;
	int Size() const override;
	void Push(const int value) override;
	void Pop() override;
	int Top() const override;
	int& Top() override;
};

class AbstractQueue : public AbstractContainer
{

public:

	virtual void PushBack(const int value) = 0;
	virtual void PopFront() = 0;
	virtual int Front() const = 0;
	virtual int& Front() = 0;

};

class LimitedArrayQueue : public AbstractQueue
{

	vector<int> arr_;
	int capacity_;
	int size_;
	int shift_;
	LimitedArrayQueue();

public:

	LimitedArrayQueue(const int size);
	LimitedArrayQueue(const int size, const int value);
	LimitedArrayQueue(const LimitedArrayQueue& other);
	LimitedArrayQueue(LimitedArrayQueue&& other) noexcept;
	LimitedArrayQueue& operator= (const LimitedArrayQueue& other);
	LimitedArrayQueue& operator= (LimitedArrayQueue&& other) noexcept;
	~LimitedArrayQueue();
	bool IsEmpty() const override;
	int Size() const override;
	void Resize(int size);
	void Reserve(int size);
	void PushBack(const int value) override;
	void PopFront() override;
	int Front() const override;
	int& Front() override;

};

struct Node
{

	int data;
	Node* next, * previous;
	Node();
	Node(const int value);

};

class ListQueue : public AbstractQueue
{

	Node* head_, * tail_;

public:

	ListQueue();
	ListQueue(int size);
	ListQueue(int size, int value);
	ListQueue(const ListQueue& other);
	ListQueue(ListQueue&& other) noexcept;
	ListQueue& operator= (const ListQueue& other);
	ListQueue& operator= (ListQueue&& other) noexcept;
	~ListQueue();
	bool IsEmpty() const override;
	int Size() const override;
	void PushBack(const int value) override;
	void PopFront() override;
	int Front() const override;
	int& Front() override;

};