#pragma once
#include "Interfaces.h"

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
UnlimitedArrayStack<T>::UnlimitedArrayStack() {}
template <typename T>
UnlimitedArrayStack<T>::UnlimitedArrayStack(const int size)
{
	arr_.resize(size, T(0));
}
template <typename T>
UnlimitedArrayStack<T>::UnlimitedArrayStack(const int size, const T value)
{
	arr_.resize(size, value);
}
template <typename T>
UnlimitedArrayStack<T>::UnlimitedArrayStack(const UnlimitedArrayStack<T>& other)
{
	arr_ = other.arr_;
}
template <typename T>
UnlimitedArrayStack<T>::UnlimitedArrayStack(UnlimitedArrayStack<T>&& other) noexcept
{
	swap(arr_, other.arr_);
}
template <typename T>
UnlimitedArrayStack<T>& UnlimitedArrayStack<T>::operator= (const UnlimitedArrayStack<T>& other)
{
	if (this != &other)
	{
		arr_ = other.arr_;
	}
	return *this;
}
template <typename T>
UnlimitedArrayStack<T>& UnlimitedArrayStack<T>::operator= (UnlimitedArrayStack<T>&& other) noexcept
{
	if (this != &other)
	{
		arr_.clear();
		swap(arr_, other.arr_);
	}
	return *this;
}
template <typename T>
UnlimitedArrayStack<T>::~UnlimitedArrayStack() {};
template <typename T>
bool UnlimitedArrayStack<T>::IsEmpty() const
{
	return arr_.size() == 0;
}
template <typename T>
int UnlimitedArrayStack<T>::Size() const
{
	return arr_.size();
}
template <typename T>
void UnlimitedArrayStack<T>::Resize(int size)
{
	arr_.resize(size);
}
template <typename T>
void UnlimitedArrayStack<T>::Push(const T value)
{
	arr_.push_back(value);
}
template <typename T>
void UnlimitedArrayStack<T>::Pop()
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	arr_.pop_back();
}
template <typename T>
T UnlimitedArrayStack<T>::Top() const
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	return arr_[arr_.size() - 1];
}
template <typename T>
T& UnlimitedArrayStack<T>::Top()
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	return arr_[arr_.size() - 1];
}