/*
Даны два ненулевых вектора. Требуется вычислить:
• Длину первого и второго вектора (два числа)
• Вектор, образованный сложением данных двух векторов
• Скалярное и векторное произведение данных векторов
• Площадь треугольника, построенного из этих векторов
Input format
В двух строках входного файла заданы по четыре целых числа, не превосходящих по модулю 10000 – координаты начала и конца первого вектора, затем второго.
Output format
В каждой строке выходного файла – ответ на соответствующий пункт задачи с точностью не менее 10^-6.
*/

//Coded by Artur Kulapin

#include <iostream>
#include <cmath>

class Vector {
    double xStart;
    double yStart;
    double xEnd;
    double yEnd;
    double XLength() const {
        return xEnd - xStart;
    }
    double YLength() const {
        return yEnd - yStart;
    }
    friend double Angle(const Vector& vOne, const Vector& vTwo) {
        return acos(ScalarMultiple(vOne, vTwo) / (vOne.Length() * vTwo.Length()));
    }
public:
    Vector() = default;
    Vector(double xS, double yS, double xE,double yE) : xStart(xS), yStart(yS), xEnd(xE), yEnd(yE) {}
    ~Vector() = default;
    double Length() const {
        return sqrt(pow((this->XLength()), 2) + pow(this->YLength(), 2));
    }

    friend Vector operator+(const Vector& vOne, const Vector& vTwo) {
        return Vector(0, 0, vOne.XLength() + vTwo.XLength(), vOne.YLength() + vTwo.YLength());
    }

    friend double ScalarMultiple(const Vector& vOne, const Vector& vTwo) {
        return vOne.XLength() * vTwo.XLength() + vOne.YLength() * vTwo.YLength();
    }

    friend double VectorMultiple(const Vector& vOne, const Vector& vTwo) {
        return vOne.XLength() * vTwo.YLength() - vTwo.XLength() * vOne.YLength();
    }

    friend double TriangleVectorBasedSquare(const Vector& vOne, const Vector& vTwo) {
        return 0.5 * abs(VectorMultiple(vOne, vTwo));
    }

    friend std::istream& operator>>(std::istream& is, Vector& vector) {
        std::cin >> vector.xStart >> vector.yStart >> vector.xEnd >> vector.yEnd;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Vector& vector) {
        std::cout << vector.XLength() << ' ' << vector.YLength() << '\n';
        return os;
    }
};


int main() {
    std::cout.precision(20);
    Vector a, b;
    std::cin >> a;
    std::cin >> b;
    std::cout << a.Length() << ' ' << b.Length() << '\n';
    std::cout << a + b;
    std::cout << ScalarMultiple(a, b) << ' ' << VectorMultiple(a, b) << '\n';
    std::cout << TriangleVectorBasedSquare(a, b);
    return 0;
}

