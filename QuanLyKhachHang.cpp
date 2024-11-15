#include "KhachHang.h"
#include <algorithm>
#include <cctype>
using namespace std;

KhachHang::KhachHang() : KhachHangThanThiet(false), SoDonHang(0) {}

KhachHang::KhachHang(string hoTen, string soDienThoai, int soDonHang, bool khachHangThanThiet)
    : HoTen(hoTen), SoDienThoai(soDienThoai), SoDonHang(soDonHang), KhachHangThanThiet(khachHangThanThiet) {}

// Hàm chuyển chuỗi sang chữ in hoa
string KhachHang::convertToUpper(const string &str) {
    string upperStr = str;
    transform(upperStr.begin(), upperStr.end(), upperStr.begin(), ::toupper);
    return upperStr;
}

bool KhachHang::kiemTraTrungLap() const {
    ifstream file("logs/ThongTinKhachHang.txt");
    string line;
    while (getline(file, line)) {
        if (line.find("Ho Ten: " + HoTen) != string::npos &&
            getline(file, line) && line.find("So Dien Thoai: " + SoDienThoai) != string::npos) {
            return true;
        }
    }
    return false;
}

void KhachHang::NhapKhachHangMoi() {
    cin.ignore(); // Đặt cin.ignore() ở đây
    do {
        cout << "Nhap Ho Ten: ";
        getline(cin, HoTen);
        HoTen = convertToUpper(HoTen); // Chuyển tên thành chữ in hoa

        cout << "Nhap So Dien Thoai: ";
        getline(cin, SoDienThoai);
        KhachHangThanThiet = false;
        SoDonHang = 0; // Mặc định số đơn hàng là 0

        if (kiemTraTrungLap()) {
            cout << "Khach hang da ton tai, vui long nhap lai!\n";
        } else {
            break;
        }
    } while (true);
}


void KhachHang::LuuThongTinKhachHang() {
    ofstream file("logs/ThongTinKhachHang.txt", ios::app);
    if (file.is_open()) {
        file << "Ho Ten: " << HoTen << "\n";
        file << "So Dien Thoai: " << SoDienThoai << "\n";
        file << "So Don Hang: " << SoDonHang << "\n";
        file << "Khach Hang Than Thiet: " << (KhachHangThanThiet ? "Co" : "Khong") << "\n";
        file << "---------------------------------------------\n";
        file.close();
        cout << "Them Khach Hang Thanh Cong!" << endl;
    } else {
        cout << "Them khach hang khong thanh cong!" << endl;
    }
}

void KhachHang::InThongTinKhachHang() {
    ifstream file("logs/ThongTinKhachHang.txt");
    if (file.is_open()) {
        cout << "THONG TIN KHACH HANG\n";
        cout << "---------------------------------------------\n";
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Khong the mo file de doc thong tin khach hang!" << endl;
    }
}

void KhachHang::XoaKhachHang() {
    cout << "Nhap Ho Ten Khach Hang Can Xoa: ";
    string tenXoa;
    cin.ignore();
    getline(cin, tenXoa);
    tenXoa = convertToUpper(tenXoa);

    ifstream file("logs/ThongTinKhachHang.txt");
    ofstream tempFile("logs/temp.txt");

    bool found = false;
    if (file.is_open() && tempFile.is_open()) {
        string line;
        
        while (getline(file, line)) {
            if (line.find("Ho Ten: " + tenXoa) != string::npos) {
                found = true;
                cout << "Khach hang da duoc xoa!\n";
                for (int i = 0; i < 3; ++i) getline(file, line);
            } else {
                tempFile << line << "\n";
            }
        }

        file.close();
        tempFile.close();

        remove("logs/ThongTinKhachHang.txt");
        rename("logs/temp.txt", "logs/ThongTinKhachHang.txt");

        if (!found) {
            cout << "Khong tim thay khach hang can xoa!\n";
        }
    } else {
        cout << "Khong the mo file!\n";
    }
}

