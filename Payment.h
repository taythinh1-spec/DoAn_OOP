#ifndef PAYMENT_H
#define PAYMENT_H

class IPayment {
public:
    virtual void processPayment(double amount) = 0;
    virtual ~IPayment() {}
};

class CreditCardPayment : public IPayment {
public:
    void processPayment(double amount) override;
};

class MomoPayment : public IPayment {
public:
    void processPayment(double amount) override;
};

#endif
