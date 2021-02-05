/*
Разработать шаблонный класс квадратной матрицы SquareMatrix, наследованный от Matrix, удовлетворяющий требованиям:
• Класс можно параметризовать любым типом, реализующим сложение, вычитание, умножение и деление.
• Обеспечить конструктор, принимающий размер матрицы.
• Метод getSize().
• Операции сложения, умножения, вычитания над Matrix должны возвращать Matrix, операции над SquareMatrix должны возвращать SquareMatrix. Если в операции участвуют Matrix и SquareMatrix, результат должен быть Matrix.
• Реализовать метод обращения квадратных матриц в двух вариантах: мутирующем (invert) с возвратом ссылки на объект и немутирующем (getInverse) с возвратом нового объекта.
• Нахождение детерминанта и следа.
• При попытке найти обратную матрицу для вырожденной должно генерироваться исключение MatrixIsDegenerateError.
• Определить все методы, операции и дополнительные классы так, чтобы предложенный тестирующий код выводил ожидаемый результат в соответствии с общепринятой семантикой.
Ссылка на код: square_matrix.cpp (main function)
Input format
В первой строке дано 3 целых числа m, n, p и одно рациональное число r.
Далее во входном файле идет матрица с рациональными числами размеров m x n
Далее во входном файле идет квадратная матрица с рациональными числами размера p x p
Все числа во входном файле не превосходят по модулю 10.
Для понимания смотрите примеры.
Output format
Результат работы square_matrix.cpp при правильно реализованных методах класса.
*/

//Coded by Artur Kulapin

#include <iostream>
#include <cstdlib>
#include <exception>


class MatrixWrongSizeError : public std::exception {
    const char* what() const noexcept override {
        return "Matrix's sizes don't fit to make the operation";
    }
};

class MatrixIndexError : public std::exception {
    const char* what() const noexcept override {
        return "You tried to get an element with incorrect pair of index";
    }
};


class MatrixIsDegenerateError : public std::exception {
    const char* what() const noexcept override {
        return "Matrix's determinant is zero - it's bad idea to invert it";
    }
};


// non-specified functions to get "zero" and "one" of type T

template <typename T> T getZero() {
    return T(0);
}

template <typename T> T getOne() {
    return T(1);
}

//=============== Matrix class ===============//

template <typename T>
class Matrix {
protected:
    int height_ = 0;
    T** matrixField_;

    int width_ = 0;
public:
    Matrix<T>() = default;
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
    template <typename M, typename U>
    friend Matrix<M> operator*(const U& scalar, const Matrix<M>& rmx);
    template <typename M, typename U>
    friend Matrix<M> operator*(const Matrix<M>& rmx, const U& scalar);

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

    virtual void ClearMatrix() {
        for (int i = 0; i < height_; ++i) {
            delete[] matrixField_[i];
        }
        delete[] matrixField_;
    }
};


//=============== SquareMatrix class ===============//

template <typename T>
class SquareMatrix : public Matrix<T> {


public:
    SquareMatrix<T>(const Matrix<T>& other);
    SquareMatrix<T>(const int size);
    SquareMatrix<T>& operator=(const SquareMatrix<T>& other) {
        if (other.matrixField_ != this ->matrixField_) {
            this->ClearMatrix();
            this->width_ = other.width_;
            this->height_ = other.height_;
            this->matrixField_ = new T*[this->height_];
            for (int i = 0; i < this->height_; ++i) {
                this->matrixField_[i] = new T[this->width_];
            }
            for (int i = 0; i < this->height_; ++i) {
                for (int j = 0; j < this->width_; ++j) {
                    this->matrixField_[i][j] = other(i, j);
                }
            }
        }
        return *this;
    }

    T getTrace() const;
    T getDeterminant() const;

    int getSize() const;

    SquareMatrix& invert();
    SquareMatrix getInverse() const;

    SquareMatrix& Transpose();
    SquareMatrix getTransposed();

