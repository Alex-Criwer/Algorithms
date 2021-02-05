/*
Даны три точки A, B и C. Необходимо подсчитать расстояния от точки C до прямой, луча и отрезка, образованного точками A и B.
Input format
В первой строке входного файла даны два целых числа – координаты точки C. В двух следующих строках в таком же формате заданы точки A и B (A ≠ B).
Все числа во входном файле по модулю не превосодят 10000.
Output format
В первой строке выходного файла выведите одно вещественное число – расстояние от точки C до прямой. В следующих двух строках выведите соответственно расстояния до луча AB (A – начало луча) и до отрезка AB. Все числа выводить с точностью не менее 10^-6.
*/

//Coded by Artur Kulapin

#include <iostream>
#include <cmath>

struct Point {
    int x_, y_;
public:
    friend std::istream& operator>>(std::istream& is, Point& point) {
        std::cin >> point.x_ >> point.y_;
        return is;
    }
};

class Vector {
    double x_, y_;
public:
    Vector() = default;
    Vector(double x, double y) : x_(x), y_(y) {}
    Vector(Point a, Point b) {
        x_ = b.x_ - a.x_;
        y_ = b.y_ - a.y_;
    }

    Vector operator * (double b) {
        return Vector(x_ * b, y_ * b);
    }

    Vector operator / (double b) {
        return Vector(x_ / b, y_ / b);
    }

    Vector operator + (const Vector& other) {
        return Vector(x_ + other.x_, y_ + other.y_);
    }

    friend double operator*(const Vector& a, const Vector& b) {
        return a.x_ * b.x_ + a.y_ * b.y_;
    }

    friend double operator^(const Vector& a, const Vector& b) {
        return a.x_*b.y_ - a.y_*b.x_;
    }

    double abs() {
        return sqrt(x_ * x_ + y_ * y_);
    }

};


class Line {
    Point a_;
    Point b_;
public:
    Line() = default;
    Line(Point a, Point b) : a_(a), b_(b) {}

    double distance(const Point& c) {
        return abs(Vector(c, a_) ^ Vector(c, b_)) / Vector(a_, b_).abs();
    }
};

class Ray {
    Point a_;
    Point b_;
public:
    Ray() = default;
    Ray(Point a, Point b) : a_(a), b_(b) {}

    double distance(const Point& c) {
        Vector vOne(a_, c);
        Vector vTwo(a_, b_);

        if (vOne * vTwo >= 0) {
            Line line(a_, b_);
            return line.distance(c);
        } else {
            return vOne.abs();
        }
    }
};

class Segment {
    Point a_;
    Point b_;
public:
    Segment() = default;
    Segment(Point a, Point b) : a_(a), b_(b) {}

    double distance(Point c) {
        Vector vOne(a_, b_);
        Vector vTwo(a_, c);
        Vector vThree(b_, c);
        if (vOne * vTwo < 0) {
            return vTwo.abs();
        }
        else if ((vOne * -1) * vThree < 0) {
            return vThree.abs();
        }
        else {
            Line line(a_, b_);
            return line.distance(c);
        }
    }
};


int main() {
    std::cout.precision(10);
    Point a, b, c;
    std::cin >> c >> a >> b;
    Line line(a, b);
    Ray ray(a, b);
    Segment segment(a, b);
    std::cout << std::fixed << line.distance(c) << '\n';
    std::cout << std::fixed << ray.distance(c) << '\n';
    std::cout << std::fixed << segment.distance(c);
    return 0;
}