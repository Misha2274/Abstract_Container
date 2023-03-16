#pragma once
#include "Interfaces.h"

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

template <typename T>
Node<T>::Node() : data(T(0)), next(nullptr), previous(nullptr) {}
template <typename T>
Node<T>::Node(const T value) : data(value), next(nullptr), previous(nullptr) {}

template <typename T>
ListQueue<T>::ListQueue() : head_(nullptr), tail_(nullptr) {}
template <typename T>
ListQueue<T>::ListQueue(int size)
{
	if (size != 0)
	{
		head_ = new Node<T>;
		tail_ = head_;
		for (auto i = head_, tail_ = head_; (size - 1); size--, i = i->next)
		{
			i->next = new Node<T>;
			i->next->previous = i;
			tail_ = i;
		}
	}
	else
	{
		head_ = nullptr;
		tail_ = nullptr;
	}
}
template <typename T>
ListQueue<T>::ListQueue(int size, T value)
{
	if (size != 0)
	{
		head_ = new Node<T>(value);
		tail_ = head_;
		for (auto i = head_, tail_ = head_; (size - 1); size--, i = i->next)
		{
			i->next = new Node<T>(value);
			i->next->previous = i;
			tail_ = i;
		}
	}
	else
	{
		head_ = nullptr;
		tail_ = nullptr;
	}
}
template <typename T>
ListQueue<T>::ListQueue(const ListQueue& other)
{
	if (!other.IsEmpty())
	{
		head_ = new Node<T>(other.Front());
		tail_ = head_;
		for (auto i = head_, j = other.head_; j->next != nullptr; i = i->next, j = j->next)
		{
			i->next = new Node<T>(j->next->data);
			i->next->previous = i;
			tail_ = i->next;
		}
	}
	else
	{
		head_ = nullptr;
		tail_ = nullptr;
	}
}
template <typename T>
ListQueue<T>::ListQueue(ListQueue<T>&& other) noexcept
{
	head_ = other.head_;
	other.head_ = nullptr;
	tail_ = other.tail_;
	other.tail_ = nullptr;
}
template <typename T>
ListQueue<T>& ListQueue<T>::operator= (const ListQueue<T>& other)
{
	if (this != &other)
	{
		while (!IsEmpty())
		{
			PopFront();
		}
		head_ = nullptr;
		tail_ = nullptr;
		if (!other.IsEmpty())
		{
			head_ = new Node<T>(other.head_->data);
			for (auto i = head_, j = other.head_; j->next != nullptr; i = i->next, j = j->next)
			{
				i->next = new Node<T>(j->next->data);
				i->next->previous = i;
				tail_ = i->next;
			}
		}
	}
	return *this;
}
template <typename T>
ListQueue<T>& ListQueue<T>::operator= (ListQueue<T>&& other) noexcept
{
	if (this != &other)
	{
		while (!IsEmpty())
		{
			PopFront();
		}
		head_ = nullptr;
		tail_ = nullptr;
		head_ = other.head_;
		tail_ = other.tail_;
		other.head_ = nullptr;
		other.tail_ = nullptr;
	}
	return *this;
}
template <typename T>
ListQueue<T>::~ListQueue()
{
	while (!IsEmpty())
	{
		PopFront();
	}
}
template <typename T>
bool ListQueue<T>::IsEmpty() const
{
	return head_ == nullptr;
}
template <typename T>
int ListQueue<T>::Size() const
{
	if (IsEmpty())
		return 0;
	int size = 1;
	for (auto i = head_; i != tail_; i = i->next, size++);
	return size;
}
template <typename T>
void ListQueue<T>::PushBack(const T value)
{
	if (IsEmpty())
	{
		tail_ = new Node<T>(value);
		head_ = tail_;
		return;
	}
	Node<T>* push = new Node<T>(value);
	push->previous = tail_;
	tail_->next = push;
	tail_ = push;
}
template <typename T>
void ListQueue<T>::PopFront()
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	Node<T>* pop = head_;
	head_ = head_->next;
	delete pop;
}
template <typename T>
T ListQueue<T>::Front() const
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	return head_->data;
}
template <typename T>
T& ListQueue<T>::Front()
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	return head_->data;
}