#ifndef QUANLYKHACHHANG_H
#define QUANLYKHACHHANG_H

#include "./KhachHang.h"
#include <iostream>
using namespace std;

void QuanLyKhachHang() {
    KhachHang kh;
    int choice;
    do {
        cout << "\n--- Quan Ly Khach Hang ---\n";
        cout << "1. Them Khach Hang Moi\n";
        cout << "2. Xem Thong Tin Khach Hang\n";
        cout << "3. Xoa Khach Hang\n";
        cout << "4. Tim Kiem Khach Hang\n";    // Thêm chức năng tìm kiếm
        cout << "5. Chinh Sua Khach Hang\n";   // Thêm chức năng chỉnh sửa
        cout << "0. Quay lai\n";
        cout << "Chon chuc nang: ";
        cin >> choice;
        cout << "\n";

        switch (choice) {
            case 1:
                kh.NhapKhachHangMoi();
                kh.LuuThongTinKhachHang();
                break;
            case 2:
                kh.InThongTinKhachHang();
                break;
            case 3:
                kh.XoaKhachHang(); // Gọi hàm xóa khách hàng
                break;
            case 4:
                kh.TimKiemKhachHang(); // Gọi hàm tìm kiếm
                break;
            case 5:
                kh.ChinhSuaKhachHang(); // Gọi hàm chỉnh sửa
                break;
            case 0:
                cout << "Quay lai menu chinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);
}

#endif