    template<typename M>
    friend SquareMatrix<M> operator+(const SquareMatrix<M> &lmx, const SquareMatrix<M> &rmx);
    template<typename M>
    friend SquareMatrix<M> operator-(const SquareMatrix<M> &lmx, const SquareMatrix<M> &rmx);
    template<typename M>
    friend SquareMatrix<M> operator*(const SquareMatrix<M> &lmx, const SquareMatrix<M> &rmx);

    template<typename M, typename U>
    friend SquareMatrix<M> operator*(const U& scalar, const SquareMatrix<M> &rmx);
    template<typename M, typename U>
    friend SquareMatrix<M> operator*(const SquareMatrix<M> &lmx, const U& scalar);

    template<typename M, typename U>
    friend Matrix<M> operator*(const SquareMatrix<M> &lmx, const Matrix<U> &rmx);
    template<typename M, typename U>
    friend Matrix<M> operator*(const Matrix<M> &lmx, const SquareMatrix<U> &rmx);

    template <typename U>
    friend void GaussAlgorithm(SquareMatrix<U>& matrix, bool& isDetZero, int& stringSwapsCounter);
    template <typename U, typename M>
    friend void CreateInvert(SquareMatrix<M>& ematrix, SquareMatrix<U>& matrix, bool& isDetZero);
};

template <typename T>
int SquareMatrix<T>::getSize() const {
    return this->getColumnsNumber();
}

template <typename T>
SquareMatrix<T>& SquareMatrix<T>::Transpose() {
    return (Matrix<T>(*this).Transpose());
}
template <typename T>
SquareMatrix<T> SquareMatrix<T>::getTransposed() {
    return static_cast<SquareMatrix<T>>(Matrix<T>(*this).Transpose());
}

template <typename T>
SquareMatrix<T>::SquareMatrix(const int size) {
    this->width_ = size;
    this->height_ = size;
    this->matrixField_ = new T*[size];
    for (int i = 0; i < size; ++i) {
        this->matrixField_[i] = new T[size];
    }
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            (*this)(i, j) = getZero<T>();
        }
    }
}
template <typename T>
SquareMatrix<T>::SquareMatrix(const Matrix<T>& matrix) {
    int size = matrix.getColumnsNumber();
    this->height_ = this->width_ = size;
    this->matrixField_ = new T*[size];
    for (int i = 0; i < size; ++i) {
        this->matrixField_[i] = new T[size];
    }
    for (int i = 0; i < this->width_; ++i) {
        for (int j = 0; j < this->width_; ++j) {
            (*this)(i, j) = matrix(i, j);
        }
    }
}

template <typename T>
T SquareMatrix<T>::getTrace() const {
    T trace = 0;
    for (int i = 0; i < this->width_; ++i) {
        trace += (*this)(i, i);
    }
    return trace;
}

template <typename T>
SquareMatrix<T>& SquareMatrix<T>::invert() {
    bool isDetZero = false;
    SquareMatrix<T> matrix(*this);
    SquareMatrix<T> eMatrix(this->getSize());
    for (int i = 0; i < eMatrix.width_; ++i) {
        for (int j = 0; j < eMatrix.width_; ++j) {
            if (i == j) {
                eMatrix(i, j) = 1;
            } else {
                eMatrix(i, j) = 0;
            }
        }
    }
    CreateInvert(eMatrix, matrix, isDetZero);
    *this = eMatrix;
    if (isDetZero) {
        throw MatrixIsDegenerateError();
    } else {
        return *this;
    }
}
template <typename T>
SquareMatrix<T> SquareMatrix<T>::getInverse() const {
    bool isDetZero = false;
    SquareMatrix<T> matrix(*this);
    SquareMatrix<T> eMatrix(this->getSize());
    for (int i = 0; i < eMatrix.width_; ++i) {
        for (int j = 0; j < eMatrix.width_; ++j) {
            if (i == j) {
                eMatrix(i, j) = getOne<T>();
            } else {
                eMatrix(i, j) = getZero<T>();
            }
        }
    }
    //std::cout << eMatrix<< std::endl;
    CreateInvert(eMatrix, matrix, isDetZero);
    if (isDetZero) {
        throw MatrixIsDegenerateError();
    } else {
        return eMatrix;
    }
}

