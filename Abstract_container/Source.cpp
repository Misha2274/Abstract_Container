#include <iostream>
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

	LimitedArrayStack() : capacity_(5000), size_(0)
	{
		arr_ = new int[capacity_];
	}

public:

	LimitedArrayStack(const int size) : capacity_(size), size_(0)
	{
		arr_ = new int[capacity_];
	}
	LimitedArrayStack(const int size, const int value) : capacity_(size), size_(size)
	{
		arr_ = new int[capacity_];
		for (int i = 0; i < capacity_; i++)
		{
			arr_[i] = value;
		}
	}
	LimitedArrayStack(const LimitedArrayStack& other) : capacity_(other.capacity_), size_(other.size_)
	{
		arr_ = new int[capacity_];
		for (int i = 0; i < size_; i++)
		{
			arr_[i] = other.arr_[i];
		}
	}
	LimitedArrayStack& operator= (const LimitedArrayStack& other)
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
	~LimitedArrayStack()
	{
		delete[] arr_;
	}
	bool IsEmpty() const override
	{
		return size_ == 0;
	}
	int Size() const override
	{
		return size_;
	}
	void Resize(int size)
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
	void Push(const int value) override
	{
		if (size_ == capacity_)
		{
			throw runtime_error("Out_of_range");
		}
		arr_[size_] = value;
		size_++;
	}
	void Pop() override
	{
		if (IsEmpty())
		{
			throw runtime_error("Out_of_range");
		}
		size_--;
	}
	int Top() const override
	{
		if (IsEmpty())
		{
			throw runtime_error("Out_of_range");
		}
		return arr_[size_ - 1];
	}
	int& Top() override
	{
		if (IsEmpty())
		{
			throw runtime_error("Out_of_range");
		}
		return arr_[size_ - 1];
	}
};

class UnlimitedArrayStack : public AbstractStack
{

	vector<int> arr_;

public:

	UnlimitedArrayStack() {}
	UnlimitedArrayStack(const int size) 
	{
		arr_.resize(size, 0);
	}
	UnlimitedArrayStack(const int size, const int value)
	{
		arr_.resize(size, value);
	}
	UnlimitedArrayStack(const UnlimitedArrayStack& other)
	{
		arr_ = other.arr_;
	}
	UnlimitedArrayStack& operator= (const UnlimitedArrayStack& other)
	{
		if (this != &other)
		{
			arr_ = other.arr_;
		}
		return *this;
	}
	~UnlimitedArrayStack(){};
	bool IsEmpty() const override
	{
		return arr_.size() == 0;
	}
	int Size() const override
	{
		return arr_.size();
	}
	void Resize(int size)
	{
		arr_.resize(size);
	}
	void Push(const int value) override
	{
		arr_.push_back(value);
	}
	void Pop() override
	{
		if (IsEmpty())
		{
			throw runtime_error("Out_of_range");
		}
		arr_.pop_back();
	}
	int Top() const override
	{
		if (IsEmpty())
		{
			throw runtime_error("Out_of_range");
		}
		return arr_[arr_.size() - 1];
	}
	int& Top() override
	{
		if (IsEmpty())
		{
			throw runtime_error("Out_of_range");
		}
		return arr_[arr_.size() - 1];
	}
};

struct ForwardNode
{
	int data;
	ForwardNode* next;
	ForwardNode(): data(0), next(nullptr){}
	ForwardNode(const int value) : data(value), next(nullptr) {}
};

class ListStack : public AbstractStack
{

	ForwardNode* head_;

public:

