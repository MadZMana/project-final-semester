#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct barang {
    string nama;
    float harga;
    unsigned int jumlah;
};

void saveToFile(barang* isi, int size) {
    ofstream file("barang.txt");
    if (!file) {
        cerr << "Data tidak ditemukan" << endl;
        return;
    }

    for (int i = 0; i < size; ++i) {
        file << isi[i].nama << " " << isi[i].harga << " " << isi[i].jumlah << endl;
    }
    file.close();
}

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

void menuPembeli() {
    // Membaca data dari file
    ifstream file("barang.txt");
    if (!file) {
        cerr << "Data tidak ditemukan" << endl;
        return;
    }

    // Hitung jumlah barang
    int count = 0;
    string line;
    while (getline(file, line)) {
        count++;
    }
    file.clear();
    file.seekg(0, ios::beg);

    // Alokasikan memori untuk barang
    barang* isi = new barang[count];

    for (int i = 0; i < count; ++i) {
        file >> isi[i].nama >> isi[i].harga >> isi[i].jumlah;
        if (file.fail()) {
            cerr << "Data tidak ditemukan" << i + 1 << endl;
            delete[] isi;
            return;
        }
    }
    file.close();

    int choice = 1;
    cout << "\n Nama\t\tHarga\tJumlah";
    cout << "\n---------------------------------------";
    while (choice != count + 1) {
        for (int i = 0; i < count; ++i) {
            cout << "\n " << (i + 1) << ") " << isi[i].nama
                 << "\t" << isi[i].harga
                 << "\t(" << isi[i].jumlah << ")";
        }
        cout << "\n " << (count + 1) << ") Batal \n\n";
        cout << "Pilih barang: ";
        cin >> choice;

        if (choice >= 1 && choice <= count) {
            if (isi[choice - 1].jumlah == 0) {
                cout << "\n" << isi[choice - 1].nama << " habis";
                getchar();
                getchar();
                continue;
            }
        }

        if (choice == count + 1)
            cout << "Terima kasih telah menggunakan layanan kami";
        else if (choice <= count) {
            float uang;
            cout << "Masukkan uang: ";
            cin >> uang;

            float harga = isi[choice - 1].harga;
            if (uang < harga) {
                cout << "Uang tidak cukup.";
                getchar();
                getchar();
                continue;
            }

            cout << "Uang kembalian: " << "Rp. " << (uang - harga) << "\n";
            isi[choice - 1].jumlah = isi[choice - 1].jumlah - 1;

            cout << "Barang tersisa: " << isi[choice - 1].jumlah << "\n";
            cout << "Terima kasih telah berbelanja" << "\n";

            // Perbarui file dengan data terbaru
            saveToFile(isi, count);

            getchar();
            getchar();
        } else {
            cout << "Barang tidak ada di menu";
        }
        break;
    }

    delete[] isi;
}

void menuPenjual() {
    if (login() == 0) {
        // Membaca data dari file
        ifstream file("barang.txt");
        if (!file) {
            cerr << "Data tidak ditemukan" << endl;
            return;
        }

        // Hitung jumlah barang
        int count = 0;
        string line;
        while (getline(file, line)) {
            count++;
        }
        file.clear();
        file.seekg(0, ios::beg);

        // Alokasikan memori untuk barang
        barang* isi = new barang[count];

        for (int i = 0; i < count; ++i) {
            file >> isi[i].nama >> isi[i].harga >> isi[i].jumlah;
            if (file.fail()) {
                cerr << "Data tidak ditemukan" << i + 1 << endl;
                delete[] isi;
                return;
            }
        }
        file.close();

        cout << "Berapa barang yang ingin ditambahkan: ";
        int jumlahBarang;
        cin >> jumlahBarang;
        for (int i = 0; i < jumlahBarang; i++) {
            string namaBarang;
            float hargaBarang;
            unsigned int jumlahBarangBaru;
            cout << "Nama barang: ";
            cin >> namaBarang;
            cout << "Harga barang: ";
            cin >> hargaBarang;
            cout << "Jumlah barang: ";
            cin >> jumlahBarangBaru;

            // Ubah huruf pertama menjadi kapital
            if (!namaBarang.empty()) {
                namaBarang[0] = toupper(namaBarang[0]);
            }

            bool found = false;
            for (int j = 0; j < count; j++) {
                if (isi[j].nama == namaBarang) {
                    isi[j].jumlah += jumlahBarangBaru;
                    found = true;
                    break;
                }
            }

            if (!found) {
                barang* temp = new barang[count + 1];
                for (int j = 0; j < count; j++) {
                    temp[j] = isi[j];
                }
                temp[count].nama = namaBarang;
                temp[count].harga = hargaBarang;
                temp[count].jumlah = jumlahBarangBaru;
                delete[] isi;
                isi = temp;
                count++;
            }
        }

        // Perbarui file dengan data terbaru
        saveToFile(isi, count);

        delete[] isi;
        cout << "Barang berhasil ditambahkan." << endl;
    }
}

int main() {
    int pilihan = 0;
    cout << "1. Menambahkan barang" << "\n";
    cout << "2. Membeli barang" << "\n";
    cout << "Apa yang anda inginkan: ";
    cin >> pilihan;
    switch (pilihan)
    {
    case 1:
        menuPenjual();
        break;
    case 2:
        menuPembeli();
        break;
    }
    return 0;
}
