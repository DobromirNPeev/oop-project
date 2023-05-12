#include "Vector.h"
#include <exception>
#include <cmath>

template <class T>
Vector<T>::Vector() : data(nullptr),size(0),capacity(0){ }

template <class T>
Vector<T>::Vector(size_t capacity) : capacity(capacity) {
	data = new T[capacity];
}

template <class T>
Vector<T>::Vector(const Vector<T>& other) {
	copyFrom(other);
}

template <class T> 
Vector<T>::Vector(Vector<T>&& other) {
	move(std::move(other));
}
template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other) {
	if (this != &other) {
		free();
		copyFrom(other);
	}

	return *this;
}

template<class T>
Vector<T>& Vector<T>::operator=(Vector<T>&& other) {
	if (this != &other) {
		free();
		move(std::move(other));
	}

	return *this;
}
template<class T>
Vector<T>::~Vector() {
	free();
}

template<class T>
void Vector<T>::assertIndex(size_t index) const {
	if (index >= size) {
		throw std::exception("Out of range");
	}
}

template<class T>
void Vector<T>::upsizeIfNeeded() {
	if (size == capacity) {
		resize(capacity * 2);
	}
}

template<class T>
void Vector<T>::downsizeIfNeeded() {
	if (size * 2 * 2 <= capacity) {
		resize(capacity / 2);
	}
}

template<class T>
void Vector<T>::resize(size_t newCapacity) {
	capacity = newCapacity;
	T* temp = new T[capacity];

	// Note: the std::vector allocates ONLY MORE than the current capacity
	if (size > newCapacity) {
		size = newCapacity;
	}

	for (size_t i = 0; i < size; i++) {
		temp[i] = data[i];
	}

	delete[] data;
	data = temp;
}

template<class T>
size_t Vector<T>::getSize() const {
	return size;
}

template<class T>
size_t Vector<T>::getCapacity() const {
	return capacity;
}

template<class T>
void Vector<T>::pushBack(const T& element) {
	upsizeIfNeeded();
	data[size++] = element;
}

template<class T>
void Vector<T>::pushBack(T&& element) {
	upsizeIfNeeded();
	data[size++] = std::move(element);
}

template<class T>
void Vector<T>::pushAt(const T& element, size_t index) {
	assertIndex(index);
	upsizeIfNeeded();

	for (size_t i = size; i > index; i--) {
		data[i] = data[i - 1];
	}

	data[index] = element;
	size++;
}

template<class T>
void Vector<T>::pushAt(T&& element, size_t index) {
	assertIndex(index);
	upsizeIfNeeded();

	for (size_t i = size; i > index; i--) {
		data[i] = data[i - 1];
	}

	data[index] = std::move(element);
	size++;
}

template<class T>
T Vector<T>::popBack() {
	if (empty()) {
		throw std::exception("Vector is empty");
	}
	// Note: the actual std::vector does NOT lower its capacity on this function
	//downsizeIfNeeded();
	// Note: the actual std::vector does NOT return on popback
	return data[size--];
}

template<class T>
T Vector<T>::popAt(size_t index) {
	assertIndex(index);
	// Note: the actual std::vector does NOT lower its capacity on this function
	downsizeIfNeeded();

	T temp = data[index];
	size--;
	for (size_t i = index; i < size; i++) {
		data[i] = data[i + 1];
	}

	return data[index];
}

template<class T>
bool Vector<T>::empty() const {
	return size == 0;
}

template<class T>
void Vector<T>::clear() {
	size = 0;
}

template<class T>
void Vector<T>::shrinkToFit() {
	resize(size);
}

template<class T>
T& Vector<T>::operator[](size_t index) {
	assertIndex(index);

	return data[index];
}

template<class T>
const T& Vector<T>::operator[](size_t index) const {
	assertIndex(index);

	return data[index];
}

template<class T>
void Vector<T>::move(Vector<T>&& other) {
	size = other.size;
	capacity = other.capacity;
	data = other.data;
	other.data = nullptr;
}

template<class T>
void Vector<T>::copyFrom(const Vector<T>& other) {
	size = other.size;
	capacity = other.capacity;
	data = new T[capacity];


	for (size_t i = 0; i < other.size; i++) {
		data[i] = other.data[i];
	}
}

template<class T>
void Vector<T>::free() {
	delete[] data;
	data = nullptr;
	size = capacity = 0;
}
 // explicit instantiation of the class for int type
//template class Vector<MyString>; // explicit instantiation of the class for int type
template class Vector<User>;
template class Vector<Topic>;
template class Vector<Post>;
template class Vector<Comment>;
template class Vector<MyString>;