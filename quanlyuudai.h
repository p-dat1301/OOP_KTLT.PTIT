#ifndef QUANLYUUDAI_H
#define QUANLYUUDAI_H
#include "UuDai.h"
#include <iostream>
using namespace std;

void QuanLyUuDai() {
    UuDai ud;
    int choice;
    do {
        cout << "\n--- Quan Ly Uu Dai ---\n";
        cout << "1. Tao Chuong Trinh Moi\n";
        cout << "2. Xem Danh Sach Uu Dai\n";
        cout << "3. Tim Kiem Uu Dai Theo Ma\n";
        cout << "4. Tim Kiem Chuong Trinh Het Han\n";
        cout << "5. Sua Thong Tin Chuong Trinh\n";
        cout << "6. Xoa Chuong Trinh Uu Dai\n";
        cout << "0. Quay lai\n";
        cout << "Chon chuc nang: ";
        cin >> choice;

        switch (choice) {
            case 1:
                ud.TaoChuongTrinhMoi();
                break;
            case 2:
                ud.XemDanhSachUuDai();
                break;
            case 3:
                ud.TimKiemUuDaiTheoMa();
                break;
            case 4:
                ud.LietKeUuDaiHetHan();
                break;
            case 5:
                ud.SuaThongTinChuongTrinh();
                break;
            case 6:
                ud.XoaUuDaiTheoMa();
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
