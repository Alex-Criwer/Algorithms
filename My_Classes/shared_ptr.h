#ifndef SHARED_PTR_H
#define SHARED_PTR_H

#include <iostream>
#include <stdexcept>

class BadWeakPtr : public std::logic_error {
public:
    BadWeakPtr() : logic_error("It's a bad idea, honey") {}
};

struct Counter {
    int strong_counter = 0;
    int weak_counter = 0;
};

template<class T>
class WeakPtr;

template<class T>
class SharedPtr {
private:
    T *value = nullptr;
    Counter *counter = nullptr;
public:
    SharedPtr() : value(nullptr) {}

    SharedPtr(T *ptr);

    SharedPtr(const SharedPtr<T> &other);

    SharedPtr &operator=(const SharedPtr<T> &other);

    SharedPtr &operator=(T *other);

    SharedPtr(SharedPtr &&other);

    SharedPtr &operator=(SharedPtr<T> &&other);

    T *Get() const;

    int UseCount() const;

    void Reset(T *ptr = nullptr);

    void Swap(SharedPtr<T> &other);

    T &operator*() const;

    T *operator->() const;

    operator bool() const;

    Counter *getCounter() const;

    ~SharedPtr();

    void deleter();

    SharedPtr(const WeakPtr<T> &other);

    friend class WeakPtr<T>;

};

template<class T>
class WeakPtr {
    T *value = nullptr;
    Counter *counter = nullptr;
public:

    WeakPtr() : value(nullptr) {}

    WeakPtr(T *ptr);

    WeakPtr(nullptr_t);

    WeakPtr(const WeakPtr<T> &other);

    WeakPtr(const SharedPtr<T> &other);

    WeakPtr &operator=(const WeakPtr<T> &other);

    WeakPtr(WeakPtr<T> &&other);

    WeakPtr &operator=(WeakPtr<T> &&other);

    void Swap(WeakPtr<T> &other);

    void Reset();

    int UseCount() const;

    bool Expired() const;

    SharedPtr<T> Lock();

    T *Get() const;

    Counter *getCounter() const;

    void deleterWeak();

    ~WeakPtr();
};


template<class T>
SharedPtr<T>::SharedPtr(T *ptr) {
    this->value = ptr;
    counter = new Counter;
    this->counter->strong_counter++;
}

template<class T>
T *SharedPtr<T>::Get() const {
    return value;
}

template<class T>
SharedPtr<T>::SharedPtr(const SharedPtr &other) {
    this->value = other.value;
    this->counter = other.counter;
    this->counter->strong_counter++;

}

template<class T>
SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr &other) {
    if (this == &other) {
        return *this;
    }
    deleter();
    this->value = other.value;
    this->counter = other.counter;
    ++this->counter->strong_counter;
    return *this;
}

template<class T>
SharedPtr<T> &SharedPtr<T>::operator=(T *other) {
    if (this->value == other) {
        return *this;
    }
    deleter();
    if (other != nullptr) {
        this->value = other;
        counter = new Counter;
        this->counter->strong_counter++;
    } else {
        this->value = nullptr;
        this->counter = nullptr;
    }
    return *this;
}


template<class T>
SharedPtr<T>::SharedPtr(SharedPtr<T> &&other) {
    this->value = std::move(other.value);
    this->counter = std::move(other.counter);
    other.counter = nullptr;
    other.value = nullptr;
}

template<class T>
SharedPtr<T> &SharedPtr<T>::operator=(SharedPtr<T> &&other) {
    if (this == &other) {
        return *this;
    }
    deleter();
    this->value = std::move(other.value);
    this->counter = std::move(other.counter);
    other.counter = nullptr;
    other.value = nullptr;
    return *this;
}

template<class T>
int SharedPtr<T>::UseCount() const {
    if (this->counter != nullptr) {
        return this->counter->strong_counter;
    }
    return 0;
}

template<class T>
SharedPtr<T>::~SharedPtr() {
    deleter();
}

template<class T>
void SharedPtr<T>::Swap(SharedPtr<T> &other) {
    std::swap(value, other.value);
    std::swap(counter, other.counter);
}

