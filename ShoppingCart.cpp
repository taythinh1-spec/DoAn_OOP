#include "ShoppingCart.h"
#include <iostream>
#include <iomanip>

using namespace std;

OrderItem::OrderItem(shared_ptr<Product> _product, int _quantity) : product(_product), quantity(_quantity) {}
shared_ptr<Product> OrderItem::getProduct() const { return product; }
int OrderItem::getQuantity() const { return quantity; }
double OrderItem::getSubTotal() const { return product->getPrice() * quantity; }

void ShoppingCart::addItem(shared_ptr<Product> product, int quantity) {
    for (auto& item : items) {
        if (item.getProduct()->getId() == product->getId()) {
            cout << "=> San pham da co trong gio! Vui long them moi.\n";
            return;
        }
    }
    items.push_back(OrderItem(product, quantity));
    cout << "=> Da them " << quantity << "x [" << product->getName() << "] vao gio hang!\n";
}

void ShoppingCart::displayCart() const {
    if (items.empty()) {
        cout << "=> Gio hang dang trong!\n";
        return;
    }
    cout << "\n--- CHI TIET GIO HANG ---\n";
    cout << fixed << setprecision(0);
    for (const auto& item : items) {
        cout << "- " << item.getProduct()->getName()
            << " (SL: " << item.getQuantity()
            << ") -> Thanh tien: " << item.getSubTotal() << " VND\n";
    }
    cout << "------------------------\n";
}

double ShoppingCart::calculateTotal(const DiscountCoupon* coupon) const {
    double total = 0;
    for (const auto& item : items) {
        total += item.getSubTotal();
    }
    if (coupon != nullptr) {
        total = coupon->apply(total);
    }
    return total;
}

void ShoppingCart::clearCart() { items.clear(); }
bool ShoppingCart::isEmpty() const { return items.empty(); }