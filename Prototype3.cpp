#include <iostream>
#include <string>
#include <iomanip> 

using namespace std;

// Struktur untuk menyimpan informasi produk
struct Produk {
    string nama;
    double harga;
};

// Struktur untuk menyimpan data penjualan harian
struct PenjualanHarian {
    double totalPenjualan;
    int hari;
    int bulan;
    int tahun;
};

// Fungsi untuk menampilkan menu dengan tanggal saat ini
void tampilkanMenu(int hari, int bulan, int tahun) {
    cout << "=== Menu ===" << endl;
    cout << "Tanggal: " << hari << "/" << bulan << "/" << tahun << endl;
    cout << "1. Input Penjualan Harian" << endl;
    cout << "2. Tampilkan Data Penjualan" << endl; // Menu untuk menampilkan data penjualan
    cout << "3. Tampilkan Tabungan Bersih" << endl; // Menu untuk tabungan bersih
    cout << "4. Exit" << endl;
    cout << "Pilih menu: ";
}

// Fungsi untuk input penjualan harian
double inputPenjualan(Produk produk[], int jumlahProduk) {
    double totalPenjualan = 0;
    int kuantitas;

    cout << "Input Penjualan Hari Ini:" << endl;

    for (int i = 0; i < jumlahProduk; i++) {
        cout << produk[i].nama << " (Rp " << produk[i].harga << ") - Masukkan kuantitas: ";
        cin >> kuantitas;

        // Menghitung total penjualan
        totalPenjualan += produk[i].harga * kuantitas;
    }

    return totalPenjualan;
}

