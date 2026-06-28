#ifndef DISCOUNTCOUPON_H
#define DISCOUNTCOUPON_H
#include <string>

class DiscountCoupon {
private:
    std::string code;
    double discountPercent;
    bool active;

public:
    DiscountCoupon(std::string _code, double _percent);
    bool isValid(const std::string& inputCode) const;
    double apply(double originalPrice) const;
    double getPercent() const;
    std::string getCode() const;
    void deactivate();
};

#endif
