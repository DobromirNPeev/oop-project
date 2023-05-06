#pragma once
#include "User.h"
#include "Topic.h"

template <class T>
class UniquePtr {
public:
    static T* get();
    static void set(T* user);
private:
    static T* currentUser_;
};
