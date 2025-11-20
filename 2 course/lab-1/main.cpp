#include "linalg.h"
#include <iostream>

int main() {
    linalg::Matrix m;

    std::cout << "Task 1: 1: m_ptr, m_rows, m_cols, .rows(), .cols(), .empty().\n\n";

    m.rows();           // garbage.
    m.cols();           // garbage.
    m.empty();          // grabage.

    std::cout << "\n===\n\n";

    std::cout << "Taks 2: 1: Matrix(), Matrix(rows), Matrix(rows, cols).\n\n";

    linalg::Matrix m1;

    m1.rows();          // 0.
    m1.cols();          // 0.
    m1.empty();         // true.

    std::cout << "\n\n";

    linalg::Matrix m2(3);

    m2.rows();          // 3.
    m2.cols();          // 1.
    m2.empty();         // false.

    std::cout << "\n\n";

    linalg::Matrix m3 = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

    m3.rows();          // 3.
    m3.cols();          // 4.
    m3.empty();         // false.

     std::cout << "\n===\n\n";

    std::cout << "Task 1: 2: .reshape() with std::runtime_error.\n\n";

    m3.reshape(2, 6);   // OK.

    m3.rows();          // 2.
    m3.cols();          // 6.

    std::cout << "\n\n";

    try {
        m3.reshape(2, 5);
    } catch(std::runtime_error err) {
        std::cout << "New rows count: 2\nNew cols count: 5\n"; 
        std::cout << "Run time error: " << err.what() << std::endl;
    }

    std::cout << "\n===\n\n";

    std::cout << "Task 2: 2: copy and movement constructors, initializer_list.\n\n";

    linalg::Matrix m4(m3);

    m3(1, 1) = 0;

    std::cout << m3;
    std::cout << m4;

    std::cout << "\n\n";

    linalg::Matrix m5(std::move(m3));

    m5.rows();
    m5.cols();

    m3.rows();
    m3.cols();

    std::cout << "\n\n";

    linalg::Matrix m6 = {{1, 2, 3}, {4, 5, 6}};

    m6.rows();
    m6.cols();

    std::cout << "\n\n";

    try {
        linalg::Matrix m7 = {{1, 2}, {3, 4, 5, 6}};
    } catch (std::runtime_error err) {
        std::cout << err.what() << std::endl;
    }

    std::cout << "\n\n";

    linalg::Matrix m7 = {{1}, {2}};

    m7.rows();
    m7.cols();

    std::cout << "Tasks 3-8.\n\n";

    std::cout << m7;

    std::cout << m;

    std::cout << m6;

    m7 = m6;

    std::cout << m7;

    m7 = linalg::Matrix{1, 2, 3};

    std::cout << m7;

    m7(2, 1) = 10;

    std::cout << m7;

    const linalg::Matrix m8 = {1, 2, 3};
    linalg::Matrix m9 = {1, 2, 3};
    linalg::Matrix m10 = {{1, 2, 3}};
    linalg::Matrix m11 = {{2, 2}, {2, 2}};

    std::cout << m10;
    std::cout << m9;

    std::cout << (m9 + m8 - m7);
    std::cout << (m9 *= m10);

    std::cout << m11 * m11;

    std::cout << (m11 *= 0.5);

    std::cout << (m11 * 2);

    linalg::Matrix m12 = {1, 2, 3};
    linalg::Matrix m13 = {1, 2, 3};

    std::cout << (m12 == m13) << std::endl;

    m13(3, 1) = 1;

    std::cout << (m12 == m13) << std::endl; 
    std::cout << (m12 != m13);

    std::cout << m11;
    std::cout << "Det: " << m11.det() << "\n";
    std::cout << "Trace: " << m11.trace() << "\n";
    std::cout << "Norm: " << m11.norm() << "\n";

    return 0;
}