#include "DoanhThu.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <algorithm>
using namespace std;



DoanhThu::DoanhThu() {}

string ToUpperCase(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}


void DoanhThu::CapNhatDoanhThu() {
    ifstream fileIn("logs/QuanLyDonHang.txt");
    ofstream fileOut("logs/QuanLyDoanhThu.txt");

    if (!fileIn.is_open()) {
        cout << "Khong the mo file QuanLyDonHang.txt de cap nhat doanh thu!" << endl;
        return;
    }
    if (!fileOut.is_open()) {
        cout << "Khong the mo file QuanLyDoanhThu.txt de ghi!" << endl;
        return;
    }

    string line;
    
    while (getline(fileIn, line)) {
        if (line.find("Ma Don Hang: ") != string::npos) {
            fileOut << line << "\n"; 

            getline(fileIn, line);
            fileOut << line << "\n";

            getline(fileIn, line);
            fileOut << line << "\n";

            getline(fileIn, line);
            fileOut << line << "\n"; 

            getline(fileIn, line); 
            fileOut << line << "\n";

            getline(fileIn, line);
            fileOut << line << "\n";

            
            fileOut << "---------------------------------------------\n";
        }
    }

    fileIn.close();
    fileOut.close();

    cout << "Cap nhat thong tin doanh thu thanh cong tu QuanLyDonHang.txt vao QuanLyDoanhThu.txt\n";
}


void DoanhThu::TinhTongDoanhThu(string period) {
    ifstream file("logs/QuanLyDoanhThu.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file QuanLyDoanhThu.txt de tinh tong doanh thu!" << endl;
        return;
    }

    string ngayCanTim;
    if (period == "ngay") {
        string day, month, year;
        cout << "Nhap ngay (dd): ";
        cin >> day;
        cout << "Nhap thang (mm): ";
        cin >> month;
        cout << "Nhap nam (yyyy): ";
        cin >> year;
        ngayCanTim = day + "/" + month + "/" + year;
    } else if (period == "thang") {
        string month, year;
        cout << "Nhap thang (mm): ";
        cin >> month;
        cout << "Nhap nam (yyyy): ";
        cin >> year;
        ngayCanTim = month + "/" + year;
    } else if (period == "nam") {
        cout << "Nhap nam (yyyy): ";
        cin >> ngayCanTim;
    } else {
        cout << "Loai ky bao cao khong hop le!" << endl;
        return;
    }

    double tongDoanhThu = 0.0;
    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line.find("Ngay Dat Hang: ") != string::npos) {
            string ngayDatHang = line.substr(15); 

            
            if ((period == "ngay" && ngayDatHang == ngayCanTim) ||
                (period == "thang" && ngayDatHang.substr(3) == ngayCanTim) ||
                (period == "nam" && ngayDatHang.substr(6) == ngayCanTim)) {

                found = true;
                getline(file, line); // Dòng sản phẩm
                getline(file, line); // Dòng tổng tiền
                double soTien = stod(line.substr(11)); // Lấy giá trị sau "Tong Tien: "
                tongDoanhThu += soTien;
            }
        }
    }

    file.close();

    if (found) {
        cout << "Tong doanh thu " << period << " " << ngayCanTim << " la: " << tongDoanhThu << " VND\n";
    } else {
        cout << "Khong co doanh thu cho " << period << " " << ngayCanTim << ".\n";
    }
}





void DoanhThu::ThongKeDoanhThuCacLoaiDoUong() {
    ifstream file("logs/QuanLyDoanhThu.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file QuanLyDoanhThu.txt de thong ke doanh thu cac loai do uong!" << endl;
        return;
    }

    string period, ngayCanTim;
    cout << "Nhap ky thong ke (ngay/thang/nam): ";
    cin >> period;

    
    if (period == "ngay") {
        string day, month, year;
        cout << "Nhap ngay (dd): ";
        cin >> day;
        cout << "Nhap thang (mm): ";
        cin >> month;
        cout << "Nhap nam (yyyy): ";
        cin >> year;
        ngayCanTim = day + "/" + month + "/" + year;
    } else if (period == "thang") {
        string month, year;
        cout << "Nhap thang (mm): ";
        cin >> month;
        cout << "Nhap nam (yyyy): ";
        cin >> year;
        ngayCanTim = month + "/" + year;
    } else if (period == "nam") {
        cout << "Nhap nam (yyyy): ";
        cin >> ngayCanTim;
    } else {
        cout << "Loai ky thong ke khong hop le!" << endl;
        return;
    }

    map<string, int> thongKeDoUong;
    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line.find("Ngay Dat Hang: ") != string::npos) {
            string ngayDatHang = line.substr(15);

            if ((period == "ngay" && ngayDatHang == ngayCanTim) ||
                (period == "thang" && ngayDatHang.substr(3) == ngayCanTim) ||
                (period == "nam" && ngayDatHang.substr(6) == ngayCanTim)) {

                found = true;
                getline(file, line); // Dòng sản phẩm
                string sanPham = line.substr(10);
                thongKeDoUong[sanPham]++;
            }
        }
    }

    file.close();

    if (found) {
        cout << "Thong ke san pham ban duoc trong " << period << " " << ngayCanTim << ":\n";
        for (const auto& pair : thongKeDoUong) {
            cout << "San pham: " << pair.first << " - So luong: " << pair.second << "\n";
        }
    } else {
        cout << "Khong co don hang nao trong " << period << " " << ngayCanTim << ".\n";
    }
}



void DoanhThu::TimKiemDoanhThuTheoMaDonHang() {
    ifstream file("logs/QuanLyDoanhThu.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file QuanLyDoanhThu.txt de tim kiem doanh thu theo ma don hang!" << endl;
        return;
    }

    string maDonHang;
    cout << "Nhap ma don hang: ";
    getline(cin, maDonHang);
    maDonHang = ToUpperCase(maDonHang);

    string line;
    bool found = false;

    while (getline(file, line)) {
        if (line.find("Ma Don Hang: ") != string::npos) {
            string maDon = ToUpperCase(line.substr(13));

            if (maDon == maDonHang) {
                found = true;
                // Bỏ qua các dòng cho đến khi đến dòng tổng tiền
                getline(file, line); // Ten Khach Hang
                getline(file, line); // So Dien Thoai
                getline(file, line); // Ngay Dat Hang
                getline(file, line); // San Pham
                getline(file, line); // Tong Tien
                double tongTien = stod(line.substr(11)); // Lấy giá trị sau "Tong Tien: "
                cout << "Tong tien cho ma don hang " << maDonHang << " la: " << tongTien << " VND\n";
                break;
            }
        }
    }

    file.close();

    if (!found) {
        cout << "Khong tim thay don hang voi ma don hang " << maDonHang << ".\n";
    }
}


