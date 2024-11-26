#include <iostream>
#include <string>
#include <iomanip> // Untuk manipulasi output

using namespace std;

// Struktur untuk menyimpan informasi produk dengan kategori
struct Produk {
    string nama;
    double harga;
    string kategori; // Menambahkan kategori untuk setiap produk
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
    cout << "2. Tampilkan Data Penjualan" << endl;
    cout << "3. Tampilkan Tabungan Bersih" << endl; // Menu baru untuk tabungan bersih
    cout << "4. Exit" << endl;
    cout << "Pilih menu: ";
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

// Fungsi untuk input penjualan harian berdasarkan kategori produk.
double inputPenjualan(Produk produk[], int jumlahProduk) {
    double totalPenjualan = 0;
    int kuantitas;

    cout << "Input Penjualan Hari Ini:" << endl;

    for (int i = 0; i < jumlahProduk; i++) {
        cout << produk[i].nama << " (Rp " << produk[i].harga << ") [" 
             << produk[i].kategori << "] - Masukkan kuantitas: ";
        cin >> kuantitas;

        // Menghitung total penjualan
        totalPenjualan += produk[i].harga * kuantitas;
    }

    return totalPenjualan;
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
                 << fixed<< setprecision(2)
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

    for (int h = 0; h < 31; h++) { // Iterasi melalui setiap hari di bulan yang dipilih.
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
             <<"."<<endl; // Menampilkan kerugian jika negatif.
    }
}

// Fungsi utama program.
int main() {
    const int jumlahProduk = 25; // Jumlah produk baru sesuai kategori.
    
	// Daftar produk dengan harga dan kategori.
	Produk produk[jumlahProduk] = {
		{"Sapu",    	15000, "Alat Rumah Tangga"},
		{"Pel",     	20000, "Alat Rumah Tangga"},
		{"Serokan Hujan",25000,"Alat Rumah Tangga"},
		
		{"Telur",  	20000, "Sembako"},
		{"Minyak",  	15000, "Sembako"},
		{"Gula",    	8000, "Sembako"},
		{"Teh",     	5000, "Sembako"},
		{"Kopi",    	10000,"Sembako"},
		{"Indomie",  	3000,"Sembako"},
		{"Susu",    	12000,"Sembako"},
		{"Gas Elpiji",200000,"Sembako"},
		
		{"Mixagrip",  	7500,"Obat Warung"},
		{"Bodrex",  	6000,"Obat Warung"},
		{"Paracetamol",  	5000,"Obat Warung"},
		{"Bodrex Migra",  	8000,"Obat Warung"},
	    {"Bodrex Extra",  	9000,"Obat Warung"},
	    {"Promag",  	7000,"Obat Warung"},
	    {"Tolak Angin",  	10000,"Obat Warung"},
	    {"Ultraflu",  	12000,"Obat Warung"},
	    {"Paramex",  	6000,"Obat Warung"},
	    {"Decolgen",  	10000,"Obat Warung"},

	    {"Panadol",  	8000,"Obat Warung"},
	    {"Freshcare",  	5000,"Obat Warung"},
	    {"Minyak Kayu Putih",4000,"Obat Warung"},
	    {"Betadine",  	15000,"Obat Warung"},
	    {"Hansaplas",  	12000,"Obat Warung"},

	    // Jajanan bocah.
	    {"Ale Ale",3000,"Jajanan Bocah"},  
	    {"Teh Gelas",2000,"Jajanan Bocah"},  
	    {"Okky Jelly Drink",3000,"Jajanan Bocah"},  
	    {"Teh Pucuk ",3000,"Jajanan Bocah"},  
	    {"Ultra Milk ",6000,"Jajanan Bocah"},  
	    {"Top Coco ",5000,"Jajanan Bocah"},  
	    {"Aqua ",4000,"Jajanan Bocah"},  
	    {"Es Teler ",8000,"Jajanan Bocah"},  
	    {"Nongkrong Kopi ",6000,"Jajanan Bocah"},  
	    {"Panther ",5000,"Jajanan Bocah"},  
	    {"Teh Rio ",3000,"Jajanan Bocah"},  
	    {"Power F ",5000,"Jajanan Bocah"},  
	    {"Granita ",6000,"Jajanan Bocah"},  
	    {"Bear Brand ",8000,"Jajanan Bocah"},  
	    {"Yakult ",4000,"Jajanan Bocah"},  
	    {"Floridina ",3000,"Jajanan Bocah"},  
	    {"Mizone ",5000,"Jajanan Bocah"},  
	    {"Dylan ",4000,"Jajanan Bocah"},  
	    {"Astor ",6000,"Jajanan Bocah"},  
	    {"Bembeng ",3000,"Jajanan Bocah"},  
	    {"Momogi ",2000,"Jajanan Bocah"},  
	    {"Aoka ",3000,"Jajanan Bocah"},  
	    {"Oreo Soft Cake ",7000 ,"Jajanan bocah" },   
	    { "Good Time ",6000 ,"Jajanan bocah" },   
	    { "Nextar ",5500 ,"Jajanan bocah" },   
	    { "Yupi ",3500 ,"Jajanan bocah" },   
	    { "Sosis Sonice ",8500 ,"Jajanan bocah" },   
	    { "Potatos ",4500 ,"Jajanan bocah" },   
	    { "Krupuk Nina ",2500 ,"Jajanan bocah" },   
	    { "Better ",3500 ,"Jajanan bocah" },   
	    { "Malkist ",5500 ,"Jajanan bocah" },   
	    { "Kacang Rosta ",6500 ,"Jajanan bocah" },   
	    { "Tango ",4500 ,"Jajanan bocah" },   
	    { "Nabati ",3500 ,"Jajanan bocah" },   
	    { "Pilus ",2500 ,"Jajanan bocah" },   
	    { "Kacang Garuda ",65000 ,"Jajanan bocah" },   
	    { "Chiki Balls ",80000 ,"Jajanan bocah" },   
	    { "Lite ",70000 ,"Jajanan bocah" },   
	    { "Kacang Atom ",40000 ,"Jajanan bocah" },   
	    { "Regal ",70000 ,"jajan bocah" },   
	    { "Superco ",70000 ,"jajan bocah"}   
     };

	const int MAX_BULAN =12; // Maksimal jumlah bulan dalam setahun.
	const int MAX_HARI =31; // Maksimal jumlah hari dalam sebulan.

	PenjualanHarian penjual[MAX_BULAN][MAX_HARI] = {}; // Array dua dimensi untuk menyimpan data penjual harian.

	double modalBulanan;

	cout<<"Masukkan Modal Bulanan: Rp ";
	cin>>modalBulanan;

	int hariAwal,bulanAwal,tahunAwal;

	cout<<"Masukkan Tanggal Awal (DD MM YYYY): ";
	cin>>hariAwal>>bulanAwal>>tahunAwal;

	int hari=hariAwal;
	int bulan=bulanAwal;
	int tahun=tahunAwal;

	while(true){
    	tampilkanMenu(hari,bulan,tahun);
    	int pilihan;
    	cin>>pilihan;

    	if(pilihan==1){ // Input Penjual Harian.
			int kategoriPilihan;
			cout<<"Pilih Kategori Produk:\n";
			cout<<"1. Alat Rumah Tangga\n";
			cout<<"2. Sembako\n";
			cout<<"3. Obat Warung\n";
			cout<<"4. Jajanan Bocah\n";
			cout<<"Masukkan pilihan kategori: ";
			cin>>kategoriPilihan;

			switch(kategoriPilihan) {
				case 1:
					inputPenjualan(produk + 0,3); // Hanya ambil alat rumah tangga
					break;
				case 2:
					inputPenjualan(produk + 3,8); // Hanya ambil sembako
					break;
				case 3:
					inputPenjualan(produk + 11,15); // Hanya ambil obat warung
					break;
				case 4:
					inputPenjualan(produk + 26,jumlahProduk-26); // Hanya ambil jajanan bocah
					break;
				default:
					cout<<"Kategori tidak valid!"<<endl;
					break;
			}

			double totalHariIni = inputPenjualan(produk,jumlahProduk);
			
			cout<<"Total Penjual Hari Ini: Rp "<<fixed<<setprecision(2)<<totalHariIni<<endl;

			tambahSatuHari(hari,bulan,tahun);

    	}else if(pilihan==2){ // Tampilkan Data Penjual.
			int bulanDipilih;
			cout<<"Pilih Bulan (1-12): ";
			cin>>bulanDipilih;

			if(bulanDipilih>=1 && bulanDipilih<=MAX_BULAN){
				tampilkanDataPenjualan(penjual,bulanDipilih);
			}else{
				cout<<"Bulan tidak valid! Silakan coba lagi."<<endl;
			}

    	}else if(pilihan==3){ // Tampilkan Tabungan Bersih.
			int bulanDipilih;
			cout<<"Pilih Bulan untuk Tabungan Bersih (1-12): ";
			cin>>bulanDipilih;

			if(bulanDipilih>=1 && bulanDipilih<=MAX_BULAN){
				tampilkanTabunganBersih(penjual,modalBulanan,bulanDipilih);
			}else{
				cout<<"Bulan tidak valid! Silakan coba lagi."<<endl;
			}

    	}else if(pilihan==4){ // Exit.
			break;

    	}else{
			cout<<"Pilihan tidak valid! Silakan coba lagi."<<endl;
    	}
}

return  0;}
