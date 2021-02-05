/*
Реализовать класс Rational для работы с рациональными числами вида p/q, где p – целое число, q – натуральное. Определить все методы, операции и дополнительные классы так, чтобы предложенный тестирующий код выводил ожидаемый результат в соответствии с общепринятой семантикой.
Формат ввода и вывода объектов: несократимая дробь <p>/<q> – если q ≠ 1, и <p> в противном случае, где p – целое число, q – натуральное
Гарантируется, что в тестах в результате любой операции над Rational числитель и знаменатель не переполнят тип int. Ссылка на код: rational.cpp
Input format
В первой строке дано целое число, меньшее по модулю 2^15.
Во второй строке дано два целых числа, меньших по модулю 2^15. Гарантируется, что второе число не равно 0.
Во третьей и четвертой строке дано по одному рациональному числу в вышеописанном формате. |p|,|q| < 2^15
Для понимания смотрите примеры и rational.cpp (main function).
Output format
Результат работы rational.cpp при правильно реализованных методах класса.
Для понимания смотрите примеры и rational.cpp.
*/

//Coded by Artur Kulapin

#include <iostream>
#include <cstdlib>
#include <exception>
#include <cmath>
using std::cin;
using std::cout;
using std::endl;

class RationalDivisionByZero : public std::exception {
    const char* what() const noexcept override {
        return "You tried to divide by zero. It is mistake";
    }
};


class Rational {
private:
    int p_;
    int q_; // is maintained to be positive


    int gcd(int a, int b) {

        while (a > 0 && b > 0) {
            if (a > b) {
                a = a % b;
            } else {
                b = b % a;
            }
        }
        return (a + b);
    }

    void reduce() {
        if (q_ < 0) {
            q_ *= -1;
            p_ *= -1;
        }
        if (p_ == 0) {
            q_ = 1;
        }
        int reduceNumber = gcd(abs(p_), abs(q_));
        p_ /= reduceNumber;
        q_ /= reduceNumber;
    }

public:
    Rational(const int p, const int q) : p_(p), q_(q) {
        this->reduce();
    }
    Rational(const int p) : p_(p), q_(1) {}
    Rational() : p_(0), q_(1) {}

    int getNumerator() const {
        return p_;
    }
    int getDenominator() const {
        return q_;
    }

    friend std::istream& operator>>(std::istream& is, Rational& number) {
        int read = scanf("%d/%d", &number.p_, &number.q_);
        if (number.q_ == 0 || number.p_ == 0 || read < 2) {
            number.q_ = 1;
        }
        number.reduce();
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Rational& number) {
        if (number.p_ == 0) {
            std::cout << 0;
        } else if (number.q_ != 1) {
            std::cout << number.p_ << '/' << number.q_;
        } else {
            std::cout << number.p_;
        }
        return os;
    }


    friend bool operator<(const Rational& rOne, const Rational& rTwo) {
        return rOne.p_ * rTwo.q_ < rTwo.p_ * rOne.q_;
    }
    friend bool operator>(const Rational& rOne, const Rational& rTwo) {
        return rOne.p_ * rTwo.q_ > rTwo.p_ * rOne.q_;
    }
    friend bool operator==(const Rational& rOne, const Rational& rTwo) {
        return rOne.p_ * rTwo.q_ == rTwo.p_ * rOne.q_;
    }
    friend bool operator>=(const Rational& rOne, const Rational& rTwo) {
        return rOne.p_ * rTwo.q_ >= rTwo.p_ * rOne.q_;
    }
    friend bool operator<=(const Rational& rOne, const Rational& rTwo) {
        return rOne.p_ * rTwo.q_ <= rTwo.p_ * rOne.q_;
    }
    friend bool operator!=(const Rational& rOne, const Rational& rTwo) {
        return rOne.p_ * rTwo.q_ != rTwo.p_ * rOne.q_;
    }

