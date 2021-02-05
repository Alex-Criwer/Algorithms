/*
Реализовать класс BigInteger, поддерживающий работу с большими числами. В классе должны содержаться:
• Конструкторы на основе int, unsigned int, long long, unsigned long long, си-строки с десятеричным представлением числа
• Операции сложения, вычитания, умножения этих чисел с самими собой, в том числе модифицирующие операции вида @= и (пост-, пре-) инкремент/декремент
• Те же операции со стандартными типами (int, unsigned int, long long, unsigned long long), для любого порядка типов аргументов.
• Вывод в стандартный поток и чтение из него в десятеричной системе счисления.
Также необходимо генерировать исключение BigIntegerOverflow, если в результате операции результат не помещается в выделенную память.
При решении задач на длинную арифметику необходимо использовать реализованный класс, обращая внимание на ограничения конкретной задачи.
Ссылка на код: big_integer.cpp (в нем реализованы объявления классов и main)
Примечание:
Код не обязательно должен быть оптимальным, но старайтесь избегать копирования кода: большинство функций можно реализовать через уже имеющиеся.
Input format
Дано три числа a, b и c. Первые два числа содержат не более 20000 цифр в десятеричной записи, третье число лежит в диапазоне [-10^9, 10^9]
Output format
Необходимо вывести результат работы функции main() big_integer.cpp
*/

//Coded by Artur Kulapin


#include <cstring>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <iomanip>
#include <exception>

template <typename T>
int length(T number) {
    int length = 0;
    number > 0 ? number : number *= -1;
    while (number > 0) {
        number /= 10;
        ++length;
    }
    if (length > 0) {
        return length;
    } else {
        return 1;
    }
}


class BigIntegerOverflow : public std::exception {
    const char* what() const noexcept override {
        return "Result is too large";
    }
};

class BigInteger {
private:
    const static size_t maxLength = 3000; // number of digits
    const static uint8_t baseLog = 9; // use 1 or 2 for debug

    typedef uint32_t digit_type;
    typedef uint64_t double_digit_type; // for multiplication

    const static uint32_t base = static_cast<double_digit_type>(1e9);  // base of numeral system
    const static size_t maxReadSize = 20010; // for reading (buffer size)

    digit_type digits_[maxLength];
    size_t size_ = 1;
    bool isNegative_ = false;

    void FillDigitsFromString(const char* number);
    size_t Size() const;
    static BigInteger SumPositives(const BigInteger& lhs, const BigInteger& rhs);
    static BigInteger SubstractPositives(const BigInteger& lhs, const BigInteger& rhs);
    static BigInteger MultiplyPositives(const BigInteger& lhs, const BigInteger& rhs);

    friend bool HaveSameSign(const BigInteger& lhs, const BigInteger& rhs);


public:
    BigInteger();
    explicit BigInteger(const char* number);
    template <class T>
    BigInteger(const T& number);
    BigInteger(const BigInteger& other);
    BigInteger(BigInteger&& other) noexcept;

    friend std::istream& operator>>(std::istream& is, BigInteger& number) {
        char* input = new char[maxReadSize];
        is >> input;
        number.FillDigitsFromString(input);
        delete[] input;
        return is;
    }
    friend std::ostream& operator<<(std::ostream& os, const BigInteger& number) {
        BigInteger uNumber = number;
        uNumber.isNegative_ = false;
        if (number.isNegative_ && uNumber > 0) {
            os << '-';
        }
        bool leadZerosFinished = false;
        for (size_t i = number.Size(); i >= 1; --i) {
            if (number.digits_[i - 1] != 0 && !leadZerosFinished) {
                leadZerosFinished = true;
            }
            if (number.size_ == 1 && number.digits_[0] == 0) {
                leadZerosFinished = true;
            }
            if (leadZerosFinished) {
                digit_type digit = number.digits_[i - 1];
                int delta = baseLog - length(digit);
                for (int j = delta; j > 0 && i != number.size_; --j) {
                    os << '0';
                }
                os << number.digits_[i - 1];
            }
        }
        return os;
    }

    BigInteger& operator=(const BigInteger& other);
    BigInteger& operator=(BigInteger&& other) noexcept;

