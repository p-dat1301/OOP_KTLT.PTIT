#ifndef DOANHTHU_H
#define DOANHTHU_H

#include <iostream>
#include <string>
#include <fstream>
#include <map>

using namespace std;

class DoanhThu {
private:
    
public:
    DoanhThu(); 

    static void CapNhatDoanhThu(); // Phương thức mới để cập nhật dữ liệu từ QuanLyDonHang.txt vào QuanLyDoanhThu.txt
    static void TinhTongDoanhThu(string period); // Hàm tổng hợp doanh thu theo ngày/tháng/năm
    static void ThongKeDoanhThuCacLoaiDoUong(); // Hàm thống kê doanh thu các loại đồ uống
    static void TinhTongDoanhThuTheoKhachHang(); // Hàm tính tổng doanh thu theo khách hàng
    static void TimKiemDoanhThuTheoMaDonHang(); // Hàm tìm kiếm doanh thu theo mã đơn hàng
};

#endif
