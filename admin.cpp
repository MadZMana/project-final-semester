#include <iostream>
#include <fstream>
using namespace std;

int login() {
    string password;
    cout << "Masukkan password admin: ";
    ifstream passwordFile("password.txt");
    if (passwordFile.is_open()) {
        getline(passwordFile, password);
        passwordFile.close();
        string inputPassword;
        cin >> inputPassword;
        if (inputPassword == password) {
            cout << "Password benar. Anda adalah admin." << endl;
        } else {
            cout << "Password salah. Akses ditolak." << endl;
            return 1;
        }
    } else {
        cout << "Tidak dapat membuka file password." << endl;
        return 1;
    }
    return 0;
}

int main() {
    int pilihan = 0;
    cout << "Apa yang anda inginkan: " << "\n";
    cout << "1. Menambahkan barang" << "\n";
    cout << "2. Membeli barang" << "\n";
    cin >> pilihan;
    if (pilihan == 1) {
        if (login() == 0) {
            cout << "Berapa barang yang ingin ditambahkan: ";
            int jumlahBarang;
            cin >> jumlahBarang;
            string barang[jumlahBarang];
            int harga[jumlahBarang];
            for (int i = 0; i < jumlahBarang; i++) {
                cout << "Nama barang: ";
                cin >> barang[i];
                cout << "Harga barang: ";
                cin >> harga[i];
                ofstream barangFile("barang.txt", ios::app);
            if (barangFile.is_open()) {
                barangFile << barang[i] << " " << harga[i] << endl;
                barangFile.close();
                cout << "Barang berhasil ditambahkan." << endl;
            } else {
                cout << "Tidak dapat membuka file barang." << endl;
            }
        }
    }} else if (pilihan == 2) {
        cout << "Anda memilih untuk membeli barang." << endl;
        cout << "Berikut adalah daftar barang yang tersedia: " << endl;
        ifstream barangFile("barang.txt");
        if (barangFile.is_open()) {
            string line;
            int lineNumber = 1;
            while (getline(barangFile, line)) {
            cout << lineNumber << ". " << line << endl;
            lineNumber++;
            }
            barangFile.close();
        } else {
            cout << "Tidak dapat membuka file barang." << endl;
        }
    } else {
        cout << "Pilihan tidak valid." << endl;
    }
}