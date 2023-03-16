#pragma once
#include "Interfaces.h"

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
LimitedArrayStack<T>::LimitedArrayStack() : capacity_(5000), size_(0)
{
	arr_ = new T[capacity_];
}
template <typename T>
LimitedArrayStack<T>::LimitedArrayStack(const int size) : capacity_(size), size_(0)
{
	arr_ = new T[capacity_];
}
template <typename T>
LimitedArrayStack<T>::LimitedArrayStack(const int size, const T value) : capacity_(size), size_(size)
{
	arr_ = new T[capacity_];
	for (int i = 0; i < capacity_; i++)
	{
		arr_[i] = value;
	}
}
template <typename T>
LimitedArrayStack<T>::LimitedArrayStack(const LimitedArrayStack<T>& other) : capacity_(other.capacity_), size_(other.size_)
{
	arr_ = new T[capacity_];
	for (int i = 0; i < size_; i++)
	{
		arr_[i] = other.arr_[i];
	}
}
template <typename T>
LimitedArrayStack<T>::LimitedArrayStack(LimitedArrayStack<T>&& other) noexcept
{
	arr_ = other.arr_;
	size_ = other.size_;
	capacity_ = other.capacity_;
	other.arr_ = nullptr;
	other.size_ = NULL;
	other.capacity_ = NULL;
}
template <typename T>
LimitedArrayStack<T>& LimitedArrayStack<T>::operator= (const LimitedArrayStack<T>& other)
{
	if (this != &other)
	{
		delete[] arr_;
		arr_ = new T[other.capacity_];
		capacity_ = other.capacity_;
		size_ = other.size_;
		for (int i = 0; i < other.size_; i++)
		{
			arr_[i] = other.arr_[i];
		}
	}
	return *this;
}
template <typename T>
LimitedArrayStack<T>& LimitedArrayStack<T>::operator= (LimitedArrayStack<T>&& other) noexcept
{
	if (this != &other)
	{
		delete[] arr_;
		arr_ = other.arr_;
		size_ = other.size_;
		other.arr_ = nullptr;
		other.size_ = NULL;
	}
	return *this;
}
template <typename T>
LimitedArrayStack<T>::~LimitedArrayStack()
{
	delete[] arr_;
}
template <typename T>
bool LimitedArrayStack<T>::IsEmpty() const
{
	return size_ == 0;
}
template <typename T>
int LimitedArrayStack<T>::Size() const
{
	return size_;
}
template <typename T>
void LimitedArrayStack<T>::Resize(int size)
{
	int* arr = new T[size];
	for (int i = 0; i < min(size_, size); i++)
	{
		arr[i] = arr_[i];
	}
	size = size_;
	delete[] arr_;
	arr_ = arr;
}
template <typename T>
void LimitedArrayStack<T>::Push(const T value)
{
	if (size_ == capacity_)
	{
		throw runtime_error("Out_of_range");
	}
	arr_[size_] = value;
	size_++;
}
template <typename T>
void LimitedArrayStack<T>::Pop()
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	size_--;
}
template <typename T>
T LimitedArrayStack<T>::Top() const
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	return arr_[size_ - 1];
}
template <typename T>
T& LimitedArrayStack<T>::Top()
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	return arr_[size_ - 1];
}