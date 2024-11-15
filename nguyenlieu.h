#ifndef NGUYENLIEU_H
#define NGUYENLIEU_H

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <ctime>
using namespace std;

class NguyenLieu {
private:
    string MaNguyenLieu;          // Mã nguyên liệu
    string TenNguyenLieu;
    int SoLuongTonKho;
    int MucCanhBao;
    string NgayNhapCuoi;          // Ngày nhập cuối

public:
    NguyenLieu();
    NguyenLieu(string maNguyenLieu, string tenNguyenLieu, int soLuongTonKho, int mucCanhBao, const string& ngayNhapCuoi);

    void ThemNguyenLieuMoi();
    void SuaThongTinNguyenLieu();
    void XoaNguyenLieu();
    void TaoCanhBao();
    void QuanLyNhapNguyenLieu();
    void XemDanhSachNguyenLieu();
    void TimKiemNguyenLieu();
    void LuuThongTinNguyenLieu();
    void CapNhatSoLuongNguyenLieu(const string& tenSanPham);

    int getSoLuongTonKho() const;

private:
    bool KiemTraNguyenLieuTonTai(const string& maNguyenLieu);
    bool KiemTraTrongMenu(const string& tenNguyenLieu);
    string toUpperCase(const string& str);
    string LayNgayHienTai();       // Hàm lấy ngày hiện tại
};

#endif
