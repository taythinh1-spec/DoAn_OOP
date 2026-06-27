#include <iostream>
#include <memory>
class IPayment { public: virtual void processPayment(double amount) = 0; virtual ~IPayment() {} };
class OrderItem { std::shared_ptr<void> product; int qty; };
int main() { std::unique_ptr<IPayment> payment; std::cout << "Fix leak memory!\n"; return 0; }
