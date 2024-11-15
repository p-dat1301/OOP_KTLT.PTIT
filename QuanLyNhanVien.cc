#include <algorithm> 
#include "NhanVien.h"
#include <fstream>
#include <iostream>
using namespace std;

// Hàm chuyển chuỗi thành chữ hoa
string ChuyenChuoiThanhChuHoa(const string& str) {
    string chuoiChuHoa = str;
    transform(chuoiChuHoa.begin(), chuoiChuHoa.end(), chuoiChuHoa.begin(), ::toupper);
    return chuoiChuHoa;
}

NhanVien::NhanVien() {}

NhanVien::NhanVien(string maNV, string tenNV, string sdt, string chucVu)
    : MaNhanVien(ChuyenChuoiThanhChuHoa(maNV)), 
      TenNhanVien(ChuyenChuoiThanhChuHoa(tenNV)), 
      SoDienThoai(sdt), 
      ChucVu(ChuyenChuoiThanhChuHoa(chucVu)) {}


bool NhanVien::KiemTraMaNhanVienTonTai(const string& maNV) {
    ifstream file("logs/ThongTinNhanVien.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.find("Ma Nhan Vien: ") != string::npos) {
                string maNhanVienTrongFile = line.substr(14);
                if (ChuyenChuoiThanhChuHoa(maNhanVienTrongFile) == ChuyenChuoiThanhChuHoa(maNV)) {
                    file.close();
                    return true; // Mã nhân viên đã tồn tại
                }
            }
        }
        file.close();
    }
    return false; // Mã nhân viên không tồn tại
}

void NhanVien::NhapNhanVienMoi() {
    cin.ignore();
    do {
        cout << "Nhap Ma Nhan Vien: ";
        getline(cin, MaNhanVien);
        MaNhanVien = ChuyenChuoiThanhChuHoa(MaNhanVien);

        if (KiemTraMaNhanVienTonTai(MaNhanVien)) {
            cout << "Ma Nhan Vien da ton tai. Vui long nhap lai!\n";
        }
    } while (KiemTraMaNhanVienTonTai(MaNhanVien));

    cout << "Nhap Ten Nhan Vien: ";
    getline(cin, TenNhanVien);
    TenNhanVien = ChuyenChuoiThanhChuHoa(TenNhanVien);

    cout << "Nhap So Dien Thoai: ";
    getline(cin, SoDienThoai);

    // Kiểm tra chức vụ trong BangLuong.txt
    do {
        cout << "Nhap Chuc Vu: ";
        getline(cin, ChucVu);
        ChucVu = ChuyenChuoiThanhChuHoa(ChucVu);
        Luong = LayLuongTheoChucVu(ChucVu);
        
        if (Luong == -1) {
            cout << "Chuc vu khong ton tai. Vui long nhap lai.\n";
        } else {
            cout << "Luong cho chuc vu " << ChucVu << " la: " << Luong << " / Ngay\n";
        }
    } while (Luong == -1); // Yêu cầu nhập lại nếu chức vụ không tồn tại
}

double NhanVien::LayLuongTheoChucVu(const string& chucVu) {
    ifstream file("logs/BangLuong.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.find("Chuc Vu: " + chucVu) != string::npos) {
                // Lấy dòng tiếp theo chứa lương
                getline(file, line);
                file.close();
                return stod(line.substr(7)); // Lấy giá trị lương sau "Luong: "
            }
        }
        file.close();
    }
    return -1; // Trả về -1 nếu không tìm thấy chức vụ
}

void NhanVien::LuuThongTinNhanVien() {
    ofstream file("logs/ThongTinNhanVien.txt", ios::app);
    if (file.is_open()) {
        file << "Ma Nhan Vien: " << MaNhanVien << "\n";
        file << "Ten Nhan Vien: " << TenNhanVien << "\n";
        file << "So Dien Thoai: " << SoDienThoai << "\n";
        file << "Chuc Vu: " << ChucVu << "\n";
        file << "Luong: " << Luong << " / Ngay\n";
        file << "---------------------------------------------\n";
        file.close();
        cout << "Them Nhan Vien Thanh Cong!" << endl;
    } else {
        cout << "Them nhan vien khong thanh cong!" << endl;
    }
}

void NhanVien::InThongTinNhanVien() {
    ifstream file("logs/ThongTinNhanVien.txt");
    if (file.is_open()) {
        cout << "THONG TIN NHAN VIEN\n";
        cout << "---------------------------------------------\n";
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    } else {
        cout << "Khong the mo file de doc thong tin nhan vien!" << endl;
    }
}

void NhanVien::XoaNhanVien(const string& maNVXoa) {
    ifstream file("logs/ThongTinNhanVien.txt");
    ofstream tempFile("logs/temp.txt");

    if (!file.is_open() || !tempFile.is_open()) {
        cout << "Khong the mo file de xoa nhan vien!" << endl;
        return;
    }

    string line;
    bool found = false;
    string maNVUpper = ChuyenChuoiThanhChuHoa(maNVXoa);

    while (getline(file, line)) {
        if (line.find("Ma Nhan Vien: ") != string::npos) {
            string maNhanVienTrongFile = ChuyenChuoiThanhChuHoa(line.substr(14));
            if (maNhanVienTrongFile == maNVUpper) {
                found = true;
                // Bỏ qua các dòng tiếp theo chứa thông tin của nhân viên cần xóa
                for (int i = 0; i < 4; ++i) getline(file, line);
                continue;
            }
        }
        tempFile << line << endl;
    }

    file.close();
    tempFile.close();

    if (found) {
        remove("logs/ThongTinNhanVien.txt");
        rename("logs/temp.txt", "logs/ThongTinNhanVien.txt");
        cout << "Xoa nhan vien '" << maNVXoa << "' thanh cong!" << endl;
    } else {
        cout << "Khong tim thay nhan vien '" << maNVXoa << "' de xoa!" << endl;
        remove("logs/temp.txt");
    }
}

