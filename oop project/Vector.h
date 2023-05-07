#pragma once
#include <iostream>
#include "Topic.h"
#include "Post.h"
#include "User.h"
#include "Comment.h"


template<class T>
class Vector {
private:
	T* data = nullptr;
	size_t size = 0;
	size_t capacity;
	// the resize function of the actual std::vector
	// just lowers the size, this function is called reserve there
	void resize(size_t newCapacity);

	// Not needed functions - created by in class
	void assertIndex(size_t index) const;
	void upsizeIfNeeded();
	void downsizeIfNeeded();
public:
	Vector();
	Vector(size_t capacity);
	Vector(const Vector<T>& other);
	Vector(Vector<T>&& other);
	//operator=(const Vector& other);
	Vector& operator=(const Vector<T>& other);
	Vector& operator=(Vector<T>&& other);
	~Vector();

	size_t getSize() const;
	size_t getCapacity() const;

	// push/pop at do not exist in actual std::vector
	void pushBack(const T& element);
	void pushBack(T&& element);
	void pushAt(const T& element, size_t index);
	void pushAt(T&& element, size_t index);
	T popBack();
	T popAt(size_t index);

	bool empty() const;
	void clear();
	void shrinkToFit();

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

private:
	void move(Vector<T>&& other);
	void copyFrom(const Vector<T>& other);
	void free();
};
