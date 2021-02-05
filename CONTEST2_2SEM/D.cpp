/*
Определите, принадлежит ли точка C заданной прямой, лучу и отрезку, образованными точками A и B.
Input format
В первой строке входного файла даны два целых числа – координаты точки C. В двух следующих строках в таком же формате заданы точки A и B (A ≠ B).
Все числа во входном файле по модулю не превосходят 10000.
Output format
В первой строке выведите «YES», если точка C принадлежит прямой AB, и «NO» в противном случае. Во второй и третьей строках аналогично выведите ответы для луча AB (A – начало луча) и отрезка AB.
*/

//Coded by Artur Kulapin

#include <iostream>
#include <cmath>
#include <cassert>

const double EPS = 1E-10;


struct Point {
    double x;
    double y;
    friend std::istream& operator>>(std::istream& is, Point& point) {
        std::cin >> point.x >> point.y;
        return is;
    }
};

class Line {
    double a_x;
    double a_y;
    double b_x;
    double b_y;

public:
    friend std::istream& operator>>(std::istream& is, Line& line) {
        std::cin >> line.a_x >> line.a_y >> line.b_x >> line.b_y;
        return is;
    }

    bool IsInLine(const Point& c) {
        if (b_x != a_x) {
            double k = (b_y - a_y) / (b_x - a_x);
            double b = a_y - k * a_x;
            return fabs(c.y - (k * c.x + b)) < EPS;
        }
        else {
            return c.x == a_x;
        }
    }

    bool IsInSegment(const Point& c) {
        if (b_x != a_x) {
            return IsInLine(c) && c.x <= std::max(a_x, b_x) && c.x >= std::min(a_x, b_x);
        } else {
            return IsInLine(c) && c.y <= std::max(a_y, b_y) && c.y >= std::min(a_y, b_y);
        }
    }

    bool IsInRay(const Point& c) {
        if (a_x != b_x) {
            return IsInLine(c) && (a_x <= b_x ? c.x >= a_x : c.x <= a_x);
        } else {
            return IsInLine(c) && (a_y <= b_y ? c.y >= a_y : c.y <= a_y);
        }
    }


};


int main() {
    Point c;
    std::cin >> c;
    Line p;
    std::cin >> p;
    p.IsInLine(c) ? std::cout << "YES\n" : std::cout << "NO\n";
    p.IsInRay(c) ? std::cout << "YES\n" : std::cout << "NO\n";
    p.IsInSegment(c) ? std::cout << "YES\n" : std::cout << "NO\n";
    return 0;
}

