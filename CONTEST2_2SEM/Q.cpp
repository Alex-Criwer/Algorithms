/*
Input format
Во входном файле два целых положительных числа A и B (1 ≤ A, B ≤ 10^500) каждое в своей строке.
Output format
В выходной файл выведите наибольший общий делитель A и B.
*/

//Coded by Artur Kulapin

#include <iostream>
#include <cstring>

const int MAX_SIZE = 501;

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

    friend BigInteger operator/(const BigInteger& a, const BigInteger& b) {
        BigInteger aCopy(a);
        BigInteger bCopy(b);
        BigInteger result = 0;
        BigInteger current = 0;

        int i = 1;
        while (i <= a.size_) {
            if (!(current == 0 && a[a.size_ - i] == 0)) {
                bool more_than_one_digit_required = false;
                while (current < b) {
                    if (i <= a.size_) {
                        current = current * 10 + a[a.size_ - i];
                        ++i;
                        if (more_than_one_digit_required) {
                            result = result * 10;
                        }
                        more_than_one_digit_required = true;
                    } else {
                        break;
                    }
                }
            } else {
                while (a[a.size_ - i] == 0) {
                    if (i > a.size_) {
                        return result;
                    }
                    result = result * 10;
                    ++i;
                }
                continue;
            }

            int left = 0, right = 10, x = 0;
            while (left <= right) {
                int middle = (left + right) / 2;
                if (bCopy * middle <= current) {
                    x = middle;
                    left = middle + 1;
                } else {
                    right = middle - 1;
                }
            }

            current = current - b * x;
            result = result * 10 + x;
        }
        return result;
    }
    friend BigInteger operator%(const BigInteger& a, const BigInteger& b) {
        BigInteger result = a - (a / b) * b;
        if (result.isNegative_) {
            result = result + b;
        }
        return result;
    }

    int& operator[](const int index) const {
        return number_[index];
    }

    friend BigInteger gcd(const BigInteger& a, const BigInteger& b) {
        BigInteger aCopy = a;
        BigInteger bCopy = b;
        while (aCopy > 0 && bCopy > 0) {
            if (aCopy > bCopy) {
                aCopy = aCopy % bCopy;
            } else {
                bCopy = bCopy % aCopy;
            }
        }
        return (aCopy + bCopy);
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
    std::cin >> a >> b;
    std::cout << gcd(a, b);
    return 0;
}

