#include "Containers.h"

LimitedArrayStack::LimitedArrayStack() : capacity_(5000), size_(0)
{
	arr_ = new int[capacity_];
}
LimitedArrayStack::LimitedArrayStack(const int size) : capacity_(size), size_(0)
{
	arr_ = new int[capacity_];
}
LimitedArrayStack::LimitedArrayStack(const int size, const int value) : capacity_(size), size_(size)
{
	arr_ = new int[capacity_];
	for (int i = 0; i < capacity_; i++)
	{
		arr_[i] = value;
	}
}
LimitedArrayStack::LimitedArrayStack(const LimitedArrayStack& other) : capacity_(other.capacity_), size_(other.size_)
{
	arr_ = new int[capacity_];
	for (int i = 0; i < size_; i++)
	{
		arr_[i] = other.arr_[i];
	}
}
LimitedArrayStack::LimitedArrayStack(LimitedArrayStack&& other) noexcept
{
	arr_ = other.arr_;
	size_ = other.size_;
	capacity_ = other.capacity_;
	other.arr_ = nullptr;
	other.size_ = NULL;
	other.capacity_ = NULL;
}
LimitedArrayStack& LimitedArrayStack::operator= (const LimitedArrayStack& other)
{
	if (this != &other)
	{
		delete[] arr_;
		arr_ = new int[other.capacity_];
		capacity_ = other.capacity_;
		size_ = other.size_;
		for (int i = 0; i < other.size_; i++)
		{
			arr_[i] = other.arr_[i];
		}
	}
	return *this;
}
LimitedArrayStack& LimitedArrayStack::operator= (LimitedArrayStack&& other) noexcept
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
LimitedArrayStack::~LimitedArrayStack()
{
	delete[] arr_;
}
bool LimitedArrayStack::IsEmpty() const
{
	return size_ == 0;
}
int LimitedArrayStack::Size() const
{
	return size_;
}
void LimitedArrayStack::Resize(int size)
{
	int* arr = new int[size];
	for (int i = 0; i < min(size_, size); i++)
	{
		arr[i] = arr_[i];
	}
	size = size_;
	delete[] arr_;
	arr_ = arr;
}
void LimitedArrayStack::Push(const int value)
{
	if (size_ == capacity_)
	{
		throw runtime_error("Out_of_range");
	}
	arr_[size_] = value;
	size_++;
}
void LimitedArrayStack::Pop()
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	size_--;
}
int LimitedArrayStack::Top() const
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	return arr_[size_ - 1];
}
int& LimitedArrayStack::Top()
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	return arr_[size_ - 1];
}

UnlimitedArrayStack::UnlimitedArrayStack() {}
UnlimitedArrayStack::UnlimitedArrayStack(const int size)
{
	arr_.resize(size, 0);
}
UnlimitedArrayStack::UnlimitedArrayStack(const int size, const int value)
{
	arr_.resize(size, value);
}
UnlimitedArrayStack::UnlimitedArrayStack(const UnlimitedArrayStack& other)
{
	arr_ = other.arr_;
}
UnlimitedArrayStack::UnlimitedArrayStack(UnlimitedArrayStack&& other) noexcept
{
	swap(arr_, other.arr_);
}
UnlimitedArrayStack& UnlimitedArrayStack::operator= (const UnlimitedArrayStack& other)
{
	if (this != &other)
	{
		arr_ = other.arr_;
	}
	return *this;
}
UnlimitedArrayStack& UnlimitedArrayStack::operator= (UnlimitedArrayStack&& other) noexcept
{
	if (this != &other)
	{
		arr_.clear();
		swap(arr_, other.arr_);
	}
	return *this;
}
UnlimitedArrayStack::~UnlimitedArrayStack() {};
bool UnlimitedArrayStack::IsEmpty() const
{
	return arr_.size() == 0;
}
int UnlimitedArrayStack::Size() const
{
	return arr_.size();
}
void UnlimitedArrayStack::Resize(int size)
{
	arr_.resize(size);
}
void UnlimitedArrayStack::Push(const int value) 
{
	arr_.push_back(value);
}
void UnlimitedArrayStack::Pop() 
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	arr_.pop_back();
}
int UnlimitedArrayStack::Top() const
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	return arr_[arr_.size() - 1];
}
int& UnlimitedArrayStack::Top()
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	return arr_[arr_.size() - 1];
}

ForwardNode::ForwardNode() : data(0), next(nullptr) {}
ForwardNode::ForwardNode(const int value) : data(value), next(nullptr) {}

ListStack::ListStack() : head_(nullptr) {}
ListStack::ListStack(int size)
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
ListStack::ListStack(int size, int value)
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
ListStack::ListStack(const ListStack& other)
{
	if (!other.IsEmpty())
	{
		head_ = new ForwardNode(other.Top());
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
ListStack::ListStack(ListStack&& other) noexcept
{
	head_ = other.head_;
	other.head_ = nullptr;
}
ListStack& ListStack::operator= (const ListStack& other)
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
			head_ = new ForwardNode;
			head_->data = other.Top();
			for (auto i = head_, j = other.head_; j->next != nullptr; i = i->next, j = j->next)
			{
				i->next = new ForwardNode(j->next->data);
			}
		}
	}
	return *this;
}
ListStack& ListStack::operator= (ListStack&& other) noexcept
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
ListStack::~ListStack()
{
	while (!IsEmpty())
	{
		Pop();
	}
}
bool ListStack::IsEmpty() const 
{
	return head_ == nullptr;
}
int ListStack::Size() const 
{
	if (IsEmpty())
		return 0;
	int size = 1;
	for (auto i = head_; i->next != nullptr; i = i->next, size++);
	return size;
}
void ListStack::Push(const int value) 
{
	if (IsEmpty())
	{
		head_ = new ForwardNode(value);
		return;
	}
	ForwardNode* push = new ForwardNode(value);
	push->next = head_;
	head_ = push;
}
void ListStack::Pop() 
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	ForwardNode* pop = head_;
	head_ = head_->next;
	delete pop;
}
int ListStack::Top() const 
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	return head_->data;
}
int& ListStack::Top() 
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	return head_->data;
}

