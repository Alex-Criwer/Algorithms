/*
Проверьте, является ли приведенный многоугольник выпуклым.
Input format
В первой строке одно число N (3 ≤ N ≤ 100000). Далее в N строках по паре целых чисел – координаты очередной вершины простого многоугольника в порядке обхода по или против часовой стрелки.
Координаты всех точек целые, по модулю не превосходят 10^7.
Output format
Одна строка «YES», если приведенный многоугольник является выпуклым, и «NO» в противном случае.
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

    bool IsConvex() {
        long double* crossMultiplesArray = new long double[pointsNumber_];
        for (int i = 1; i < pointsNumber_ - 1; ++i) {
            Vector ab(points_[i].x_ - points_[i - 1].x_, points_[i].y_ - points_[i - 1].y_);
            Vector bc(points_[i + 1].x_ - points_[i].x_, points_[i + 1].y_ - points_[i].y_);
            crossMultiplesArray[i - 1] = ab ^ bc;
        }
        Vector ab(points_[pointsNumber_ - 1].x_ - points_[pointsNumber_ - 2].x_,
                  points_[pointsNumber_ - 1].y_ - points_[pointsNumber_ - 2].y_);
        Vector bc(points_[0].x_ - points_[pointsNumber_ - 1].x_,
                  points_[0].y_ - points_[pointsNumber_ - 1].y_);
        Vector cd(points_[1].x_ - points_[0].x_, points_[1].y_ - points_[0].y_);
        crossMultiplesArray[pointsNumber_ - 2] = ab ^ bc;
        crossMultiplesArray[pointsNumber_ - 1] = bc ^ cd;

        /*
        for (int i = 0; i < pointsNumber_; ++i) {
            std::cout << crossMultiplesArray[i] << ' ';
        }
         */



        bool isThereNegative = false, isTherePositive = false;

        for (int i = 0; i < pointsNumber_; ++i) {
            if (crossMultiplesArray[i] < 0) {
                isThereNegative = true;
            }
            if (crossMultiplesArray[i] > 0) {
                isTherePositive = true;
            }
        }

        if ((isThereNegative && isTherePositive) || (!isThereNegative && !isTherePositive)) {
            return false;
        } else {
            return true;
        }
    }
};


int main() {
    std::cout.precision(10);
    Polygon polygon;
    std::cin >> polygon;
    if (polygon.IsConvex()) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
    return 0;
}