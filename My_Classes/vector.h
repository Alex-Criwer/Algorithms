#include <iostream>

using namespace std;

template<class T>
class Vector {
private:
    size_t size;
    size_t capacity;
    T *buffer;

    void free();

    void overWrite();

public:
    Vector();

    explicit Vector(const size_t &size);

    explicit Vector(const size_t &size, const T &value);

    Vector(const Vector<T> &that);

    Vector<T> &operator=(const Vector<T> &that);

    void Clear();

    void PushBack(const T &value);

    void PopBack();

    void Resize(const size_t &new_size);

    void Resize(const size_t &new_size, const T &value);

    void Reserve(const size_t &new_cap);

    void ShrinkToFit();

    void Swap(Vector<T> &that);

    T &operator[](const size_t &index);

    const T &operator[](const size_t &index) const;

    T &Front();

    const T &Front() const;

    T &Back();

    const T &Back() const;

    bool Empty() const;

    size_t Size() const;

    size_t Capacity() const;

    T *Data();

    const T *Data() const;

    template<class C>
    friend bool operator<(const Vector<C> &first, const Vector<C> &second);

    template<class C>
    friend bool operator==(const Vector<C> &first, const Vector<C> &second);

    template<class C>
    friend bool operator!=(const Vector<C> &first, const Vector<C> &second);

    template<class C>
    friend bool operator>(const Vector<C> &first, const Vector<C> &second);

    template<class C>
    friend bool operator>=(const Vector<C> &first, const Vector<C> &second);

    template<class C>
    friend bool operator<=(const Vector<C> &first, const Vector<C> &second);

    ~Vector();
};

template<class T>
Vector<T>::Vector() : size(0), capacity(0), buffer(nullptr) {}


template<class T>
Vector<T>::Vector(const size_t &size) {
    this->size = size;
    this->capacity = size;
    buffer = ((size != 0) ? new T[size] : nullptr);
}

template<class T>
Vector<T>::Vector(const size_t &size, const T &value): Vector(size) {
    for (size_t i = 0; i < size; ++i) {
        buffer[i] = value;
    }
}

template<class T>
Vector<T>::Vector(const Vector<T> &that) {
    if (that.buffer != nullptr) {
        this->size = that.size;
        this->capacity = that.capacity;
        buffer = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            buffer[i] = that.buffer[i];
        }
    } else {
        buffer = nullptr;
        size = capacity = 0;
    }
}

template<class T>
Vector<T> &Vector<T>::operator=(const Vector<T> &that) {
    if (that.buffer == nullptr) {
        this->free();
        buffer = nullptr;
    } else if (this != &that) {
        if (that.capacity > capacity) {
            this->free();
            capacity = that.capacity;
            buffer = new T[capacity];
        }
        size = that.size;
        for (size_t i = 0; i < size; ++i) {
            buffer[i] = that.buffer[i];
        }
    }
    return *this;
}

template<class T>
void Vector<T>::free() {
    capacity = 0;
    size = 0;
    delete[] buffer;
}

template<class T>
Vector<T>::~Vector() {
    this->free();
}

template<class T>
void Vector<T>::Clear() {
    size = 0;
}

template<class T>
void Vector<T>::PushBack(const T &value) {
    if (capacity == 0) {
        ++capacity;
        buffer = new T[capacity];
    } else if (capacity == size) {
        capacity *= 2;
        overWrite();
    }
    ++size;
    buffer[size - 1] = value;
}

template<class T>
void Vector<T>::overWrite() {

    T *newBuffer = new T[capacity];
    for (size_t i = 0; i < size; ++i) {
        newBuffer[i] = this->buffer[i];
    }
    delete[] buffer;
    buffer = newBuffer;
}

template<class T>
void Vector<T>::PopBack() {
    if (size != 0) {
        --size;
    }
}

template<class T>
void Vector<T>::Resize(const size_t &new_size) {
    if (new_size <= capacity) {
        size = new_size;
    } else {
        capacity = new_size;
        overWrite();
        size = new_size;
    }
}

template<class T>
void Vector<T>::Resize(const size_t &new_size, const T &value) {
    size_t oldSize = size;
    Resize(new_size);
    if (new_size > oldSize) {
        for (size_t i = oldSize; i < new_size; ++i) {
            buffer[i] = value;
        }
    }

}

template<class T>
void Vector<T>::Reserve(const size_t &new_cap) {
    if (new_cap > capacity) {
        capacity = new_cap;
        overWrite();
    }
}

template<class T>
void Vector<T>::ShrinkToFit() {
    capacity = size;
    overWrite();
}

template<class T>
void Vector<T>::Swap(Vector<T> &that) {
    swap(*this, that);
}

template<class T>
T &Vector<T>::operator[](const size_t &index) {
    return buffer[index];
}

template<class T>
const T &Vector<T>::operator[](const size_t &index) const {
    return buffer[index];
}

template<class T>
T &Vector<T>::Front() {
    return buffer[0];
}

template<class T>
const T &Vector<T>::Front() const {
    return buffer[0];
}

template<class T>
T &Vector<T>::Back() {
    return buffer[size - 1];
}

template<class T>
const T &Vector<T>::Back() const {
    return buffer[size - 1];
}

template<class T>
bool Vector<T>::Empty() const {
    return size == 0;
}

template<class T>
size_t Vector<T>::Size() const {
    return size;
}

template<class T>
size_t Vector<T>::Capacity() const {
    return capacity;
}

template<class T>
T *Vector<T>::Data() {
    return buffer;
}

template<class T>
const T *Vector<T>::Data() const {
    return buffer;
}

template<class T>
bool operator<(const Vector<T> &first, const Vector<T> &second) {
    size_t i = 0;
    size_t minSize = min(first.Size(), second.Size());
    while (i < minSize && first[i] == second[i]) {
        ++i;
    }
    if (i == minSize) {
        return (first.Size() < second.Size());
    }
    return first[i] < second[i];
}

template<class T>
bool operator>(const Vector<T> &first, const Vector<T> &second) {
    return second < first;
}

template<class T>
bool operator==(const Vector<T> &first, const Vector<T> &second) {
    return !(first < second) && !(second < first);
}

template<class T>
bool operator!=(const Vector<T> &first, const Vector<T> &second) {
    return (first < second || second < first);
}

template<class T>
bool operator<=(const Vector<T> &first, const Vector<T> &second) {
    return (first < second || first == second);
}

template<class T>
bool operator>=(const Vector<T> &first, const Vector<T> &second) {
    return (second < first || first == second);
}

