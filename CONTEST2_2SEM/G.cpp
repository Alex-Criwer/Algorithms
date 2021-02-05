/*
Найдите расстояние между двумя отрезками.
Input format
В двух строках входного файла даны по четыре целых числа, не превосходящих по модулю 10000, – координаты концов сначала первого, затем второго отрезков.
Output format
В первой строке выходного файла выведите одно вещественное число – расстояние между отрезками с точностью не менее 10^-6.
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

    friend bool AreIntersected(Segment sg1, Segment sg2) {
        Vector aFirst_bFirst(sg1.a_, sg1.b_);
        Vector aFirst_aSecond(sg1.a_, sg2.a_);
        Vector aFirst_bSecond(sg1.a_, sg2.b_);
        Vector bFirst_bFirst(sg2.a_, sg2.b_);
        Vector aSecond_aFirst(sg2.a_, sg1.a_);
        Vector aSecond_bFirst(sg2.a_, sg1.b_);
        if (((aFirst_bFirst ^ aFirst_aSecond) * (aFirst_bFirst ^ aFirst_bSecond) <= 0) &&
            ((aFirst_aSecond ^ bFirst_bFirst) * (bFirst_bFirst ^ aSecond_bFirst) <= 0) &&
            (std::max(sg1.a_.x_, sg1.b_.x_) >= std::min(sg2.a_.x_, sg2.b_.x_)) &&
            (std::max(sg2.a_.x_, sg2.b_.x_) >= std::min(sg1.a_.x_, sg1.b_.x_)) &&
            (std::max(sg1.a_.y_, sg1.b_.y_) >= std::min(sg2.a_.y_, sg2.b_.y_)) &&
            (std::max(sg2.a_.y_, sg2.b_.y_) >= std::min(sg1.a_.y_, sg1.b_.y_))) {
            return true;
        } else {
            return false;
        }
    }
};


int main() {
    std::cout.precision(10);
    Point a, b, c, d;
    std::cin >> a >> b >> c >> d;
    Segment sOne(a, b);
    Segment sTwo(c, d);
    double distance = 0;
    if (!AreIntersected(sOne, sTwo)) {
        distance = std::min(std::min(sTwo.distance(a), sTwo.distance(b)),
                            std::min(sOne.distance(c), sOne.distance(d)));
    }
    std::cout << distance;
}

