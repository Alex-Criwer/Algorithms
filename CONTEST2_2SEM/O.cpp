/*
Input format
Во входном файле два целых неотрицательных числа A и B (0 ≤ A, B ≤ 10^10000) каждое в своей строке.
Output format
В выходной файл выведите одно число, равное произведению A и B.
*/

//Let's suppose, that you didn't solve task L :)

//Coded by Artur Kulapin

#include <iostream>
#include <cstring>

const int MAX_SIZE = 20001;

class BigInteger {
    int* number_ = new int[MAX_SIZE];
    int size_;
    bool isNegative_;
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
            if (copy == 0) {
                break;
            }
            copy /= 10;
        }
        for (int i = size_; i < MAX_SIZE; ++i) {
            number_[i] = 0;
        }
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
        BigInteger result;

        for (int i = 0; i < a.size_ + 1; ++i) {
            int transfer = 0;
            for (int j = 0; j < b.size_ + 1; ++j) {
                int current_composition = result[i + j] + aCopy[i] * bCopy[j] + transfer;
                result[i + j] = current_composition % 10;
                transfer = current_composition / 10;
            }
        }

        result.size_ = result.Size();
        result.isNegative_ = a.isNegative_ ^ b.isNegative_;
        return result;
    }

    int& operator[](const int index) {
        return number_[index];
    }
};


int main() {
    BigInteger a;
    BigInteger b;
    std::cin >> a >> b;
    std::cout << a * b;
    return 0;
}
