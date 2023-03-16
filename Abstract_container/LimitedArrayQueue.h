#pragma once
#include "Interfaces.h"

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
LimitedArrayQueue<T>::LimitedArrayQueue() : capacity_(5000), size_(0), shift_(0)
{
	arr_.resize(5000, T(0));
}
template <typename T>
LimitedArrayQueue<T>::LimitedArrayQueue(const int size) : capacity_(size), size_(0), shift_(0)
{
	arr_.resize(size, T(0));
}
template <typename T>
LimitedArrayQueue<T>::LimitedArrayQueue(const int size, const T value) : capacity_(size), size_(size), shift_(0)
{
	arr_.resize(size, value);
}
template <typename T>
LimitedArrayQueue<T>::LimitedArrayQueue(const LimitedArrayQueue<T>& other) : capacity_(other.capacity_), size_(other.size_), shift_(0)
{
	if (other.shift_ == 0)
		arr_ = other.arr_;
	else
	{
		for (int i = 0; i < size_; i++)
		{
			arr_[i % capacity_] = other.arr_[i + shift_ % capacity_];
		}
	}
}
template <typename T>
LimitedArrayQueue<T>::LimitedArrayQueue(LimitedArrayQueue<T>&& other) noexcept
{
	swap(arr_, other.arr_);
	capacity_ = other.capacity_;
	other.capacity_ = NULL;
	size_ = other.size_;
	other.size_ = NULL;
	shift_ = other.shift_;
	other.shift_ = NULL;
}
template <typename T>
LimitedArrayQueue<T>& LimitedArrayQueue<T>::operator= (const LimitedArrayQueue<T>& other)
{
	if (this != &other)
	{
		shift_ = 0;
		size_ = other.size_;
		if (other.shift_ == 0)
			arr_ = other.arr_;
		else
		{
			for (int i = 0; i < size_; i++)
			{
				arr_[i % capacity_] = other.arr_[i + shift_ % capacity_];
			}
		}
	}
	return *this;
}
template <typename T>
LimitedArrayQueue<T>& LimitedArrayQueue<T>::operator= (LimitedArrayQueue<T>&& other) noexcept
{
	if (this != &other)
	{
		arr_.clear();
		swap(arr_, other.arr_);
		capacity_ = other.capacity_;
		size_ = other.size_;
		shift_ = other.shift_;
		other.capacity_ = NULL;
		other.size_ = NULL;
		other.shift_ = NULL;
	}
	return *this;
}
template <typename T>
LimitedArrayQueue<T>::~LimitedArrayQueue() {};
template <typename T>
bool LimitedArrayQueue<T>::IsEmpty() const
{
	return size_ == 0;
}
template <typename T>
int LimitedArrayQueue<T>::Size() const
{
	return size_;
}
template <typename T>
void LimitedArrayQueue<T>::Resize(int size)
{
	size_ = size;
	if (shift_ != 0)
	{
		for (int i = 0; i < size_; i++)
		{
			arr_[i % capacity_] = arr_[i + shift_ % capacity_];
		}
		shift_ = 0;
	}
	capacity_ = size_;
	arr_.resize(size_);
}
template <typename T>
void LimitedArrayQueue<T>::Reserve(int size)
{
	if (size < size_)
	{
		throw runtime_error("Out_of_range");
	}
	if (shift_ != 0)
	{
		for (int i = 0; i < size_; i++)
		{
			arr_[i % capacity_] = arr_[i + shift_ % capacity_];
		}
		shift_ = 0;
	}
	capacity_ = size;
	arr_.resize(capacity_);
}
template <typename T>
void LimitedArrayQueue<T>::PushBack(const T value)
{
	arr_[size_ + shift_] = value;
	size_++;
}
template <typename T>
void LimitedArrayQueue<T>::PopFront()
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	size_--;
	shift_++;
}
template <typename T>
T LimitedArrayQueue<T>::Front() const
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	return arr_[shift_ % capacity_];
}
template <typename T>
T& LimitedArrayQueue<T>::Front()
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	return arr_[shift_ % capacity_];
}