LimitedArrayQueue::LimitedArrayQueue() : capacity_(5000), size_(0), shift_(0)
{
	arr_.resize(5000, 0);
}
LimitedArrayQueue::LimitedArrayQueue(const int size) : capacity_(size), size_(0), shift_(0)
{
	arr_.resize(size, 0);
}
LimitedArrayQueue::LimitedArrayQueue(const int size, const int value) : capacity_(size), size_(size), shift_(0)
{
	arr_.resize(size, value);
}
LimitedArrayQueue::LimitedArrayQueue(const LimitedArrayQueue& other) : capacity_(other.capacity_), size_(other.size_), shift_(0)
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
LimitedArrayQueue::LimitedArrayQueue(LimitedArrayQueue&& other) noexcept
{
	swap(arr_, other.arr_);
	capacity_ = other.capacity_;
	other.capacity_ = NULL;
	size_ = other.size_;
	other.size_ = NULL;
	shift_ = other.shift_;
	other.shift_ = NULL;
}
LimitedArrayQueue& LimitedArrayQueue::operator= (const LimitedArrayQueue& other)
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
LimitedArrayQueue& LimitedArrayQueue::operator= (LimitedArrayQueue&& other) noexcept
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
LimitedArrayQueue::~LimitedArrayQueue() {};
bool LimitedArrayQueue::IsEmpty() const
{
	return size_ == 0;
}
int LimitedArrayQueue::Size() const
{
	return size_;
}
void LimitedArrayQueue::Resize(int size)
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
void LimitedArrayQueue::Reserve(int size)
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
void LimitedArrayQueue::PushBack(const int value)
{
	arr_[size_ + shift_] = value;
	size_++;
}
void LimitedArrayQueue::PopFront()
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	size_--;
	shift_++;
}
int LimitedArrayQueue::Front() const
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	return arr_[shift_ % capacity_];
}
int& LimitedArrayQueue::Front()
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	return arr_[shift_ % capacity_];
}

Node::Node() : data(0), next(nullptr), previous(nullptr) {}
Node::Node(const int value) : data(value), next(nullptr), previous(nullptr) {}

ListQueue::ListQueue() : head_(nullptr), tail_(nullptr) {}
ListQueue::ListQueue(int size)
{
	if (size != 0)
	{
		head_ = new Node;
		tail_ = head_;
		for (auto i = head_, tail_ = head_; (size - 1); size--, i = i->next)
		{
			i->next = new Node;
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
ListQueue::ListQueue(int size, int value)
{
	if (size != 0)
	{
		head_ = new Node(value);
		tail_ = head_;
		for (auto i = head_, tail_ = head_; (size - 1); size--, i = i->next)
		{
			i->next = new Node(value);
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
ListQueue::ListQueue(const ListQueue& other)
{
	if (!other.IsEmpty())
	{
		head_ = new Node(other.Front());
		tail_ = head_;
		for (auto i = head_, j = other.head_; j->next != nullptr; i = i->next, j = j->next)
		{
			i->next = new Node(j->next->data);
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
ListQueue::ListQueue(ListQueue&& other) noexcept
{
	head_ = other.head_;
	other.head_ = nullptr;
	tail_ = other.tail_;
	other.tail_ = nullptr;
}
ListQueue& ListQueue::operator= (const ListQueue& other)
{
	if (this != &other)
	{
		while (!IsEmpty())
		{
			PopFront();
			head_ = nullptr;
			tail_ = nullptr;
		}
		if (!other.IsEmpty())
		{
			head_ = new Node(other.head_->data);
			for (auto i = head_, j = other.head_; j->next != nullptr; i = i->next, j = j->next)
			{
				i->next = new Node(j->next->data);
				i->next->previous = i;
				tail_ = i->next;
			}
		}
	}
	return *this;
}
ListQueue& ListQueue::operator= (ListQueue&& other) noexcept
{
	if (this != &other)
	{
		while (!IsEmpty())
		{
			PopFront();
			head_ = nullptr;
			tail_ = nullptr;
		}
		head_ = other.head_;
		tail_ = other.tail_;
		other.head_ = nullptr;
		other.tail_ = nullptr;
	}
	return *this;
}
ListQueue::~ListQueue()
{
	while (!IsEmpty())
	{
		PopFront();
	}
}
bool ListQueue::IsEmpty() const
{
	return head_ == nullptr;
}
int ListQueue::Size() const
{
	if (IsEmpty())
		return 0;
	int size = 1;
	for (auto i = head_; i != tail_; i = i->next, size++);
	return size;
}
void ListQueue::PushBack(const int value)
{
	if (IsEmpty())
	{
		tail_ = new Node(value);
		head_ = tail_;
		return;
	}
	Node* push = new Node(value);
	push->previous = tail_;
	tail_->next = push;
	tail_ = push;
}
void ListQueue::PopFront()
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	Node* pop = head_;
	head_ = head_->next;
	delete pop;
}
int ListQueue::Front() const
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	return head_->data;
}
int& ListQueue::Front()
{
	if (IsEmpty())
	{
		throw runtime_error("Out_of_range");
	}
	return head_->data;
}