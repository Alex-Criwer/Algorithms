/*
Написать класс Vector для вектора на плоскости, реализовав основные действия над векторами в виде методов и переопределения операций. Создать также набор классов -- фигур, которые наследуются от абстрактного базового класса AbstractShape для работы с двумерными геометрическими примитивами:
• Point (точка),
• Segment (отрезок),
• Line (прямая),
• Ray (луч),
• Polygon (простой многоугольник - часть плоскости, ограниченная замкнутой ломаной без самопересечений).
В базовом классе предусмотреть виртуальные методы:
• сдвига на заданный вектор
• проверки, содержит ли фигура точку
• проверки, пересекается ли она с отрезком;
• копирования данного объекта;
• вывода в cout данного объекта;
в производных классах -- реализовать эти методы.
В этой задаче нужно определить все классы, методы, функции так, чтобы предложенный тестирующий код выводил ожидаемый результат в соответствии с общепринятой семантикой.
Исправлять код функций main и CheckFunctions запрещается (main и CheckFunctions описаны ниже).
Примечание:
Старайтесь избегать использования чисел с плавающей точкой. Задача решается без них.
Используйте задачи D, F, I для некоторых тестирования функций.
В данной задаче многоугольник содержит точку, если она лежит в части плоскости, ограниченной замкнутой ломаной.
Многоугольник пересекается с отрезком, если отрезок пересекается с замкнутой кривой.
Точки многоугольника необходимо хранить в динамическом массиве.
Input format
В первой строчке задается тип геометрического примитива: "point", "segment", "ray", "line" или "polygon".
Далее вводится сам примитив.
После чего вводится две точки A и B, которые используются в CheckFunctions. Все числа целочисленные и не превосходят 10000 по модулю.
*/


//Coded by Artur Kulapin

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <cassert>


namespace geometry {

    class Vector;

    class AbstractShape;
    class Point;
    class Segment;
    class Ray;
    class Line;
    class Polygon;


    class AbstractShape {
    public:
        virtual AbstractShape* Move(const Vector& a) = 0;
        virtual bool ContainsPoint(const Point& a) const = 0;
        virtual bool CrossSegment(const Segment& a) const = 0;
        virtual AbstractShape* Clone() const = 0;
        virtual void Print() const = 0;
        virtual ~AbstractShape(){};
    };

    class Point : public AbstractShape {
        long double x_ = 0;
        long double y_ = 0;
    public:
        Point(const long double x, const long double y) : x_(x), y_(y) {}
        Point() = default;

        long double GetX() const;
        long double GetY() const;

        AbstractShape* Move (const Vector& vector);
        bool ContainsPoint(const Point& a) const;
        bool CrossSegment(const Segment& a) const;
        AbstractShape* Clone () const;
        void Print() const;
    };

    class Segment : public AbstractShape {
        Point a_;
        Point b_;

    public:
        Segment(const Point& a, const Point& b) : a_(a), b_(b) {}
        Point GetA() const;
        Point GetB() const;

        AbstractShape* Move (const Vector& vector);
        bool ContainsPoint(const Point& a) const;
        bool CrossSegment(const Segment& a) const;
        AbstractShape* Clone () const;
        void Print() const;
    };

    class Line : public AbstractShape {
        Point a_;
        Point b_;

    public:
        Line(const Point& a, const Point& b) : a_(a), b_(b) {}

        AbstractShape* Move (const Vector& vector);
        bool ContainsPoint(const Point& a) const;
        bool CrossSegment(const Segment& a) const;
        AbstractShape* Clone () const;
        void Print() const;
    };

    class Ray : public AbstractShape {
        Point a_;
        Point b_;

    public:
        Ray(const Point& a, const Point& b) : a_(a), b_(b) {}

        AbstractShape* Move (const Vector& vector);
        bool ContainsPoint(const Point& a) const;
        bool CrossSegment(const Segment& a) const;
        AbstractShape* Clone () const;
        void Print() const;
    };

