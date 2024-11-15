#ifndef QUANLYBAN_H
#define QUANLYBAN_H
#include "./Ban.h"
#include <iostream>
using namespace std;

void QuanLyBan() {
    Ban b;
    int choice;
    do {
        cout << "\n--- Quan Ly Ban ---\n";
        cout << "1. Dat Ban\n";
        cout << "2. Xem Danh Sach Ban\n";
        cout << "3. Tim Kiem Ban Theo Yeu Cau\n";
        cout << "4. Huy Dat Ban\n";
        cout << "5. Them Ban Moi\n";
        cout << "6. Sua Thong Tin Ban\n";
        cout << "7. Xoa Ban\n";
        cout << "0. Quay lai\n";
        cout << "Chon chuc nang: ";
        cin >> choice;

        switch (choice) {
            case 1:
                b.DatBan();
                break;
            case 2:
                b.XemDanhSachBan();
                break;
            case 3:
                b.TimKiemBanTheoYeuCau();
                break;
            case 4:
                b.HuyDatBan();
                break;
            case 5:
                b.ThemBanMoi();
                b.LuuThongTinBan();
                break;
            case 6:
                b.SuaThongTinBan();
                break;
            case 7:
                b.XoaBan();
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
