#include <iostream>

class MyClass{
  // static void print() { std::cout << s_value; }
  private:
    inline static int s_value;
};

// struct MyStruct {
//   void operator &() {
//     std::cout << "Operator &!\n";
//   }
// };

// int print_address(const MyStruct& obj) {
//   std::cout << &obj;
// }

int MyClass::s_value{1};

int main() {  
  // MyStruct obj;
  // print_address(obj);
  // &obj;

  // MyClass obj();
  // MyClass::print();

  std::cout << MyClass::s_value;
}