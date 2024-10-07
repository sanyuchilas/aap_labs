#include <iostream>


int main() {
    int arr[5] = { 1, 2, 3, 4, 5 };
    *(*(&arr + 1) - 1) = 10;

    std::cout << (*(&arr + 1) - 1);
}