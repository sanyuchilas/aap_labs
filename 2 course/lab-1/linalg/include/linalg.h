#pragma once

#include <initializer_list>
#include <ostream>

namespace linalg {

    class Matrix {
        public: // constructors and public methods.
            Matrix() noexcept;
            ~Matrix();

            Matrix(int rows);
            Matrix(int rows, int cols);

            Matrix(const Matrix& from);

            // && - rvalue reference.
            Matrix(Matrix&& from);

            template <typename T> Matrix(std::initializer_list<T> list);
            template <typename T> Matrix(std::initializer_list<std::initializer_list<T>> list);

            int rows() const noexcept;
            int cols() const noexcept;
            bool empty() const noexcept;
            void reshape(int rows, int cols);

            double trace() const;
            double det() const;
            double norm() const;
            double minor(int i, int j) const;

            Matrix crop_matrix(int i, int j) const;

        public: // operators.
            Matrix& operator=(const Matrix& from);
            Matrix& operator=(Matrix&& from);

            // m_i = matrix indexation.
            double& operator()(int row_m_i, int col_m_i);
            const double& operator()(int row_m_i, int col_m_i) const;

            Matrix& operator+=(const Matrix& right);
            Matrix& operator-=(const Matrix& right);

            Matrix& operator*=(const Matrix& right);

            Matrix& operator*=(double right);

        private: // members.
            double* m_ptr;
            int m_rows;
            int m_cols;

    };  

    std::ostream& operator << (std::ostream& out, const Matrix& from);

    Matrix operator+(const Matrix& left, const Matrix& right);
    Matrix operator-(const Matrix& left, const Matrix& right);

    Matrix operator*(const Matrix& left, const Matrix& right);
    Matrix operator*(double left, const Matrix& right);
    Matrix operator*(const Matrix& left, double right);

    bool operator==(const Matrix& left, const Matrix& right);
    bool operator!=(const Matrix& left, const Matrix& right);
}