template <typename T>
T SquareMatrix<T>::getDeterminant() const {
    bool isDetZero = false;
    T Det = 1;
    SquareMatrix<T> matrix(*this);
    int stringSwapsCounter = 0;
    GaussAlgorithm(matrix, isDetZero, stringSwapsCounter);
    if (isDetZero) {
        return 0;
    } else {
        for (int i = 0; i < this->getSize(); ++i) {
            Det *= matrix(i, i);
        }
        return Det * (stringSwapsCounter % 2 == 0 ? 1 : -1);
    }
}


template <typename U, typename T>
void CreateInvert(SquareMatrix<T>& eMatrix, SquareMatrix<U>& matrix, bool& isDetZero) {
    int size = matrix.getSize();

    bool isThereZeroSubMatrix = true;
    for (int i = 0; i < size; ++i) {
        if (matrix(i, i) != 0) {
            for (int j = i + 1; j < size; ++j) {
                if (matrix(j, i) != 0) {
                    T temp = matrix(j, i) / matrix(i, i);
                    for (int k = 0; k < size; ++k) {
                        matrix(j, k) -= matrix(i, k) * temp;
                        eMatrix(j, k) -= eMatrix(i, k) * temp;
                    }
                }
            }
        } else {
            isThereZeroSubMatrix = true;
            for (int j = i + 1; j < size; ++j) {
                if (matrix(j, i) != 0) {
                    std::swap(matrix.matrixField_[i], matrix.matrixField_[j]);
                    std::swap(eMatrix.matrixField_[i], eMatrix.matrixField_[j]);
                    isThereZeroSubMatrix = false;
                    break;
                }
            }
            if (i < size - 1) {
                --i;
            }
            if (isThereZeroSubMatrix) {
                isDetZero = true;
                break;
            }
        }
    }

    if (!isDetZero) {
        for (int i = size - 1; i >= 0; --i) {
            for (int j = i - 1; j >= 0; --j) {
                T temp = matrix(j, i) / matrix(i, i);
                for (int k = size - 1; k >= 0; --k) {
                    matrix(j, k) -= matrix(i, k) * temp;
                    eMatrix(j, k) -= eMatrix(i, k) * temp;
                }
            }
        }

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                eMatrix(i, j) /= matrix(i, i);
            }
            matrix(i, i) = 1;
        }
    }

}
template <typename T>
void GaussAlgorithm(SquareMatrix<T>& matrix, bool& isDetZero, int& stringSwapsCounter) {
    int size = matrix.getSize();

    bool isThereZeroSubMatrix = true;
    for (int i = 0; i < size; ++i) {
        if (matrix(i, i) != 0) {
            for (int j = i + 1; j < size; ++j) {
                if (matrix(j, i) != 0) {
                    T temp = matrix(j, i) / matrix(i, i);
                    for (int k = i; k < size; ++k) {
                        matrix(j, k) -= matrix(i, k) * temp;
                    }
                }
            }
        } else {
            isThereZeroSubMatrix = true;
            for (int j = i + 1; j < size; ++j) {
                if (matrix(j, i) != 0) {
                    std::swap(matrix.matrixField_[i], matrix.matrixField_[j]);
                    ++stringSwapsCounter;
                    isThereZeroSubMatrix = false;
                    break;
                }
            }
            if (i < size - 1) {
                --i;
            }
            if (isThereZeroSubMatrix) {
                isDetZero = true;
                break;
            }
        }
    }
}



// this works also for SquareMatrix as this does not rely on any square-specific features

//================ class Rational ===============//

class RationalDivisionByZero : public std::exception {
    const char* what() const noexcept override {
        return "Aaaaaaa";
    }
};