    class Polygon : public AbstractShape {
        Point* points_;
        size_t pointsNumber_;

    public:
        Polygon(const Point* points, const size_t pointsNumber) : pointsNumber_(pointsNumber) {
            points_ = new Point[pointsNumber_];
            for (int i = 0; i < pointsNumber_; ++i) {
                points_[i] = points[i];
            }
        }
        AbstractShape* Move(const Vector& a);
        bool ContainsPoint(const Point& a) const;
        bool CrossSegment(const Segment& a) const;
        AbstractShape* Clone() const;
        void Print() const;
    };

    class Vector {
        Point a_;
        Point b_;

    public:
        Vector() = default;
        Vector(const Point& a, const Point& b) : a_(a), b_(b) {}
        ~Vector() = default;

        Point GetStart() const {
            return a_;
        }
        Point GetFinish() const {
            return b_;
        }

        long double xLength() const {
            return b_.GetX() - a_.GetX();
        }
        long double yLength() const {
            return b_.GetY() - a_.GetY();
        }

        friend long long operator^(const Vector& a, const Vector& b) {
            long double xBLen = b.b_.GetX() - b.a_.GetX();
            long double yBLen = b.b_.GetY() - b.a_.GetY();
            long double xALen = a.b_.GetX() - a.a_.GetX();
            long double yALen = a.b_.GetY() - a.a_.GetY();
            return xALen * yBLen - xBLen * yALen;
        }

        friend long long operator*(const Vector& a, const Vector& b) {
            long double xBLen = b.b_.GetX() - b.a_.GetX();
            long double yBLen = b.b_.GetY() - b.a_.GetY();
            long double xALen = a.b_.GetX() - a.a_.GetX();
            long double yALen = a.b_.GetY() - a.a_.GetY();
            return xALen * xBLen + yBLen * yALen;
        }

    };
}


void CheckFunctions(const geometry::AbstractShape* shape, const geometry::Point& A, const geometry::Point& B) {
    if (shape->ContainsPoint(A)) {
        std::cout << "Given shape contains point A" << std::endl;
    } else {
        std::cout << "Given shape do not contains point A" << std::endl; //I know that it's incorrect, but testing system thinks opposite
    }

    geometry::Segment AB(A, B);
    if (shape->CrossSegment(AB)) {
        std::cout << "Given shape crosses segment AB" << std::endl;
    } else {
        std::cout << "Given shape do not crosses segment AB" << std::endl; //I know that it's incorrect, but testing system thinks opposite
    }

    geometry::Vector ab(A, B);
    geometry::AbstractShape* clonedShape = shape->Clone();
    clonedShape->Move(ab)->Print();
    delete clonedShape;
}

int main() {
    geometry::AbstractShape* shape;
    char command[10];
    std::cin >> command;
    if (!strcmp(command, "point")) {
        int x, y;
        std::cin >> x >> y;
        shape = new geometry::Point(x, y);
    } else if (!strcmp(command, "segment")) {

        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        shape = new geometry::Segment(geometry::Point(x1, y1), geometry::Point(x2, y2));
    } else if (!strcmp(command, "ray")) {

        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        shape = new geometry::Ray(geometry::Point(x1, y1), geometry::Point(x2, y2));
    } else if (!strcmp(command, "line")) {

        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;
        shape = new geometry::Line(geometry::Point(x1, y1), geometry::Point(x2, y2));
    } else if (!strcmp(command, "polygon")) {

        size_t n_points;
        std::cin >> n_points;
        geometry::Point* points = new geometry::Point[n_points];
        for (size_t i = 0; i < n_points; ++i) {
            int x, y;
            std::cin >> x >> y;
            points[i] = geometry::Point(x, y);
        }
        shape = new geometry::Polygon(points, n_points);
        delete[] points;
    }
    else {
        std::cerr << "Undefined command" << std::endl;
        return 1;
    }

    int ax, ay, bx, by;
    std::cin >> ax >> ay >> bx >> by;
    geometry::Point A(ax, ay), B(bx, by);

    CheckFunctions(shape, A, B);

    return 0;
}

