#include "DiscountCoupon.h"

using namespace std;

DiscountCoupon::DiscountCoupon(string _code, double _percent) : code(_code), discountPercent(_percent), active(true) {}
bool DiscountCoupon::isValid(const string& inputCode) const {
    return active && (code == inputCode);
}
double DiscountCoupon::apply(double originalPrice) const {
    return originalPrice * (1.0 - discountPercent / 100.0);
}
double DiscountCoupon::getPercent() const { return discountPercent; }
string DiscountCoupon::getCode() const { return code; }
void DiscountCoupon::deactivate() { active = false; }