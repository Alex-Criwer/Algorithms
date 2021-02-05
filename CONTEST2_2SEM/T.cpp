/*
Необходимо разработать шаблонный класс Matrix, удовлетворяющий требованиям:
• Класс Matrix можно параметризовать любым типом (условно назовём его "число"), реализующим сложение, вычитание и умножение.
• Значения элементов матрицы хранятся в двумерном массиве, выделенном в динамической памяти
• Обеспечить классу конструктор, принимающий размеры, а также конструктор копирования, операцию присваивания и деструктор.
• Методы getRowsNumber() и getColumnsNumber().
• Реализовать операции сложения, вычитания, перемножения матриц и умножения матрицы на "число" слева и справа, в том числе операции +=, -=, *=.
• Реализовать метод транспонирования матрицы в двух вариантах: мутирующем (transpose) с возвратом ссылки на объект и немутирующем (getTransposed) с возвратом нового объекта.
• Определить операцию вызова operator()(i,j) для обращения к элементам матрицы.
• Методы классов должны генерировать исключения:
MatrixWrongSizeError - если складываются/перемножаются матрицы неподходящих размеров;
MatrixIndexError - при попытке получить доступ к элементам с невалидными индексами;
• Реализовать ввод матриц из std::istream и вывод в std::ostream в виде прямоугольной таблицы, где элементы строки матрицы разделены пробелами, а в конце каждой строки матрицы идёт символ конца строки.
• Определить все методы, операции и дополнительные классы так, чтобы предложенный тестирующий код выводил ожидаемый результат                в соответствии с общепринятой семантикой.
Ссылка на код: matrix.cpp (main function)
Input format
В первой строке дано 4 целых числа m, n, p, q.
Далее во входном файле идут две целочисленные матрицы размеров m x n и p x q соответственно
        Далее во входном файле идет рациональное число в формате, описанном в предыдущей задаче
        Далее во входном файле идут две матрицы с рациональными числами размеров m x n и p x q соответственно
Все числа во входном файле не превосходят по модулю 10.
Output format
Результат работы matrix.cpp при правильно реализованных методах класса.
*/

//Coded by Artur Kulapin

#include <iostream>
#include <cstdlib>
#include <exception>


class MatrixWrongSizeError : public std::exception {
    const char* what() const noexcept override {
        return "Matrix's sizes don't fit to complete the operation";
    }
};

class MatrixIndexError : public std::exception {
    const char* what() const noexcept override {
        return "You tried to get element with incorrect pair of index";
    }
};

// non-specified functions to get "zero" of type T

template<typename T>
T getZero() {
    return T(0);
}

//=============== Matrix class ===============//

template <typename T>
class Matrix {
protected:
    int height_ = 0;
    int width_ = 0;
    T** matrixField_;

public:
    Matrix(const int width, const int height);
    Matrix(const Matrix<T>& other);
    Matrix(Matrix<T>&& other) noexcept;
    Matrix& operator=(const Matrix& other);
    Matrix& operator=(Matrix&& other) noexcept;
    virtual ~Matrix();
    Matrix<T>& Transpose();
    Matrix<T> getTransposed();

    int getRowsNumber() const {
        return height_;
    }
    int getColumnsNumber() const {
        return width_;
    }

    template <typename M>
    friend Matrix<M> operator+(const Matrix<M>& lmx, const Matrix<M>& rmx);
    template <typename M>
    friend Matrix<M> operator-(const Matrix<M>& lmx, const Matrix<M>& rmx);
    template <typename M>
    friend Matrix<M> operator*(const Matrix<M>& lmx, const Matrix<M>& rmx);
    template <typename M>
    friend Matrix<M> operator*(const M scalar, const Matrix<M>& rmx);
    template <typename M>
    friend Matrix<M> operator*(const Matrix<M>& rmx, const M scalar);

    template <typename M>
    Matrix<T>& operator+=(const M& number) {
        return *this = (*this + number);
    }
    template <typename M>
    Matrix<T>& operator-=(const M& number) {
        return *this = (*this - number);
    }
    template <typename M>
    Matrix<T>& operator*=(const M& number) {
        return *this = (*this * number);
    }

    T& operator()(const int positionHeight, const int positionWidth);
    T operator()(const int positionHeight, const int positionWidth) const;

