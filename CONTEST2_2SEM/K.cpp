/*
Дано N точек на плоскости.
Нужно построить их выпуклую оболочку.
Гарантируется, что выпуклая оболочка не вырождена.
Input format
На первой строке число N (3 ≤ N ≤ 100000). Следующие N строк содержат пары целых чисел x и y (-10^9 ≤ x, y ≤ 10^9) – точки.
Будьте аккуратны! Точки произвольны. Бывают совпадающие, бывают лежащие на одной прямой в большом количестве.
Output format
В первой строке выведите N – число вершин выпуклой оболочки. Следующие N строк должны содержать координаты вершин в порядке обхода.
Никакие три подряд идущие точки не должны лежать на одной прямой.
Кроме того, в последней строке выведите площадь получившейся выпуклой оболочки. Площадь необходимо вывести абсолютно точно.
*/

//Coded by Artur Kulapin

#include <iostream>
#include <vector>
#include <algorithm>

struct Point {
    long long x;
    long long y;
};

bool leftTurn(Point a, Point b, Point c) {
    return a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y) < 0;
}

bool rightTurn(Point a, Point b, Point c) {
    return a.x*(b.y - c.y) + b.x*(c.y - a.y) + c.x*(a.y - b.y) > 0;
}

void ConvexHull(std::vector<Point>& p) {
    sort(p.begin(), p.end(), [](Point a, Point b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });

    Point A = p[0];
    Point B = p.back();
    std::vector<Point> up, down;
    up.push_back(A);
    down.push_back(A);

    for (int i = 1; i < p.size(); ++i) {
        if (i == p.size() - 1 || leftTurn(A, p[i], B)) {
            while (up.size() >= 2 && !leftTurn(up[up.size() - 2], up[up.size() - 1], p[i])) {
                up.pop_back();
            }
            up.push_back(p[i]);
        }
        if (i == p.size() - 1 || rightTurn(A, p[i], B)) {
            while (down.size() >= 2 && !rightTurn(down[down.size() - 2], down[down.size() - 1], p[i])) {
                down.pop_back();
            }
            down.push_back(p[i]);
        }
    }
    p.clear();

    for (int i = 0; i < up.size(); ++i) {
        p.push_back(up[i]);
    }
    for (int i = down.size() - 2; i > 0; --i) {
        p.push_back(down[i]);
    }
}

long long Area(std::vector<Point>& p) {
    long long area = 0;
    for (int i = 0, j = p.size() - 1; i < p.size(); j = i++) {
        area += (p[i].x - p[j].x) * (p[i].y + p[j].y);
    }
    return std::abs(area);
}

void ReadPoly(std::vector<Point>& points, const int pointsNumber) {
    for (int i = 0; i < pointsNumber; ++i) {
        std::cin >> points[i].x >> points[i].y;
    }
}
void PrintPoly(std::vector<Point>& points) {
    for (int i = 0; i < points.size(); ++i) {
        std::cout << points[i].x << ' ' << points[i].y << std::endl;
    }
}

//This function is necessary, because LongDouble's precision is 15 numbers, but precision we need is 18 numbers :(

void PrintArea(const long long area) {
    std::cout << area / 2;
    (area % 2) ? std::cout << ".5" : std::cout << ".0";
    std::cout << std::endl;
}

int main() {
    int pointsNumber;
    std::cin >> pointsNumber;

    std::vector<Point> p(pointsNumber);
    ReadPoly(p, pointsNumber);
    ConvexHull(p);

    std::cout << p.size() << std::endl;
    PrintPoly(p);
    PrintArea(Area(p));
    return 0;
}

