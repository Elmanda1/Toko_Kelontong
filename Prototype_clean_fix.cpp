#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Produk {
    string nama;
    double harga;
    string kategori;
};

struct PenjualanHarian {
    double totalPenjualan;
    int hari;
    int bulan;
    int tahun;
};

void tampilkanMenu(int hari, int bulan, int tahun) {
    cout << "\n======= Menu =======" << endl;
    cout << "Tanggal: " << hari << "/" << bulan << "/" << tahun << endl;
    cout << "1. Input Penjualan Harian" << endl;
    cout << "2. Tampilkan Data Penjualan" << endl;
    cout << "3. Tampilkan Tabungan Bersih" << endl;
    cout << "4. Perbarui Tanggal Awal" << endl;
    cout << "5. Perbarui Modal Bulanan" << endl;
    cout << "6. Ganti ke Hari Berikutnya" << endl;
    cout << "7. Exit" << endl;
    cout << "\nPilih menu: ";
}

void tambahSatuHari(int &hari, int &bulan, int &tahun) {
    const int jumlahHari[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    hari++;
    
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

double inputPenjualan(Produk produk[], int jumlahProduk) {
    double totalPenjualan = 0;
    int pilihanProduk, kuantitas;

    while (true) {
        cout << "\n=== Pilih Produk ===" << endl;
        for (int i = 0; i < jumlahProduk; i++) {
            cout << i + 1 << ". " << produk[i].nama << " (Rp " << produk[i].harga << ")" << endl;
        }
        
        cout << "Masukkan nomor produk yang ingin dibeli (0 untuk selesai): ";
        cin >> pilihanProduk;

        if (pilihanProduk == 0) break;
        if (pilihanProduk < 1 || pilihanProduk > jumlahProduk) {
            cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
            continue;
        }

        cout << "Masukkan kuantitas untuk " << produk[pilihanProduk - 1].nama << ": ";
        cin >> kuantitas;

        totalPenjualan += produk[pilihanProduk - 1].harga * kuantitas;
    }

    return totalPenjualan;
}

void tampilkanDataPenjualan(PenjualanHarian penjualan[][31], int bulanDipilih) {
    double totalKeseluruhan = 0;

    cout << "\n=== Data Penjualan Bulan " << bulanDipilih << " ===" << endl;

    for (int h = 0; h < 31; h++) {
        if (penjualan[bulanDipilih - 1][h].totalPenjualan > 0) {
            cout << "Tanggal: " 
                 << penjualan[bulanDipilih - 1][h].hari << "/" 
                 << penjualan[bulanDipilih - 1][h].bulan << "/" 
                 << penjualan[bulanDipilih - 1][h].tahun 
                 << " - Total Penjualan: Rp " 
                 << fixed<< setprecision(2) 
                 << penjualan[bulanDipilih - 1][h].totalPenjualan 
                 << endl;

            totalKeseluruhan += penjualan[bulanDipilih - 1][h].totalPenjualan;
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

void tampilkanTabunganBersih(PenjualanHarian penjual[][31], double modalBulanan, int bulanDipilih) {
    double totalPenjualBulanan = 0;

    for (int h = 0; h < 31; h++) {
        totalPenjualBulanan += penjual[bulanDipilih - 1][h].totalPenjualan;
    }

    double tabunganBersih = totalPenjualBulanan - modalBulanan;

    cout << "\n=== Tabungan Bersih Bulan " 
         << bulanDipilih 
         << " ===" << endl;

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
             <<"."<<endl;
    }
}

int main() {
    const int jumlahProduk = 67; // Total produk
    Produk produk[jumlahProduk] = {
        {"Sapu",25000,"Alat Rumah Tangga"},
        {"Kain pel",25000,"Alat Rumah Tangga"},
        {"Wiper lantai",20000,"Alat Rumah Tangga"},
        
        {"Telur 1kg",27000,"Sembako"},
        {"Minyak 1L",18000,"Sembako"},
        {"Gula 1L",20000,"Sembako"},
        {"Teh Celup Kotak",6000,"Sembako"},
        {"Kopi Sachet",2000,"Sembako"},
        {"Indomie",3500,"Sembako"},
        {"Susu Kental Manis Sachet",2000,"Sembako"},
        {"Gas Elpiji 3kg",22000,"Sembako"},
        
        // Obat-obatan
        {"Mixagrip",3000,"Obat-Obatan"},
        {"Bodrex",3000,"Obat-Obatan"},
        {"Paracetamol",10000,"Obat-Obatan"},
        {"Bodrex Migra",3000,"Obat-Obatan"},
        {"Bodrex Extra",3000,"Obat-Obatan"},
        {"Promag",10000,"Obat-Obatan"},
        {"Tolak Angin",4000,"Obat-Obatan"},
        {"Ultraflu",3000,"Obat-Obatan"},
        {"Paramex",3000,"Obat-Obatan"},
        {"Decolgen",3000,"Obat-Obatan"},
        {"Panadol",15000,"Obat-Obatan"},
        {"Freshcare",12000,"Obat-Obatan"},
        {"Minyak Kayu Putih",7000,"Obat-Obatan"},
        {"Betadine",7000,"Obat-Obatan"},
        {"Hansaplast",500,"Obat-Obatan"},

       // Snack dan Minuman
       {"Ale Ale",1000,"Snack dan Minuman"},
       {"Teh Gelas",1000,"Snack dan Minuman"},
       {"Okky Jelly Drink",2000,"Snack dan Minuman"},
       {"Teh Pucuk",4000,"Snack dan Minuman"},
       {"Ultra Milk",5500,"Snack dan Minuman"},
       {"Top Coco",1000,"Snack dan Minuman"},
       {"Aqua gelas",500,"Snack dan Minuman"},
       {"Es Teler",1000,"Snack dan Minuman"},
       {"Kopi Nongkrong",1000,"Snack dan Minuman"},
       {"Panther",1000,"Snack dan Minuman"},
       {"Teh Rio",1000,"Snack dan Minuman"},
       {"Power F",1000,"Snack dan Minuman"},
       {"Granita",1000,"Snack dan Minuman"},
       {"Susu Bear Brand",11000,"Snack dan Minuman"},
       {"Yakult",2500,"Snack dan Minuman"},
       {"Floridina",5000,"Snack dan Minuman"},
       {"Mizone",8000,"Snack dan Minuman"},
       {"Dilan Bar",2000,"Snack dan Minuman"},       
       {"Astor",1000 ,"Snack dan Minuman"},       
       {"Beng beng  ",2500 ,"Snack dan Minuman"},       
       {"Momogi ",1000 ,"Snack dan Minuman"},       
       {"Roti Aoka ",2500 ,"Snack dan Minuman"},       
       {"Oreo Soft Cake ",2500 ,"Snack dan Minuman"},       
       {"Good Time ",2000 ,"Snack dan Minuman"},       
       {"Nextar ",2000 ,"Snack dan Minuman"},       
       {"Permen yupi ",500 ,"Snack dan Minuman"},       
       {"Sosis Sonice ",1000 ,"Snack dan Minuman"},       
       {"Potatos ",2000 ,"Snack dan Minuman"},       
       {"Krupuk Nina ",2000 ,"Snack dan Minuman"},       
       {"Better ",1500 ,"Snack dan Minuman"},       
	   {"Kacang Rosta ",1000 ,"Snack dan Minuman"},  
       {"Malkist ",1000 ,"Snack dan Minuman"},  
       {"Tango ",2000 ,"Snack dan Minuman"},  
       {"Nabati ",2000 ,"Snack dan Minuman"},  
       {"Kacang Garuda ",5000 ,"Snack dan Minuman"},  
       {"Chiki Balls ",2000 ,"Snack dan Minuman"},  
       {"Chitato Lite ",2000 ,"Snack dan Minuman"},  
       {"Kacang Atom ",1000 ,"Snack dan Minuman"},  
       {"Regal ",1000 ,"Snack dan Minuman"},  
       {"Superco",1000 ,"Snack dan Minuman"},  
   };

   const int MAX_BULAN =12; // Maksimal bulan
   const int MAX_HARI =31; // Maksimal hari

   PenjualanHarian penjual[MAX_BULAN][MAX_HARI] = {};

   int hariAwal, bulanAwal, tahunAwal;

   cout<<"=== SISTEM MANAJEMEN KEUANGAN TOKO KELONTONG 09 ==="<<endl;

   // Input tanggal awal
   cout<<"Masukkan Tanggal Awal (DD/MM/YYYY)"<<endl;

   cout<<"Tanggal: "; cin>>hariAwal;
   cout<<"Bulan: "; cin>>bulanAwal;
   cout<<"Tahun: "; cin>>tahunAwal;

   int hari = hariAwal;
   int bulan = bulanAwal;
   int tahun = tahunAwal;

   double modalBulanan;

   cout<<"Masukkan Modal Bulanan: Rp "; cin>>modalBulanan;

   while(true){
      tampilkanMenu(hari, bulan, tahun);
      int pilihan; cin>>pilihan; cout<<endl;

      if(pilihan == 1){
          while(true) {
              int kategoriPilihan;

              // Pilih kategori produk
              cout<<"Pilih Kategori Produk:\n";
              cout<<"1. Alat Rumah Tangga\n";
              cout<<"2. Sembako\n";
              cout<<"3. Obat-Obatan\n";
              cout<<"4. Snack dan Minuman\n";
              cout<<"5. Kembali ke Menu Utama\n";
              cout<<"Masukkan pilihan kategori: "; 
			  cin>>kategoriPilihan;

              if(kategoriPilihan == 5) break;
              
              double totalHariIni = 0; // Reset total per hari

				switch(kategoriPilihan) {
					case 1:
						totalHariIni += inputPenjualan(produk + 0,3); // Hanya ambil alat rumah tangga
						break;
					case 2:
						totalHariIni += inputPenjualan(produk + 3,8); // Hanya ambil sembako
						break;
					case 3:
						totalHariIni += inputPenjualan(produk + 11,15); // Hanya ambil obat warung
						break;
					case 4:
						totalHariIni += inputPenjualan(produk + 26,jumlahProduk-27); // Hanya ambil jajanan bocah
						break;
					default:
						cout<<"Kategori tidak valid!"<<endl;
						break;
				}

                // Simpan data penjual harian setelah selesai input di satu kategori
                PenjualanHarian& currentDaySales = penjual[bulan-1][hari-1];
                currentDaySales.totalPenjualan += totalHariIni; 
                currentDaySales.hari = hari; 
                currentDaySales.bulan = bulan; 
                currentDaySales.tahun = tahun;

				char lanjutkanInput;
				cout<<"Apakah ada pembelian di kategori lain? (y/n): ";
				cin >> lanjutkanInput;

				if(lanjutkanInput != 'y' && lanjutkanInput != 'Y') break; // Kembali ke menu utama jika bukan 'y'
			cout<<endl;
			}
    	
      
      } else if(pilihan == 2){
          int bulanDipilih;            
          cout<<"Pilih Bulan (1-12): "; cin>>bulanDipilih;            
          if(bulanDipilih >=1 && bulanDipilih <= MAX_BULAN){
              tampilkanDataPenjualan(penjual, bulanDipilih);
          } else {
              cout<<"Bulan tidak valid! Silakan coba lagi.\n";                
          }
      } else if(pilihan == 3){
          int bulanDipilih;            
          cout<<"Pilih Bulan untuk Tabungan Bersih (1-12): "; cin>>bulanDipilih;            
          if(bulanDipilih >=1 && bulanDipilih <= MAX_BULAN){
              tampilkanTabunganBersih(penjual, modalBulanan, bulanDipilih);
          } else {
              cout<<"Bulan tidak valid! Silakan coba lagi.\n";                
          }
      } else if(pilihan == 4){
          // Update tanggal awal
          cout<<"Masukkan Tanggal Awal yang Baru (DD/MM/YYYY)\n";            
          cout<<"Tanggal: "; cin>>hari;            
          cout<<"Bulan: "; cin>>bulan;            
          cout<<"Tahun: "; cin>>tahun;            
      } else if(pilihan == 5){
          // Update modal bulanan
          cout<<"Masukkan Modal Bulanan Baru: Rp "; cin >> modalBulanan;            
          cout<<"Modal bulanan telah diperbarui menjadi: Rp "<<modalBulanan<<endl;            
      } else if(pilihan == 6){
          tambahSatuHari(hari, bulan, tahun);
      } else if(pilihan == 7){
          break;            
      } else {
          cout<<"Pilihan tidak valid! Silakan coba lagi.\n";            
      }
   }
	cout<<"Terima kasih sudah menggunakan layanan kami!";
   return 0;
}
