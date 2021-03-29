#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

class Vector {
private:
    long double x1, y1, x2, y2;
public:
    Vector();

    Vector(long double x1, long double y1, long double x2, long double y2);

    friend std::istream &operator>>(std::istream &is, Vector &myVector);

    friend std::ostream &operator<<(std::ostream &os, const Vector &myVector);

    friend Vector operator+(Vector &first, Vector &second);

    long double scalarProduct(const Vector &that);

    long double vectorProduct(const Vector &that);

    long double triangleSquere(const Vector &that);

    long double proectionX() const;

    long double proectionY() const;

    long double length() const;

};

int main() {
    Vector vec1, vec2;
    cin >> vec1 >> vec2;
    cout << setprecision(10) << vec1.length() << " " << vec2.length() << endl;
    cout << setprecision(10) << (vec1 + vec2).proectionX() << " " << (vec1 + vec2).proectionY() << endl;
    cout << setprecision(10) << vec1.scalarProduct(vec2) << " " << vec1.vectorProduct(vec2) << endl;
    cout << setprecision(10) << vec1.triangleSquere(vec2);
    return 0;
}


Vector::Vector() {
    x1 = 0, y1 = 0, x2 = 0, y2 = 0;
}

Vector::Vector(long double x1, long double y1, long double x2, long double y2) : x1(x1), y1(y1), x2(x2), y2(y2) {}

std::istream &operator>>(std::istream &is, Vector &myVector) {
    long double x1, y1, x2, y2;
    is >> x1 >> y1 >> x2 >> y2;
    myVector.x1 = x1, myVector.y1 = y1, myVector.x2 = x2, myVector.y2 = y2;
    return is;
}

long double Vector::length() const {
    return sqrt(pow(proectionX(), 2) + pow(proectionY(), 2));
}

std::ostream &operator<<(std::ostream &os, const Vector &myVector) {
    os << myVector.x1 << " " << myVector.y1 << " " << myVector.x2 << " " << myVector.y2;
}

Vector operator+(Vector &first, Vector &second) {
    return Vector(0, 0, first.proectionX() + second.proectionX(), first.proectionY() + second.proectionY());
}

long double Vector::proectionX() const {
    return x2 - x1;
}

long double Vector::proectionY() const {
    return y2 - y1;
}

long double Vector::scalarProduct(const Vector &that) {
    return proectionX() * that.proectionX() + proectionY() * that.proectionY();
}

long double Vector::vectorProduct(const Vector &that) {
    return proectionX() * that.proectionY() - proectionY() * that.proectionX();
}

long double Vector::triangleSquere(const Vector &that) {
    return 0.5 * abs(vectorProduct(that));
}

