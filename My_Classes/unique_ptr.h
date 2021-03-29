#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

#include <utility>

#include <iostream>

template<class T>
class UniquePtr {
    T *ptr;
public:
    UniquePtr() : ptr(nullptr) {}

    explicit UniquePtr(T *otherPtr) : ptr(otherPtr) {}

    UniquePtr(const UniquePtr &other) = delete;

    UniquePtr &operator=(const UniquePtr &other) = delete;

    UniquePtr(UniquePtr &&other);

    UniquePtr &operator=(UniquePtr &&other);

    T *Get() const;

    T &operator*() const;

    T *operator->() const;

    T *Release();

    void Reset(T *ptrT = nullptr);

    void Swap(UniquePtr<T> &other);

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
UniquePtr<T> &UniquePtr<T>::operator=(UniquePtr<T> &&other) {
    if (this == &other) {
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
T &UniquePtr<T>::operator*() const {
    return *ptr;
}

template<class T>
T *UniquePtr<T>::operator->() const {
    return ptr;
}

template<class T>
T *UniquePtr<T>::Release() {
    T *newPtr = Get();
    ptr = nullptr;
    return newPtr;
}

template<class T>
UniquePtr<T>::operator bool() const {
    return ptr != nullptr;
}

template<class T>
void UniquePtr<T>::Reset(T *ptrT) {

    std::swap(this->ptr, ptrT);
    delete ptrT;
    ptrT = nullptr;

}

template<class T>
void UniquePtr<T>::Swap(UniquePtr<T> &other) {
    std::swap(ptr, other.ptr);
}
//#define MAKE_UNIQUE_IMPLEMENTED

#endif // UNIQUE_PTR_H
