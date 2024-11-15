#include "DonHang.h"
#include "uudai.h"
#include "nguyenlieu.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

DonHang::DonHang() 
    : MaDonHang(""), TenKhachHang(""), SoDienThoai(""), SanPham(""), 
      TongTien(0), NgayThangNam(""), MaUuDai("") {}

DonHang::DonHang(string maDonHang, string tenKhachHang, const string& soDienThoai, const string& sanPham, double tongTien, const string& ngayThangNam, const string& maUuDai)
    : MaDonHang(maDonHang), TenKhachHang(tenKhachHang), SoDienThoai(soDienThoai), SanPham(sanPham), TongTien(tongTien), NgayThangNam(ngayThangNam), MaUuDai(maUuDai) {}

string DonHang::ChuyenSangChuHoa(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

int DonHang::SoDonHangKhachHang() {
    ifstream file("./logs/ThongTinKhachHang.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file ThongTinKhachHang.txt!" << endl;
        return 0;
    }

    string line;
    while (getline(file, line)) {
        if (line.find("Ho Ten: " + TenKhachHang) != string::npos) {
            while (getline(file, line)) {
                if (line.find("So Dien Thoai: " + SoDienThoai) != string::npos) {
                    getline(file, line); // Dòng có "So Don Hang:"
                    return stoi(line.substr(line.find(":") + 2));
                }
            }
        }
    }

    file.close();
    return 0; // Nếu không tìm thấy khách hàng
}


bool DonHang::KiemTraMaDonHang(const string& maDonHang) {
    ifstream file("logs/QuanLyDonHang.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file de kiem tra ma don hang!" << endl;
        return false;
    }

    string line;
    while (getline(file, line)) {
        if (line.find("Ma Don Hang: " + maDonHang) != string::npos) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}


void DonHang::CapNhatSoDonHang() {
    ifstream inputFile("./logs/ThongTinKhachHang.txt");
    ofstream tempFile("logs/temp.txt");

    if (!inputFile.is_open() || !tempFile.is_open()) {
        cout << "Không thể mở file để cập nhật số đơn hàng!" << endl;
        return;
    }

    string line;
    bool khachHangTimThay = false;

    while (getline(inputFile, line)) {
        if (line.find("Ho Ten: " + TenKhachHang) != string::npos) {
            getline(inputFile, line);
            if (line.find("So Dien Thoai: " + SoDienThoai) != string::npos) {
                khachHangTimThay = true;
                tempFile << "Ho Ten: " << TenKhachHang << endl;
                tempFile << "So Dien Thoai: " << SoDienThoai << endl;

                getline(inputFile, line);
                if (line.find("So Don Hang:") != string::npos) {
                    int soDonHangHienTai = stoi(line.substr(line.find(":") + 2));
                    soDonHangHienTai += 1;
                    tempFile << "So Don Hang: " << soDonHangHienTai << endl;
                }

                while (getline(inputFile, line) && line.find("---------------------------------------------") == string::npos) {
                    tempFile << line << endl;
                }
                tempFile << "---------------------------------------------" << endl;
            } else {
                tempFile << "Ho Ten: " << TenKhachHang << endl;
                tempFile << line << endl;
            }
        } else {
            tempFile << line << endl;
        }
    }

    inputFile.close();
    tempFile.close();

    if (khachHangTimThay) {
        remove("./logs/ThongTinKhachHang.txt");
        rename("logs/temp.txt", "./logs/ThongTinKhachHang.txt");
    } else {
        remove("logs/temp.txt");
    }
}

bool DonHang::KiemTraDinhDangNgay(const string& ngay) {
    if (ngay.length() != 10 || ngay[2] != '/' || ngay[5] != '/') return false;
    for (int i = 0; i < ngay.length(); i++) {
        if (i != 2 && i != 5 && !isdigit(ngay[i])) return false;
    }
    return true;
}

void DonHang::NhapDonHang() {
    cin.ignore();
    cout << "Nhap Ma Don Hang: ";
    getline(cin, MaDonHang);
    MaDonHang = ChuyenSangChuHoa(MaDonHang);

    while (KiemTraMaDonHang(MaDonHang)) {
        cout << "Ma Don Hang da ton tai! Vui long nhap lai: ";
        getline(cin, MaDonHang);
    }

    cout << "Nhap Ten Khach Hang: ";
    getline(cin, TenKhachHang);
    TenKhachHang = ChuyenSangChuHoa(TenKhachHang);

    cout << "Nhap So Dien Thoai Khach Hang: ";
    getline(cin, SoDienThoai);

    do {
        cout << "Nhap Ngay Dat Hang (dd/mm/yyyy): ";
        getline(cin, NgayThangNam);
        if (!KiemTraDinhDangNgay(NgayThangNam)) {
            cout << "Dinh dang ngay khong hop le. Vui long nhap lai theo dinh dang dd/mm/yyyy.\n";
        }
    } while (!KiemTraDinhDangNgay(NgayThangNam));

    unordered_set<string> menuItems;
    ifstream menuFile("./logs/menu.txt");
    if (menuFile.is_open()) {
        string item;
        while (getline(menuFile, item)) {
            menuItems.insert(ChuyenSangChuHoa(item));
        }
        menuFile.close();
    } else {
        cout << "Khong the mo file menu.txt de kiem tra san pham!" << endl;
        return;
    }

    cout << "Nhap San Pham: ";
    getline(cin, SanPham);
    SanPham = ChuyenSangChuHoa(SanPham);

    while (menuItems.find(SanPham) == menuItems.end()) {
        cout << "San pham khong co trong menu! Vui long nhap lai: ";
        getline(cin, SanPham);
        SanPham = ChuyenSangChuHoa(SanPham);
    }

    // Kiểm tra số lượng nguyên liệu trong kho
    ifstream fileIn("./logs/QuanLyNguyenLieu.txt");
    bool enoughIngredient = false;
    string line;

    while (getline(fileIn, line)) {
        if (ChuyenSangChuHoa(line).find("TEN NGUYEN LIEU: " + SanPham) != string::npos) {
            getline(fileIn, line); // Đọc dòng tiếp theo để lấy số lượng
            int soLuongThem = stoi(line.substr(line.find(":") + 2));
            getline(fileIn, line); // Đọc dòng tiếp theo để lấy mức cảnh báo
            int mucCanhBao = stoi(line.substr(line.find(":") + 2));

            if (soLuongThem <= 0) {
                cout << "Don hang bi HUY do khong du nguyen lieu: " << SanPham << endl;
                cout << "Them DonHang That Bai!" << endl;
                fileIn.close();
                return;
            }
            enoughIngredient = true;
            break;
        }
    }

    fileIn.close();

    if (!enoughIngredient) {
        cout << "Khong tim thay nguyen lieu " << SanPham << " trong danh sach nguyen lieu.\n";
        return;
    }

    cout << "Nhap Tong Tien: ";
    cin >> TongTien;
    cin.ignore();

    cout << "Nhap Ma Uu Dai (hoac 0 neu khong co): ";
    getline(cin, MaUuDai);

    if (MaUuDai != "0") {
        int phanTramGiam = 0;
        MaUuDai = ChuyenSangChuHoa(MaUuDai);
        UuDai uuDai;

        if (uuDai.KiemTraUuDai(MaUuDai, SoDonHangKhachHang(), NgayThangNam, phanTramGiam)) {
            cout << "Ap dung uu dai " << phanTramGiam << "% cho don hang!\n";
            TongTien -= TongTien * phanTramGiam / 100;
        } else {
            cout << "Ma uu dai khong hop le, het han, hoac khong du dieu kien ap dung.\n";
            MaUuDai = "0";
        }
    }

    CapNhatSoDonHang();
    LuuDonHang();

    // Cập nhật lại số lượng nguyên liệu trong kho
    NguyenLieu nguyenLieuCapNhat;
    nguyenLieuCapNhat.CapNhatSoLuongNguyenLieu(SanPham);
}


void DonHang::TimKiemDonHangTheoMa(const string& maDonHang) {
    ifstream file("logs/QuanLyDonHang.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file de tim kiem don hang!" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        if (line.find("Ma Don Hang: " + maDonHang) != string::npos) {
            found = true;
            cout << "THONG TIN DON HANG\n";
            cout << "---------------------------------------------\n";
            cout << line << endl;
            while (getline(file, line) && line.find("---------------------------------------------") == string::npos) {
                cout << line << endl;
            }
            break;
        }
    }

    if (!found) {
        cout << "Khong tim thay don hang voi ma: " << maDonHang << endl;
    }

    file.close();
}

void DonHang::LuuDonHang() {
    ofstream file("logs/QuanLyDonHang.txt", ios::app);
    if (file.is_open()) {
        file << "Ma Don Hang: " << MaDonHang<< "\n";
        file << "Ten Khach Hang: " << TenKhachHang<< "\n";
        file << "So Dien Thoai: " << SoDienThoai << "\n";
        file << "Ngay Dat Hang: " << NgayThangNam << "\n";
        file << "San Pham: " << SanPham << "\n";
        file << "Tong Tien: " << TongTien << "\n";
        file << "Ma Uu Dai: " << (MaUuDai.empty() ? "0" : MaUuDai) << "\n";
        file << "---------------------------------------------\n";
        file.close();
        cout << "Them Don Hang Thanh Cong!" << endl;
    } else {
        cout << "Them don hang khong thanh cong!" << endl;
    }
}



void DonHang::InThongTinDonHang() {
    ifstream file("logs/QuanLyDonHang.txt");
    if (file.is_open()) {
        cout << "THONG TIN DON HANG\n";
        cout << "---------------------------------------------\n";
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Khong the mo file de doc thong tin don hang!" << endl;
    }
}

void DonHang::XoaDonHang(const string& maDonHang) {
    ifstream file("logs/QuanLyDonHang.txt");
    ofstream tempFile("logs/temp.txt");

    if (file.is_open() && tempFile.is_open()) {
        string line;
        bool found = false;

        while (getline(file, line)) {
            if (line.find("Ma Don Hang: " + maDonHang) != string::npos) {
                found = true;
                for (int i = 0; i < 6; ++i) getline(file, line);
                continue;
            }
            tempFile << line << endl;
        }

        file.close();
        tempFile.close();

        if (found) {
            remove("logs/QuanLyDonHang.txt");
            rename("logs/temp.txt", "logs/QuanLyDonHang.txt");
            cout << "Xoa don hang thanh cong!" << endl;
        } else {
            cout << "Khong tim thay don hang de xoa!" << endl;
        }
    } else {
        cout << "Khong the mo file de xoa don hang!" << endl;
    }
}
