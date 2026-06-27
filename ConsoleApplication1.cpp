#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <memory>
#include <limits>

using namespace std;

class IPayment {
public:
    virtual void processPayment(double amount) = 0;
    virtual ~IPayment() {}
};

class CreditCardPayment : public IPayment {
public:
    void processPayment(double amount) override {
        cout << fixed << setprecision(0);
        cout << "=> [Thanh toan] Dang xu ly the tin dung: " << amount << " VND..." << endl;
        cout << "=> Giao dich qua the tin dung THANH CONG!" << endl;
    }
};

class MomoPayment : public IPayment {
public:
    void processPayment(double amount) override {
        cout << fixed << setprecision(0);
        cout << "=> [Thanh toan] Dang ket noi vi Momo: " << amount << " VND..." << endl;
        cout << "=> Giao dich qua vi Momo THANH CONG!" << endl;
    }
};

class User {
private:
    int id;
    string name;
    string email;

public:
    User(int _id, string _name, string _email)
        : id(_id), name(_name), email(_email) {}
    virtual ~User() {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getEmail() const { return email; }

    void setName(string _name) { name = _name; }

    virtual void displayRole() const = 0;
};

class Customer : public User {
private:
    string address;
public:
    Customer(int _id, string _name, string _email, string _address)
        : User(_id, _name, _email), address(_address) {}

    string getAddress() const { return address; }

    void displayRole() const override {
        cout << "Vai tro: Khach hang - Ten: " << getName() << endl;
    }
};

class Admin : public User {
private:
    int manageLevel;
public:
    Admin(int _id, string _name, string _email, int _level)
        : User(_id, _name, _email), manageLevel(_level) {}

    int getManageLevel() const { return manageLevel; }

    void displayRole() const override {
        cout << "Vai tro: Quan tri vien - Ten: " << getName() << endl;
    }
};

class Product {
private:
    int productId;
    string productName;
    double price;

public:
    Product(int _id, string _name, double _price)
        : productId(_id), productName(_name), price(_price) {}
    virtual ~Product() {}

    int getId() const { return productId; }
    string getName() const { return productName; }
    double getPrice() const { return price; }

    virtual void displayDetails() const {
        cout << fixed << setprecision(0);
        cout << "ID: " << productId << " | " << productName << " | Gia: " << price << " VND";
    }
};

class Electronics : public Product {
private:
    int warrantyPeriod;
public:
    Electronics(int _id, string _name, double _price, int _warranty)
        : Product(_id, _name, _price), warrantyPeriod(_warranty) {}

    void displayDetails() const override {
        Product::displayDetails();
        cout << " | Bao hanh: " << warrantyPeriod << " thang (Do dien tu)" << endl;
    }
};

class Clothing : public Product {
private:
    string size;
public:
    Clothing(int _id, string _name, double _price, string _size)
        : Product(_id, _name, _price), size(_size) {}

    void displayDetails() const override {
        Product::displayDetails();
        cout << " | Size: " << size << " (Thoi trang)" << endl;
    }
};

class DiscountCoupon {
private:
    string code;
    double discountPercent; 
    bool active;

public:
    DiscountCoupon(string _code, double _percent)
        : code(_code), discountPercent(_percent), active(true) {}

    bool isValid(const string& inputCode) const {
        return active && (code == inputCode);
    }

    double apply(double originalPrice) const {
        return originalPrice * (1.0 - discountPercent / 100.0);
    }

    double getPercent() const { return discountPercent; }
    string getCode() const { return code; }

    void deactivate() { active = false; }
};

class OrderItem {
private:
    shared_ptr<Product> product;
    int quantity;
public:
    OrderItem(shared_ptr<Product> _product, int _quantity)
        : product(_product), quantity(_quantity) {}

    shared_ptr<Product> getProduct() const { return product; }
    int getQuantity() const { return quantity; }
    double getSubTotal() const { return product->getPrice() * quantity; }
};

class ShoppingCart {
private:
    vector<OrderItem> items;
public:
    void addItem(shared_ptr<Product> product, int quantity) {
        for (auto& item : items) {
            if (item.getProduct()->getId() == product->getId()) {
                cout << "=> San pham da co trong gio! Vui long them moi.\n";
                return;
            }
        }
        items.push_back(OrderItem(product, quantity));
        cout << "=> Da them " << quantity << "x [" << product->getName() << "] vao gio hang!\n";
    }