// Fungsi untuk menambah satu hari ke tanggal
void tambahSatuHari(int &hari, int &bulan, int &tahun) {
    const int jumlahHari[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    hari++;

    // Cek apakah bulan Februari dan tahun kabisat
    if (bulan == 2 && ((tahun % 4 == 0 && tahun % 100 != 0) || (tahun % 400 == 0))) {
        if (hari > 29) {
            hari = 1;
            bulan++;
        }
    } else if (hari > jumlahHari[bulan - 1]) {
        hari = 1;
        bulan++;
        
        if (bulan > 12) {
            bulan = 1;
            tahun++;
        }
    }
}

// Fungsi untuk menampilkan data penjualan berdasarkan bulan yang dipilih
void tampilkanDataPenjualan(PenjualanHarian penjualan[][31], int bulanDipilih) {
    double totalKeseluruhan = 0;

    cout << "\n=== Data Penjualan Bulan " << bulanDipilih << " ===" << endl;

    for (int h = 0; h < 31; h++) { // Iterasi melalui setiap hari di bulan yang dipilih
        if (penjualan[bulanDipilih - 1][h].totalPenjualan > 0) { // Hanya tampilkan jika ada penjualan
            cout << "Tanggal: "
                 << penjualan[bulanDipilih - 1][h].hari << "/"
                 << penjualan[bulanDipilih - 1][h].bulan << "/"
                 << penjualan[bulanDipilih - 1][h].tahun
                 << " - Total Penjualan: Rp "
                 << fixed << setprecision(2)
                 << penjualan[bulanDipilih - 1][h].totalPenjualan
                 << endl;

            totalKeseluruhan += penjualan[bulanDipilih - 1][h].totalPenjualan; // Menjumlahkan total keseluruhan
        }
    }

    if (totalKeseluruhan > 0) {
        cout << "Total Keseluruhan Penjualan Bulan " 
             << bulanDipilih 
             << ": Rp "
             << fixed<< setprecision(2)
             << totalKeseluruhan 
             << endl;
    } else {
        cout << "Tidak ada data penjualan untuk bulan ini."<<endl;
    }
}

// Fungsi untuk menghitung dan menampilkan tabungan bersih berdasarkan bulan yang dipilih
void tampilkanTabunganBersih(PenjualanHarian penjual[][31], double modalBulanan, int bulanDipilih) {
    double totalPenjualBulanan = 0;

    for (int h = 0; h < 31; h++) { // Iterasi melalui setiap hari di bulan yang dipilih
        totalPenjualBulanan += penjual[bulanDipilih - 1][h].totalPenjualan;
    }

    double tabunganBersih = totalPenjualBulanan - modalBulanan;

    cout << "\n=== Tabungan Bersih Bulan " 
         << bulanDipilih 
         << " ===" 
         << endl;

    cout << "Total Penjualan Bulanan: Rp "
         << fixed<< setprecision(2)
         << totalPenjualBulanan 
         << endl;

    cout << "Modal Bulanan: Rp "
         << fixed<< setprecision(2)
         << modalBulanan 
         << endl;

    
    if (tabunganBersih > 0) {
        cout << "Tabungan Bersih: Rp "
             << fixed<< setprecision(2)
             << tabunganBersih 
             << endl;
    } else {
        cout << "Kerugian: Rp "
             << fixed<< setprecision(2)
             << -tabunganBersih 
             << endl; // Menampilkan kerugian jika negatif
    }
}

// Fungsi utama
int main() {
    const int jumlahProduk = 4; // Jumlah produk
    Produk produk[jumlahProduk] = {
        {"Beras", 10000},
        {"Gula", 8000},
        {"Minyak Goreng", 15000},
        {"Telur", 2000}
    };

    const int MAX_BULAN = 12; // Maksimal jumlah bulan dalam setahun
    const int MAX_HARI = 31; // Maksimal jumlah hari dalam sebulan

    PenjualanHarian penjual[MAX_BULAN][MAX_HARI] = {}; // Array dua dimensi untuk menyimpan data penjual harian

    double modalBulanan;

    cout << "Masukkan Modal Bulanan: Rp ";
    cin >> modalBulanan;

    // Input tanggal awal dari pengguna sebelum menu ditampilkan
    int hariAwal, bulanAwal, tahunAwal;

    cout << "Masukkan Tanggal Awal (DD MM YYYY): ";
    cin >> hariAwal >> bulanAwal >> tahunAwal;

    // Mengatur tanggal awal sebagai tanggal saat ini
    int hari = hariAwal;
    int bulan = bulanAwal;
    int tahun = tahunAwal;

    while (true) {
        tampilkanMenu(hari, bulan, tahun);
        int pilihan;
        cin >> pilihan;

        if (pilihan == 1) { // Input Penjual Harian
            double totalHariIni = inputPenjualan(produk, jumlahProduk);
            // Simpan data penjual harian di array dua dimensi berdasarkan bulan dan hari
            penjual[bulan - 1][hari - 1] = {totalHariIni, hari, bulan, tahun};

            cout << "Total Penjual Hari Ini: Rp "
                 << fixed<< setprecision(2)
                 << totalHariIni 
                 << endl;

            // Tambah satu hari setelah input penjual 
            tambahSatuHari(hari, bulan, tahun);

        } else if (pilihan == 2) { // Tampilkan Data Penjual 
            int bulanDipilih;
            cout << "Pilih Bulan (1-12): ";
            cin >> bulanDipilih;

            if (bulanDipilih >= 1 && bulanDipilih <= MAX_BULAN) {
                tampilkanDataPenjualan(penjual, bulanDipilih);
            } else {
                cout << "Bulan tidak valid! Silakan coba lagi."<<endl;
            }

        } else if (pilihan == 3) { // Tampilkan Tabungan Bersih 
            int bulanDipilih;
            cout << "Pilih Bulan untuk Tabungan Bersih (1-12): ";
            cin >> bulanDipilih;

            if (bulanDipilih >= 1 && bulanDipilih <= MAX_BULAN) {
                tampilkanTabunganBersih(penjual, modalBulanan, bulanDipilih);
            } else {
                cout << "Bulan tidak valid! Silakan coba lagi."<<endl;
            }

        } else if (pilihan == 4) { // Exit 
            break;

        } else {
            cout << "Pilihan tidak valid! Silakan coba lagi."<<endl;
        }
    }

    return 0;
}
