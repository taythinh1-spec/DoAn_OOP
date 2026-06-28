#include "Product.h"
#include <iostream>
#include <iomanip>

using namespace std;

Product::Product(int _id, string _name, double _price) : productId(_id), productName(_name), price(_price) {}
Product::~Product() {}

int Product::getId() const { return productId; }
string Product::getName() const { return productName; }
double Product::getPrice() const { return price; }
void Product::displayDetails() const {
    cout << fixed << setprecision(0);
    cout << "ID: " << productId << " | " << productName << " | Gia: " << price << " VND";
}

Electronics::Electronics(int _id, string _name, double _price, int _warranty)
    : Product(_id, _name, _price), warrantyPeriod(_warranty) {
}
void Electronics::displayDetails() const {
    Product::displayDetails();
    cout << " | Bao hanh: " << warrantyPeriod << " thang (Do dien tu)" << endl;
}

Clothing::Clothing(int _id, string _name, double _price, string _size)
    : Product(_id, _name, _price), size(_size) {
}
void Clothing::displayDetails() const {
    Product::displayDetails();
    cout << " | Size: " << size << " (Thoi trang)" << endl;
}