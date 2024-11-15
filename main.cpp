#include <bits/stdc++.h>
#include <iostream>
#include "QuanLyKhachHang.h"
#include "QuanLyDonHang.h"
#include "quanlynguyenlieu.h"
#include "quanlyuudai.h"
#include "QuanLyBan.h"
#include "QuanLySach.h"
#include "QuanLyNhanVien.h"
#include "QuanLyDoanhThu.h"

using namespace std;

int main() {
    int choice;
    do {
        cout << "\n--- He Thong Quan Ly ---\n";
        cout << "1. Quan Ly Don Hang\n";
        cout << "2. Quan Ly Khach Hang\n";
        cout << "3. Quan Ly Ban\n";
        cout << "4. Quan Ly Uu Dai\n";
        cout << "5. Quan Ly Nguyen Lieu\n";
        cout << "6. Quan Ly Sach\n";
        cout << "7. Quan Ly Nhan Vien\n";
        cout << "8. Quan Ly Doanh Thu\n";
        cout << "0. Thoat\n";
        cout << "Chon chuc nang: ";
        cin >> choice;
        cout << "\n";

        switch (choice) {
            case 1:
                QuanLyDonHang();
                break;
            case 2:
                QuanLyKhachHang();
                break;
            case 3:
                QuanLyBan();
                break;
            case 4:
                QuanLyUuDai();
                break;
            case 5:
                QuanLyNguyenLieu();
                break;
            case 6:
                QuanLySach();
                break;
            case 7:
                QuanLyNhanVien();
                break;
            case 8:
                QuanLyDoanhThu();
                break;
            case 0:
                cout << "Thoat chuong trinh!\n";
                break;
            default:
                cout << "Chuc nang khong hop le. Vui long chon lai.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}