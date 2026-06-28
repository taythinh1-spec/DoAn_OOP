#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H
#include <vector>
#include <memory>
#include "Product.h"
#include "DiscountCoupon.h"

class OrderItem {
private:
    std::shared_ptr<Product> product;
    int quantity;
public:
    OrderItem(std::shared_ptr<Product> _product, int _quantity);
    std::shared_ptr<Product> getProduct() const;
    int getQuantity() const;
    double getSubTotal() const;
};

class ShoppingCart {
private:
    std::vector<OrderItem> items;
public:
    void addItem(std::shared_ptr<Product> product, int quantity);
    void displayCart() const;
    double calculateTotal(const DiscountCoupon* coupon = nullptr) const;
    void clearCart();
    bool isEmpty() const;
};

#endif
