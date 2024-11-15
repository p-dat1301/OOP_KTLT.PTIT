#ifndef QUANLYNGUYENLIEU_H
#define QUANLYNGUYENLIEU_H
#include "NguyenLieu.h"
#include <iostream>
using namespace std;

void QuanLyNguyenLieu() {
    NguyenLieu nl;
    int choice;
    do {
        cout << "\n--- Quan Ly Nguyen Lieu ---\n";
        cout << "1. Nhap Nguyen Lieu Moi\n";
        cout << "2. Xem Danh Sach Nguyen Lieu\n";
        cout << "3. Tim Kiem Nguyen Lieu\n";
        cout << "4. Sua Thong Tin Nguyen Lieu\n";
        cout << "5. Xoa Nguyen Lieu\n";
        cout << "0. Quay lai\n";
        cout << "Chon chuc nang: ";
        cin >> choice;

        switch (choice) {
            case 1:
                nl.ThemNguyenLieuMoi();
                break;
            case 2:
                nl.XemDanhSachNguyenLieu();
                break;
            case 3:
                nl.TimKiemNguyenLieu();
                break;
            case 4:
                nl.SuaThongTinNguyenLieu();
                break;
            case 5:
                nl.XoaNguyenLieu();
                break;
            case 0:
                cout << "Quay lai menu chinh.\n";
                break;
            default:
                cout << "Chuc nang khong hop le. Vui long chon lai.\n";
                break;
        }
    } while (choice != 0);
}
#endif