    friend Rational operator+(const Rational& rOne, const Rational& rTwo) {
        Rational result(rOne.p_ * rTwo.q_ + rOne.q_ * rTwo.p_, rOne.q_ * rTwo.q_);
        result.reduce();
        return result;
    }
    friend Rational operator-(const Rational& rOne, const Rational& rTwo) {
        Rational result(rOne.p_ * rTwo.q_ - rOne.q_ * rTwo.p_, rOne.q_ * rTwo.q_);
        result.reduce();
        return result;
    }
    friend Rational operator*(const Rational& rOne, const Rational& rTwo) {
        return Rational(rOne.p_ * rTwo.p_, rOne.q_ * rTwo.q_);
    }
    friend Rational operator/(const Rational& rOne, const Rational& rTwo) {
        if (rTwo == 0) {
            throw RationalDivisionByZero();
        }
        return Rational(rOne.p_ * rTwo.q_, rOne.q_ * rTwo.p_);
    }

    Rational operator-() const {
        return Rational(-1 * p_, q_);
    }
    Rational operator+() const {
        return *this;
    }

    const Rational operator++(int) {
        this->p_ += q_;
        return Rational(this->p_ - this->q_, this->q_);
    }
    Rational& operator++() {
        return (*this += 1);
    }
    const Rational operator--(int) {
        this->p_ -= q_;
        return Rational(this->p_ + this->q_, this->q_);
    }
    Rational& operator--() {
        return (*this -= 1);
    }

    Rational& operator+=(const Rational& number) {
        return *this = (*this + number);
    }
    Rational& operator-=(const Rational& number) {
        return *this = (*this - number);
    }
    Rational& operator*=(const Rational& number) {
        return *this = (*this * number);
    }
    Rational& operator/=(const Rational& number) {
        return *this = (*this / number);
    }
};

int main() {
    int a;
    cin >> a;

    int p, q;
    cin >> p >> q;
    const Rational rc(p, q); // q != 0 is guaranteed by author of tests
    cout << rc.getNumerator() << ' ' << rc.getDenominator() << endl;

    Rational r1, r2;
    cin >> r1 >> r2;

    cout << r1 << endl;
    cout << r2 << endl;

    try {
        cout << 1/r1 << endl;
    } catch (const RationalDivisionByZero& ex) {
        cout << "Cannot get reciprocal of r1." << endl;
    }

    try {
        cout << rc/r2 << endl;
    } catch (const RationalDivisionByZero& ex) {
        cout << "Cannot divide by r2." << endl;
    }

    cout << (r1 < r2) << endl;
    cout << (r1 <= r2) << endl;
    cout << (r1 > r2) << endl;
    cout << (r1 >= r2) << endl;
    cout << (r1 == r2) << endl;
    cout << (r1 != r2) << endl;

    cout << (r1 < a) << endl;
    cout << (r1 <= a) << endl;
    cout << (r1 > a) << endl;
    cout << (r1 >= a) << endl;
    cout << (r1 == a) << endl;
    cout << (r1 != a) << endl;

    cout << (a < r2) << endl;
    cout << (a <= r2) << endl;
    cout << (a > r2) << endl;
    cout << (a >= r2) << endl;
    cout << (a == r2) << endl;
    cout << (a != r2) << endl;

    cout << rc + a << endl
         << a + rc << endl
         << -rc * r1 << endl
         << (+r1 - r2 * rc) * a << endl;

    cout << ++r1 << endl;
    cout << r1 << endl;
    cout << r1++ << endl;
    cout << r1 << endl;
    cout << --r1 << endl;
    cout << r1 << endl;
    cout << r1-- << endl;
    cout << r1 << endl;
    cout << ++(++r1) << endl;
    cout << r1 << endl;

    cout << ((((r1 += r2) /= Rational(-5,3)) -= rc) *= a) << endl;
    cout << (r1 += r2 /= 3) << endl;
    cout << r1 << endl;
    cout << r2 << endl;
    return 0;
}
