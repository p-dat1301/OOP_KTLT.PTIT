#ifndef QUANLYNHANVIEN_H
#define QUANLYNHANVIEN_H
#include "./NhanVien.h"
#include <iostream>
using namespace std;

void QuanLyNhanVien() {
    NhanVien nv;
    int choice;
    do {
        cout << "\n--- Quan Ly Nhan Vien ---\n";
        cout << "1. Them Nhan Vien Moi\n";
        cout << "2. Xem Thong Tin Nhan Vien\n";
        cout << "3. Sua Thong Tin Nhan Vien\n";
        cout << "4. Tim Kiem Nhan Vien\n";
        cout << "5. Tinh Luong Nhan Vien\n";
        cout << "6. Xoa Nhan Vien\n"; // Đưa xóa nhân viên xuống cuối
        cout << "0. Quay lai\n";
        cout << "Chon chuc nang: ";
        cin >> choice;
        cout << "\n";

        string maNV;
        switch (choice) {
            case 1:
                nv.NhapNhanVienMoi();
                nv.LuuThongTinNhanVien();
                break;
            case 2:
                nv.InThongTinNhanVien();
                break;
            case 3:
                cout << "Nhap Ma Nhan Vien Can Sua: ";
                cin.ignore();
                getline(cin, maNV);
                nv.SuaNhanVien(maNV);
                break;
            case 4:
                cout << "Nhap Ma Nhan Vien Can Tim: ";
                cin.ignore();
                getline(cin, maNV);
                nv.TimKiemNhanVien(maNV);
                break;
            case 5:
                nv.TinhLuongNhanVien(); // Gọi phương thức tính lương
                break;
            case 6:
                cout << "Nhap Ma Nhan Vien Can Xoa: ";
                cin.ignore();
                getline(cin, maNV);
                nv.XoaNhanVien(maNV);
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