    template <typename M>
    friend std::istream& operator>>(std::istream& is, Matrix<M>& matrix);
    template <typename M>
    friend std::ostream& operator<<(std::ostream& os, const Matrix<M>& matrix);

    void ClearMatrix() {
        for (int i = 0; i < height_; ++i) {
            delete[] matrixField_[i];
        }
        delete[] matrixField_;
    }
};


template<typename T>
T getZero();

template <typename T>
Matrix<T>::Matrix(const int height, const int width) {
    height_ = height;
    width_ = width;
    matrixField_ = new T*[height];
    for (int i = 0; i < height_; ++i) {
        matrixField_[i] = new T[width];
    }
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            matrixField_[i][j] = getZero<T>();
        }
    }
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other) {
    width_ = other.width_;
    height_ = other.height_;
    matrixField_ = new T*[height_];
    for (int i = 0; i < height_; ++i) {
        matrixField_[i] = new T[width_];
    }
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            matrixField_[i][j] = other.matrixField_[i][j];
        }
    }
}

template <typename T>
Matrix<T>::Matrix(Matrix<T>&& other) noexcept {
    std::swap(matrixField_, other.matrixField_);
    width_ = other.width_;
    height_ = other.height_;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    if (other.matrixField_ != this ->matrixField_) {
        this->ClearMatrix();
        width_ = other.width_;
        height_ = other.height_;
        this->matrixField_ = new T*[height_];
        for (int i = 0; i < height_; ++i) {
            matrixField_[i] = new T[width_];
        }
        for (int i = 0; i < height_; ++i) {
            for (int j = 0; j < width_; ++j) {
                matrixField_[i][j] = other.matrixField_[i][j];
            }
        }
    }
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) noexcept {
    if (other.matrixField_ != this->matrixField_) {
        width_ = other.width_;
        height_ = other.height_;
        std::swap(matrixField_, other.matrixField_);
    }
    return *this;
}

template <typename T>
Matrix<T>::~Matrix() {
    for (int i = 0; i < height_; ++i) {
        delete[] matrixField_[i];
    }
    delete[] matrixField_;
}

template <typename T>
Matrix<T> operator+(const Matrix<T> &lmx, const Matrix<T> &rmx) {
    if (lmx.width_ != rmx.width_ || lmx.height_ != rmx.height_) {
        throw MatrixWrongSizeError();
    }
    Matrix<T> newMatrix(lmx.height_, lmx.width_);
    for (int i = 0; i < newMatrix.height_; ++i) {
        for (int j = 0; j < newMatrix.width_; ++j) {
            newMatrix.matrixField_[i][j] = lmx.matrixField_[i][j] + rmx.matrixField_[i][j];
        }
    }
    return newMatrix;
}

template <typename T>
Matrix<T> operator-(const Matrix<T> &lmx, const Matrix<T> &rmx) {
    if (lmx.width_ != rmx.width_ || lmx.height_ != rmx.height_) {
        throw MatrixWrongSizeError();
    }
    Matrix<T> newMatrix(lmx.height_, lmx.width_);
    for (int i = 0; i < newMatrix.height_; ++i) {
        for (int j = 0; j < newMatrix.width_; ++j) {
            newMatrix.matrixField_[i][j] = lmx.matrixField_[i][j] - rmx.matrixField_[i][j];
        }
    }
    return newMatrix;
}

template <typename T>
Matrix<T> operator*(const T scalar, const Matrix<T> &lmx) {
    Matrix<T> newMatrix(lmx.height_, lmx.width_);
    for (int i = 0; i < newMatrix.height_; ++i) {
        for (int j = 0; j < newMatrix.width_; ++j) {
            newMatrix.matrixField_[i][j] = lmx.matrixField_[i][j] * scalar;
        }
    }
    return newMatrix;
}

template <typename T>
Matrix<T> operator*(const Matrix<T> &lmx, const T scalar) {
    Matrix<T> newMatrix(lmx.height_, lmx.width_);
    for (int i = 0; i < newMatrix.height_; ++i) {
        for (int j = 0; j < newMatrix.width_; ++j) {
            newMatrix.matrixField_[i][j] = lmx.matrixField_[i][j] * scalar;
        }
    }
    return newMatrix;
}

