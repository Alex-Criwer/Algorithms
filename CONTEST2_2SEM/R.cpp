/*
Input format
Дано число A(0 ≤ A ≤ 10^250)
Output format
Выведите такое наибольшее целое число X, что X^2 ≤ A.
*/

//Coded by Artur Kulapin


#include <iostream>
#include <cstring>

const int MAX_SIZE = 250;

class BigInteger {
    int* number_ = new int[MAX_SIZE];
    int size_ = 1;
    bool isNegative_ = false;
    int Size() const {
        for (int i = MAX_SIZE - 1; i >= 0; --i) {
            if (number_[i] != 0) {
                return i + 1;
            }
        }
        return 1;
    }


public:

    ~BigInteger() {
        delete[] number_;
    }

    BigInteger() {
        size_ = 0;
        isNegative_ = false;
        for (int i = 0; i < MAX_SIZE; ++i) {
            number_[i] = 0;
        }
    }
    BigInteger(const BigInteger& other) {
        if (other.number_ != this->number_) {
            isNegative_ = other.isNegative_;
            size_ = other.size_;
            for (int i = 0; i < MAX_SIZE; ++i) {
                number_[i] = other.number_[i];
            }
        }
    }

    BigInteger(const int& other) {
        if (other < 0) {
            isNegative_ = true;
        }

        int copy = other;
        size_ = 0;
        for (int i = 0; i < 1000; ++i) {
            number_[i] = copy % 10;
            ++size_;
            copy /= 10;
            if (copy == 0) {
                break;
            }
        }
        for (int i = size_; i < MAX_SIZE; ++i) {
            number_[i] = 0;
        }
    }

    BigInteger& operator=(const BigInteger& other) {
        if (this->number_ != other.number_) {
            int needSize = std::max(size_, other.size_);
            size_ = other.size_;
            isNegative_ = other.isNegative_;
            for (int i = 0; i < needSize; ++i) {
                number_[i] = other.number_[i];
            }
        }
        return *this;
    }

    friend std::istream& operator>>(std::istream& is, BigInteger& value) {
        char* input = new char[MAX_SIZE];
        is >> input;
        int size = static_cast<int>(strlen(input));
        value.size_ = size;
        if (input[0] == '-') {
            value.isNegative_ = true;
            --value.size_;
        }
        for (int i = 0; i < size; ++i) {
            value.number_[i] = input[size- 1 - i] - '0' ;
        }
        for (int i = size; i < MAX_SIZE; ++i) {
            value.number_[i] = 0;
        }
        delete[] input;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const BigInteger& value) {
        if (value.isNegative_) {
            std::cout << '-';
        }
        for (int i = value.size_ - 1; i >= 0; --i) {
            std::cout << value.number_[i];
        }
        return os;
    }

    friend BigInteger operator+(const BigInteger& a, const BigInteger& b) {
        BigInteger result;
        int transfer = 0;
        for (int i = 0; i < MAX_SIZE; ++i) {
            if ((i == std::max(a.size_, b.size_) && transfer > 0) || (i < std::max(a.size_, b.size_))) {
                ++result.size_;
            }
            result.number_[i] = (a.number_[i] + b.number_[i] + transfer) % 10;
            transfer = (a.number_[i] + b.number_[i] + transfer) / 10;

        }
        return result;
    }

    friend BigInteger operator-(const BigInteger& a, const BigInteger& b) {
        BigInteger result;
        int transfer = 0;
        BigInteger aCopy(a);
        BigInteger bCopy(b);

        for (int i = 0; i < std::max(a.size_, b.size_); ++i) {
            transfer = 0;
            if (aCopy.number_[i] < bCopy.number_[i]) {
                transfer = 10;
                --aCopy.number_[i + 1];
            }
            result.number_[i] = aCopy.number_[i] + transfer - bCopy.number_[i];
        }
        result.size_ = result.Size();
        return result;
    }

    friend BigInteger operator*(const BigInteger& a, const BigInteger& b) {
        BigInteger aCopy(a);
        BigInteger bCopy(b);
        BigInteger result = 0;

        for (int i = 0; i < a.size_ + 1; ++i) {
            int transfer = 0;
            for (int j = 0; j < b.size_ + 1; ++j) {
                long long current_composition = result[i + j] + aCopy[i] * bCopy[j] + transfer;
                result[i + j] = current_composition % 10;
                transfer = current_composition / 10;
            }
        }

        result.size_ = result.Size();
        result.isNegative_ = a.isNegative_ ^ b.isNegative_;
        return result;
    }

    int& operator[](const int index) const {
        return number_[index];
    }

    BigInteger sqrt() const {
        BigInteger left = 0;
        BigInteger right = *this;

        BigInteger x = 0;
        while (left <= right) {
            BigInteger middle = (left + right) / 2;
            if (middle * middle <= *this) {
                x = middle;
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }
        return x;
    }

    friend bool operator<(const BigInteger& a, const BigInteger& b) {
        if (a.size_ > b.size_) {
            return false;
        } else if (a.size_ < b.size_) {
            return true;
        } else {
            for (int i = a.size_ - 1; i >= 0; --i) {
                if (a[i] > b[i]) {
                    return false;
                } else if (a[i] < b[i]) {
                    return true;
                }
            }
        }
        return false;
    }
    friend bool operator>(const BigInteger& a, const BigInteger& b) {
        return b < a;
    }
    friend bool operator==(const BigInteger& a, const BigInteger& b) {
        return !(a > b || a < b);
    }
    friend bool operator<=(const BigInteger& a, const BigInteger& b) {
        return a == b || a < b;
    }
};


int main() {
    BigInteger a;
    BigInteger b;
    std::cin >> a;
    std::cout << a.sqrt();
    return 0;
}