void KhachHang::TimKiemKhachHang() {
    cout << "Nhap Ho Ten Khach Hang Can Tim: ";
    string tenTimKiem;
    cin.ignore();
    getline(cin, tenTimKiem);
    tenTimKiem = convertToUpper(tenTimKiem);

    ifstream file("logs/ThongTinKhachHang.txt");
    bool found = false;
    string line;
    while (getline(file, line)) {
        if (line.find("Ho Ten: " + tenTimKiem) != string::npos) {
            found = true;
            cout << line << endl;
            for (int i = 0; i < 3; ++i) {
                getline(file, line);
                cout << line << endl;
            }
            cout << "---------------------------------------------\n";
        }
    }
    if (!found) {
        cout << "Khong tim thay khach hang co ten: " << tenTimKiem << endl;
    }
}

void KhachHang::ChinhSuaKhachHang() {
    cout << "Nhap Ho Ten Khach Hang Can Sua: ";
    string tenSua;
    cin.ignore();
    getline(cin, tenSua);
    tenSua = convertToUpper(tenSua);

    cout << "Nhap So Dien Thoai: ";
    string sdtSua;
    getline(cin, sdtSua);

    ifstream file("logs/ThongTinKhachHang.txt");
    ofstream tempFile("logs/temp.txt");

    bool found = false;
    string line;

    if (file.is_open() && tempFile.is_open()) {
        while (getline(file, line)) {
            if (line == "Ho Ten: " + tenSua) {
                string nextLine;
                getline(file, nextLine); // Đọc dòng số điện thoại

                if (nextLine == "So Dien Thoai: " + sdtSua) {
                    found = true;
                    cout << "Thong tin khach hang hien tai:\n" << line << "\n";
                    cout << nextLine << "\n";

                    getline(file, line); cout << line << "\n"; // Số đơn hàng
                    getline(file, line); cout << line << "\n"; // Khách hàng thân thiết

                    // Nhập thông tin mới
                    cout << "Nhap Ten Moi: ";
                    string newHoTen;
                    getline(cin, newHoTen);
                    if (!newHoTen.empty()) tenSua = convertToUpper(newHoTen);

                    cout << "Nhap So Dien Thoai Moi: ";
                    string newSoDienThoai;
                    getline(cin, newSoDienThoai);
                    if (!newSoDienThoai.empty()) sdtSua = newSoDienThoai;

                    cout << "Nhap So Don Hang Moi: ";
                    string soDonHangStr;
                    getline(cin, soDonHangStr);
                    int newSoDonHang = !soDonHangStr.empty() ? stoi(soDonHangStr) : 0;

                    cout << "Khach Hang Than Thiet (Co/Khong): ";
                    string khachThanThietStr;
                    getline(cin, khachThanThietStr);
                    bool newKhachHangThanThiet = (khachThanThietStr == "Co" || khachThanThietStr == "co");

                    // Lưu thông tin đã chỉnh sửa vào file tạm
                    tempFile << "Ho Ten: " << tenSua << "\n";
                    tempFile << "So Dien Thoai: " << sdtSua << "\n";
                    tempFile << "So Don Hang: " << newSoDonHang << "\n";
                    tempFile << "Khach Hang Than Thiet: " << (newKhachHangThanThiet ? "Co" : "Khong") << "\n";
                    tempFile << "---------------------------------------------\n";

                    // Bỏ qua các dòng còn lại của khách hàng trong file gốc
                    getline(file, line); // bỏ qua đường phân cách
                } else {
                    // Nếu số điện thoại không khớp, ghi lại cả khối thông tin khách hàng vào file tạm
                    tempFile << line << "\n";
                    tempFile << nextLine << "\n";
                    getline(file, line); tempFile << line << "\n"; // Số đơn hàng
                    getline(file, line); tempFile << line << "\n"; // Khách hàng thân thiết
                    tempFile << "---------------------------------------------\n";
                }
            } else {
                // Ghi lại toàn bộ các dòng không liên quan
                tempFile << line << "\n";
            }
        }

        file.close();
        tempFile.close();

        if (!found) {
            cout << "Khong tim thay khach hang can sua!\n";
        } else {
            remove("logs/ThongTinKhachHang.txt");
            rename("logs/temp.txt", "logs/ThongTinKhachHang.txt");
            cout << "Chinh sua khach hang thanh cong!\n";
        }
    } else {
        cout << "Khong the mo file!\n";
    }
}



