#ifndef QUANLYDOANHTHU_H
#define QUANLYDOANHTHU_H

#include "DoanhThu.h"
#include <iostream>

using namespace std;

void QuanLyDoanhThu() {
    DoanhThu dt;
    int choice;
    do {
        cout << "\n--- He Thong Quan Ly Doanh Thu ---\n";
        cout << "1. Cap Nhat Toan Bo Doanh Thu\n";
        cout << "2. Tinh Tong Doanh Thu theo Ngay/Thang/Nam\n";
        cout << "3. Thong Ke Doanh Thu Cac Loai Do Uong\n";
        cout << "4. Tim Kiem Doanh Thu Theo Ma Don Hang\n";
        cout << "0. Quay lai\n";
        cout << "Chon chuc nang: ";
        cin >> choice;
        cin.ignore(); // Bỏ dòng thừa khi đọc dữ liệu vào

        string tenKhachHang, soDienThoai, maDonHang, period;
        switch (choice) {
            case 1:
                dt.CapNhatDoanhThu();
                break;
            case 2:
                cout << "Nhap ky bao cao (ngay/thang/nam): ";
                cin >> period;
                dt.TinhTongDoanhThu(period);
                break;
            case 3:
                dt.ThongKeDoanhThuCacLoaiDoUong();
                break;
            case 4:
                dt.TimKiemDoanhThuTheoMaDonHang();
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