template <typename T>
Matrix<T> operator*(const Matrix<T> &lmx, const Matrix<T>& rmx) {
    if (lmx.height_ != rmx.width_) {
        throw MatrixWrongSizeError();
    }
    Matrix<T> newMatrix(lmx.height_, rmx.width_);
    for (int i = 0; i < lmx.height_; ++i) {
        for (int j = 0; j < rmx.width_; ++j) {
            for (int k = 0; k < lmx.width_; ++k) {
                newMatrix.matrixField_[i][j] += lmx.matrixField_[i][k] * rmx.matrixField_[k][j];
            }
        }
    }
    return newMatrix;
}


template <typename T>
T& Matrix<T>::operator()(const int positionHeight, const int positionWidth) {
    if (positionHeight < 0 || positionHeight >= height_ || positionWidth < 0 || positionWidth >= width_) {
        throw MatrixIndexError();
    }
    return matrixField_[positionHeight][positionWidth];
}

template <typename T>
T Matrix<T>::operator()(const int positionHeight, const int positionWidth) const {
    if (positionHeight < 0 || positionHeight >= height_ || positionWidth < 0 || positionWidth >= width_) {
        throw MatrixIndexError();
    }
    return matrixField_[positionHeight][positionWidth];
}

template <typename T>
std::istream& operator>>(std::istream& is, Matrix<T>& matrix) {
    matrix.matrixField_ = new T*[matrix.height_];
    for (int i = 0; i < matrix.height_; ++i) {
        matrix.matrixField_[i] = new T[matrix.width_];
    }

    for (int i = 0; i < matrix.height_; ++i) {
        for (int j = 0; j < matrix.width_; ++j) {
            is >> matrix.matrixField_[i][j];
        }
    }
    return is;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
    for (int i = 0; i < matrix.height_; ++i) {
        for (int j = 0; j < matrix.width_; ++j) {
            os << matrix.matrixField_[i][j] << ' ';
        }
        os << '\n';
    }
    return os;
}

template <typename T>
Matrix<T> Matrix<T>::getTransposed() {
    Matrix<T> newMatrix(width_, height_);
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            newMatrix.matrixField_[j][i] = matrixField_[i][j];
        }
    }
    return newMatrix;
}

template <typename T>
Matrix<T>& Matrix<T>::Transpose() {
    Matrix<T> newMatrix(width_, height_);
    for (int i = 0; i < height_; ++i) {
        for (int j = 0; j < width_; ++j) {
            newMatrix.matrixField_[j][i] = matrixField_[i][j];
        }
    }
    *this = newMatrix;
    return *this;
}


//================ class Rational ===============//

class RationalDivisionByZero : public std::exception {
    const char* what() const noexcept override {
        return "It is bad decision to divide by zero";
    }
};

class Rational {
private:
    int p_;
    unsigned int q_; // is maintained to be positive

    static int gcd(int a, int b) {
        while (a > 0 && b > 0) {
            if (a > b) {
                a = a % b;
            } else {
                b = b % a;
            }
        }
        return (a + b);
    }

    void reduce() {
        if (q_ < 0) {
            q_ *= -1;
            p_ *= -1;
        }
        if (p_ == 0) {
            q_ = 1;
        }
        int reduceNumber = gcd(abs(p_), q_);
        p_ /= reduceNumber;
        q_ /= reduceNumber;
    }

public:
    Rational(const int p, const int q) : p_(p), q_(q) {
        this->reduce();
    }
    Rational(const int p) : p_(p), q_(1) {}
    Rational(){}

    int getNumerator() const {
        return p_;
    }
    int getDenominator() const {
        return q_;
    }

    friend std::istream& operator>>(std::istream& is, Rational& number) {
        char frac;
        int read = scanf("%d/%d", &number.p_, &number.q_);
        if (number.q_ == 0 || number.p_ == 0 || read < 2) {
            number.q_ = 1;
        }
        number.reduce();
        return is;
    }

    friend std::ostream& operator<<(std::ostream& os, const Rational& number) {
        if (number.p_ == 0) {
            std::cout << 0;
        } else if (number.q_ != 1) {
            std::cout << number.p_ << '/' << number.q_;
        } else {
            std::cout << number.p_;
        }
        return os;
    }


