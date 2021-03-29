#include<iostream>
#include <cstring>

int MAXSIZE = 20020;

class BigInteger {
private:
    int size = 1;
    int *number = new int[MAXSIZE];

    int findCell(const BigInteger &currDiv, const BigInteger &other) const;

    BigInteger currentDivident(const BigInteger &other) const;

    int sizeOfInt();

public:
    BigInteger();

    BigInteger(const BigInteger &that);

    BigInteger(const int &num);

    BigInteger &operator=(const BigInteger &other);

    friend std::ostream &operator<<(std::ostream &os, const BigInteger &myNumber);

    friend std::istream &operator>>(std::istream &is, BigInteger &myNumber);

    friend BigInteger operator+(const BigInteger &first, const BigInteger &second);

    friend BigInteger operator%(const BigInteger &first, const BigInteger &second);

    friend BigInteger operator-(const BigInteger &first, const BigInteger &second);

    friend BigInteger operator*(const BigInteger &first, const BigInteger &second);

    friend BigInteger operator/(const BigInteger &first, const BigInteger &second);

    friend bool operator<(const BigInteger &first, const BigInteger &second);

    friend bool operator>(const BigInteger &first, const BigInteger &second);

    friend bool operator<=(const BigInteger &first, const BigInteger &second);

    friend bool operator==(const BigInteger &first, const BigInteger &second);

    ~BigInteger();
};

int main() {
    BigInteger a;
    BigInteger b;
    std::cin >> a >> b;
    std::cout << a / b << ' ' << a % b;
    return 0;
}

int BigInteger::sizeOfInt() {
    for (int i = MAXSIZE - 1; i >= 0; --i) {
        if (number[i] != 0) {
            return i + 1;
        }
    }
    return 1;
}

BigInteger::BigInteger() {
    size = 0;
    for (int i = 0; i < MAXSIZE; ++i) {
        number[i] = 0;
    }
}

BigInteger::~BigInteger() {
    delete[] number;
}

std::ostream &operator<<(std::ostream &os, const BigInteger &myNumber) {
    for (int i = myNumber.size - 1; i >= 0; --i) {
        os << myNumber.number[i];
    }
    return os;
}

std::istream &operator>>(std::istream &is, BigInteger &myNumber) {
    char *line = new char[MAXSIZE];
    is >> line;
    myNumber.size = strlen(line);
    for (int i = 0; i < myNumber.size; ++i) {
        myNumber.number[i] = line[myNumber.size - 1 - i] - '0';
    }
    for (int i = myNumber.size; i < MAXSIZE; ++i) {
        myNumber.number[i] = 0;
    }
    delete[] line;
    return is;
}

BigInteger operator*(const BigInteger &first, const BigInteger &second) {
    int remainder = 0;
    BigInteger multi;
    for (int i = 0; i < first.size + 1; ++i) {
        remainder = 0;
        for (int j = 0; j < second.size + 1; ++j) {
            int temp = multi.number[i + j] + first.number[i] * second.number[j] + remainder;
            multi.number[i + j] = temp % 10;
            remainder = temp / 10;
        }
    }
    multi.size = multi.sizeOfInt();
    return multi;
}

BigInteger::BigInteger(const BigInteger &that) {
    size = that.size;
    for (int i = 0; i < MAXSIZE; ++i) {
        number[i] = that.number[i];
    }
}

BigInteger::BigInteger(const int &num) {
    int copy = num;
    size = 0;
    for (int i = 0; i < MAXSIZE; ++i) {
        number[i] = copy % 10;
        ++size;
        copy /= 10;
        if (copy == 0) {
            break;
        }
    }
    for (int i = size; i < MAXSIZE; ++i) {
        number[i] = 0;
    }
}

BigInteger operator+(const BigInteger &first, const BigInteger &second) {
    int remainder = 0;
    BigInteger sum;
    for (int i = 0; i < MAXSIZE; ++i) {
        sum.number[i] = (first.number[i] + second.number[i] + remainder) % 10;
        remainder = (first.number[i] + second.number[i] + remainder) / 10;
    }
    sum.size = sum.sizeOfInt();
    return sum;
}


BigInteger operator-(const BigInteger &first, const BigInteger &second) {
    int remainder = 0;
    BigInteger diff;
    BigInteger firstCopy(first);
    BigInteger secondCopy(second);
    for (int i = 0; i < std::max(first.size, second.size); ++i) {
        remainder = 0;
        if (firstCopy.number[i] < secondCopy.number[i]) {
            remainder = 10;
            --firstCopy.number[i + 1];
        }
        diff.number[i] = (firstCopy.number[i] + remainder - secondCopy.number[i]);
    }
    diff.size = diff.sizeOfInt();
    return diff;
}

BigInteger &BigInteger::operator=(const BigInteger &other) {
    if (this->number != other.number) {
        int temp = std::max(size, other.size);
        size = other.size;
        for (int i = 0; i < temp; ++i) {
            this->number[i] = other.number[i];
        }
    }
    return *this;
}

bool operator<(const BigInteger &first, const BigInteger &second) {
    if (first.size > second.size) {
        return false;
    } else if (first.size < second.size) {
        return true;
    } else {
        for (int i = first.size - 1; i >= 0; --i) {
            if (first.number[i] > second.number[i]) {
                return false;
            } else if (first.number[i] < second.number[i]) {
                return true;
            }
        }
    }
    return false;
}

bool operator>(const BigInteger &first, const BigInteger &second) {
    return second < first;
}

bool operator<=(const BigInteger &first, const BigInteger &second) {
    return !(first > second);
}

bool operator==(const BigInteger &first, const BigInteger &second) {
    return !(first > second || first < second);
}

BigInteger operator/(const BigInteger &first, const BigInteger &second) {
    BigInteger result = 0;
    BigInteger currentDiv = first.currentDivident(second);
    int currCell = 0;
    BigInteger firstCopy(first);
    BigInteger secondCopy(second);
    int difference = firstCopy.size - secondCopy.size;
    while (difference >= 0) {
        currCell = firstCopy.findCell(currentDiv, secondCopy);
        currentDiv = currentDiv - secondCopy * currCell;
        result = result * 10;
        result = result + currCell;
        if (difference > 0) {
            currentDiv = currentDiv * 10;
            currentDiv = currentDiv + firstCopy.number[difference - 1];
        }
        --difference;
    }

    return result;
}

BigInteger operator%(const BigInteger &first, const BigInteger &second) {
    BigInteger result = first - (first / second) * second;
    return result;
}

int BigInteger::findCell(const BigInteger &currDiv, const BigInteger &other) const {
    int left = 0, right = 10;
    int middle = (left + right) / 2;
    BigInteger temp;

    while (left <= right) {
        temp = middle * other;

        if (temp == currDiv) {
            break;
        } else if (temp > currDiv) {
            right = middle - 1;
        } else {
            left = middle + 1;
            if ((middle + 1) * other > currDiv) {
                break;
            }
        }
        middle = (left + right) / 2;
    }
    return middle;
}

BigInteger BigInteger::currentDivident(const BigInteger &other) const {
    int indexOfLastDigit = size - 1;
    BigInteger currDiv = 0;
    while (indexOfLastDigit > size - other.size - 1) {
        currDiv = currDiv * 10;
        currDiv = currDiv + number[indexOfLastDigit];
        --indexOfLastDigit;
    }
    return currDiv;
}

