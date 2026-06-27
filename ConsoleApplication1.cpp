#include <iostream>
class IPayment { public: virtual void processPayment(double amount) = 0; virtual ~IPayment() {} };
class MomoPayment : public IPayment {
public: void processPayment(double amount) override { std::cout << "Thanh toan Momo\n"; }
};
class OrderItem { void* product; int qty; };
int main() { std::cout << "Them IPayment va OrderItem (Raw pointer)\n"; return 0; }