class Rational {
private:
    long long p_, q_;

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
        int reduceNumber = gcd(abs(p_), abs(q_));
        p_ /= reduceNumber;
        q_ /= reduceNumber;
    }

public:
    Rational(const int p, const int q) : p_(p), q_(q) {
        this->reduce();
    }
    Rational(const int p) : p_(p), q_(1) {}
    Rational() : p_(0), q_(1) {}

    int getNumerator() const {
        return p_;
    }
    int getDenominator() const {
        return q_;
    }

    friend std::istream& operator>>(std::istream& is, Rational& number) {
        char frac;
        int read = scanf("%lld/%lld", &number.p_, &number.q_);
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
    int m, n, p;
    Rational r;
    cin >> m >> n >> p >> r;

    Matrix<Rational> A(m, n);
    SquareMatrix<Rational> S(p);
    cin >> A >> S;

    try {
        cout << (A * S) * A.getTransposed() << endl;
    } catch (const MatrixWrongSizeError&) {
        cout << "A and S have not appropriate sizes for multiplication." << endl;
    }

    cout << (r * (S = S) * S).getSize() << endl;

    SquareMatrix<Rational> P(S);

    cout << (P * (S + S - 3 * P)).getDeterminant() << endl;

    const SquareMatrix<Rational>& rS = S;

    cout << rS.getSize() << ' ' << rS.getDeterminant() << ' ' << rS.getTrace() << endl;
    cout << (S = S) * (S + rS) << endl;
    cout << (S *= S) << endl;

    try {
        cout << rS.getInverse() << endl;
        cout << P.invert().getTransposed().getDeterminant() << endl;
        cout << P << endl;
    } catch (const MatrixIsDegenerateError&) {
        cout << "Cannot inverse matrix." << endl;
    }

    return 0;
}

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
            matrixField_[i][j] = 0;
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
template <typename T, typename U>
Matrix<T> operator*(const U& scalar, const Matrix<T> &lmx) {
    Matrix<T> newMatrix(lmx.height_, lmx.width_);
    for (int i = 0; i < newMatrix.height_; ++i) {
        for (int j = 0; j < newMatrix.width_; ++j) {
            newMatrix.matrixField_[i][j] = lmx.matrixField_[i][j] * scalar;
        }
    }
    return newMatrix;
}

template <typename T, typename U>
Matrix<T> operator*(const Matrix<T> &lmx, const U& scalar) {
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
    if (lmx.width_ != rmx.height_) {
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

template <typename T>
SquareMatrix<T> operator+(const SquareMatrix<T> &lmx, const SquareMatrix<T> &rmx) {
    return static_cast<SquareMatrix<T>>(Matrix<T>(lmx) + Matrix<T>(rmx));
}
template <typename T>
SquareMatrix<T> operator-(const SquareMatrix<T> &lmx, const SquareMatrix<T> &rmx) {
    return static_cast<SquareMatrix<T>>(Matrix<T>(lmx) - Matrix<T>(rmx));
}
template <typename T>
SquareMatrix<T> operator*(const SquareMatrix<T> &lmx, const SquareMatrix<T> &rmx) {
    return static_cast<SquareMatrix<T>>(Matrix<T>(lmx) * Matrix<T>(rmx));
}

template <typename T, typename M>
SquareMatrix<T> operator*(const SquareMatrix<T> &lmx, const M& value) {
    const Matrix<T>& a = lmx;
    return static_cast<SquareMatrix<T>>(a * value);
}
template <typename T, typename M>
SquareMatrix<T> operator*(const M& value, const SquareMatrix<T> &lmx) {
    const Matrix<T>& a = lmx;
    return static_cast<SquareMatrix<T>>(a * value);
}

template <typename T, typename M>
Matrix<T> operator*(const SquareMatrix<T>& lmx, const Matrix<M>& rmx) {
    return lmx * Matrix<M>(lmx);
}
template <typename T, typename M>
Matrix<T> operator*(const Matrix<T>& lmx, const SquareMatrix<M>& rmx) {
    return lmx * Matrix<M>(rmx);
}