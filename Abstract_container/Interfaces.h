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
class AbstractQueue : public AbstractContainer<T>
{

public:

	virtual void PushBack(const T value) = 0;
	virtual void PopFront() = 0;
	virtual T Front() const = 0;
	virtual T& Front() = 0;

};
