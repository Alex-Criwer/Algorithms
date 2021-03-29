#ifndef ANY_H
#define ANY_H

#include<iostream>
#include <stdexcept>
#include <memory>

class BadAnyCast : public std::logic_error {
public:
    BadAnyCast() : logic_error("It's a bad idea, honey") {}
};

class Base {
public:
    virtual std::shared_ptr<Base> Clone() const = 0;
};

template<class T>
class Derived : public Base {
    T value;
public:
    Derived(T value) : value(value) {}

    T getValue() const {
        return value;
    }

    std::shared_ptr<Base> Clone() const override {
        return std::make_shared<Derived<T>>(value);
    }
};

class Any {
    std::shared_ptr<Base> ptr;

public:
    Any() : ptr(nullptr) {}

    Any(const Any &other);

    Any(Any &&other);

    Any &operator=(Any &&other);

    Any &operator=(const Any &other);

    template<class T>
    Any(const T &value): ptr(std::make_shared<Derived<T>>(value)) {}

    void Swap(Any &other);

    void Reset();

    bool HasValue() const;

    template<class T>
    friend T any_cast(const Any &value);

    ~Any();

};

template<class T>
T any_cast(const Any &value) {
    const Derived<T> *tmp = dynamic_cast<const Derived<T> *>(value.ptr.get());
    if (!tmp) {
        throw BadAnyCast();
    }
    return tmp->getValue();;
}


Any::Any(const Any &other) {
    this->ptr = other.ptr->Clone();
}


Any &Any::operator=(const Any &other) {
    if (this == &other) {
        return *this;
    }
    this->ptr.reset();
    this->ptr = other.ptr->Clone();
    return *this;
}

void Any::Swap(Any &other) {
    std::swap(this->ptr, other.ptr);
}

void Any::Reset() {
    this->ptr.reset();
}

bool Any::HasValue() const {
    return ptr != nullptr;
}

Any::Any(Any &&other) {
    this->ptr = other.ptr->Clone();
    other.ptr.reset();
}

Any &Any::operator=(Any &&other) {
    this->ptr.reset();
    this->ptr = other.ptr->Clone();
    other.ptr.reset();
    return *this;
}

Any::~Any() {
    ptr.reset();
}


#endif // ANY_H

