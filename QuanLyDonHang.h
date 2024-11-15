#ifndef QUANLYDONHANG_H
#define QUANLYDONHANG_H

#include "DonHang.h"
#include <iostream>

using namespace std;

void QuanLyDonHang() {
    DonHang dh;
    int choice;
    string maDonHang;

    do {
        cout << "\n==============================\n";
        cout << "  HE THONG QUAN LY DON HANG\n";
        cout << "==============================\n";
        cout << "1. Them Don Hang Moi\n";
        cout << "2. Xem Danh Sach Don Hang\n";
        cout << "3. Xoa Don Hang\n";
        cout << "4. Tim Kiem Don Hang Theo Ma\n";
        cout << "0. Quay lai\n";
        cout << "==============================\n";
        cout << "Chon chuc nang: ";
        cin >> choice;
        cout << "\n";

        switch (choice) {
            case 1:
                cout << "Nhap thong tin cho don hang moi:\n";
                dh.NhapDonHang();
                break;
            case 2:
                cout << "Dang hien thi thong tin tat ca don hang:\n";
                dh.InThongTinDonHang();
                cout << "-----------------------------------\n";
                break;
            case 3:
                cout << "Nhap ma don hang can xoa: ";
                cin.ignore();
                getline(cin, maDonHang);
                dh.XoaDonHang(maDonHang);
                cout << "Don hang da duoc xoa neu ton tai.\n";
                break;
            case 4:
                cout << "Nhap ma don hang can tim kiem: ";
                cin.ignore();
                getline(cin, maDonHang);
                dh.TimKiemDonHangTheoMa(maDonHang);
                break;
            case 0:
                cout << "Quay lai menu chinh. Hen gap lai!\n";
                break;
            default:
                cout << "Chuc nang khong hop le. Vui long chon lai.\n";
                break;
        }
    } while (choice != 0);
}

#endif
