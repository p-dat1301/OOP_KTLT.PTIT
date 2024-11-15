#ifndef BAN_H
#define BAN_H
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Ban {
private:
    string IdBan; // ID của bàn
    int SoGhe; // Số ghế trong bàn
    bool TrangThai; // false: Trống, true: Có khách
    bool HangBan; // true = VIP, false = Thường

public:
    Ban();
    Ban(string Idban, int SoGhe, bool HangBan, bool TrangThai);

    void ThemBanMoi();
    void SuaThongTinBan();
    void DatBan();
    void LuuThongTinBan();
    void XemDanhSachBan();
    void TimKiemBanTheoYeuCau();
    void HuyDatBan();
    void XoaBan();

    string getIdBan() const;
    bool getTrangThai() const;

    // Hàm kiểm tra ID bàn có tồn tại trong file không
    bool KiemTraTonTaiIdBan(const string& id);
};
#endif
