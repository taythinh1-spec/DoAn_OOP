#ifndef USER_H
#define USER_H
#include <string>

class User {
private:
    int id;
    std::string name;
    std::string email;

public:
    User(int _id, std::string _name, std::string _email);
    virtual ~User();

    int getId() const;
    std::string getName() const;
    std::string getEmail() const;
    void setName(std::string _name);

    virtual void displayRole() const = 0;
};

class Customer : public User {
private:
    std::string address;
public:
    Customer(int _id, std::string _name, std::string _email, std::string _address);
    std::string getAddress() const;
    void displayRole() const override;
};

class Admin : public User {
private:
    int manageLevel;
public:
    Admin(int _id, std::string _name, std::string _email, int _level);
    int getManageLevel() const;
    void displayRole() const override;
};

#endif
