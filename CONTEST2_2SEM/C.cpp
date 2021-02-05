/*
Даны коэффициенты A_1, B_1, C_1 уравнения первой прямой и коэффициенты A_2, B_2, C_2 уравнения второй прямой. Требуется:
• Для каждой прямой вывести координаты любого направляющего вектора
• Найти точку пересечения двух прямых или вычислить расстояние между ними, если они параллельны
Input format
В первой строке входного файла находятся три числа – коэффициенты нормального уравнения для первой прямой. Во второй строке – коэффициенты для второй прямой.
Все числа во входном файле по модулю не превосодят 10000.
Output format
В каждой строке выходного файла выведите ответ на соответствующий пункт задачи с точностью до 10^-6.
*/

//Coded by Artur Kulapin

#include <iostream>
#include <cmath>
#include <cassert>

const double EPS = 1E-8;

struct Point {
    double first;
    double second;

    friend std::ostream& operator<<(std::ostream& os, const Point& point) {
        std::cout << point.first << ' ' << point.second << '\n';
        return os;
    }
};

class Line {
    double a;
    double b;
    double c;
public:
    Line(double a, double b, double c) : a(a), b(b), c(c) {}
    Line() = default;
    ~Line() = default;
    friend std::istream& operator>>(std::istream& is, Line& line) {
        std::cin >> line.a >> line.b >> line.c;
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Line& line) {
        if (line.b != 0) {
            std::cout << 1 << ' ' << -line.a / line.b;
        } else {
            std::cout << 0 << ' ' << 1;
        }
        return os;
    }

    friend bool areParallel(const Line& lOne, const Line& lTwo) {
        return abs(lOne.a * lTwo.b - lTwo.a * lOne.b) < EPS;
    }

    friend bool areSame(const Line& lOne, const Line& lTwo) {
        if (lOne.a != 0) {
            return areParallel(lOne, lTwo) && ((lOne.a / lTwo.a) * lTwo.c == lOne.c);
        } else {
            return areParallel(lOne, lTwo) && ((lOne.b / lTwo.b) * lTwo.c == lOne.c);
        }
    }

    friend Point IntersectionPoint(const Line& lOne, const Line& lTwo) {
        Point intersectionPoint;
        intersectionPoint.first = (lOne.b * lTwo.c - lTwo.b * lOne.c) / (lOne.a * lTwo.b - lOne.b * lTwo.a);
        intersectionPoint.second = (lOne.a * lTwo.c - lTwo.a * lOne.c) / (lOne.b * lTwo.a - lOne.a * lTwo.b);
        return intersectionPoint;
    }

    friend double Distance(const Line& lOne, const Line& lTwo) {
        double distance;
        if (lTwo.a != 0) {
            double coef = lOne.a / lTwo.a;
            Line temp(lOne.a / coef, lOne.b / coef, lOne.c / coef);
            distance = (lTwo.c - temp.c) / sqrt(lTwo.a * lTwo.a + lTwo.b * lTwo.b);
        } else {
            distance = (lOne.c - lTwo.c) / lTwo.b;
        }
        if (distance < 0) {
            distance *= -1;
        }
        return distance;
    }
};


int main() {
    std::cout.precision(10);
    Line a, b;
    std::cin >> a >> b;
    std::cout << std::fixed << a << std::endl << std::fixed << b << std::endl;
    if (areSame(a, b)) {
        std::cout << 0;
    }
    else if (areParallel(a, b)) {
        std::cout << std::fixed << Distance(a, b);
    } else {
        std::cout << std::fixed << IntersectionPoint(a, b);
    }
    return 0;
}

