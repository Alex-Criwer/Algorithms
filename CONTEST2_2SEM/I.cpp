/*
Проверьте, лежит ли заданная точка внутри или на границе приведенного многоугольника.
Input format
В первой строке вводятся три целых числа – N (3 ≤ N ≤ 100000) и координаты точки. Далее в N строках задается по паре целых чисел – координаты очередной вершины простого многоугольника в порядке обхода по или против часовой стрелки.
Output format
Выведите одну строку: «YES», если заданная точка содержится в приведённом многоугольнике или на его границе, и «NO» в противном случае.
*/

//Coded by Artur Kulapin

/*
Here you can find cheat solution of this problem :)
If it doesn't pass all tests, you should improve it :)
*/

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

long double eps = 1e-8;

bool behind(long double a, long double b, long double n) {
    if (b < a) {
        swap(a, b);
    }
    return a <= n && n <= b;
}

struct Point {
    long double x, y;
    void read() {
        cin >> x >> y;
    }
    void write() {
        cout << x << ' ' << y << endl;
    }
    long double distance(Point p) {
        return (x - p.x) * (x - p.x) + (y - p.y) * (y - p.y);
    }
};

long double rotate(Point p1, Point p2, Point p3) {
    return (p2.x - p1.x) * (p3.y - p2.y) - (p3.x - p2.x) * (p2.y - p1.y);
}

struct Segment {
    Point p1, p2;
    long double a, b, c;
    Segment(Point beg, Point end) {
        p1 = beg;
        p2 = end;
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        c = -a * p1.x - b * p1.y;
    }
    bool on_segment(Point p) {
        if (!(abs(a * p.x + b * p.y + c) <= eps)) {
            return false;
        } else {
            if (behind(p1.x, p2.x, p.x) && behind(p1.y, p2.y, p.y)) {
                return true;
            }
            else {
                return false;
            }
        }
    }
};

struct Line {
    long double a, b, c;
    Line() {
        a = 0;
        b = 0;
        c = 0;
    }
    Line(Point p1, Point p2) {
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        c = -a * p1.x - b * p1.y;
    }
    bool intersect(Segment line, Point &p) {
        long double a2 = line.a,
                b2 = line.b,
                c2 = line.c;
        Point ans;
        ans.x = (c2 * b - b2 * c) / (a * b2 - a2 * b);
        ans.y = (c * a2 - c2 * a) / (a * b2 - a2 * b);
        if (line.on_segment(ans)) {
            p = ans;
            return true;
        }
        else {
            return false;
        }
    }
    bool on_line(Point p) {
        return (abs(a * p.x + b * p.y + c) <= eps);
    }
};

struct Luch {
    Point beg;
    Line line;
    Luch(Line line, Point beg) {
        this->line = line;
        this->beg = beg;
    }
    bool on_luch(Point p) {
        if (!line.on_line(p)) return false;
        if (p.x > beg.x) return true;
        else return false;
    }
};

struct Polygon {
    vector<Point> points;
    bool inside(Point p) {
        int n = points.size();
        int ans = 0;
        Point far;

        for (int i = 0; i < n - 1; ++i) {
            Segment seg_a = Segment(points[i], points[i + 1]);
            if (seg_a.on_segment(p))
                return true;
        }

        Segment seg_a = Segment(points[n - 1], points[0]);
        if (seg_a.on_segment(p)) {
            return true;
        }
        far.x = 1.234123;
        far.y = 128191.12351;
        Line sep = Line(p, far);
        Luch luch = Luch(sep, p);
        for (int i = 1; i < n; ++i) {
            Point beg = points[i - 1];
            Point end = points[i];
            Segment seg = Segment(beg, end);
            Point inter;
            if (sep.intersect(seg, inter)) {
                if (luch.on_luch(inter)) ans++;
            }
        }
        Point beg = points[n - 1];
        Point end = points[0];
        Segment seg = Segment(beg, end);
        Point inter;
        if (sep.intersect(seg, inter)) {
            if (luch.on_luch(inter)) {
                ans++;
            }
        }

        if (ans % 2 == 0) {
            return false;
        } else {
            return true;
        }
    }
};


int main() {
    Polygon pol;
    int n;
    cin >> n;

    Point point;
    cin >> point.x >> point.y;
    vector<Point> ps;
    for (int i = 0; i < n; ++i) {
        Point p;
        p.read();
        pol.points.push_back(p);
    }
    if (pol.inside(point)) {
        cout << "YES";
    } else {
        cout << "NO";
    }
    return 0;
}//
// Created by Asus on 08.02.2020.
//

