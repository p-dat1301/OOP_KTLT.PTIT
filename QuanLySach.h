#ifndef QUANLYSACH_H
#define QUANLYSACH_H
#include "./Sach.h"
#include<iostream>
using namespace std;

void QuanLySach(){
    Sach s;
    int choice;
    do {
        cout << "\n--- Quan Ly Sach ---\n";
        cout << "1. Them Sach Moi\n";
        cout << "2. Xem Thong Tin Sach\n";
        cout << "3. Xoa Sach\n";
        cout << "4. Tim Sach\n";
        cout << "5. Chinh Sua Thong Tin Sach\n";
        cout << "0. Quay lai\n";
        cout << "Chon chuc nang: ";
        cin >> choice;
        cout<<"\n";
        

        switch (choice) {
            case 1:
                s.NhapSachMoi();
                s.LuuThongTinSach();
                break;
            case 2:
                s.InThongTinSach();
                break;
            case 3:
                s.XoaSach();
                break;
            case 4:
                s.TimKiemSach();
                break;
            case 5:
                s.ChinhSuaThongTinSach();
                break;
            case 0:
                cout << "Quay lai menu chinh.\n";
                break;
            default:
                cout << "Chuc nang khong hop le. Vui long chon lai.\n";
                break;
        }
    } while (choice != 0);
};
#endif