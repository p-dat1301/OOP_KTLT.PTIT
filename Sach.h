#ifndef SACH_H
#define SACH_H
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
class Sach{
private:
    string TenSach;
    string TenTG;
    string NXB;
    int NamXuatBan;
public:
    Sach(); // Constructor
    Sach(string TenSach, string TenTG, string NXB,int NamXuatBan);

    void NhapSachMoi();
    void InThongTinSach();
    void LuuThongTinSach();
    void XoaSach();
    void TimKiemSach();
    void ChinhSuaThongTinSach();
};
#endif