    void displayCart() const {
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

    double calculateTotal(const DiscountCoupon* coupon = nullptr) const {
        double total = 0;
        for (const auto& item : items) {
            total += item.getSubTotal();
        }
        if (coupon != nullptr) {
            total = coupon->apply(total);
        }
        return total;
    }

    void clearCart() { items.clear(); }
    bool isEmpty() const { return items.empty(); }
};

bool docSoNguyen(int& value) {
    cin >> value;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return false;
    }
    return true;
}

int main() {
    Customer currentCustomer(1, "Nguyen Van A", "a@gmail.com", "TP.HCM");
    ShoppingCart gioHang;

    vector<shared_ptr<Product>> danhSachSP;
    danhSachSP.push_back(make_shared<Electronics>(101, "Laptop Dell XPS", 25000000.0, 12));
    danhSachSP.push_back(make_shared<Electronics>(102, "iPhone 15 Pro", 22000000.0, 12));
    danhSachSP.push_back(make_shared<Clothing>(201, "Ao thun Polo UTH", 350000.0, "L"));
    danhSachSP.push_back(make_shared<Clothing>(202, "Quan Jean Chi Tiet", 500000.0, "32"));

    vector<DiscountCoupon> danhSachCoupon = {
        DiscountCoupon("UTH10",  10.0),  
        DiscountCoupon("SALE20", 20.0),  
        DiscountCoupon("VIP50",  50.0)   
    };

    int luaChon;
    while (true) {
        cout << "\n=========================================";
        cout << "\n     HE THONG MUA SAM TRUC TUYEN      ";
        cout << "\n=========================================";
        cout << "\nXin chao, " << currentCustomer.getName();
        cout << "\n1. Xem danh sach san pham";
        cout << "\n2. Them san pham vao gio hang";
        cout << "\n3. Xem gio hang hien tai";
        cout << "\n4. Tien hanh thanh toan";
        cout << "\n5. Thoat chuong trinh";
        cout << "\n=========================================";
        cout << "\nNhap lua chon cua ban (1-5): ";

        if (!docSoNguyen(luaChon)) {
            cout << "=> Vui long chi nhap so tu 1 den 5!\n";
            continue;
        }

        switch (luaChon) {
            case 1:
                cout << "\n--- DANH SACH SAN PHAM CO SAN ---\n";
                for (const auto& p : danhSachSP) {
                    p->displayDetails(); 
                }
                break;

            case 2: {
                int pid, qty;
                cout << "\nNhap ID san pham muon mua: ";
                if (!docSoNguyen(pid)) { cout << "=> ID khong hop le!\n"; break; }
                cout << "Nhap so luong: ";
                if (!docSoNguyen(qty) || qty <= 0) { cout << "=> So luong phai la so duong!\n"; break; }

                bool timThay = false;
                for (const auto& p : danhSachSP) {
                    if (p->getId() == pid) {
                        gioHang.addItem(p, qty);
                        timThay = true;
                        break;
                    }
                }
                if (!timThay) cout << "=> Khong tim thay san pham co ID = " << pid << "!\n";
                break;
            }

            case 3:
                gioHang.displayCart();
                break;

            case 4: {
                if (gioHang.isEmpty()) {
                    cout << "=> Gio hang dang trong! Vui long mua hang truoc.\n";
                    break;
                }

                gioHang.displayCart();
                double tongTienGoc = gioHang.calculateTotal();
                cout << fixed << setprecision(0);
                cout << "=> Tong tien goc: " << tongTienGoc << " VND\n";

                cout << "\nNhap ma giam gia (nhan Enter de bo qua): ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string maGiam;
                getline(cin, maGiam);

                const DiscountCoupon* couponApDung = nullptr;
                if (!maGiam.empty()) {
                    for (auto& c : danhSachCoupon) {
                        if (c.isValid(maGiam)) {
                            couponApDung = &c;
                            cout << "=> Ma [" << c.getCode() << "] hop le! "
                                 << "Giam " << c.getPercent() << "% gia tri don hang.\n";
                            break;
                        }
                    }
                    if (!couponApDung) {
                        cout << "=> Ma [" << maGiam << "] khong hop le hoac da het han. Tinh gia goc.\n";
                    }
                }

                double tongTienSauGiam = gioHang.calculateTotal(couponApDung);

                if (couponApDung != nullptr) {
                    cout << "=> So tien duoc giam: " << (tongTienGoc - tongTienSauGiam) << " VND\n";
                }
                cout << "=> TONG SO TIEN THANH TOAN: " << tongTienSauGiam << " VND\n";

                cout << "\nChon phuong thuc (1: The Tin Dung | 2: Vi Momo): ";
                int loaiPhuongThuc;
                if (!docSoNguyen(loaiPhuongThuc)) {
                    cout << "=> Lua chon khong hop le!\n";
                    break;
                }

                unique_ptr<IPayment> hinhThucTT;
                if (loaiPhuongThuc == 1) {
                    hinhThucTT = make_unique<CreditCardPayment>();
                } else if (loaiPhuongThuc == 2) {
                    hinhThucTT = make_unique<MomoPayment>();
                } else {
                    cout << "=> Phuong thuc thanh toan khong hop le!\n";
                    break;
                }

                hinhThucTT->processPayment(tongTienSauGiam);
                gioHang.clearCart();
                cout << "=> Don hang da duoc dat thanh cong! Cam on ban.\n";
                break;
            }

            case 5:
                cout << "\n=> Cam on " << currentCustomer.getName()
                     << " da su dung dich vu! Hen gap lai.\n";
                return 0;

            default:
                cout << "=> Lua chon [" << luaChon << "] sai! Vui long nhap tu 1 den 5.\n";
                break;
        }
    }

    return 0;
}
