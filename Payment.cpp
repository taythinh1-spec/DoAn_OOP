#include "Payment.h"
#include <iostream>
#include <iomanip>

using namespace std;

void CreditCardPayment::processPayment(double amount) {
    cout << fixed << setprecision(0);
    cout << "=> [Thanh toan] Dang xu ly the tin dung: " << amount << " VND..." << endl;
    cout << "=> Giao dich qua the tin dung THANH CONG!" << endl;
}

void MomoPayment::processPayment(double amount) {
    cout << fixed << setprecision(0);
    cout << "=> [Thanh toan] Dang ket noi vi Momo: " << amount << " VND..." << endl;
    cout << "=> Giao dich qua vi Momo THANH CONG!" << endl;
}