template<class T>
void SharedPtr<T>::Reset(T *ptr) {
    deleter();
    this->value = ptr;
    this->counter = nullptr;
    if (ptr != nullptr) {
        counter = new Counter;
        ++counter->strong_counter;
    }

}

template<class T>
T &SharedPtr<T>::operator*() const {
    return *value;
}

template<class T>
T *SharedPtr<T>::operator->() const {
    return value;
}

template<class T>
SharedPtr<T>::operator bool() const {
    return Get() != nullptr;
}

template<class T>
Counter *SharedPtr<T>::getCounter() const {
    return counter;
}

template<class T>
SharedPtr<T>::SharedPtr(const WeakPtr<T> &other) {
    if (other.Expired()) {
        throw BadWeakPtr();
    }
    this->value = other.Get();
    this->counter = other.getCounter();
    if (value != nullptr) {
        this->counter->strong_counter++;
    }
}

template<class T>
void SharedPtr<T>::deleter() {
    if (this->counter != nullptr) {
        this->counter->strong_counter--;
        if (this->counter->strong_counter == 0) {
            delete value;
        }
        if (this->counter->strong_counter + this->counter->weak_counter == 0) {
            delete counter;
        }
    }
}


template<class T>
WeakPtr<T>::WeakPtr(T *ptr) {
    this->value = ptr;
    this->counter = nullptr;
    if (ptr != nullptr) {
        counter = new Counter;
        this->counter->weak_counter++;
    }

}

template<class T>
WeakPtr<T>::WeakPtr(nullptr_t) {
    this->value = nullptr;
    counter = new Counter;
    counter->weak_counter = 0;
}

template<class T>
WeakPtr<T>::WeakPtr(const WeakPtr &other) {
    this->value = other.value;
    this->counter = other.counter;
    if (value != nullptr) {
        this->counter->weak_counter++;
    }
}


template<class T>
WeakPtr<T> &WeakPtr<T>::operator=(const WeakPtr &other) {
    if (this == &other) {
        return *this;
    }
    deleterWeak();
    this->value = other.value;
    this->counter = other.counter;
    ++this->counter->weak_counter;
    return *this;
}

template<class T>
WeakPtr<T>::WeakPtr(WeakPtr<T> &&other) {
    this->value = std::move(other.value);
    this->counter = std::move(other.counter);
    other.counter = nullptr;
    other.value = nullptr;
}

template<class T>
WeakPtr<T> &WeakPtr<T>::operator=(WeakPtr<T> &&other) {
    if (this == &other) {
        return *this;
    }
    deleterWeak();
    this->value = std::move(other.value);
    this->counter = std::move(other.counter);
    other.counter = nullptr;
    other.value = nullptr;
    return *this;
}

template<class T>
WeakPtr<T>::WeakPtr(const SharedPtr<T> &other) {
    this->value = other.Get();
    this->counter = other.getCounter();
    if (this->value != nullptr) {
        this->counter->weak_counter++;
    }
}

template<class T>
void WeakPtr<T>::Swap(WeakPtr<T> &other) {
    std::swap(this->value, other.value);
    std::swap(this->counter, other.counter);
}

template<class T>
void WeakPtr<T>::Reset() {
    deleterWeak();
    this->value = nullptr;
    this->counter = nullptr;
}

template<class T>
int WeakPtr<T>::UseCount() const {
    if (this->counter != nullptr) {
        return this->counter->strong_counter;
    }
    return 0;
}

template<class T>
bool WeakPtr<T>::Expired() const {
    return value == nullptr || counter->strong_counter == 0;
}

template<class T>
SharedPtr<T> WeakPtr<T>::Lock() {
    if (Expired()) {
        return nullptr;
    }
    SharedPtr<T> tmp(*this);
    return tmp;
}

template<class T>
T *WeakPtr<T>::Get() const {
    return value;
}

template<class T>
Counter *WeakPtr<T>::getCounter() const {
    return counter;
}

template<class T>
void WeakPtr<T>::deleterWeak() {
    if (this->counter != nullptr) {
        this->counter->weak_counter--;
        if (this->counter->strong_counter + this->counter->weak_counter == 0) {
            delete counter;
        }
    }
}

template<class T>
WeakPtr<T>::~WeakPtr() {
    deleterWeak();
}

#endif //SHARED_PTR_H
