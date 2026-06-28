#include "User.h"
#include <iostream>

using namespace std;

User::User(int _id, string _name, string _email) : id(_id), name(_name), email(_email) {}
User::~User() {}

int User::getId() const { return id; }
string User::getName() const { return name; }
string User::getEmail() const { return email; }
void User::setName(string _name) { name = _name; }

Customer::Customer(int _id, string _name, string _email, string _address)
    : User(_id, _name, _email), address(_address) {
}
string Customer::getAddress() const { return address; }
void Customer::displayRole() const {
    cout << "Vai tro: Khach hang - Ten: " << getName() << endl;
}

Admin::Admin(int _id, string _name, string _email, int _level)
    : User(_id, _name, _email), manageLevel(_level) {
}
int Admin::getManageLevel() const { return manageLevel; }
void Admin::displayRole() const {
    cout << "Vai tro: Quan tri vien - Ten: " << getName() << endl;
}