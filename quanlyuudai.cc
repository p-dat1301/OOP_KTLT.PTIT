#include "UuDai.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sys/stat.h>
#include <cctype>
#include <algorithm>

using namespace std;

UuDai::UuDai() 
    : MaUuDai(""), NgayBatDau(""), NgayKetThuc(""), PhanTramGiam(0), DieuKienApDung(0) {}

UuDai::UuDai(string maUuDai, int phanTramGiam, string ngayBatDau, string ngayKetThuc, int dieuKienApDung)
    : MaUuDai(maUuDai), NgayBatDau(ngayBatDau), NgayKetThuc(ngayKetThuc), PhanTramGiam(phanTramGiam), DieuKienApDung(dieuKienApDung) {}

bool UuDai::KiemTraMaUuDaiTrung(const string& ma) {
    ifstream file("./logs/QuanLyUuDai.txt");
    string line;

    if (!file.is_open()) {
        cout << "Khong the mo file de kiem tra ma uu dai.\n";
        return false;
    }

    string maUpper = convertToUpper(ma);

    while (getline(file, line)) {
        if (convertToUpper(line).find("MA UU DAI: " + maUpper) != string::npos) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

string ConvertDateToComparableString(const string &date) {
    return date.substr(6, 4) + date.substr(3, 2) + date.substr(0, 2);
}

string convertToUpper(const string& str) {
    string result = str;
    transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

bool UuDai::KiemTraDinhDangNgay(const string& ngay) {
    if (ngay.length() != 10 || ngay[2] != '/' || ngay[5] != '/') return false;
    for (int i = 0; i < ngay.length(); i++) {
        if (i != 2 && i != 5 && !isdigit(ngay[i])) return false;
    }
    return true;
}

void UuDai::TaoChuongTrinhMoi() {
    do {
        cout << "Nhap ma uu dai: ";
        cin >> MaUuDai;
        MaUuDai = convertToUpper(MaUuDai);

        if (KiemTraMaUuDaiTrung(MaUuDai)) {
            cout << "Ma uu dai da ton tai. Vui long nhap ma khac.\n";
        }
    } while (KiemTraMaUuDaiTrung(MaUuDai));

    do {
        cout << "Nhap ngay bat dau (dd/mm/yyyy): ";
        cin >> NgayBatDau;
        if (!KiemTraDinhDangNgay(NgayBatDau)) {
            cout << "Ngay bat dau khong dung dinh dang. Vui long nhap lai.\n";
        }
    } while (!KiemTraDinhDangNgay(NgayBatDau));

    do {
        cout << "Nhap ngay het han (dd/mm/yyyy): ";
        cin >> NgayKetThuc;
        if (!KiemTraDinhDangNgay(NgayKetThuc)) {
            cout << "Ngay het han khong dung dinh dang. Vui long nhap lai.\n";
        }
    } while (!KiemTraDinhDangNgay(NgayKetThuc));

    do {
        cout << "Nhap phan tram giam (0 - 100): ";
        cin >> PhanTramGiam;
        if (PhanTramGiam < 0 || PhanTramGiam > 100) {
            cout << "Phan tram giam khong hop le. Vui long nhap lai.\n";
        }
    } while (PhanTramGiam < 0 || PhanTramGiam > 100);

    cout << "Nhap dieu kien ap dung (so don hang da mua): ";
    cin >> DieuKienApDung;

    cout << "Uu dai moi da duoc tao thanh cong!\n";
    LuuThongTinUuDai();
}

void UuDai::LuuThongTinUuDai() {
    ofstream file("./logs/QuanLyUuDai.txt", ios::app);
    if (file.is_open()) {
        file << "Ma uu dai: " << MaUuDai << endl
             << "Ngay bat dau: " << NgayBatDau << endl
             << "Ngay het han: " << NgayKetThuc << endl
             << "Giam gia: " << PhanTramGiam << "%" << endl
             << "Dieu kien ap dung: " << DieuKienApDung << " da mua " << endl
             << "------------------------------" << endl;
        file.close();
        cout << "Thong tin uu dai da duoc luu vao file.\n";
    } else {
        cout << "Khong the mo file de luu thong tin uu dai.\n";
    }
}

void UuDai::SuaThongTinChuongTrinh() {
    string maCanSua;
    cout << "Nhap ma uu dai can sua: ";
    cin >> maCanSua;
    maCanSua = convertToUpper(maCanSua);

    ifstream fileIn("./logs/QuanLyUuDai.txt");
    ofstream fileOut("./logs/temp.txt");
    string line;
    bool found = false;

    if (!fileIn.is_open() || !fileOut.is_open()) {
        cout << "Khong the mo file de doc hoac ghi du lieu.\n";
        return;
    }

    while (getline(fileIn, line)) {
        // Kiểm tra nếu dòng chứa mã ưu đãi cần sửa
        if (line.find("Ma uu dai: " + maCanSua) != string::npos) {
            found = true;

            // Nhập các thông tin mới
            cout << "Nhap ma uu dai moi: ";
            cin >> MaUuDai;
            MaUuDai = convertToUpper(MaUuDai);

            do {
                cout << "Nhap ngay bat dau moi (dd/mm/yyyy): ";
                cin >> NgayBatDau;
                if (!KiemTraDinhDangNgay(NgayBatDau)) {
                    cout << "Ngay bat dau khong dung dinh dang. Vui long nhap lai.\n";
                }
            } while (!KiemTraDinhDangNgay(NgayBatDau));

            do {
                cout << "Nhap ngay het han moi (dd/mm/yyyy): ";
                cin >> NgayKetThuc;
                if (!KiemTraDinhDangNgay(NgayKetThuc)) {
                    cout << "Ngay het han khong dung dinh dang. Vui long nhap lai.\n";
                }
            } while (!KiemTraDinhDangNgay(NgayKetThuc));

            do {
                cout << "Nhap phan tram giam moi (0 - 100): ";
                cin >> PhanTramGiam;
                if (PhanTramGiam < 0 || PhanTramGiam > 100) {
                    cout << "Phan tram giam khong hop le. Vui long nhap lai.\n";
                }
            } while (PhanTramGiam < 0 || PhanTramGiam > 100);

            cout << "Nhap dieu kien ap dung moi (so don hang da mua): ";
            cin >> DieuKienApDung;

            // Ghi thông tin mới vào file tạm
            fileOut << "Ma uu dai: " << MaUuDai << endl
                    << "Ngay bat dau: " << NgayBatDau << endl
                    << "Ngay het han: " << NgayKetThuc << endl
                    << "Giam gia: " << PhanTramGiam << "%" << endl
                    << "Dieu kien ap dung: " << DieuKienApDung << " da mua" << endl
                    << "------------------------------" << endl;

            // Bỏ qua các dòng cũ của ưu đãi hiện tại
            for (int i = 0; i < 5; ++i) getline(fileIn, line);

        } else {
            // Ghi các dòng không liên quan đến ưu đãi cần sửa vào file tạm
            fileOut << line << endl;
        }
    }

    fileIn.close();
    fileOut.close();

    if (found) {
        remove("./logs/QuanLyUuDai.txt");
        rename("./logs/temp.txt", "./logs/QuanLyUuDai.txt");
        cout << "Thong tin uu dai da duoc cap nhat.\n";
    } else {
        cout << "Khong tim thay uu dai can sua.\n";
        remove("./logs/temp.txt");
    }
}

bool SoSanhNgay(const string& ngay1, const string& ngay2) {
    // Tách ngày, tháng, năm từ chuỗi ngay1
    int ngay1D, ngay1M, ngay1Y;
    char delim;
    istringstream iss1(ngay1);
    iss1 >> ngay1D >> delim >> ngay1M >> delim >> ngay1Y;

    // Tách ngày, tháng, năm từ chuỗi ngay2
    int ngay2D, ngay2M, ngay2Y;
    istringstream iss2(ngay2);
    iss2 >> ngay2D >> delim >> ngay2M >> delim >> ngay2Y;

    // So sánh theo thứ tự năm, tháng, ngày
    if (ngay1Y != ngay2Y)
        return ngay1Y < ngay2Y;
    if (ngay1M != ngay2M)
        return ngay1M < ngay2M;
    return ngay1D <= ngay2D;
}

bool UuDai::KiemTraUuDai(const string& maUuDai, int soDonHang, const string& ngayHienTai, int& phanTramGiam) {
    ifstream file("./logs/QuanLyUuDai.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file!" << endl;
        return false;
    }

    string line;
    bool isValid = false;
    while (getline(file, line)) {
        if (line.find("Ma uu dai: " + maUuDai) != string::npos) {
            string ngayBatDau, ngayHetHan, dieuKienApDungStr;
            int dieuKienApDung;
            
            // Đọc các thông tin liên quan
            getline(file, line); // Ngày bắt đầu
            ngayBatDau = line.substr(line.find(":") + 2);
            getline(file, line); // Ngày hết hạn
            ngayHetHan = line.substr(line.find(":") + 2);
            getline(file, line); // Điều kiện áp dụng
            dieuKienApDungStr = line.substr(line.find(":") + 2);
            dieuKienApDung = stoi(dieuKienApDungStr);

            // Kiểm tra ngày và số đơn hàng
            if (SoSanhNgay(ngayBatDau, ngayHienTai) && SoSanhNgay(ngayHienTai, ngayHetHan) && soDonHang >= dieuKienApDung) {
                phanTramGiam = stoi(line.substr(line.find(":") + 2)); // Lấy phần trăm giảm giá
                isValid = true;
                break;
            }
        }
    }

    file.close();
    return isValid;
}


void UuDai::XemDanhSachUuDai() {
    ifstream file("./logs/QuanLyUuDai.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file QuanLyUuDai.txt!" << endl;
        return;
    }

    string line;
    cout << "Danh sach uu dai:\n";
    cout << "---------------------------------------------\n";
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}



void UuDai::TimKiemUuDaiTheoMa() {
    string maCanTim;
    cout << "Nhap ma uu dai can tim: ";
    cin >> maCanTim;
    maCanTim = convertToUpper(maCanTim);

    ifstream file("./logs/QuanLyUuDai.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file QuanLyUuDai.txt!" << endl;
        return;
    }

    string line;
    bool found = false;
    while (getline(file, line)) {
        if (convertToUpper(line).find("MA UU DAI: " + maCanTim) != string::npos) {
            found = true;
            cout << "Thong tin uu dai:\n";
            cout << "---------------------------------------------\n";
            cout << line << endl;
            while (getline(file, line) && line.find("---------------------------------------------") == string::npos) {
                cout << line << endl;
            }
            break;
        }
    }

    if (!found) {
        cout << "Khong tim thay uu dai voi ma: " << maCanTim << endl;
    }

    file.close();
}


void UuDai::LietKeUuDaiHetHan() {
    ifstream file("./logs/QuanLyUuDai.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file QuanLyUuDai.txt!" << endl;
        return;
    }

    string line, ngayHienTai;
    cout << "Nhap ngay hien tai (dd/mm/yyyy): ";
    cin >> ngayHienTai;

    // Kiểm tra định dạng ngày hiện tại
    while (!KiemTraDinhDangNgay(ngayHienTai)) {
        cout << "Ngay hien tai khong dung dinh dang. Vui long nhap lai (dd/mm/yyyy): ";
        cin >> ngayHienTai;
    }

    // Chuyển đổi ngày hiện tại sang định dạng có thể so sánh
    string ngayHienTaiComparable = ConvertDateToComparableString(ngayHienTai);

    cout << "Danh sach uu dai het han:\n";
    cout << "---------------------------------------------\n";

    bool uuDaiHetHan = false;
    string maUuDai, ngayBatDau, ngayKetThuc, giamGia, dieuKienApDung;

    while (getline(file, line)) {
        if (line.find("Ma uu dai: ") != string::npos) {
            maUuDai = line;
        } else if (line.find("Ngay bat dau: ") != string::npos) {
            ngayBatDau = line;
        } else if (line.find("Ngay het han: ") != string::npos) {
            ngayKetThuc = line;
        } else if (line.find("Giam gia: ") != string::npos) {
            giamGia = line;
        } else if (line.find("Dieu kien ap dung: ") != string::npos) {
            dieuKienApDung = line;

            // Chuyển đổi ngày hết hạn để so sánh
            string ngayHetHanComparable = ConvertDateToComparableString(ngayKetThuc.substr(14));

            // Kiểm tra nếu ưu đãi đã hết hạn
            if (ngayHetHanComparable < ngayHienTaiComparable) {
                uuDaiHetHan = true;
                cout << maUuDai << endl
                     << ngayBatDau << endl
                     << ngayKetThuc << endl
                     << giamGia << endl
                     << dieuKienApDung << endl;
                cout << "---------------------------------------------\n";
            }
        }
    }

    if (!uuDaiHetHan) {
        cout << "Khong co uu dai nao da het han.\n";
    }

    file.close();
}


void UuDai::XoaUuDaiTheoMa() {
    string maCanXoa;
    cout << "Nhap ma uu dai can xoa: ";
    cin >> maCanXoa;
    maCanXoa = convertToUpper(maCanXoa);

    ifstream fileIn("./logs/QuanLyUuDai.txt");
    ofstream fileOut("./logs/temp.txt");
    string line;
    bool found = false;

    if (!fileIn.is_open()) {
        cout << "Khong the mo file QuanLyUuDai.txt!" << endl;
        return;
    }

    while (getline(fileIn, line)) {
        if (convertToUpper(line).find("MA UU DAI: " + maCanXoa) != string::npos) {
            found = true;
            // Skip the next lines (the program details)
            for (int i = 0; i < 5; ++i) getline(fileIn, line); 
            continue;  // Skip this block and don't copy it to temp file
        }
        fileOut << line << endl;
    }

    fileIn.close();
    fileOut.close();

    if (found) {
        remove("./logs/QuanLyUuDai.txt");
        rename("./logs/temp.txt", "./logs/QuanLyUuDai.txt");
        cout << "Uu dai da duoc xoa!" << endl;
    } else {
        cout << "Khong tim thay uu dai can xoa!" << endl;
        remove("./logs/temp.txt");
    }
}
