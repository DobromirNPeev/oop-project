#pragma once

template <class T>
class UniquePtr {
public:
    static T* get();
    static void set(T* user);
private:
    static T* ptr;
};

template <class T>
T* UniquePtr<T>::ptr = nullptr;

template <class T>
void UniquePtr<T>::set(T* user) {
    ptr = user;
}
template <class T>
T* UniquePtr<T>::get() {
    return ptr;
}