#ifndef KHACHHANG_H
#define KHACHHANG_H
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class KhachHang {
private:
    string HoTen;
    string SoDienThoai;
    bool KhachHangThanThiet;
    int SoDonHang;

    string convertToUpper(const string &str); // Hàm chuyển chuỗi sang chữ in hoa

public:
    KhachHang();
    KhachHang(string HoTen, string SoDienThoai, int SoDonHang, bool KhachHangThanThiet = false);

    void NhapKhachHangMoi();
    void InThongTinKhachHang();
    void LuuThongTinKhachHang();
    void XoaKhachHang();         // Hàm xóa khách hàng
    bool kiemTraTrungLap() const;

    void TimKiemKhachHang();     // Thêm chức năng tìm kiếm
    void ChinhSuaKhachHang();    // Thêm chức năng chỉnh sửa

    string getHoTen() const;
    string getSoDienThoai() const;
    bool isKhachHangThanThiet() const;
    int getSoDonHang() const;
};

#endif
