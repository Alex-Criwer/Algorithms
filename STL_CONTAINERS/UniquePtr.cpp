#include <iostream>
#include <bits/unique_ptr.h>

template<class T>
class UniquePtr {
    T *ptr;
public:
    UniquePtr() : ptr(nullptr) {}

    explicit UniquePtr(T *otherPtr) : ptr(otherPtr) {}

    UniquePtr(const UniquePtr &other) = delete;

    UniquePtr &operator=(const UniquePtr &other) = delete;

    UniquePtr(UniquePtr&& other);

    UniquePtr& operator =(UniquePtr&& other);

    T* Get() const;

    T& operator*() const;

    T*operator->() const;

    T* Release();

    void Reset(T* ptrT = nullptr){
        std::swap(this->ptr,ptrT);
        delete ptrT;
        ptrT = nullptr;
    }

    void Swap(UniquePtr<T>& other){
        std::swap(ptr,other.ptr);
    }

    operator bool() const;

    ~UniquePtr();

};

template<class T>
UniquePtr<T>::~UniquePtr() {
    delete ptr;
}

template<class T>
UniquePtr<T>::UniquePtr(UniquePtr<T> &&other) {
    this->ptr = other.ptr;
    other.ptr = nullptr;
}

template<class T>
UniquePtr<T>& UniquePtr<T>::operator=(UniquePtr<T> &&other) {
    if(this == &other){
        return *this;
    }
    delete ptr;
    ptr = other.ptr;
    other.ptr = nullptr;
    return *this;
}

template<class T>
T *UniquePtr<T>::Get() const {
    return ptr;
}

template<class T>
T& UniquePtr<T>::operator*() const {
    return *ptr;
}

template<class T>
T *UniquePtr<T>::operator->() const {
    return ptr;
}

template<class T>
T *UniquePtr<T>::Release() {
    T* newPtr = Get();
    ptr = nullptr;
    return newPtr;
}

template<class T>
UniquePtr<T>::operator bool() const {
    return ptr != nullptr;
}

int main() {


    return 0;
}