    friend bool operator<(const Rational& rOne, const Rational& rTwo) {
        return rOne.p_ * rTwo.q_ < rTwo.p_ * rOne.q_;
    }
    friend bool operator>(const Rational& rOne, const Rational& rTwo) {
        return rOne.p_ * rTwo.q_ > rTwo.p_ * rOne.q_;
    }
    friend bool operator==(const Rational& rOne, const Rational& rTwo) {
        return rOne.p_ * rTwo.q_ == rTwo.p_ * rOne.q_;
    }
    friend bool operator>=(const Rational& rOne, const Rational& rTwo) {
        return rOne.p_ * rTwo.q_ >= rTwo.p_ * rOne.q_;
    }
    friend bool operator<=(const Rational& rOne, const Rational& rTwo) {
        return rOne.p_ * rTwo.q_ <= rTwo.p_ * rOne.q_;
    }
    friend bool operator!=(const Rational& rOne, const Rational& rTwo) {
        return rOne.p_ * rTwo.q_ != rTwo.p_ * rOne.q_;
    }

    friend Rational operator+(const Rational& rOne, const Rational& rTwo) {
        Rational result(rOne.p_ * rTwo.q_ + rOne.q_ * rTwo.p_, rOne.q_ * rTwo.q_);
        result.reduce();
        return result;
    }
    friend Rational operator-(const Rational& rOne, const Rational& rTwo) {
        Rational result(rOne.p_ * rTwo.q_ - rOne.q_ * rTwo.p_, rOne.q_ * rTwo.q_);
        result.reduce();
        return result;
    }
    friend Rational operator*(const Rational& rOne, const Rational& rTwo) {
        return Rational(rOne.p_ * rTwo.p_, rOne.q_ * rTwo.q_);
    }
    friend Rational operator/(const Rational& rOne, const Rational& rTwo) {
        if (rTwo == 0) {
            throw RationalDivisionByZero();
        }
        return Rational(rOne.p_ * rTwo.q_, rOne.q_ * rTwo.p_);
    }

    Rational operator-() const {
        return Rational(-1 * p_, q_);
    }
    Rational operator+() const {
        return *this;
    }

    const Rational operator++(int) {
        this->p_ += q_;
        return Rational(this->p_ - this->q_, this->q_);
    }
    Rational& operator++() {
        return (*this += 1);
    }
    const Rational operator--(int) {
        this->p_ -= q_;
        return Rational(this->p_ + this->q_, this->q_);
    }
    Rational& operator--() {
        return (*this -= 1);
    }

    Rational& operator+=(const Rational& number) {
        return *this = (*this + number);
    }
    Rational& operator-=(const Rational& number) {
        return *this = (*this - number);
    }
    Rational& operator*=(const Rational& number) {
        return *this = (*this * number);
    }
    Rational& operator/=(const Rational& number) {
        return *this = (*this / number);
    }
};

//=================== main() ===============//

using namespace std;

int main() {
    int m, n, p, q;
    cin >> m >> n >> p >> q;

    Matrix<int> A(m, n), B(p, q);
    cin >> A >> B;


    //cout << A << B;
    A = A;
    //cout << A << B;
    try {
        cout << A + B * 2 - m * A << endl;
        cout << (A -= B += A *= 2) << endl;
        cout << (((A -= B) += A) *= 2) << endl;
    } catch (const MatrixWrongSizeError&) {
        cout << "A and B are of different size." << endl;
    }
    B = A;

    {
        Matrix<int> AA(A);
        Matrix<int> AAA(1, 1);
        AAA = A;
        cout << AA << endl;
        cout << (AAA += Matrix<int>(m, n)) + B << endl;
    }

    Rational r;
    cin >> r;
    Matrix<Rational> C(m, n), D(p, q);
    cin >> C >> D;
    try {
        cout << C * D << endl;
        cout << (C *= D) << endl;
        cout << C << endl;
    } catch (const MatrixWrongSizeError&) {
        cout << "C and D have not appropriate sizes for multiplication." << endl;
    }
    cout << C.getTransposed() * (r * C) << endl;
    cout << C.Transpose() << endl;
    try {
        (C(0, 0) *= 6) /= 3;
        cout << C(0, 0) << endl;
        cout << C(m, m) << endl;
    } catch (const MatrixIndexError&) {
        cout << "Index out of range." << endl;
    }

    {
        const Matrix<Rational>& rC = C;
        cout << rC << endl;
        cout << rC.getRowsNumber() << ' ' << rC.getColumnsNumber() << ' ' << rC(0, 0) << endl;
        cout << (C = C) * (Rational(1, 2) * rC).getTransposed() << endl;
    }
    return 0;
}