	ListStack() : head_(nullptr) {}
	ListStack(int size)
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
	ListStack(int size, int value)
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
	ListStack(const ListStack& other)
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
	ListStack& operator= (const ListStack& other)
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
	~ListStack()
	{
		while (!IsEmpty())
		{
			Pop();
		}
	}
	bool IsEmpty() const override
	{
		return head_ == nullptr;
	}
	int Size() const override
	{
		if (IsEmpty())
			return 0;
		int size = 1;
		for (auto i = head_; i->next != nullptr; i = i->next, size++);
		return size;
	}
	void Push(const int value) override
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
	void Pop() override
	{
		if (IsEmpty())
		{
			throw runtime_error("Out_of_range");
		}
		ForwardNode* pop = head_;
		head_ = head_->next;
		delete pop;
	}
	int Top() const override
	{
		if (IsEmpty())
		{
			throw runtime_error("Out_of_range");
		}
		return head_->data;
	}
	int& Top() override
	{
		if (IsEmpty())
		{
			throw runtime_error("Out_of_range");
		}
		return head_->data;
	}
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
	LimitedArrayQueue() : capacity_(5000), size_(0), shift_(0)
	{
		arr_.resize(5000, 0);
	}

public:

	LimitedArrayQueue(const int size) : capacity_(size), size_(0), shift_(0)
	{
		arr_.resize(size, 0);
	}
	LimitedArrayQueue(const int size, const int value) : capacity_(size), size_(size), shift_(0)
	{
		arr_.resize(size, value);
	}
	LimitedArrayQueue(const LimitedArrayQueue& other) : capacity_(other.capacity_), size_(other.size_), shift_(0)
	{
		if(other.shift_ == 0)
			arr_ = other.arr_;
		else
		{
			for (int i = 0; i < size_; i++)
			{
				arr_[i % capacity_] = other.arr_[i + shift_ % capacity_];
			}
		}
	}
	LimitedArrayQueue& operator= (const LimitedArrayQueue& other)
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
	~LimitedArrayQueue() {};
	bool IsEmpty() const override
	{
		return size_ == 0;
	}
	int Size() const override
	{
		return size_;
	}
	void Resize(int size)
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
	void Reserve(int size)
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
	void PushBack(const int value) override
	{
		arr_[size_ + shift_] = value;
		size_++;
	}
	void PopFront() override
	{
		if (IsEmpty())
		{
			throw runtime_error("Out_of_range");
		}
		size_--;
		shift_++;
	}
	int Front() const override
	{
		if (IsEmpty())
		{
			throw runtime_error("Out_of_range");
		}
		return arr_[shift_ % capacity_];
	}
	int& Front() override
	{
		if (IsEmpty())
		{
			throw runtime_error("Out_of_range");
		}
		return arr_[shift_ % capacity_];
	}
};

struct Node
{
	int data;
	Node* next, * previous;
	Node() : data(0), next(nullptr), previous(nullptr) {}
	Node(const int value) : data(value), next(nullptr), previous(nullptr) {}
};

class ListQueue : public AbstractQueue
{

	Node* head_, * tail_;

public:

	ListQueue() : head_(nullptr), tail_(nullptr) {}
	ListQueue(int size)
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
	ListQueue(int size, int value)
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
	ListQueue(const ListQueue& other)
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
	ListQueue& operator= (const ListQueue& other)
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
	~ListQueue()
	{
		while (!IsEmpty())
		{
			PopFront();
		}
	}
	bool IsEmpty() const override
	{
		return head_ == nullptr;
	}
	int Size() const override
	{
		if (IsEmpty())
			return 0;
		int size = 1;
		for (auto i = head_; i != tail_; i = i->next, size++);
		return size;
	}
	void PushBack(const int value) override
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
	void PopFront() override
	{
		if (IsEmpty())
		{
			throw runtime_error("Out_of_range");
		}
		Node* pop = head_;
		head_ = head_->next;
		delete pop;
	}
	int Front() const override
	{
		if (IsEmpty())
		{
			throw runtime_error("Out_of_range");
		}
		return head_->data;
	}
	int& Front() override
	{
		if (IsEmpty())
		{
			throw runtime_error("Out_of_range");
		}
		return head_->data;
	}
};

int main()
{
	ListQueue A(2, 5);
	AbstractContainer* B = &A;
	ListQueue C(A);
	ListQueue D;
	ListQueue E(D);
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
	return 0;
}