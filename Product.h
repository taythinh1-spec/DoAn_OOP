#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>

class Product {
private:
    int productId;
    std::string productName;
    double price;

public:
    Product(int _id, std::string _name, double _price);
    virtual ~Product();

    int getId() const;
    std::string getName() const;
    double getPrice() const;
    virtual void displayDetails() const;
};

class Electronics : public Product {
private:
    int warrantyPeriod;
public:
    Electronics(int _id, std::string _name, double _price, int _warranty);
    void displayDetails() const override;
};

class Clothing : public Product {
private:
    std::string size;
public:
    Clothing(int _id, std::string _name, double _price, std::string _size);
    void displayDetails() const override;
};

#endif
