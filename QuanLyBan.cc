#include "Ban.h"
#include <fstream>
#include <iostream>
#include <iomanip>

using namespace std;


Ban::Ban() : IdBan(""), SoGhe(0), TrangThai(false), HangBan(false) {}


Ban::Ban(string idban, int soGhe, bool hangBan, bool trangThai)
    : IdBan(idban), SoGhe(soGhe), HangBan(hangBan), TrangThai(trangThai) {}


string Ban::getIdBan() const {
    return IdBan;
}


bool Ban::getTrangThai() const {
    return TrangThai;
}


bool Ban::KiemTraTonTaiIdBan(const string& id) {
    ifstream file("./logs/QuanLyBan.txt");
    string line;
    while (getline(file, line)) {
        if (line.find("ID: " + id) != string::npos) {
            return true;
        }
    }
    return false;
}


void Ban::ThemBanMoi() {
    do {
        cout << "Nhap ID ban (3 ky tu, ky tu dau la chu in hoa va 2 ky tu sau la so): ";
        cin >> IdBan;

        
        if (IdBan.length() != 3 || !isupper(IdBan[0]) || !isdigit(IdBan[1]) || !isdigit(IdBan[2])) {
            cout << "ID ban khong hop le. Vui long nhap ID khac.\n";
            continue;
        }

        if (KiemTraTonTaiIdBan(IdBan)) {
            cout << "ID ban da ton tai. Vui long nhap ID khac.\n";
        } else {
            break;
        }
    } while (true);

    cout << "Nhap so ghe: ";
    cin >> SoGhe;
    cout << "Ban VIP? (1 = co, 0 = khong): ";
    cin >> HangBan;
    TrangThai = false; 
    cout << "Ban moi da duoc them thanh cong!\n";
}


void Ban::LuuThongTinBan() {
    ofstream file("./logs/QuanLyBan.txt", ios::app);
    if (file.is_open()) {
        file << "ID: " << getIdBan() << ", So ghe: " << SoGhe 
             << ", VIP: " << (HangBan ? "Co" : "Khong") 
             << ", Trang thai: " << (getTrangThai() ? "Co khach" : "Trong") << endl;
        file.close();
        cout << "Thong tin ban da duoc luu vao file.\n";
    } else {
        cout << "Khong the mo file de luu thong tin ban.\n";
    }
}


void Ban::SuaThongTinBan() {
    string id;
    cout << "Nhap ID ban can sua: ";
    cin >> id;

    ifstream fileIn("./logs/QuanLyBan.txt");
    ofstream fileOut("./logs/temp.txt");
    string line;
    bool found = false;

    while (getline(fileIn, line)) {
        if (line.find("ID: " + id) != string::npos) {
            found = true;
            cout << "Nhap so ghe moi: ";
            cin >> SoGhe;
            cout << "Ban VIP? (1 = co, 0 = khong): ";
            cin >> HangBan;
            cout << "Cap nhat trang thai (0 = Trong, 1 = Co khach): ";
            cin >> TrangThai;
            fileOut << "ID: " << id << ", So ghe: " << SoGhe 
                    << ", VIP: " << (HangBan ? "Co" : "Khong") 
                    << ", Trang thai: " << (getTrangThai() ? "Co khach" : "Trong") << endl;
            cout << "Thong tin ban da duoc cap nhat.\n";
        } else {
            fileOut << line << endl;
        }
    }

    fileIn.close();
    fileOut.close();
    remove("./logs/QuanLyBan.txt");
    rename("./logs/temp.txt", "./logs/QuanLyBan.txt");

    if (!found) {
        cout << "Khong tim thay ID ban can sua.\n";
    }
}

// Hàm đặt bàn
void Ban::DatBan() {
    string id;
    cout << "Nhap ID ban can dat: ";
    cin >> id;

    ifstream fileIn("./logs/QuanLyBan.txt");
    ofstream fileOut("./logs/temp.txt");
    string line;
    bool found = false;

    while (getline(fileIn, line)) {
        if (line.find("ID: " + id) != string::npos && line.find("Trong") != string::npos) {
            found = true;
            TrangThai = true; 
            fileOut << "ID: " << id << ", So ghe: " << SoGhe 
                    << ", VIP: " << (HangBan ? "Co" : "Khong") 
                    << ", Trang thai: " << (getTrangThai() ? "Co khach" : "Trong") << endl;
            cout << "Ban da duoc dat thanh cong.\n";
        } else {
            fileOut << line << endl;
        }
    }

    fileIn.close();
    fileOut.close();
    remove("./logs/QuanLyBan.txt");
    rename("./logs/temp.txt", "./logs/QuanLyBan.txt");

    if (!found) {
        cout << "Khong tim thay ban trong hoac ID khong ton tai.\n";
    }
}


void Ban::XemDanhSachBan() {
    ifstream file("./logs/QuanLyBan.txt");
    string line;

    if (file.is_open()) {
        cout << "\n--- Danh sach ban ---\n";
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Khong the mo file de xem danh sach ban.\n";
    }
}


void Ban::TimKiemBanTheoYeuCau() {
    string id;
    cout << "Nhap ID ban can tim: ";
    cin >> id;

    ifstream file("./logs/QuanLyBan.txt");
    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line.find("ID: " + id) != string::npos) {
            cout << line << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Khong tim thay ban voi ID: " << id << endl;
    }

    file.close();
}


void Ban::HuyDatBan() {
    string id;
    cout << "Nhap ID ban can huy dat: ";
    cin >> id;

    ifstream fileIn("./logs/QuanLyBan.txt");
    ofstream fileOut("./logs/temp.txt");
    string line;
    bool found = false;

    while (getline(fileIn, line)) {
        if (line.find("ID: " + id) != string::npos && line.find("Co khach") != string::npos) {
            found = true;
            TrangThai = false;
            fileOut << "ID: " << id << ", So ghe: " << SoGhe 
                    << ", VIP: " << (HangBan ? "Co" : "Khong") 
                    << ", Trang thai: " << (getTrangThai() ? "Co khach" : "Trong") << endl;
            cout << "Ban da duoc huy dat thanh cong.\n";
        } else {
            fileOut << line << endl;
        }
    }

    fileIn.close();
    fileOut.close();
    remove("./logs/QuanLyBan.txt");
    rename("./logs/temp.txt", "./logs/QuanLyBan.txt");

    if (!found) {
        cout << "Khong tim thay ban da dat hoac ID khong ton tai.\n";
    }
}


void Ban::XoaBan() {
    string id;
    cout << "Nhap ID ban can xoa: ";
    cin >> id;

    ifstream fileIn("./logs/QuanLyBan.txt");
    ofstream fileOut("./logs/temp.txt");
    string line;
    bool found = false;

    while (getline(fileIn, line)) {
        if (line.find("ID: " + id) != string::npos) {
            found = true;
            cout << "Ban da duoc xoa thanh cong.\n";
        } else {
            fileOut << line << endl;
        }
    }

    fileIn.close();
    fileOut.close();
    remove("./logs/QuanLyBan.txt");
    rename("./logs/temp.txt", "./logs/QuanLyBan.txt");

    if (!found) {
        cout << "Khong tim thay ban can xoa.\n";
    }
}
