#include "Sach.h"
#include <fstream>
#include <iostream>
#include <random>
#include <unordered_set>
#include<bits/stdc++.h>
using namespace std;



Sach::Sach() {}

string upper(string s){
    string ans="";
    for (int i=0; i<s.length(); i++){
        ans+=toupper(s[i]);
    }
    return ans;
}


Sach::Sach(string tenSach, string tenTG, string tenNXB,int NamXuatBan)
    : TenSach(tenSach), TenTG(tenTG) ,NXB(tenNXB), NamXuatBan(NamXuatBan) {}

void Sach::NhapSachMoi() {
    cin.ignore();
    cout << "Nhap Ten Sach: ";
    string TenSachTmp;
    getline(cin, TenSachTmp);
    TenSach = upper(TenSachTmp);

    cout << "Nhap Ten Tac Gia: ";
    string TenTGTmp;
    getline(cin, TenTGTmp);
    TenTG = upper(TenTGTmp);

    cout << "Nhap nha XB: ";
    string TenNXBTmp;
    getline(cin, TenNXBTmp);
    NXB = upper(TenNXBTmp);
    
    cout << "Nhap Nam Xuat Ban: ";
    cin>>NamXuatBan;

}


//----------------




void Sach::LuuThongTinSach() { 

    ofstream file("logs/ThongTinSach.txt", ios::app);
    if (file.is_open()) {
        file << "Ten Sach: " << TenSach << "\n";
        file << "Ten Tac Gia: " << TenTG << "\n";
        file << "Ten Nha XB: " << NXB << "\n";
        file << "Nam Xuat Ban: " << NamXuatBan << "\n";
        file << "---------------------------------------------\n";
        file.close();
        cout << "Them Sach Thanh Cong!" << endl;
    } else {
        cout << "Them sach khong thanh cong!" << endl;
    }
}

//--------------------
void Sach :: InThongTinSach() {
    ifstream file("logs/ThongTinSach.txt");
    if (file.is_open()) {
        cout<<"THONG TIN SACH\n";
        cout<< "---------------------------------------------\n";
        string line;
        while (getline(file, line)) {
            cout << line << endl;  
        }
        file.close();
    } else {
        cout << "Khong the mo file de doc thong tin sach!" << endl;
    }
}

//-------------------

void Sach::XoaSach() {
    cout << "Nhap Ten Sach Can Xoa: ";
    string tenSachXoa;
    cin.ignore();
    getline(cin, tenSachXoa);
    tenSachXoa = upper(tenSachXoa);

    ifstream file("logs/ThongTinSach.txt");
    ofstream tempFile("logs/temp.txt");

    if (file.is_open() && tempFile.is_open()) {
        string line;
        bool found = false;

        while (getline(file, line)) {
            if (line == "Ten Sach: " + tenSachXoa) {
                found = true;
                
                for (int i = 0; i < 4; ++i) getline(file, line);
                continue;
            }
            tempFile << line << endl;
        }

        file.close();
        tempFile.close();

        remove("logs/ThongTinSach.txt");
        rename("logs/temp.txt", "logs/ThongTinSach.txt");

        if (found) {
            cout << "Xoa sach '" << tenSachXoa << "' thanh cong!" << endl;
        } else {
            cout << "Khong tim thay sach '" << tenSachXoa << "' de xoa!" << endl;
        }
    } else {
        cout << "Khong the mo file de xoa sach!" << endl;
    }
}

//-------------------

void Sach::TimKiemSach() {
    cout << "Nhap Ten Sach Can Tim: ";
    string keyword;
    cin.ignore();
    getline(cin, keyword);
    keyword = upper(keyword);  

    ifstream file("logs/ThongTinSach.txt");
    if (!file.is_open()) {
        cout << "Khong the mo file!" << endl;
        return;
    }

    bool found = false;
    string line;

    while (getline(file, line)) {
        
        if (line.find("Ten Sach: " + keyword) != string::npos) {
            found = true;

            
            cout << line << endl; 

            // Đọc và in các thông tin tiếp theo
            getline(file, line); // Tên tác giả
            cout << line << endl;

            getline(file, line); // Nhà xuất bản
            cout << line << endl;

            getline(file, line); // Năm xuất bản
            cout << line << endl;

            cout << "---------------------------------------------" << endl; 
        }
    }

    if (!found) {
        cout << "Khong tim thay sach!" << endl;
    }

    file.close();
}

void Sach::ChinhSuaThongTinSach() {
    cout << "Nhap Ten Sach Can Chinh Sua: ";
    string tenSachSua;
    cin.ignore();
    getline(cin, tenSachSua);
    tenSachSua = upper(tenSachSua); 

    ifstream file("logs/ThongTinSach.txt");
    ofstream tempFile("logs/temp.txt");

    if (file.is_open() && tempFile.is_open()) {
        string line;
        bool found = false;

        while (getline(file, line)) {
            if (line == "Ten Sach: " + tenSachSua) { 
                found = true;
                cout << "Nhap Thong Tin Moi Cho Sach:\n";
                
                
                cout << "Nhap Ten Sach: ";
                getline(cin, TenSach);
                TenSach = upper(TenSach);
                cout << "Nhap Ten Tac Gia: ";
                getline(cin, TenTG);
                TenTG = upper(TenTG);
                cout << "Nhap Nha XB: ";
                getline(cin, NXB);
                NXB = upper(NXB);
                cout << "Nhap Nam Xuat Ban: ";
                cin >> NamXuatBan;
                cin.ignore();

               
                tempFile << "Ten Sach: " << TenSach << endl;
                tempFile << "Ten Tac Gia: " << TenTG << endl;
                tempFile << "Ten Nha XB: " << NXB << endl;
                tempFile << "Nam Xuat Ban: " << NamXuatBan << endl;
                tempFile << "---------------------------------------------" << endl;

                
                for (int i = 0; i < 4; ++i) getline(file, line);
            } else {
                tempFile << line << endl;
            }
        }

        file.close();
        tempFile.close();

        remove("logs/ThongTinSach.txt");
        rename("logs/temp.txt", "logs/ThongTinSach.txt");

        if (found) {
            cout << "Chinh sua thong tin sach thanh cong!" << endl;
        } else {
            cout << "Khong tim thay sach can chinh sua!" << endl;
        }
    } else {
        cout << "Khong the mo file de chinh sua thong tin sach!" << endl;
    }
}





