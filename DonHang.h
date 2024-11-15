#ifndef DONHANG_H
#define DONHANG_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class DonHang {
private:
    string MaDonHang;
    string TenKhachHang;
    string SoDienThoai;
    string SanPham;
    double TongTien;
    string NgayThangNam;
    string MaUuDai;  // Thêm thuộc tính mã ưu đãi

public:
    DonHang();
    DonHang(string maDonHang, string tenKhachHang, const string& soDienThoai, const string& sanPham, double tongTien, const string& ngayThangNam, const string& maUuDai = "");

    void NhapDonHang();
    void LuuDonHang();
    void InThongTinDonHang();
    void XoaDonHang(const string& maDonHang);
    void CapNhatSoDonHang(); // Cập nhật số đơn hàng cho khách hàng

    // Getter
    string getMaDonHang() const;
    string getTenKhachHang() const;
    string getSoDienThoai() const;
    double getTongTien() const;

    string ChuyenSangChuHoa(const string& str);

    // Phương thức tìm kiếm đơn hàng theo mã đơn hàng
    void TimKiemDonHangTheoMa(const string& maDonHang);


    bool KiemTraDinhDangNgay(const string& ngay);
    
private:
    bool KiemTraMaDonHang(const string& maDonHang);

    // Hàm mới để lấy số đơn hàng của khách hàng
    int SoDonHangKhachHang();
};

#endif
