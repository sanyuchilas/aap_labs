#include "linalg.h"
#include <iostream>
#include <iomanip>      // std::setw
#include <cmath>

bool compare_doubles(double a, double b, double epsilon = 1e-9) {
    return std::fabs(a - b) < epsilon;
}
namespace linalg {
    Matrix::Matrix () noexcept : m_cols(0), m_rows(0), m_ptr(nullptr) {}

    Matrix::~Matrix() {
        delete [] m_ptr;

        m_rows = 0;
        m_cols = 0;

        m_ptr = nullptr;
    }

    Matrix::Matrix(int rows) {
        m_rows = rows;
        m_cols = 1;

        m_ptr = new double[rows * 1];
    }

    Matrix::Matrix(int rows, int cols) {
        m_rows = rows;
        m_cols = cols;

        m_ptr = new double[rows * cols];
    }

    Matrix::Matrix(const Matrix& from) : Matrix(from.m_rows, from.m_cols) {
        for (int i = 0; i < m_rows * m_cols; i++) {
            m_ptr[i] = from.m_ptr[i];
        }
    }

    Matrix::Matrix(Matrix&& from) : Matrix(from) {
        from.m_cols = 0;
        from.m_rows = 0;

        delete [] m_ptr;
        
        m_ptr = nullptr;
    }
    
    template <> Matrix::Matrix(std::initializer_list<int> list) : Matrix(list.size(), 1) {
        int i = 0;

        for (auto el : list) {
            m_ptr[i] = el;
            i++;
        }
    }

    template <> Matrix::Matrix(std::initializer_list<std::initializer_list<int>> list) : Matrix(list.size(), list.begin()->size()) {
        int els_count = 0;
        int prev_col_size = list.begin()->size();

        for (auto row_el : list) {
            if (prev_col_size != row_el.size()) {
                throw std::runtime_error("Incorrect matrix.");
            }

            for (auto col_el : row_el) {
                m_ptr[els_count] = col_el;
                els_count++;
            }
        }
    }

    int Matrix::rows() const noexcept {
        return m_rows;
    }

    int Matrix::cols() const noexcept {
        return m_cols;
    }

    bool Matrix::empty() const noexcept {
        bool is_empty = (m_ptr == nullptr);
        return is_empty;
    }

    void Matrix::reshape(int rows, int cols) {
        if (rows * cols != m_rows * m_cols) {
            throw std::runtime_error("Matrix shouldn't change it's elements or element's count. Please, input other arguments.");
        }

        m_rows = rows;
        m_cols = cols;
    }
    
    std::ostream& operator << (std::ostream& out, const Matrix& from) {
        out << "My best matrix:" << std::endl;

        if (from.empty()) {
            return out << "| =( |" << std::endl;
        }

        for (int i = 0; i < from.rows(); i++) {
            out << "|";

            for (int j = 0; j < from.cols(); j++) {
                out << std::setw(5) << from(i + 1, j + 1) << " ";
            }

            out << "|\n";
        }
    }

    Matrix& Matrix::operator=(const Matrix& from) {
        m_cols = from.cols();
        m_rows = from.rows();

        m_ptr = new double[m_cols * m_rows];

        for (int i = 0; i < m_rows; i++) {
            for (int j = 0; j < m_cols; j++) {
                m_ptr[i * m_cols + j] = from.m_ptr[i * m_cols + j];
            }
        }

        return *this;
    }


    Matrix& Matrix::operator=(Matrix&& from) {
        m_cols = from.cols();
        m_rows = from.rows();

        m_ptr = new double[m_cols * m_rows];

        for (int i = 0; i < m_rows; i++) {
            for (int j = 0; j < m_cols; j++) {
                m_ptr[i * m_cols + j] = from.m_ptr[i * m_cols + j];
            }
        }

        from.m_cols = 0;
        from.m_rows = 0;

        delete [] from.m_ptr;

        from.m_ptr = nullptr;

        return *this;
    }

    double& Matrix::operator()(int row_m_i, int col_m_i) {
        if (row_m_i < 1 || row_m_i > m_rows || col_m_i < 1 || col_m_i > m_cols) {
            throw std::runtime_error("Cannot get element outside matrix range.");
        }

        return m_ptr[(row_m_i - 1) * m_cols + (col_m_i - 1)];
    }

    const double& Matrix::operator()(int row_m_i, int col_m_i) const {
       if (row_m_i < 1 || row_m_i > m_rows || col_m_i < 1 || col_m_i > m_cols) {
            throw std::runtime_error("Cannot get element outside matrix range.");
        }

        return m_ptr[(row_m_i - 1) * m_cols + (col_m_i - 1)];
    }

    Matrix operator+(const Matrix& left, const Matrix& right) {
        if (left.cols() != right.cols() || left.rows() != right.rows()) {
            throw std::runtime_error("Cannot made operation. Incorrect matrices for summing");
        }

        Matrix tmp = left;

        return tmp += right;
    }

