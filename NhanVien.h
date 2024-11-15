#ifndef NHANVIEN_H
#define NHANVIEN_H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class NhanVien {
private:
    string MaNhanVien;
    string TenNhanVien;
    string SoDienThoai;
    string ChucVu;
    double Luong; // Thuộc tính mới

public:
    NhanVien(); // Constructor không tham số
    NhanVien(string maNV, string tenNV, string sdt, string chucVu); // Constructor có tham số

    // Các phương thức xử lý nhân viên
    void NhapNhanVienMoi();   // Nhập thông tin nhân viên mới
    void InThongTinNhanVien(); // In thông tin toàn bộ nhân viên từ file
    void LuuThongTinNhanVien(); // Lưu thông tin nhân viên vào file
    void XoaNhanVien(const string& maNV); // Thay đổi để nhận mã nhân viên từ bên ngoài
    void SuaNhanVien(const string& maNV); // Thay đổi để nhận mã nhân viên từ bên ngoài
    bool TimKiemNhanVien(const string& maNV); // Tìm kiếm nhân viên theo mã nhân viên
    double LayLuongTheoChucVu(const string& chucVu); // Lấy lương theo chức vụ
    bool KiemTraMaNhanVienTonTai(const string& maNV);
    void TinhLuongNhanVien();
};

#endif