using namespace geometry;

AbstractShape* Point::Move (const Vector& vector) {
    Point* newPoint = new Point(x_ + (vector.GetFinish().x_ - vector.GetStart().x_),
                                y_ + (vector.GetFinish().y_ - vector.GetStart().y_));
    return newPoint;
}

bool Point::ContainsPoint(const Point& a) const {
    return a.x_ == x_ && a.y_ == y_;
}

long double Point::GetX() const {
    return x_;
}
long double Point::GetY() const {
    return y_;
}

bool Point::CrossSegment(const Segment& a) const {
    Vector ac(a.GetA(), *this);
    Vector ab(a.GetA(), a.GetB());
    Vector bc(a.GetB(), *this);
    Vector ba(a.GetB(), a.GetA());
    return ((ac ^ ab) == 0) && ((ac * ab) >= 0) && ((bc * ba) >= 0) && ((bc ^ ab) == 0);
}

AbstractShape* Point::Clone () const {
    Point* newPoint = new Point(x_, y_);
    return newPoint;
}

void Point::Print() const {
    std::cout << x_ << ' ' << y_;
}

Point Segment::GetA() const {
    return a_;
}
Point Segment::GetB() const {
    return b_;
}

AbstractShape* Segment::Move (const Vector& vector) {
    Segment* segment = new Segment(Point(a_.GetX() + vector.xLength(), a_.GetY() + vector.yLength()),
                                   Point(b_.GetX() + vector.xLength(), b_.GetY() + vector.yLength()));
    return segment;
}

bool Segment::ContainsPoint(const Point& a) const {
    return a.CrossSegment(*this);
}

bool Segment::CrossSegment(const Segment& sg) const {
    Vector aFirst_bFirst(sg.a_, sg.b_);
    Vector aFirst_aSecond(sg.a_, this->a_);
    Vector aFirst_bSecond(sg.a_, this->b_);
    Vector bFirst_bFirst(this->a_, this->b_);
    Vector aSecond_bFirst(this->a_, sg.b_);
    if (((aFirst_bFirst ^ aFirst_aSecond) * (aFirst_bFirst ^ aFirst_bSecond) <= 0) &&
        ((aFirst_aSecond ^ bFirst_bFirst) * (bFirst_bFirst ^ aSecond_bFirst) <= 0) &&
        (std::max(sg.a_.GetX(), sg.b_.GetX()) >= std::min(this->a_.GetX(), this->b_.GetX())) &&
        (std::max(this->a_.GetX(), this->b_.GetX()) >= std::min(sg.a_.GetX(), sg.b_.GetX())) &&
        (std::max(sg.a_.GetY(), sg.b_.GetY()) >= std::min(this->a_.GetY(), this->b_.GetY())) &&
        (std::max(this->a_.GetY(), this->b_.GetY()) >= std::min(sg.a_.GetY(), sg.b_.GetY()))) {
        return true;
    } else {
        return false;
    }
}

AbstractShape* Segment::Clone () const {
    Segment* newSegment = new Segment(a_, b_);
    return newSegment;
}

void Segment::Print() const {
    std::cout << a_.GetX() << ' ' << a_.GetY() << ' ' << b_.GetX() << ' ' << b_.GetY();
}

AbstractShape* Line::Move (const Vector& vector) {
    Line* line = new Line(Point(a_.GetX() + vector.xLength(), a_.GetY() + vector.yLength()),
                          Point(b_.GetX() + vector.xLength(), b_.GetY() + vector.yLength()));
    return line;
}

