#ifndef UUDAI_H
#define UUDAI_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class UuDai {
private:
    string MaUuDai;
    int PhanTramGiam;
    string NgayBatDau;
    string NgayKetThuc;
    int DieuKienApDung;

public:
    UuDai();
    UuDai(string MaUuDai, int PhanTramGiam, string NgayBatDau, string NgayKetThuc, int DieuKienApDung);

    void TaoChuongTrinhMoi();
    void SuaThongTinChuongTrinh();
    void LietKeUuDaiHetHan();
    void QuanLyThoiGianHieuLuc();
    void XoaUuDaiTheoMa();

    void LuuThongTinUuDai();
    void XemDanhSachUuDai();
    void TimKiemUuDaiTheoMa();

    string ChuyenMaUuDaiThanhChuHoa(const string& input);
    bool KiemTraDinhDangNgay(const string& ngay);
    bool KiemTraMaUuDaiTrung(const string& ma);

    // Hàm kiểm tra ưu đãi
    bool KiemTraUuDai(const string& maUuDai, int soDonHang, const string& ngayHienTai, int& phanTramGiam);
};

static string convertToUpper(const string& str);

#endif
