#include "Containers.h"

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
		head_ = new ForwardNode;
		for (auto i = head_; (size - 1); size--, i = i->next)
		{
			i->next = new ForwardNode;
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
		head_ = new ForwardNode(value);
		for (auto i = head_; (size - 1); size--, i = i->next)
		{
			i->next = new ForwardNode(value);
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
			i->next = new ForwardNode(j->next->data);
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
	ForwardNode* push = new ForwardNode<T>(value);
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
	ForwardNode* pop = head_;
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
	Node* push = new Node<T>(value);
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
	Node* pop = head_;
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