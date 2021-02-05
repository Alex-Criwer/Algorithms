/*
Найдите площадь простого многоуольника.
Input format
В первой строке одно число N (3 ≤ N ≤ 100000). Далее в N строках по паре чисел – координаты очередной вершины простого многоугольника в порядке обхода по или против часовой стрелки.
Координаты целые по модулю не превосходят 10000.
Output format
Одно число – величина площади приведённого многоугольника с абсолютной точностью.
*/

//Coded by Artur Kulapin

#include <iostream>
#include <cmath>


struct Point {
    int x_, y_;
public:
    Point(int x, int y) : x_(x), y_(y) {}
    Point() = default;

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
    Vector(Point a, Point b) : x_(b.x_ - a.x_), y_(b.y_ - a.y_) {}

    Vector operator * (double b) {
        return Vector(x_ * b, y_ * b);
    }

    Vector operator / (double b) {
        return Vector(x_ / b, y_ / b);
    }

    Vector operator + (const Vector& other) {
        return Vector(x_ + other.x_, y_ + other.y_);
    }

    friend long double operator^(const Vector& a, const Vector& b) {
        return a.x_*b.y_ - a.y_*b.x_;
    }


};

class Polygon {
    Point* points_;
    int pointsNumber_;

public:

    friend std::istream& operator>>(std::istream& is, Polygon& polygon) {
        std::cin >> polygon.pointsNumber_;
        polygon.points_ = new Point[polygon.pointsNumber_];
        for (int i = 0; i < polygon.pointsNumber_; ++i) {
            std::cin >> polygon.points_[i];
        }
        return is;
    }

    long double Square() {
        long double square = 0;
        Point start(0, 0);
        for (int i = 0; i < pointsNumber_ - 1; i++) {
            Vector p1(start, points_[i]);
            Vector p2(start, points_[i + 1]);
            square += (p1 ^ p2) / 2;
        }
        Vector p1(start, points_[pointsNumber_ - 1]);
        Vector p2(start, points_[0]);
        square += (p1 ^ p2) / 2;
        return fabs(square);
    }
};



int main() {
    std::cout.precision(15);
    Polygon polygon;
    std::cin >> polygon;
    std::cout << std::fixed << polygon.Square();
}//
// Created by Asus on 08.02.2020.
//