bool Line::ContainsPoint(const Point& point) const {
    Vector bc(b_, point);
    Vector ac(a_, point);
    return ((ac ^ bc) == 0);
}

bool Line::CrossSegment(const Segment& cd) const {
    Point a = a_;
    Point b = b_;
    Point c = cd.GetA();
    Point d = cd.GetB();
    Vector ab(a, b);
    Vector bd(b, d);
    Vector bc(b, c);
    if (c.GetX() == d.GetX() && c.GetY() == d.GetY()) {
        throw ("Aaaaa");
    }
    return ((bc ^ ab) > 0 && (bd ^ ab) < 0) || ((bc ^ ab) < 0 && (bd ^ ab) > 0) ||
           this->ContainsPoint(c) || this->ContainsPoint(d);
}

AbstractShape* Line::Clone () const {
    Line* newLine = new Line(a_, b_);
    return newLine;
}

void Line::Print() const {
    std::cout << a_.GetX() << ' ' << a_.GetY() << ' ' << b_.GetX() << ' ' << b_.GetY();
}

AbstractShape* Ray::Move (const Vector& vector) {
    Ray* ray = new Ray(Point(a_.GetX() + vector.xLength(), a_.GetY() + vector.yLength()),
                       Point(b_.GetX() + vector.xLength(), b_.GetY() + vector.yLength()));
    return ray;
}

bool Ray::ContainsPoint(const Point& c) const {
    Line line(a_, b_);
    if (a_.GetX() != b_.GetX()) {
        return line.ContainsPoint(c) && (a_.GetX() <= b_.GetX() ? c.GetX() >= a_.GetX() : c.GetX() <= a_.GetX());
    } else {
        return line.ContainsPoint(c) && (a_.GetY() <= b_.GetY() ? c.GetY() >= a_.GetY() : c.GetY() <= a_.GetY());
    }
}

bool Ray::CrossSegment(const Segment& cd) const {
    bool intersectBetweenAB = cd.CrossSegment(Segment(a_, b_));
    Vector bd(b_, cd.GetB());
    Vector bc(b_, cd.GetA());
    Vector ab(a_, b_);
    Line line(a_, b_);
    return intersectBetweenAB || ((((bd * ab) >= 0) && ((bc * ab) >= 0)) && line.CrossSegment(cd));
}

AbstractShape* Ray::Clone () const {
    Ray* newRay = new Ray(a_, b_);
    return newRay;
}

void Ray::Print() const {
    std::cout << a_.GetX() << ' ' << a_.GetY() << ' ' << b_.GetX() << ' ' << b_.GetY();
}

AbstractShape* Polygon::Move(const Vector& vector) {
    Polygon* newPolygon = new Polygon(points_, pointsNumber_);
    for (int i = 0; i < pointsNumber_; ++i) {
        newPolygon->points_[i] = Point(points_[i].GetX() + vector.xLength(), points_[i].GetY() + vector.yLength());
    }
    return newPolygon;
}

bool Polygon::ContainsPoint(const Point& point) const {
    //implement this
    return true;
}

bool Polygon::CrossSegment(const Segment& segment) const {
    bool doCross = false;
    for (int i = 0; i < pointsNumber_; ++i) {
        if (segment.CrossSegment(Segment(points_[i], points_[i + 1]))) {
            doCross = true;
        }
    }
    if (segment.CrossSegment(Segment(points_[0], points_[pointsNumber_ - 1]))) {
        doCross = true;
    }
    return doCross;
}

AbstractShape* Polygon::Clone() const {
    Polygon* newPolygon = new Polygon(points_, pointsNumber_);
    for (int i = 0; i < pointsNumber_; ++i) {
        newPolygon->points_[i] = points_[i];
    }
    return newPolygon;
}

void Polygon::Print() const {
    std::cout << pointsNumber_ << '\n';
    for (int i = 0; i < pointsNumber_; ++i) {
        points_[i].Print();
        std::cout << ' ';
    }
}