    friend BigInteger operator+(const BigInteger& value);
    friend BigInteger operator-(const BigInteger& value);

    BigInteger& operator+=(const BigInteger& value);
    BigInteger& operator-=(const BigInteger& value);
    BigInteger& operator*=(const BigInteger& value);

    BigInteger& operator++();
    const BigInteger operator++(int);

    BigInteger& operator--();
    const BigInteger operator--(int);



    friend BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs);
    friend BigInteger operator-(const BigInteger& lhs, const BigInteger& rhs);
    friend BigInteger operator*(const BigInteger& lhs, const BigInteger& rhs);

    friend bool operator<(const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator>(const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator>=(const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator<=(const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator==(const BigInteger& lhs, const BigInteger& rhs);
    friend bool operator!=(const BigInteger& lhs, const BigInteger& rhs);
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    BigInteger a, b;
    std::cin >> a >> b;
    int c;
    std::cin >> c;

    std::cout << (a * c == c * (--b)++) << '\n';
    std::cout << (a + 5 < (++b)--) << '\n';
    std::cout << (a <= b) << '\n';
    std::cout << (a > b - 5) << '\n';
    std::cout << (a >= b - 5) << '\n';
    //std::cout << b * c << std::endl;
    std::cout << (a != b * c) << '\n';
    std::cout << (a == -b) << '\n';

    BigInteger d("123"), e(1ULL << 63);
    std::cout << (d + c) * e << '\n';

    try {
        a += b;
        //std::cout << a << ' ' << b << '\n';
        b = a - b; // b = a
        //std::cout << a << ' ' << b << '\n';
        a -= b; // a = b
        //std::cout << a << ' ' << b << '\n';
        std::cout << a + b << '\n';
        std::cout << a - b << '\n';
        std::cout << a * b << '\n';
    } catch (BigIntegerOverflow& ex) {
        std::cout << "Overflow" << '\n';
    }
}

size_t BigInteger::Size() const {
    for (size_t i = maxLength; i >= 1; --i) {
        if (digits_[i - 1] != 0) {
            return i;
        }
    }
    return 1;
}
bool HaveSameSign(const BigInteger& lhs, const BigInteger& rhs) {
    return lhs.isNegative_ == rhs.isNegative_;
}

BigInteger::BigInteger() {
    for (int i = 0; i < maxLength; ++i) {
        digits_[i] = 0;
    }
    isNegative_ = false;
    size_ = 1;
}

template <class T>
BigInteger::BigInteger(const T& number) {
    T copyNumber = number;
    if (number < 0) {
        isNegative_ = true;
        copyNumber *= -1;
    }
    for (size_t i = 0; i < maxLength; ++i) {

        digits_[i] = copyNumber % base;
        if (copyNumber > 0) {
            ++size_;
        }
        copyNumber /= base;
    }
    this->size_ = this->Size();
}

void BigInteger::FillDigitsFromString(const char *number) {
    for (int i = 0; i < maxLength; ++i) {
        digits_[i] = 0;
    }
    int startIndex = 0;
    if (number[0] == '-') {
        isNegative_ = true;
        startIndex = 1;
    }
    size_t length = strlen(number);
    size_ = 0;
    while (length > startIndex) {
        digit_type tenthDegree = 1;
        for (int i = 0; i < baseLog && i < length - startIndex; ++i) {
            digit_type digit = static_cast<digit_type>(number[length - 1 - i] - '0');
            digit_type currDigit = digit * tenthDegree;
            digits_[size_] += currDigit;
            tenthDegree *= 10;
        }
        if (length < baseLog) {
            length = 0;
        } else {
            length -= baseLog;
        }
        ++size_;
    }
    for (size_t currSize = size_; currSize < maxLength; ++currSize) {
        digits_[currSize] = 0;
    }
}

BigInteger::BigInteger(const char* number) {
    this->FillDigitsFromString(number);
}

BigInteger& BigInteger::operator=(const BigInteger& other) {
    if (this->digits_ != other.digits_) {
        size_ = other.size_;
        isNegative_ = other.isNegative_;
        for (int i = 0; i < other.size_; ++i) {
            digits_[i] = other.digits_[i];
        }
    }
    return *this;
}

BigInteger& BigInteger::operator=(BigInteger&& other) noexcept {
    std::swap(digits_, other.digits_);
    isNegative_ = other.isNegative_;
    size_ = other.size_;
    return *this;
}

BigInteger::BigInteger(const BigInteger &other) {
    isNegative_ = other.isNegative_;
    size_ = other.size_;
    for (size_t i = 0; i < maxLength; ++i) {
        digits_[i] = other.digits_[i];
    }
}

BigInteger::BigInteger(BigInteger &&other) noexcept {
    std::swap(digits_, other.digits_);
    isNegative_ = other.isNegative_;
    size_ = other.size_;
}

BigInteger BigInteger::SumPositives(const BigInteger &lhs, const BigInteger &rhs) {
    BigInteger result;
    digit_type transfer = 0;
    for (int i = 0; i < maxLength; ++i) {
        digit_type currSum = lhs.digits_[i] + rhs.digits_[i] + transfer;
        result.digits_[i] = currSum % base;
        transfer = currSum / base;
    }
    if (transfer > 0) {
        throw BigIntegerOverflow();
    }
    result.size_ = result.Size();
    if (result == 0) {
        result.isNegative_ = false;
    }
    return result;
}
BigInteger BigInteger::SubstractPositives(const BigInteger &lhs, const BigInteger &rhs) {
    BigInteger result;
    digit_type transfer = 0;
    BigInteger aCopy(lhs);
    aCopy.isNegative_ = false;
    BigInteger bCopy(rhs);
    bCopy.isNegative_ = false;

    for (int i = 0; i < maxLength; ++i) {
        transfer = 0;
        if (aCopy.digits_[i] < bCopy.digits_[i]) {
            transfer = base;
            aCopy.digits_[i] += base;
            for (int j = i + 1; j < maxLength; ++j) {
                if (aCopy.digits_[j] != 0) {
                    --aCopy.digits_[j];
                    break;
                } else {
                    aCopy.digits_[j] = base - 1;
                }
            }
        }
        result.digits_[i] = aCopy.digits_[i]  - bCopy.digits_[i];
    }
    result.size_ = result.Size();
    if (result == 0) {
        result.isNegative_ = false;
    }
    return result;
}
BigInteger BigInteger::MultiplyPositives(const BigInteger &lhs, const BigInteger &rhs) {  //Check try-catch-throw
    BigInteger result;
    for (size_t i = 0; i < lhs.size_; ++i) {
        digit_type transfer = 0;
        for (size_t j = 0; j < rhs.size_ || transfer != 0; ++j) {
            double_digit_type curr = static_cast<double_digit_type>(lhs.digits_[i]) *
                                     static_cast<double_digit_type>(rhs.digits_[j]);
            double_digit_type current_composition = result.digits_[i + j] + curr + transfer;
            result.digits_[i + j] = static_cast<digit_type>(current_composition % base);
            transfer = static_cast<digit_type>(current_composition / base);

            if (transfer > 0 && (i + j) == maxLength) {
                throw BigIntegerOverflow();
            }

        }
    }
    result.size_ = result.Size();
    if (result == 0) {
        result.isNegative_ = false;
    }
    return result;
}

BigInteger operator+(const BigInteger &value) {
    return value;
}
BigInteger operator-(const BigInteger &value) {
    BigInteger number = value;
    if (number != 0) {
        number.isNegative_ = !value.isNegative_;
    } else {
        number.isNegative_ = false;
    }
    return number;
}

BigInteger operator+(const BigInteger& lhs, const BigInteger& rhs) {
    BigInteger result;
    BigInteger ulhs = lhs;
    ulhs.isNegative_ = false;
    BigInteger urhs = rhs;
    urhs.isNegative_ = false;

    if (HaveSameSign(lhs, rhs)) {
        result = BigInteger::SumPositives(lhs, rhs);
        result.isNegative_ = lhs.isNegative_;
    } else if (!lhs.isNegative_ && ulhs >= urhs) {
        result = BigInteger::SubstractPositives(ulhs, urhs);
    } else if (!lhs.isNegative_ && ulhs < urhs) {
        result = -BigInteger::SubstractPositives(urhs, ulhs);
    } else if (lhs.isNegative_ && ulhs >= urhs) {
        result = -BigInteger::SubstractPositives(ulhs, urhs);
    } else {
        result = BigInteger::SubstractPositives(urhs, ulhs);
    }
    return result;
}
BigInteger operator-(const BigInteger& lhs, const BigInteger& rhs) {
    BigInteger result;
    BigInteger ulhs = lhs;
    ulhs.isNegative_ = false;
    BigInteger urhs = rhs;
    urhs.isNegative_ = false;

    if (!lhs.isNegative_ && !rhs.isNegative_ && ulhs >= urhs) {
        result = BigInteger::SubstractPositives(ulhs, urhs);
    } else if (!lhs.isNegative_ && !rhs.isNegative_ && ulhs < urhs) {
        result = -BigInteger::SubstractPositives(urhs, ulhs);
    } else if (!lhs.isNegative_ && rhs.isNegative_) {
        result = BigInteger::SumPositives(ulhs, urhs);
    } else if (lhs.isNegative_ && rhs.isNegative_ && ulhs >= urhs) {
        result = -BigInteger::SubstractPositives(ulhs, urhs);
    } else if (lhs.isNegative_ && rhs.isNegative_ && ulhs < urhs) {
        result = BigInteger::SubstractPositives(urhs, ulhs);
    } else {
        result = -BigInteger::SumPositives(urhs, ulhs);
    }

    return result;
}
BigInteger operator*(const BigInteger& lhs, const BigInteger& rhs) {
    BigInteger result = BigInteger::MultiplyPositives(lhs, rhs);
    if (result != 0) {
        result.isNegative_ = !HaveSameSign(lhs, rhs);
    } else {
        result.isNegative_ = false;
    }
    return result;
}

BigInteger& BigInteger::operator+=(const BigInteger& value) {
    return *this = (*this + value);
}
BigInteger& BigInteger::operator-=(const BigInteger& value) {
    return *this = (*this - value);
}
BigInteger& BigInteger::operator*=(const BigInteger& value) {
    return *this = (*this * value);
}

BigInteger& BigInteger::operator++() {
    return (*this += 1);
}
const BigInteger BigInteger::operator++(int) {
    *this += 1;
    return *this - 1;
}

BigInteger& BigInteger::operator--() {
    return (*this -= 1);
}
const BigInteger BigInteger::operator--(int) {
    *this -= 1;
    return *this + 1;
}

bool operator<(const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs.isNegative_ && !rhs.isNegative_) {
        return true;
    } else if (!lhs.isNegative_ && rhs.isNegative_) {
        return false;
    } else if (lhs.isNegative_ && rhs.isNegative_) {
        BigInteger ulhs = lhs;
        ulhs.isNegative_ = false;
        BigInteger urhs = rhs;
        urhs.isNegative_ = false;
        return urhs < ulhs;
    } else {
        if (lhs.size_ < rhs.size_) {
            return true;
        } else if (lhs.size_ > rhs.size_) {
            return false;
        } else {
            for (size_t i = lhs.size_; i >= 1; --i) {
                if (lhs.digits_[i - 1] > rhs.digits_[i - 1]) {
                    return false;
                } else if (lhs.digits_[i - 1] < rhs.digits_[i - 1]){
                    return true;
                }
            }
        }
        return false;
    }
}
bool operator>(const BigInteger& lhs, const BigInteger& rhs) {
    return rhs < lhs;
}
bool operator==(const BigInteger& lhs, const BigInteger& rhs) {
    return !(lhs > rhs) && !(lhs < rhs);
}
bool operator!=(const BigInteger& lhs, const BigInteger& rhs) {
    return !(lhs == rhs);
}
bool operator>=(const BigInteger& lhs, const BigInteger& rhs) {
    return !(lhs < rhs);
}
bool operator<=(const BigInteger& lhs, const BigInteger& rhs) {
    return !(lhs > rhs);
}