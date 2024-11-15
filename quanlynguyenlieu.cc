#include "NguyenLieu.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cctype>

using namespace std;

NguyenLieu::NguyenLieu() : MaNguyenLieu(""), TenNguyenLieu(""), SoLuongTonKho(0), MucCanhBao(0), NgayNhapCuoi("") {}

NguyenLieu::NguyenLieu(string maNguyenLieu, string tenNguyenLieu, int soLuongTonKho, int mucCanhBao, const string& ngayNhapCuoi)
    : MaNguyenLieu(maNguyenLieu), TenNguyenLieu(tenNguyenLieu), SoLuongTonKho(soLuongTonKho), MucCanhBao(mucCanhBao), NgayNhapCuoi(ngayNhapCuoi) {}

int NguyenLieu::getSoLuongTonKho() const {
    return SoLuongTonKho;
}



string NguyenLieu::toUpperCase(const string& str) {
    string upperStr = str;
    transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
    return upperStr;
}


bool NguyenLieu::KiemTraTrongMenu(const string& tenNguyenLieu) {
    ifstream file("./logs/menu.txt");
    string line;
    string upperTenNguyenLieu = toUpperCase(tenNguyenLieu);

    while (getline(file, line)) {
        if (toUpperCase(line) == upperTenNguyenLieu) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}


bool NguyenLieu::KiemTraNguyenLieuTonTai(const string& tenNguyenLieu) {
    ifstream file("./logs/QuanLyNguyenLieu.txt");
    string line;
    string upperTenNguyenLieu = toUpperCase(tenNguyenLieu);

    while (getline(file, line)) {
        if (line.find("Ten Nguyen Lieu: " + upperTenNguyenLieu) != string::npos) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void NguyenLieu::ThemNguyenLieuMoi() {
    cout << "Nhap ma nguyen lieu: ";
    cin >> MaNguyenLieu;
    MaNguyenLieu = toUpperCase(MaNguyenLieu);

    cout << "Nhap ten nguyen lieu: ";
    cin.ignore();
    getline(cin, TenNguyenLieu);
    TenNguyenLieu = toUpperCase(TenNguyenLieu);

    if (!KiemTraTrongMenu(TenNguyenLieu)) {
        cout << "Nguyen lieu khong co trong menu. Vui long nhap lai.\n";
        return;
    }

    cout << "Nhap so luong them: ";
    int soLuongThem;
    cin >> soLuongThem;
    cin.ignore();  

    ifstream fileIn("./logs/QuanLyNguyenLieu.txt");
    ofstream fileOut("./logs/temp.txt");
    string line;
    bool found = false;

    while (getline(fileIn, line)) {
        
        if (line.find("Ma Nguyen Lieu: " + MaNguyenLieu) != string::npos) {
            getline(fileIn, line);
            if (line.find("Ten Nguyen Lieu: " + TenNguyenLieu) != string::npos) {
                found = true;
                fileOut << "Ma Nguyen Lieu: " << MaNguyenLieu << "\n";
                fileOut << "Ten Nguyen Lieu: " << TenNguyenLieu << "\n";

                
                getline(fileIn, line);
                int soLuongHienTai = stoi(line.substr(line.find(":") + 2));
                soLuongHienTai += soLuongThem;
                fileOut << "So Luong Them: " << soLuongHienTai << "\n";

                
                getline(fileIn, line);
                fileOut << line << "\n";

                
                cout << "Nhap ngay nhap cuoi moi (dd/mm/yyyy): ";
                getline(cin, NgayNhapCuoi);
                fileOut << "Ngay Nhap Cuoi: " << NgayNhapCuoi << "\n";

                
                getline(fileIn, line); 
                getline(fileIn, line); 
                fileOut << line << "\n";
            } else {
                fileOut << "Ma Nguyen Lieu: " << MaNguyenLieu << "\n" << line << "\n";
            }
        } else {
            fileOut << line << "\n";
        }
    }

    fileIn.close();
    fileOut.close();

    if (!found) {
        
        ofstream file("./logs/QuanLyNguyenLieu.txt", ios::app);
        if (file.is_open()) {
            file << "Ma Nguyen Lieu: " << MaNguyenLieu << "\n";
            file << "Ten Nguyen Lieu: " << TenNguyenLieu << "\n";
            file << "So Luong Them: " << soLuongThem << "\n";
            cout << "Nhap muc canh bao: ";
            cin >> MucCanhBao;
            cin.ignore();
            file << "Muc Canh Bao: " << MucCanhBao << "\n";
            cout << "Nhap ngay nhap cuoi (dd/mm/yyyy): ";
            getline(cin, NgayNhapCuoi);
            file << "Ngay Nhap Cuoi: " << NgayNhapCuoi << "\n";
            file << "----------------------------------------------\n";
            file.close();
            cout << "Nguyen lieu moi da duoc them thanh cong!\n";
        } else {
            cout << "Khong the mo file de luu thong tin nguyen lieu.\n";
        }
    } else {
        remove("./logs/QuanLyNguyenLieu.txt");
        rename("./logs/temp.txt", "./logs/QuanLyNguyenLieu.txt");
        cout << "So luong nguyen lieu da duoc cap nhat thanh cong!\n";
    }
}


void NguyenLieu::LuuThongTinNguyenLieu() {
    ofstream file("./logs/QuanLyNguyenLieu.txt", ios::app);
    if (file.is_open()) {
        file << "Ten Nguyen Lieu: " << TenNguyenLieu << "\n";
        file << "So Luong Them: " << SoLuongTonKho << "\n";
        file << "Muc Canh Bao: " << MucCanhBao << "\n";
        file << "----------------------------------------------\n";
        file.close();
        cout << "Thong tin nguyen lieu da duoc luu thanh cong!\n";
    } else {
        cout << "Khong the mo file de luu thong tin nguyen lieu.\n";
    }
}

void NguyenLieu::SuaThongTinNguyenLieu() {
    cout << "Nhap ma nguyen lieu can sua: ";
    cin.ignore();
    string maCanSua;
    getline(cin, maCanSua);
    maCanSua = toUpperCase(maCanSua);

    ifstream fileIn("./logs/QuanLyNguyenLieu.txt");
    ofstream fileOut("./logs/temp.txt");
    string line;
    bool found = false;

    while (getline(fileIn, line)) {
        if (line.find("Ma Nguyen Lieu: " + maCanSua) != string::npos) {
            found = true;
            cout << "Nhap ma nguyen lieu moi: ";
            getline(cin, MaNguyenLieu);
            MaNguyenLieu = toUpperCase(MaNguyenLieu);

            cout << "Nhap ten nguyen lieu moi: ";
            getline(cin, TenNguyenLieu);
            TenNguyenLieu = toUpperCase(TenNguyenLieu);

            cout << "Nhap so luong ton kho moi: ";
            cin >> SoLuongTonKho;
            cout << "Nhap muc canh bao moi: ";
            cin >> MucCanhBao;
            cin.ignore();

            cout << "Nhap ngay nhap cuoi moi (dd/mm/yyyy): ";
            getline(cin, NgayNhapCuoi);

            
            fileOut << "Ma Nguyen Lieu: " << MaNguyenLieu << "\n";
            fileOut << "Ten Nguyen Lieu: " << TenNguyenLieu << "\n";
            fileOut << "So Luong Them: " << SoLuongTonKho << "\n";
            fileOut << "Muc Canh Bao: " << MucCanhBao << "\n";
            fileOut << "Ngay Nhap Cuoi: " << NgayNhapCuoi << "\n";
            fileOut << "----------------------------------------------\n";

            // Bỏ qua các dòng dữ liệu cũ của nguyên liệu này trong file gốc
            getline(fileIn, line); // Tên nguyên liệu
            getline(fileIn, line); // Số lượng
            getline(fileIn, line); // Mức cảnh báo
            getline(fileIn, line); // Ngày nhập cuối
            getline(fileIn, line); // Dòng phân cách
        } else {
            fileOut << line << endl;
        }
    }

    fileIn.close();
    fileOut.close();

    if (found) {
        remove("./logs/QuanLyNguyenLieu.txt");
        rename("./logs/temp.txt", "./logs/QuanLyNguyenLieu.txt");
        cout << "Thong tin nguyen lieu da duoc cap nhat thanh cong!\n";
    } else {
        remove("./logs/temp.txt");
        cout << "Khong tim thay nguyen lieu voi ma: " << maCanSua << "\n";
    }
}


void NguyenLieu::XoaNguyenLieu() {
    cout << "Nhap ma nguyen lieu can xoa: ";
    cin.ignore();
    string maCanXoa;
    getline(cin, maCanXoa);
    maCanXoa = toUpperCase(maCanXoa);

    cout << "Nhap ten nguyen lieu can xoa: ";
    string tenCanXoa;
    getline(cin, tenCanXoa);
    tenCanXoa = toUpperCase(tenCanXoa);

    ifstream fileIn("./logs/QuanLyNguyenLieu.txt");
    ofstream fileOut("./logs/temp.txt");
    string line;
    bool found = false;

    while (getline(fileIn, line)) {
        // Kiểm tra mã nguyên liệu
        if (line.find("Ma Nguyen Lieu: " + maCanXoa) != string::npos) {
            string nextLine;
            getline(fileIn, nextLine); 
            if (nextLine.find("Ten Nguyen Lieu: " + tenCanXoa) != string::npos) {
                found = true;
                
                getline(fileIn, line); // Số lượng
                getline(fileIn, line); // Mức cảnh báo
                getline(fileIn, line); // Ngày nhập cuối
                getline(fileIn, line); // Dòng phân cách
            } else {
                // Ghi lại cả mã nguyên liệu và tên nguyên liệu nếu tên không khớp
                fileOut << line << "\n" << nextLine << "\n";
            }
        } else {
            fileOut << line << "\n";
        }
    }

    fileIn.close();
    fileOut.close();

    if (found) {
        remove("./logs/QuanLyNguyenLieu.txt");
        rename("./logs/temp.txt", "./logs/QuanLyNguyenLieu.txt");
        cout << "Nguyen lieu da duoc xoa thanh cong!\n";
    } else {
        remove("./logs/temp.txt");
        cout << "Khong tim thay nguyen lieu voi ma va ten da nhap.\n";
    }
}

void NguyenLieu::XemDanhSachNguyenLieu() {
    ifstream file("./logs/QuanLyNguyenLieu.txt");
    string line;

    if (file.is_open()) {
        cout << "\n--- Danh sach nguyen lieu ---\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Khong the mo file de xem danh sach nguyen lieu.\n";
    }
}


void NguyenLieu::TimKiemNguyenLieu() {
    cout << "Nhap ma nguyen lieu can tim: ";
    cin.ignore();
    string maNguyenLieuCanTim;
    getline(cin, maNguyenLieuCanTim);
    maNguyenLieuCanTim = toUpperCase(maNguyenLieuCanTim);

    ifstream file("./logs/QuanLyNguyenLieu.txt");
    string line;
    bool found = false;

    cout << "\n--- Ket qua tim kiem ---\n";
    while (getline(file, line)) {
        if (line.find("Ma Nguyen Lieu: " + maNguyenLieuCanTim) != string::npos) {
            found = true;
            cout << line << endl;
            // Đọc và in ra các dòng tiếp theo của nguyên liệu tìm thấy
            getline(file, line); // Tên nguyên liệu
            cout << line << endl;
            getline(file, line); // Số lượng
            cout << line << endl;
            getline(file, line); // Mức cảnh báo
            cout << line << endl;
            getline(file, line); // Ngày nhập cuối
            cout << line << endl;
            getline(file, line); // Dòng phân cách
            cout << line << endl;
        }
    }

    if (!found) {
        cout << "Khong tim thay nguyen lieu voi ma: " << maNguyenLieuCanTim << endl;
    }

    file.close();
}

void NguyenLieu::QuanLyNhapNguyenLieu() {
    int amount;
    cout << "Nhap so luong nguyen lieu can nhap: ";
    cin >> amount;
    SoLuongTonKho += amount;

    cout << "So luong nguyen lieu sau khi nhap: " << SoLuongTonKho << endl;
    LuuThongTinNguyenLieu();
}

void NguyenLieu::TaoCanhBao() {
    if (SoLuongTonKho < MucCanhBao) {
        cout << "Canh bao: So luong nguyen lieu " << TenNguyenLieu << " duoi muc canh bao.\n";
    }
}



void NguyenLieu::CapNhatSoLuongNguyenLieu(const string& tenSanPham) {
    ifstream fileIn("./logs/QuanLyNguyenLieu.txt");
    ofstream fileOut("./logs/temp.txt");
    string line;
    bool found = false;

    while (getline(fileIn, line)) {
        if (line.find("Ten Nguyen Lieu: " + toUpperCase(tenSanPham)) != string::npos) {
            found = true;
            fileOut << line << "\n";

            // Đọc và xử lý thông tin số lượng
            getline(fileIn, line);
            int soLuongThem = stoi(line.substr(line.find(":") + 2)) - 1;
            fileOut << "So Luong Them: " << soLuongThem << "\n";

            // Giữ nguyên mức cảnh báo
            getline(fileIn, line);
            int mucCanhBao = stoi(line.substr(line.find(":") + 2));
            fileOut << line << "\n";

            // Giữ nguyên ngày nhập cuối
            getline(fileIn, line);
            fileOut << line << "\n";

            // Dòng phân cách
            getline(fileIn, line);
            fileOut << line << "\n";

            // Hiển thị thông báo nếu số lượng nhỏ hơn hoặc bằng mức cảnh báo
            if (soLuongThem <= mucCanhBao) {
                cout << "Canh bao: Nguyen lieu " << tenSanPham << " sap het! Vui long nhap them.\n";
            }

        } else {
            fileOut << line << "\n";
        }
    }

    fileIn.close();
    fileOut.close();

    if (found) {
        remove("./logs/QuanLyNguyenLieu.txt");
        rename("./logs/temp.txt", "./logs/QuanLyNguyenLieu.txt");
    } else {
        remove("./logs/temp.txt");
    }
}
