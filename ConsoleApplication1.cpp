#include <iostream>
#include <string>
using namespace std;
class User {
protected: int id; string name;
public: User(int i, string n) : id(i), name(n) {} virtual ~User() {} virtual void displayRole() const = 0;
};
class Product {
protected: int id; string name; double price;
public: Product(int i, string n, double p) : id(i), name(n), price(p) {} virtual ~Product() {}
};
int main() { cout << "Khoi tao he thong class co ban!\n"; return 0; }
