#include "LoggedUser.h"

template <class T>
T* UniquePtr<T>::currentUser_ = nullptr;

template <class T>
void UniquePtr<T>::set(T* user) {
    currentUser_ = user;
}
template <class T>
T* UniquePtr<T>::get() {
    return currentUser_;
}