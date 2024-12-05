#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

//deklarasi detail produk
struct Produk {
    string nama;
    double harga;
    string kategori;
};

//deklarasi detail penjualan
struct DetailPenjualan {
    string namaProduk;
    double harga;
    int kuantitas;
};

//deklarasi detail penjualan harian
struct PenjualanHarian {
    double totalPenjualan;
    int hari;
    int bulan;
    int tahun;
    vector<DetailPenjualan> detail;
};

//prosedur main menu
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
    cout << "Pilih menu: ";
}

//prosedur untuk menambahkan satu hari
void tambahSatuHari(int &hari, int &bulan, int &tahun) {
    int jumlahHari[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //deklarasi total hari dalam bulan di dalam array
    hari++;
//prosedur untuk bulan kabisat
    if (bulan == 2 && tahun % 4 == 0) {
        if (hari > 29) { 
            hari = 1; 
            bulan++; 
        }
//prosedur untuk mereset hari saat sudah satu bulan
    } else if (hari > jumlahHari[bulan - 1]) { //bulan-1 dimaksudkan untuk mengurangi nilai bulan yang diinput user menjadi nilai indeks array
        hari = 1; 
        bulan++; 
        if (bulan > 12) { 
            bulan = 1; 
            tahun++; 
        }
    }
}

//fungsi untuk input penjualan
double inputPenjualan(Produk produk[], int jumlahProduk, vector<DetailPenjualan> &detailPenjualan) {
    double totalPenjualan = 0;
    int pilihanProduk, kuantitas;
    while (true) {
        cout << "\n=== Pilih Produk ===" << endl;
        for (int i = 0; i < jumlahProduk; i++) { //menampilkan list produk dengan struct dan array
            cout << i + 1 <<". "<< produk[i].nama<<" (Rp " << produk[i].harga<<")" << endl; 
        }
        cout << "Masukkan nomor produk yang ingin dibeli (0 untuk selesai): ";
        cin >> pilihanProduk;

        if (pilihanProduk == 0) break;
        
        else if (pilihanProduk < 1 || pilihanProduk > jumlahProduk) {
        cout << "Pilihan tidak valid! Silakan coba lagi." << endl;
            continue; 
        } //memasukkan kuantitas untuk produk
        cout << "Masukkan kuantitas untuk " << produk[pilihanProduk-1].nama<< ": ";
        cin >> kuantitas;
        
        //operasi untuk menghitung total penjualan 
        totalPenjualan += produk[pilihanProduk - 1].harga * kuantitas;
        
        // menyimpan detail penjualan dari struct yang sudah dideklarasikan
        DetailPenjualan detail;
        detail.namaProduk = produk[pilihanProduk - 1].nama;
        detail.harga = produk[pilihanProduk - 1].harga;
        detail.kuantitas = kuantitas;
        detailPenjualan.push_back(detail); // menyimpan objek baru ke akhir list baaru
    }
    return totalPenjualan; 
}
// prosedur menampilkan data penjualan berdasarkan bulan
void tampilkanDataPenjualanBulan(PenjualanHarian penjualan[][31], int bulanDipilih) {
    double totalKeseluruhan = 0;
    cout << "\n=== Data Penjualan Bulan " << bulanDipilih << " ===" << endl;

    for (int h = 0; h < 31; h++) {
        if (penjualan[bulanDipilih - 1][h].totalPenjualan > 0) {
            cout<<"Tanggal: "<<penjualan[bulanDipilih - 1][h].hari<< "/"<<penjualan[bulanDipilih - 1][h].bulan<< "/"<<penjualan[bulanDipilih - 1][h].tahun<<" - Total Penjualan: Rp " <<fixed<<setprecision(2)<<penjualan[bulanDipilih - 1][h].totalPenjualan;
            cout<<endl;
            totalKeseluruhan += penjualan[bulanDipilih - 1][h].totalPenjualan;
        }
    }
    if (totalKeseluruhan > 0) {
        cout<<"Total Keseluruhan Penjualan Bulan " <<bulanDipilih<<": Rp "<<fixed<<setprecision(2)<<totalKeseluruhan;
	    cout<< endl;
    } else 
        cout << "Tidak ada data penjualan untuk bulan ini."<<endl;
}
// prosedur menampilkan data penjualan berdasarkan hari 
void tampilkanDataPenjualanPerHari(PenjualanHarian penjual[][31], int bulanDipilih, int hariDipilih,int tahun) {
    if (penjual[bulanDipilih - 1][hariDipilih - 1].totalPenjualan > 0) { 
        cout<<"\n=== Data Penjualan Tanggal "<<hariDipilih<<"/"<<bulanDipilih<<"/"<<tahun<<" ===";
		cout<<"\nDetail Produk:\n";
		for(size_t i =0; i < penjual[bulanDipilih-1][hariDipilih-1].detail.size(); ++i){
			DetailPenjualan& detail = penjual[bulanDipilih-1][hariDipilih-1].detail[i];
			cout<<detail.namaProduk<<"("<<detail.kuantitas<<")"<<"["<<detail.harga<<"]"<<" = Rp "<<detail.kuantitas*detail.harga<<endl;
		}
		cout<<"\nTotal Penjualan: Rp "<<fixed<<setprecision(2)<<penjual[bulanDipilih-1][hariDipilih-1].totalPenjualan;
        cout<<endl;
	} else {
        cout<<"Tidak ada data penjualan untuk tanggal ini."<<endl;
    }
}
// prosedur menampilkan tabungan bersih 
void tampilkanTabunganBersih(PenjualanHarian penjual[][31], double modalBulanan, int bulanDipilih) {
    double totalPenjualBulanan = 0;
    for (int h = 0; h < 31; h++) {
        totalPenjualBulanan += penjual[bulanDipilih - 1][h].totalPenjualan;
    }
    double tabunganBersih = totalPenjualBulanan - modalBulanan;
    cout << "\n=== Tabungan Bersih Bulan " <<bulanDipilih<< " ===" << endl;
    cout << "Total Penjualan Bulanan: Rp "<<fixed<< setprecision(2)<<totalPenjualBulanan<< endl;
    cout << "Modal Bulanan: Rp "<<fixed<< setprecision(2)<<modalBulanan<< endl;
    if (tabunganBersih > 0) {
        cout << "Tabungan Bersih: Rp "<<fixed<<setprecision(2)<<tabunganBersih <<endl;
    } else {
        cout << "Kerugian: Rp "<<fixed<<setprecision(2)<<-tabunganBersih<<"."<<endl;
    }
}

int main() {
	double totalPenjualan;
    int jumlahProduk = 67; // Total produk
     Produk produk[jumlahProduk] = {
     	// produk Alat Rumah Tangga
        {"Sapu",25000,"Alat Rumah Tangga"},
        {"Kain pel",25000,"Alat Rumah Tangga"},
        {"Wiper lantai",20000,"Alat Rumah Tangga"},
        
        // produk Sembako
        {"Telur 1kg",27000,"Sembako"},
        {"Minyak 1L",18000,"Sembako"},
        {"Gula 1L",20000,"Sembako"},
        {"Teh Celup Kotak",6000,"Sembako"},
        {"Kopi Sachet",2000,"Sembako"},
        {"Indomie",3500,"Sembako"},
        {"Susu Kental Manis Sachet",2000,"Sembako"},
        {"Gas Elpiji 3kg",22000,"Sembako"},
        
        // produk Obat-Obatan
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

       // produk Snack dan Minuman
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
   
    const int MAX_BULAN = 12; // Maksimal bulan
    const int MAX_HARI = 31; // Maksimal hari
    PenjualanHarian penjual[MAX_BULAN][MAX_HARI] = {};

	cout<<"=== SISTEM MANAJEMEN KEUANGAN TOKO KELONTONG 09 ==="<<endl;
   // Input tanggal awal
   cout<<"Masukkan Tanggal Awal (DD/MM/YYYY)"<<endl;
   cout<<"Tanggal: "; 
   int hariAwal, bulanAwal, tahunAwal;
   cin>>hariAwal;
   cout<<"Bulan: "; 
   cin>>bulanAwal;
   cout<<"Tahun: "; 
   cin>>tahunAwal;
   
   int hari = hariAwal;
   int bulan = bulanAwal;
   int tahun = tahunAwal;

   double modalBulanan;
   cout<<"Masukkan Modal Bulanan: Rp "; 
   cin>>modalBulanan;
    while (true) {
        tampilkanMenu(hari, bulan, tahun);
        int pilihan;
        cin>>pilihan;
        cout<<endl;
        // menginput data penjualan 
        if (pilihan==1) {
            while (true) {
                int kategoriPilihan;
                cout << "Pilih Kategori Produk:\n";
                cout << "1. Alat Rumah Tangga\n";
                cout << "2. Sembako\n";
                cout << "3. Obat-Obatan\n";
                cout << "4. Snack dan Minuman\n";
                cout << "5. Kembali ke Menu Utama\n";
                cout << "Masukkan pilihan kategori: ";
                cin >> kategoriPilihan;

                if (kategoriPilihan == 5) break;
                double totalHariIni = 0; // Reset total per hari
                vector<DetailPenjualan> detailPenjualan; //deklarasi vector untuk menyimpan detail penjualan
                //switch case untuk menampilkan produk sesuai kategori yang dipilih user
                switch (kategoriPilihan) {
                    case 1:
                        totalHariIni += inputPenjualan(produk + 0, 3, detailPenjualan); // Hanya menampilkan Alat Rumah Tangga
                        break;
                    case 2:
                        totalHariIni += inputPenjualan(produk + 3, 8, detailPenjualan); // Hanya menampilkan Sembako
                        break;
                    case 3:
                        totalHariIni += inputPenjualan(produk + 11, 15, detailPenjualan); // Hanya menampilan Obat-Obatan
                        break;
                    case 4:
                        totalHariIni += inputPenjualan(produk + 26, jumlahProduk - 27, detailPenjualan); // Hanya menampilkan Snack dan Minuman 
                        break;
                    default:
                        cout << "Kategori tidak valid!\n\n";
                        continue;
                }

                // Simpan data penjual harian setelah selesai input di satu kategori
                PenjualanHarian& penjualanharian = penjual[bulan - 1][hari - 1];
                penjualanharian.totalPenjualan += totalHariIni;
                penjualanharian.hari = hari;
                penjualanharian.bulan = bulan;
                penjualanharian.tahun = tahun;

                // Store the details of sales
                penjualanharian.detail.insert(penjualanharian.detail.end(), detailPenjualan.begin(), detailPenjualan.end());
				
				// mekanisme jika user masih ingin menginput produk lain 
                char lanjutkanInput;
                cout << "Apakah ada pembelian di kategori lain? (y/n): ";
                cin >> lanjutkanInput;
                if (lanjutkanInput != 'y' && lanjutkanInput != 'Y') break; // Kembali ke menu utama jika bukan 'y'
                cout << endl;
            }
        
        // menampilkan data penjualan 
       } else if (pilihan == 2) { 
   			 int pilihanWaktu;
    		cout << "Pilih cara untuk menampilkan data penjualan:\n";
    		cout << "1. Berdasarkan Hari\n";
    		cout << "2. Berdasarkan Bulan\n";
    		cout << "Masukkan pilihan: ";
    		cin >> pilihanWaktu;

    		if (pilihanWaktu == 1) { // Berdasarkan Hari
      		  int hariDipilih, bulanDipilih;
      		  cout << "Masukkan Hari (1-31): ";
      		  cin >> hariDipilih;
      			  if (hariDipilih < 1 || hariDipilih > 31) {
            		cout << "Hari tidak valid! Silakan coba lagi.\n";
             		continue;
        	}
        	  cout << "Masukkan Bulan (1-12): ";
        	  cin >> bulanDipilih;
        	  	if (bulanDipilih < 1 || bulanDipilih > MAX_BULAN) {
            	  cout << "Bulan tidak valid! Silakan coba lagi.\n";
            	  continue;
        	}
       		 tampilkanDataPenjualanPerHari(penjual, bulanDipilih, hariDipilih,tahun); // Show data for selected day
    		} else if (pilihanWaktu == 2) { // Berdasarkan Bulan
       			 int bulanDipilih;
       			 cout << "Pilih Bulan (1-12): ";
        	     cin >> bulanDipilih;
      		  if (bulanDipilih >= 1 && bulanDipilih <= MAX_BULAN) {
          	  tampilkanDataPenjualanBulan(penjual, bulanDipilih); // Show data for selected month
       		 } else 
            cout << "Bulan tidak valid! Silakan coba lagi.\n";
    	} else         
		cout << "Pilihan tidak valid! Silakan coba lagi.\n";
      
      // Menampilkan tabungan bersih
      } else if(pilihan == 3){
          int bulanDipilih;            
          cout<<"Pilih Bulan untuk Tabungan Bersih (1-12): "; cin>>bulanDipilih;            
          if(bulanDipilih >=1 && bulanDipilih <= MAX_BULAN){
              tampilkanTabunganBersih(penjual, modalBulanan, bulanDipilih);
          } else {
              cout<<"Bulan tidak valid! Silakan coba lagi.\n";                
          }
          
       // Memperbarui Tanggal Awal   
      } else if(pilihan == 4){
          cout<<"Masukkan Tanggal Awal yang Baru (DD/MM/YYYY)\n";            
          cout<<"Tanggal: "; cin>>hari;            
          cout<<"Bulan: "; cin>>bulan;            
          cout<<"Tahun: "; cin>>tahun;      
		  
		// Memeperbarui Modal bulanan Awal      
      } else if(pilihan == 5){
          cout<<"Masukkan Modal Bulanan Baru: Rp "; cin >> modalBulanan;            
          cout<<"Modal bulanan telah diperbarui menjadi: Rp "<<modalBulanan<<endl;            
        
		// Menambah Satu Hari 
      } else if(pilihan == 6){
          tambahSatuHari(hari, bulan, tahun);
          
         // Mekanisme Exit 
      } else if(pilihan == 7){
          break;            
      } else 
          cout<<"Pilihan tidak valid! Silakan coba lagi.\n";            
    }
    cout<<"Terima kasih sudah menggunakan layanan kami!\n\n"<<"Credit by Kelompok 4 TI-1C:\nFalih Elmanda Ghaisan (2407411073)\n"<<"Ahmad Raihan (2407411086)\n"<<"M.Irzaldi Alamsyah (24074110082)";
    return 0;
}
