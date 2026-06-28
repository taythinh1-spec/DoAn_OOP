#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <limits>
#include <iomanip>

// Khai báo các thư viện tự tạo
#include "Payment.h"
#include "User.h"
#include "Product.h"
#include "DiscountCoupon.h"
#include "ShoppingCart.h"

using namespace std;

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
                cout << "\n";
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
            }
            else if (loaiPhuongThuc == 2) {
                hinhThucTT = make_unique<MomoPayment>();
            }
            else {
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