/*
Input format
Во входном файле два целых неотрицательных числа A и B (0 ≤ A, B ≤ 10^10000) каждое в своей строке.
Output format
В выходной файл выведите одно число, равное сумме A и B.
*/

//Let's suppose, that you didn't solve task L :)

//Coded by Artur Kulapin

#include <iostream>
#include <cstring>

const int MAX_SIZE = 12002;

class BigInteger {
    int* number_;
    int size_;
public:
    ~BigInteger() {
        delete[] number_;
    }

    BigInteger() {
        number_ = new int[MAX_SIZE];
        size_ = 0;
    }

    BigInteger(const int& other) {
        int copy = other;
        size_ = 0;
        number_ = new int[MAX_SIZE];
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
};


int main() {
    BigInteger a;
    BigInteger b;
    std::cin >> a >> b;
    std::cout << a + b;
    return 0;
}

