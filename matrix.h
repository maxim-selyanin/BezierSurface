#pragma once
#include <type_traits>
#include <utility>

template<typename T>
using typecheck = std::enable_if_t<
std::is_integral_v<T>
|| std::is_floating_point_v<T>
>;

template<typename T, std::size_t row, std::size_t column, typename = typecheck<T>>
class matrix
{
    T data[row*column];
    std::size_t size() const {return row*column;}

public:
    matrix();
    matrix(std::initializer_list<T>);

    T *operator[](std::size_t);
    const T *operator[](std::size_t) const;
};

template<typename T, std::size_t row, std::size_t column, typename T1>
matrix<T, row, column, T1>::matrix() {
    for (std::size_t i = 0; i < this->size(); ++i) {
        data[i] = T();
    }
}

template<typename T, std::size_t row, std::size_t column, typename T1>
matrix<T, row, column, T1>::matrix(std::initializer_list<T> l) {
    for (std::size_t i = 0; i < this->size() && i < l.size(); ++i) {
        data[i] = *(l.begin() + i);
    }
    for (std::size_t i = l.size(); i < this->size(); ++i) {
        data[i] = T();
    }
}

template<typename T, std::size_t row, std::size_t column, typename T1>
T *matrix<T, row, column, T1>::operator[](std::size_t r) {
    return data + r*column;
}

template<typename T, std::size_t row, std::size_t column, typename T1>
const T *matrix<T, row, column, T1>::operator[](std::size_t r) const {
    return data + r*column;
}

template<typename T, std::size_t row, std::size_t column, typename T1>
matrix<T, row, column, T1> operator+(const matrix<T, row, column, T1> &m1,
                                     const matrix<T, row, column, T1> &m2) {
    matrix<T, row, column> m;
    for (std::size_t str = 0; str < row; ++str) {
        for (std::size_t cln = 0; cln < column; ++cln) {
            m[str][cln] = m1[str][cln] + m2[str][cln];
        }
    }
    return m;
}

template<typename T, std::size_t row, std::size_t column, typename T1>
matrix<T, row, column, T1> operator-(const matrix<T, row, column, T1> &m1,
                                     const matrix<T, row, column, T1> &m2) {
    matrix<T, row, column> m;
    for (std::size_t str = 0; str < row; ++str) {
        for (std::size_t cln = 0; cln < column; ++cln) {
            m[str][cln] = m1[str][cln] - m2[str][cln];
        }
    }
    return m;
}

template<typename T, std::size_t row1, std::size_t column1row2, std::size_t column2, typename T1>
matrix<T, row1, column2, T1> operator*(const matrix<T, row1, column1row2, T1> &m1,
                                       const matrix<T, column1row2, column2, T1> &m2) {
    matrix<T, row1, column2> m;
    T s;
    for (std::size_t str = 0; str < row1; ++str) {
        for (std::size_t cln = 0; cln < column2; ++cln) {
            s = 0;
            for (std::size_t i = 0; i < column1row2; ++i) {
                s += m1[str][i]*m2[i][cln];
            }
            m[str][cln] = s;
        }
    }
    return m;
}

template<typename T, std::size_t row, std::size_t column, typename T1>
matrix<T, row, column, T1> operator*(const matrix<T, row, column, T1> &m, T a) {
    matrix<T, row, column> result;
    for (std::size_t str = 0; str < row; ++str) {
        for (std::size_t cl = 0; cl < column; ++cl) {
            result[str][cl] = m[str][cl] * a;
        }
    }
    return result;
}

template<typename T, std::size_t row, std::size_t column, typename T1>
matrix<T, row, column, T1> operator/(const matrix<T, row, column, T1> &m, T a) {
    matrix<T, row, column> result;
    for (std::size_t str = 0; str < row; ++str) {
        for (std::size_t cl = 0; cl < column; ++cl) {
            result[str][cl] = m[str][cl] / a;
        }
    }
    return result;
}