void NhanVien::SuaNhanVien(const string& maCanSua) {
    ifstream fileIn("./logs/ThongTinNhanVien.txt");
    ofstream fileOut("./logs/temp.txt");
    string line;
    bool found = false;

    if (!fileIn.is_open() || !fileOut.is_open()) {
        cout << "Khong the mo file de doc hoac ghi du lieu.\n";
        return;
    }

    while (getline(fileIn, line)) {
        // Kiểm tra nếu đây là dòng chứa mã nhân viên cần sửa
        if (line.find("Ma Nhan Vien: " + ChuyenChuoiThanhChuHoa(maCanSua)) != string::npos) {
            found = true;

            // Nhập các thông tin mới
            cout << "Nhap Ma Nhan Vien Moi: ";
            getline(cin, MaNhanVien);
            MaNhanVien = ChuyenChuoiThanhChuHoa(MaNhanVien);

            cout << "Nhap Ten Nhan Vien Moi: ";
            getline(cin, TenNhanVien);
            TenNhanVien = ChuyenChuoiThanhChuHoa(TenNhanVien);

            cout << "Nhap So Dien Thoai Moi: ";
            getline(cin, SoDienThoai);

            do {
                cout << "Nhap Chuc Vu Moi: ";
                getline(cin, ChucVu);
                ChucVu = ChuyenChuoiThanhChuHoa(ChucVu);
                Luong = LayLuongTheoChucVu(ChucVu);

                if (Luong == -1) {
                    cout << "Chuc vu khong ton tai. Vui long nhap lai.\n";
                } else {
                    cout << "Luong cho chuc vu " << ChucVu << " la: " << Luong << " / Ngay\n";
                }
            } while (Luong == -1);

            // Ghi thông tin mới vào file tạm, thay thế thông tin cũ
            fileOut << "Ma Nhan Vien: " << MaNhanVien << endl
                    << "Ten Nhan Vien: " << TenNhanVien << endl
                    << "So Dien Thoai: " << SoDienThoai << endl
                    << "Chuc Vu: " << ChucVu << endl
                    << "Luong: " << Luong << " / Ngay" << endl;

            // Bỏ qua các dòng cũ của nhân viên hiện tại
            for (int i = 0; i < 4; ++i) getline(fileIn, line);
        } else {
            // Ghi lại các dòng không thuộc nhân viên cần sửa
            fileOut << line << endl;
        }
    }

    fileIn.close();
    fileOut.close();

    if (found) {
        remove("./logs/ThongTinNhanVien.txt");
        rename("./logs/temp.txt", "./logs/ThongTinNhanVien.txt");
        cout << "Thong tin nhan vien da duoc cap nhat.\n";
    } else {
        cout << "Khong tim thay nhan vien can sua.\n";
        remove("./logs/temp.txt");
    }
}




bool NhanVien::TimKiemNhanVien(const string& maNV) {
    ifstream file("logs/ThongTinNhanVien.txt");
    bool found = false;
    string maNVUpper = ChuyenChuoiThanhChuHoa(maNV);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.find("Ma Nhan Vien: ") != string::npos) {
                string maNhanVienTrongFile = line.substr(14); // Lấy mã nhân viên từ dòng
                if (ChuyenChuoiThanhChuHoa(maNhanVienTrongFile) == maNVUpper) {
                    found = true;
                    cout << "Thong tin nhan vien:\n" << line << endl;
                    for (int i = 0; i < 4; ++i) { // Các dòng thông tin tiếp theo
                        getline(file, line);
                        cout << line << endl;
                    }
                    break;
                }
            }
        }
        file.close();
    } else {
        cout << "Khong the mo file de tim kiem nhan vien!" << endl;
    }

    if (!found) cout << "Khong tim thay nhan vien!" << endl;
    return found;
}


void NhanVien::TinhLuongNhanVien() {
    string maNV;
    int soNgayLamViec;
    bool found = false;

    cout << "Nhap Ma Nhan Vien: ";
    cin.ignore();
    getline(cin, maNV);
    maNV = ChuyenChuoiThanhChuHoa(maNV);

    ifstream file("logs/ThongTinNhanVien.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file de tinh luong nhan vien!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.find("Ma Nhan Vien: " + maNV) != string::npos) {
            found = true;
            cout << "Nhap So Ngay Lam Viec Trong Thang: ";
            cin >> soNgayLamViec;

            // Đọc thông tin lương từ file
            for (int i = 0; i < 4; ++i) getline(file, line); // Bỏ qua các dòng tên, sdt, chức vụ

            if (line.find("Luong: ") != string::npos) {
                double luongCoBan = stod(line.substr(7)); // Lấy lương từ dòng "Luong: "
                double luongThang = luongCoBan * soNgayLamViec;
                cout << "Luong thang cua nhan vien " << maNV << " la: " << luongThang << " VND\n";
            }
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "Khong tim thay nhan vien voi ma " << maNV << "!\n";
    }
}