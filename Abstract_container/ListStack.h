#pragma once
#include "Interfaces.h"

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
ForwardNode<T>::ForwardNode() : data(T(0)), next(nullptr) {}
template <typename T>
ForwardNode<T>::ForwardNode(const T value) : data(value), next(nullptr) {}

template <typename T>
ListStack<T>::ListStack() : head_(nullptr) {}
template <typename T>
ListStack<T>::ListStack(int size)
{
	if (size != 0)
	{
		head_ = new ForwardNode<T>;
		for (auto i = head_; (size - 1); size--, i = i->next)
		{
			i->next = new ForwardNode<T>;
		}
	}
	else
	{
		head_ = nullptr;
	}
}
template <typename T>
ListStack<T>::ListStack(int size, T value)
{
	if (size != 0)
	{
		head_ = new ForwardNode<T>(value);
		for (auto i = head_; (size - 1); size--, i = i->next)
		{
			i->next = new ForwardNode<T>(value);
		}
	}
	else
	{
		head_ = nullptr;
	}
}
template <typename T>
ListStack<T>::ListStack(const ListStack<T>& other)
{
	if (!other.IsEmpty())
	{
		head_ = new ForwardNode<T>(other.Top());
		for (auto i = head_, j = other.head_; j->next != nullptr; i = i->next, j = j->next)
		{
			i->next = new ForwardNode<T>(j->next->data);
		}
	}
	else
	{
		head_ = nullptr;
	}
}
template <typename T>
ListStack<T>::ListStack(ListStack<T>&& other) noexcept
{
	head_ = other.head_;
	other.head_ = nullptr;
}
template <typename T>
ListStack<T>& ListStack<T>::operator= (const ListStack<T>& other)
{
	if (this != &other)
	{
		while (!IsEmpty())
		{
			Pop();
		}
		head_ = nullptr;
		if (!other.IsEmpty())
		{
			head_ = new ForwardNode<T>;
			head_->data = other.Top();
			for (auto i = head_, j = other.head_; j->next != nullptr; i = i->next, j = j->next)
			{
				i->next = new ForwardNode<T>(j->next->data);
			}
		}
	}
	return *this;
}
template <typename T>
ListStack<T>& ListStack<T>::operator= (ListStack<T>&& other) noexcept
{
	if (this != &other)
	{
		while (!IsEmpty())
		{
			Pop();
		}
		head_ = other.head_;
		other.head_ = nullptr;
	}
	return *this;
}
template <typename T>
ListStack<T>::~ListStack<T>()
{
	while (!IsEmpty())
	{
		Pop();
	}
}
template <typename T>
bool ListStack<T>::IsEmpty() const
{
	return head_ == nullptr;
}
template <typename T>
int ListStack<T>::Size() const
{
	if (IsEmpty())
		return 0;
	int size = 1;
	for (auto i = head_; i->next != nullptr; i = i->next, size++);
	return size;
}
template <typename T>
void ListStack<T>::Push(const T value)
{
	if (IsEmpty())
	{
		head_ = new ForwardNode<T>(value);
		return;
	}
	ForwardNode<T>* push = new ForwardNode<T>(value);
	push->next = head_;
	head_ = push;
}
template <typename T>
void ListStack<T>::Pop()
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	ForwardNode<T>* pop = head_;
	head_ = head_->next;
	delete pop;
}
template <typename T>
T ListStack<T>::Top() const
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	return head_->data;
}
template <typename T>
T& ListStack<T>::Top()
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	return head_->data;
}