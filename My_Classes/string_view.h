#pragma once

#include <iostream>
#include <utility>
#include <cstring>
#include <stdexcept>


class StringView {
    const char *str_ = nullptr;
    size_t size_ = 0;

public:
    class ConstIterator {
        const char *iterator = nullptr;
    public:
        ConstIterator(const char *pointer) : iterator(pointer) {}

        bool operator!=(const ConstIterator &that) const;

        ConstIterator &operator++();

        const char &operator*() const;
    };

    class ConstReverseIterator {
        const char *reverse_iterator = nullptr;
    public:
        ConstReverseIterator(const char *pointer) : reverse_iterator(pointer) {}

        bool operator!=(const ConstReverseIterator &that) const;

        ConstReverseIterator &operator++();

        const char &operator*() const;
    };


    StringView() : str_(nullptr), size_(0) {}

    StringView(const char *str) : str_(str), size_(strlen(str)) {}

    StringView(const char *str, size_t size) : str_(str), size_(size) {}

    const char &operator[](size_t index) const noexcept;

    const char &At(size_t index) const;

    const char &Front() const;

    const char &Back() const;

    size_t Size() const;

    size_t Length() const;

    bool Empty() const;

    const char *Data() const;

    void Swap(StringView &other);

    void RemovePrefix(size_t prefix_size);

    void RemoveSuffix(size_t suffix_size);

    StringView Substr(size_t pos, size_t count = -1) const;

    ConstIterator begin() const;

    ConstIterator cbegin() const;

    ConstIterator end() const;

    ConstIterator cend() const;

    ConstReverseIterator rbegin() const;

    ConstReverseIterator crbegin() const;

    ConstReverseIterator rend() const;

    ConstReverseIterator crend() const;

};


bool StringView::ConstIterator::operator!=(const StringView::ConstIterator &that) const {
    return this->iterator != that.iterator;
}

StringView::ConstIterator &StringView::ConstIterator::operator++() {
    ++iterator;
    return *this;
}

const char &StringView::ConstIterator::operator*() const {
    return *iterator;
}

bool StringView::ConstReverseIterator::operator!=(const StringView::ConstReverseIterator &that) const {
    return reverse_iterator != that.reverse_iterator;
}

StringView::ConstReverseIterator &StringView::ConstReverseIterator::operator++() {
    --reverse_iterator;
    return *this;
}

const char &StringView::ConstReverseIterator::operator*() const {
    return *reverse_iterator;
}


const char &StringView::operator[](size_t index) const noexcept {
    return str_[index];
}

const char &StringView::At(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("you are out of range");
    }
    return str_[index];
}

const char &StringView::Front() const {
    return str_[0];
}

const char &StringView::Back() const {
    return str_[size_ - 1];
}

size_t StringView::Size() const {
    return size_;
}

size_t StringView::Length() const {
    return size_;
}

bool StringView::Empty() const {
    return size_ == 0;
}

const char *StringView::Data() const {
    return str_;
}

void StringView::Swap(StringView &other) {
    std::swap(str_, other.str_);
}

void StringView::RemovePrefix(size_t prefix_size) {
    str_ += prefix_size;
    size_ -= prefix_size;
}

void StringView::RemoveSuffix(size_t suffix_size) {
    size_ -= suffix_size;
}

StringView StringView::Substr(size_t pos, size_t count) const {
    return StringView(str_ + pos, count);
}

StringView::ConstIterator StringView::begin() const {
    return ConstIterator{str_};
}

StringView::ConstIterator StringView::cbegin() const {
    return begin();
}

StringView::ConstIterator StringView::end() const {
    return ConstIterator{str_ + size_};
}

StringView::ConstIterator StringView::cend() const {
    return end();
}

StringView::ConstReverseIterator StringView::crbegin() const {
    return rbegin();
}

StringView::ConstReverseIterator StringView::rbegin() const {
    return ConstReverseIterator(str_ + size_ - 1);
}

StringView::ConstReverseIterator StringView::crend() const {
    return rend();
}

StringView::ConstReverseIterator StringView::rend() const {
    return ConstReverseIterator(str_ - 1);
}