    Matrix& Matrix::operator+=(const Matrix& right) {
        if (m_rows != right.rows() || m_cols != right.cols()) {
            throw std::runtime_error("Cannot made operation. Incorrect matrices for summing.");
        }

        for (int i = 0; i < m_rows; i++) {
            for (int j = 0; j < m_cols; j++) {
                m_ptr[i * m_cols + j] += right(i + 1, j + 1);
            }
        }

        return *this;
    }

     Matrix operator-(const Matrix& left, const Matrix& right) {
        if (left.cols() != right.cols() || left.rows() != right.rows()) {
            throw std::runtime_error("Cannot made operation. Incorrect matrices for subtracting");
        }

        Matrix tmp(left);

        return tmp -= right;
    }

    Matrix& Matrix::operator-=(const Matrix& right) {
        if (m_rows != right.rows() || m_cols != right.cols()) {
            throw std::runtime_error("Cannot made operation. Incorrect matrices for subtracting.");
        }

        for (int i = 0; i < m_rows; i++) {
            for (int j = 0; j < m_cols; j++) {
                m_ptr[i * m_cols + j] -= right(i + 1, j + 1);
            }
        }

        return *this;
    }

    Matrix operator*(const Matrix& left, const Matrix& right) {
        if (left.cols() != right.rows()) {
            throw std::runtime_error("Cannot made operation. Incorrect matrices for multiplying.");
        }

        Matrix tmp(left);

        return tmp *= right;
    }

    Matrix& Matrix::operator*=(const Matrix& right) {
        if (m_cols != right.rows()) {
            throw std::runtime_error("Cannot made operation. Incorrect matrices for multiplying.");
        }

        Matrix tmp(m_rows, right.cols());

        for (int i = 0; i < m_rows; i++) {
            for (int j = 0; j < right.cols(); j++) {
                double s = 0;

                for (int k = 0; k < m_cols; k++) {
                    s += m_ptr[i * m_rows + k] * right(k + 1, j + 1);
                }

                tmp(i + 1, j + 1) = s;
            }
        }

        *this = tmp;

        return *this;
    }

    Matrix operator*(const Matrix& left, double right) {
        Matrix tmp(left);

        return tmp *= right;
    }

    Matrix operator*(double left, const Matrix& right) {
        Matrix tmp(right);
        
        return tmp *= left;
    }

    Matrix& Matrix::operator*=(double right) {
 
        for (int i = 0; i < m_rows; i++) {
            for (int j = 0; j < m_cols; j++) {
                m_ptr[i * m_cols + j] *= right;
            }
        }
        
        return *this;
    }

    bool operator==(const Matrix& left, const Matrix& right) {
        if (left.cols() != right.cols() || right.rows() != left.rows()) {
            throw std::runtime_error("Cannot compare matrices with different sized.");
        }

        for (int i = 0; i < left.rows(); i++) {
            for (int j = 0; j < left.cols(); j++) {
                if (!compare_doubles(right(i + 1, j + 1), left(i + 1, j + 1))) {
                    return false;
                }
            }
        }

        return true;
    }

    bool operator!=(const Matrix& left, const Matrix& right) {
        return !(left==right);
    }

    double Matrix::norm() const {
        if (m_rows == 0) {
            throw std::runtime_error("Incorrect shape to count norm");
        }

        double sq_sum = 0;

        for (int el = 0; el < m_rows * m_cols; el++) {
            sq_sum += pow(m_ptr[el], 2);
        }

        return sqrt(sq_sum);
    }

    double Matrix::trace() const {
        if (m_cols != m_rows || m_rows == 0) {
            throw std::runtime_error("Incorrect shape to count trace");
        }

        double tr = 0;

        for (int el = 0; el < m_rows; el++) {
            tr += m_ptr[el * m_cols + el];
        }

        return tr;
    }

    double Matrix::det() const {
        if (m_cols != m_rows || m_rows == 0) {
            throw std::runtime_error("Incorrect shape to count determinant");
        }

        double d = 0;

        if (m_rows == 1) {
            return m_ptr[0];
        }

        for (int el = 0; el < m_rows; el++) {
            d += m_ptr[el] * pow(-1, el) * (*this).minor(0, el);
        }

        return d;
    }

    double Matrix::minor(int i, int j) const {
        if (m_cols != m_rows || m_rows == 0) {
            throw std::runtime_error("Incorrect shape to count minor");
        }

        return crop_matrix(i, j).det();
    }

    Matrix Matrix::crop_matrix(int row, int col) const {
        if (row > m_rows || col > m_cols) {
            throw std::runtime_error("Incorrect dimension of element");
        }

        Matrix tmp(m_rows - 1, m_cols - 1);

        for (int i= 0; i < m_rows - 1; i++) {
            for (int j = 0; j < m_cols - 1; j++) {
                tmp(i + 1, j + 1) = m_ptr[(i + (row <= i)) * m_cols + (j + (m_cols <= j))];
            }
        }

        return tmp;
    }
} 
