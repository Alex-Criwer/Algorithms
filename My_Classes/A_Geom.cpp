#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <vector>

namespace geometry {
    class Vector;

    class AbstractShape;

    class Point;

    class Segment;

    class Ray;

    class Line;

    class Polygon;

    class Circle;

    class AbstractShape {
    public:
        virtual AbstractShape *Move(const Vector &vector) = 0;

        virtual bool ContainsPoint(const Point &point) const = 0;

        virtual bool CrossSegment(const Segment &segment) const = 0;

        virtual AbstractShape *Clone() const = 0;

        virtual void Print() const = 0;
    };

    class Point : public AbstractShape {
        long double x, y;
    public:
        Point() : x(0), y(0) {}

        Point(long double x, long double y) : x(x), y(y) {}

        Point *Move(const Vector &vector) override;

        bool ContainsPoint(const Point &point) const override;

        bool CrossSegment(const Segment &segment) const override;

        Point *Clone() const override;

        void Print() const override;

        long double getX() const;

        long double getY() const;

        Point &operator=(const Point &that) {
            x = that.getX();
            y = that.getY();
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    class Segment : public AbstractShape {
        Point a, b;
    public:
        Segment() : a(0, 0), b(0, 0) {}

        Segment(const Point &a, const Point &b) : a(a), b(b) {}

        Point getA() const;

        Point getB() const;

        Segment *Move(const Vector &vector) override;

        bool ContainsPoint(const Point &point) const override;

        bool CrossSegment(const Segment &segment) const override;

        Segment *Clone() const override;

        double distanceToSegment(const Point &c) const;

        double distanceToLine(const Point &c) const;

        void Print() const override;

    };

    class Line : public AbstractShape {
        Point a, b;
    public:
        Line() : a(0, 0), b(0, 0) {}

        Line(const Point &a, const Point &b) : a(a), b(b) {}

        AbstractShape *Move(const Vector &vector) override;

        bool ContainsPoint(const Point &point) const override;

        bool CrossSegment(const Segment &segment) const override;

        AbstractShape *Clone() const override;

        void Print() const override;
    };

    class Ray : public AbstractShape {
        Point a, b;
    public:
        Ray() : a(0, 0), b(0, 0) {}

        Ray(const Point &a, const Point &b) : a(a), b(b) {}

        AbstractShape *Move(const Vector &vector) override;

        bool ContainsPoint(const Point &point) const override;

        bool CrossSegment(const Segment &segment) const override;

        AbstractShape *Clone() const override;

        void Print() const override;
    };

    class Polygon : public AbstractShape {
        std::vector<Point> arrayOfPoint;
        int n;
    public:
        Polygon(const std::vector<Point> &arrayOfPoints, const int size) : arrayOfPoint(arrayOfPoints), n(size) {}

        AbstractShape *Move(const Vector &vector) override;

        bool ContainsPoint(const Point &point) const override;

        bool CrossSegment(const Segment &segment) const override;

        AbstractShape *Clone() const override;

        void Print() const override;

        bool isPointinPoly(const Point &point) const;

        bool belongsToPoly(const Point &point) const;
    };

    class Circle : public AbstractShape {
        Point center;
        long long radius;
    public:
        Circle() : center(Point(0, 0)), radius(0) {}

        Circle(Point center, long long radius) : center(center), radius(radius) {}

        AbstractShape *Move(const Vector &vector) override;

        bool ContainsPoint(const Point &point) const override;

        bool CrossSegment(const Segment &segment) const override;

        AbstractShape *Clone() const override;

        void Print() const override;

    };

    class Vector {
        Point a, b;
    public:
        Vector() : a(0, 0), b(0, 0) {}

        Vector(const Point &a, const Point &b) : a(a), b(b) {}

        long double projectionX() const;

        long double projectionY() const;

        long double length() const;

        long double vectorMulty(const Vector &that);

        long double scalarMulty(const Vector &that);

    };
}

void CheckFunctions(const geometry::AbstractShape *shape, const geometry::Point &A, const geometry::Point &B) {
    if (shape->ContainsPoint(A)) {
        std::cout << "Given shape contains point A" << std::endl;
    } else {
        std::cout << "Given shape does not contain point A" << std::endl;
    }

    geometry::Segment AB(A, B);
    if (shape->CrossSegment(AB)) {
        std::cout << "Given shape crosses segment AB" << std::endl;
    } else {
        std::cout << "Given shape does not cross segment AB" << std::endl;
    }

    geometry::Vector ab(A, B);
    geometry::AbstractShape *clonedShape = shape->Clone();
    clonedShape->Move(ab)->Print();
    delete clonedShape;
}

int main() {
    geometry::AbstractShape *shape;
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
        std::vector<geometry::Point> points;
        points.reserve(n_points);
        for (size_t i = 0; i < n_points; ++i) {
            int x, y;
            std::cin >> x >> y;
            points.push_back(geometry::Point(x, y));
        }
        shape = new geometry::Polygon(points, n_points);
    } else if (!strcmp(command, "circle")) {
        int x, y;
        std::cin >> x >> y;
        geometry::Point center(x, y);
        int radius;
        std::cin >> radius;
        shape = new geometry::Circle(center, radius);
    } else {
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

/////////////////////////POINT/////////////////////////
long double Point::getX() const {
    return x;
}

long double Point::getY() const {
    return y;
}

Point *Point::Move(const Vector &vector) {
    x += vector.projectionX();
    y += vector.projectionY();
    return this;
}

bool Point::ContainsPoint(const Point &point) const {
    return x == point.x && y == point.y;
}

bool Point::CrossSegment(const Segment &segment) const {
    Point segBegin = segment.getA();
    Point segEnd = segment.getB();
    Vector ab(segBegin, segEnd), ba(segEnd, segBegin), ac(segBegin, *this), bc(segEnd, *this);
    return ac.vectorMulty(ab) == 0 && bc.vectorMulty(ab) == 0 && ac.scalarMulty(ab) >= 0 && bc.scalarMulty(ba) >= 0;
}

Point *Point::Clone() const {
    return new Point(*this);
}

void Point::Print() const {
    std::cout << x << " " << y;
}

//////////////////////VECTOR//////////////////////////
long double Vector::projectionX() const {
    return b.getX() - a.getX();
}

long double Vector::projectionY() const {
    return b.getY() - a.getY();
}

long double Vector::vectorMulty(const Vector &that) {
    return projectionX() * that.projectionY() - projectionY() * that.projectionX();
}

long double Vector::scalarMulty(const Vector &that) {
    return projectionX() * that.projectionX() + projectionY() * that.projectionY();
}

long double Vector::length() const {
    return sqrt(pow(projectionY(), 2) + pow(projectionX(), 2));
}

///////////////////SEGMENT////////////////////////////
Point Segment::getA() const {
    return a;
}

Point Segment::getB() const {
    return b;
}

Segment *Segment::Move(const Vector &vector) {
    a = *a.Move(vector);
    b = *b.Move(vector);
    return this;
}

bool Segment::ContainsPoint(const Point &point) const {
    if (a.getX() == b.getX() && a.getY() == b.getY() && (a.getX() != point.getX() || a.getY() != point.getY())) {
        return false;
    }
    return point.CrossSegment(*this);
}

Segment *Segment::Clone() const {
    return new Segment(*this);
}

void Segment::Print() const {
    std::cout << a.getX() << " " << a.getY() << " " << b.getX() << " " << b.getY();
}

bool Segment::CrossSegment(const Segment &segment) const {
    Vector ab(a, b), abSegment(segment.getA(), segment.getB()), aSegaMy(segment.getA(), a);
    Vector aSegbMy(segment.getA(), b), aSegb(a, segment.getB());
    return ((abSegment.vectorMulty(aSegaMy)) * (abSegment.vectorMulty(aSegbMy)) <= 0) &&
           ((aSegaMy.vectorMulty(ab)) * (ab.vectorMulty(aSegb)) <= 0) &&
           (std::max(segment.getA().getX(), segment.getB().getX()) >= std::min(a.getX(), b.getX())) &&
           (std::max(a.getX(), b.getX()) >= std::min(segment.getA().getX(), segment.getB().getX())) &&
           (std::max(segment.getA().getY(), segment.getB().getY()) >= std::min(a.getY(), b.getY())) &&
           (std::max(a.getY(), b.getY()) >= std::min(segment.getA().getY(), segment.getB().getY()));
}

double Segment::distanceToSegment(const Point &c) const {
    double ABx = b.getX() - a.getX(), ABy = b.getY() - a.getY();
    double ACx = c.getX() - a.getX(), ACy = c.getY() - a.getY();
    double BCx = c.getX() - b.getX(), BCy = c.getY() - b.getY();
    if (ABx * ACx + ABy * ACy >= 0 && ABx * BCx + ABy * BCy <= 0) {
        return distanceToLine(c);
    } else {
        return std::min(sqrt(ACx * ACx + ACy * ACy), sqrt(BCx * BCx + BCy * BCy));
    }
}

double Segment::distanceToLine(const Point &c) const {
    double ABx = b.getX() - a.getX(), ABy = b.getY() - a.getY();
    double BCx = c.getX() - b.getX(), BCy = c.getY() - b.getY();
    double distance = fabs(ABx * BCy - BCx * ABy) / sqrt(pow(a.getX() - b.getX(), 2) + pow(a.getY() - b.getY(), 2));
    return distance;
}

//////////////////////////LINE//////////////////////////////////////
AbstractShape *Line::Move(const Vector &vector) {
    a = *a.Move(vector);
    b = *b.Move(vector);
    return this;
}

bool Line::ContainsPoint(const Point &point) const {
    Vector aPoint(a, point);
    Vector bPoint(b, point);
    return aPoint.vectorMulty(bPoint) == 0;
}

bool Line::CrossSegment(const Segment &segment) const {
    Vector ab(a, b), bc(b, segment.getA()), bd(b, segment.getB());
    if (segment.getA().getX() == segment.getB().getX() && segment.getA().getY() == segment.getB().getY()) {
        throw "degenerate segment";
    }
    return ((bc.vectorMulty(ab)) > 0 && (bd.vectorMulty(ab)) < 0) ||
           ((bc.vectorMulty(ab)) < 0 && (bd.vectorMulty(ab)) > 0) ||
           this->ContainsPoint(segment.getA()) || this->ContainsPoint(segment.getB());
}

AbstractShape *Line::Clone() const {
    return new Line(*this);
}

void Line::Print() const {
    std::cout << a.getX() << " " << a.getY() << " " << b.getX() << " " << b.getY();
}

/////////////////////////RAY//////////////////////////////

AbstractShape *Ray::Move(const Vector &vector) {
    a = *a.Move(vector);
    b = *b.Move(vector);
    return this;
}

bool Ray::ContainsPoint(const Point &point) const {
    Line line(a, b);
    if (a.getX() != b.getX()) {
        return line.ContainsPoint(point) &&
               (a.getX() <= b.getX() ? point.getX() >= a.getX() : point.getX() <= a.getX());
    } else {
        return line.ContainsPoint(point) &&
               (a.getY() <= b.getY() ? point.getY() >= a.getY() : point.getY() <= a.getY());
    }

}

bool Ray::CrossSegment(const Segment &segment) const {
    Line line(a, b);
    bool check = segment.CrossSegment(Segment(a, b));
    Vector ab(a, b), bc(b, segment.getA()), bd(b, segment.getB());
    return check || (line.CrossSegment(segment) && ab.scalarMulty(bc) >= 0 && ab.scalarMulty(bd) >= 0);
}

AbstractShape *Ray::Clone() const {
    return new Ray(*this);
}

void Ray::Print() const {
    std::cout << a.getX() << " " << a.getY() << " " << b.getX() << " " << b.getY();
}

///////////////POLYGON////////////////////////////
AbstractShape *Polygon::Move(const Vector &vector) {
    for (int i = 0; i < n; ++i) {
        arrayOfPoint[i] = *(arrayOfPoint[i].Move(vector));
    }
    return this;
}

bool Polygon::ContainsPoint(const Point &point) const {
    return isPointinPoly(point) || belongsToPoly(point);
}

bool Polygon::CrossSegment(const Segment &segment) const {
    for (int i = 0; i < n; ++i) {
        if (segment.CrossSegment(Segment(arrayOfPoint[ i % n], arrayOfPoint[(i + 1) % n]))) {
            return true;
        }
    }
    return false;
}

AbstractShape *Polygon::Clone() const {
    return new Polygon(*this);
}

void Polygon::Print() const {
    std::cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        arrayOfPoint[i].Print();
        std::cout << ' ';
    }
}

bool Polygon::isPointinPoly(const Point &point) const {
    long double sumOfAngles = 0;
    for (int i = 0; i < n; ++i) {
        Vector OA(point, arrayOfPoint[i % n]);
        Vector OB(point, arrayOfPoint[(i + 1) % n]);
        long double alpha = acos(OA.scalarMulty(OB) / (OA.length() * OB.length()));
        if (OA.vectorMulty(OB) > 0) {
            sumOfAngles += alpha;
        } else {
            sumOfAngles -= alpha;
        }
    }
    return fabs(round(double(sumOfAngles) / 2.)) > 0;
}

bool Polygon::belongsToPoly(const Point &point) const {
    for (int i = 0; i < n ; ++i) {
        double x1 = arrayOfPoint[i % n].getX(), y1 = arrayOfPoint[i % n].getY();
        double x2 = arrayOfPoint[(i + 1) % n].getX(), y2 = arrayOfPoint[(i + 1) % n].getY();
        if ((point.getX() - x1) * (y2 - y1) - (point.getY() - y1) * (x2 - x1) == 0) {
            if ((point.getX() >= x2 && point.getX() <= x1) || (point.getX() <= x2 && point.getX() >= x1)) {
                return true;
            }
        }
    }
    return false;
}
///////////////////////////////CIRCLE///////////////////////////////////////////

AbstractShape *Circle::Move(const Vector &vector) {
    center = *center.Move(vector);
    return this;
}

bool Circle::ContainsPoint(const Point &point) const {
    Vector distance(center, point);
    return (distance.length() <= (double) radius);
}

bool Circle::CrossSegment(const Segment &segment) const {
    double begDistance = sqrt(
            pow(segment.getA().getX() - center.getX(), 2) + pow(segment.getA().getY() - center.getY(), 2));
    double endDistance = sqrt(
            pow(segment.getB().getX() - center.getX(), 2) + pow(segment.getB().getY() - center.getY(), 2));
    if ((begDistance <= radius && endDistance >= radius) || (begDistance >= radius && endDistance <= radius)) {
        return true;
    }
    return begDistance > radius && endDistance > radius && segment.distanceToSegment(center) <= radius;
}

AbstractShape *Circle::Clone() const {
    return new Circle(*this);
}

void Circle::Print() const {
    center.Print();
    std::cout << " " << radius;
}
