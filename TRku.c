#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>

char file_name[] = "list.txt";
char file_user[] = "user.txt";
char file_history[] = "history.txt";
char delim[] = ";";
char data_barang[200][4][200];
int jml_data_barang = 0,kode_beli[100],jumlah_beli[100],temp_stok[500000];
char data_user[200][7][200];
int jml_data_user = 0,id_user[50];
char data_history[200][6][200];
int jml_data_history = 0;
char username[50][200],password[50][200],last_login[50][200],level[50][200],namaUser[50][200],reg_date[50][200];
char uname[200],pass[200],lastlog[200],level_log[200],namalog[200];
char currentTime[200];
bool user_login = false;

char *substring(char *string, int position, int length) {
   	char *pointer;
   	int c;
 
   	pointer = malloc(length+1);
   
   	if (pointer == NULL) {
      	printf("Unable to allocate memory.\n");
		exit(EXIT_FAILURE);
   	}
 
   	for (c = 0 ; c < length ; c++) {
      	*(pointer+c) = *(string+position-1);      
      	string++;  
   	}
 
   	*(pointer+c) = '\0';
 
   	return pointer;
}

void getData() {
	FILE *fp = fopen(file_name, "r");
    char line[200];
	
	memset(data_barang,0,sizeof(data_barang));
    jml_data_barang = 0;  
	   
	if (fp == NULL) {
		printf("Gagal membuka file %s", file_name);
		exit(EXIT_FAILURE);
	} else {
		int i = 0;
		while (fgets(line, sizeof(line), fp) != NULL) {
			char *token = strtok(line, delim);
    		
    		int j = 0;
			while (token != NULL) {
				strcpy(data_barang[i][j], token);
				token = strtok(NULL, delim);
				j++;
			}
			
			i++;
			jml_data_barang++;
		}
	}
	fclose(fp);
}

void view(char judul[50]){
	getData();
    system("@cls||clear");
    printf("============================================\n");
   	printf("Menu %s\n",judul);
   	printf("============================================\n");
    if (jml_data_barang > 0) {
        printf("Kode\tNama Barang\tHarga\tStok\n");
   		printf("============================================\n");
        int i;
		for (i = 0; i < jml_data_barang; i++) {
			char nama_brg[100];
			strcpy(nama_brg, data_barang[i][1]);
			if (strlen(nama_brg) > 15) {
		   		strcpy(nama_brg, substring(nama_brg, 1, 15));
			} else if (strlen(nama_brg) < 8) {
		   		snprintf(nama_brg, sizeof nama_brg, "%s%s", data_barang[i][1], "\t");
			}
			int kode_brg = atoi(data_barang[i][0]);
            int harga_brg = atoi(data_barang[i][2]);
            int stok_brg = atoi(data_barang[i][3]);
			if(kode_brg != 0){
				printf("%d\t%s\t%d\t%d \n",kode_brg,nama_brg,harga_brg,stok_brg);
			} else {
				
			}
            
        }
    } else {
        printf("Tidak ada data barang!\n");
    }
    printf("============================================\n");
}

void viewData() {
	system("color A");
    view("Lihat Barang");
    system("pause");
    menu_utama();
}

bool addToFile(char inputan[]) {
	FILE *fp = fopen(file_name,"a+");
	if (fp == NULL) {
		return false;
	} else {
		fputs(inputan, fp);
	}
	fclose(fp);
	return true;
}

int verif(char kode[50]){
	getData();
	int i;
	bool ver = false;
		for (i = 0; i < jml_data_barang; i++) {
			char nama_brg[100];
			strcpy(nama_brg, data_barang[i][1]);
			int kode_brg = atoi(data_barang[i][0]);
            int harga_brg = atoi(data_barang[i][2]);
            int stok_brg = atoi(data_barang[i][3]);
			if (strcmp(data_barang[i][0],kode)==0){
				ver =true;
			} 
        }
        return ver;
}

void tambahData() {
	system("color A");
	system("cls");
	printf("============================================\n");
   	printf("Menu Tambah Data \n");
   	printf("============================================\n");
   	
   	char nama[100], harga[50], stok[50], kode[50], hasil[200],simpan[100][200];
   	int i,hargaa;
   	printf("Masukkan Kode Barang (5 kode):");
   	scanf("%s",kode);
   	int kodee = atoi(kode);
   	if(kodee == 0 || strlen(kode) != 5||kodee < 1000){
   		printf("Kode Salah !\n");
   		system("pause");
   		tambahData();
	}
   	if(verif(kode) == false){
		printf("Masukkan Nama Barang : ");
		scanf("%c");
	   	gets(nama);
	   	if (strlen(nama) > 15) {
	   		strcpy(nama, substring(nama, 1, 15));
		}
		
	   	printf("Masukkan Harga Barang : ");
	   	gets(harga);
	   	hargaa = atoi(harga);
	   	if (hargaa < 1000) hargaa = 1000;
	   	else if (hargaa > 9999999) hargaa = 9999999;
    } else {
    	printf("Update Stok %i\n",kodee);
	} 
   	printf("Masukkan Stok Barang : ");
   	scanf("%s",&stok);
   	int stokk = atoi(stok);
   	if (stokk < 1) stokk = 1;
   	else if (stokk > 10000) stokk = 10000;
   	
   	printf("============================================\n");
   	if(verif(kode) == false){
   		snprintf(hasil, sizeof hasil, "%d;%s;%d;%d;\n",kodee, nama, hargaa, stokk);
		if (addToFile(hasil)) {
			printf("Sukses tambah data barang!\n");
		} else {
			printf("Gagal tambah data barang!\n");
		}
	} else {
		getData();
		bool sukses = false;
		char namaBarang[100];
		for (i = 0; i < jml_data_barang; i++) {
			char nama_brg[100];
			strcpy(nama_brg, data_barang[i][1]);
			int kode_brg = atoi(data_barang[i][0]);
            int harga_brg = atoi(data_barang[i][2]);
            int stok_brg = atoi(data_barang[i][3]);
			if(strcmp(data_barang[i][1],nama) == 0 || strcmp(data_barang[i][0],kode)==0 ){
				int tambahStok = atoi(data_barang[i][3]) + stokk;
				strcpy(namaBarang,data_barang[i][1]);
				snprintf(simpan[i], sizeof simpan[i], "%s;%s;%s;%d;\n",data_barang[i][0],data_barang[i][1], data_barang[i][2], tambahStok);
			} else {
				snprintf(simpan[i], sizeof simpan[i], "%s;%s;%s;%s;\n",data_barang[i][0],data_barang[i][1], data_barang[i][2], data_barang[i][3]);
			} 
        }
        FILE *fp = fopen(file_name, "w"); //reset file jadi kosong
		fclose(fp);
        for(i=0;i<jml_data_barang;i++){
        	if(addToFile(simpan[i])){
				sukses = true;
			}	
		}
        if (sukses) {
			printf("Sukses tambah stok barang %s!\n",namaBarang);
		} else {
			printf("Gagal tambah stok barang %s!\n",namaBarang);
		}
        
	}
	
	printf("============================================\n");
	system("pause");
    menu_utama();
}

void updateHarga() {
	system("cls");
	system("color A");
	view("Update Harga Barang");
   	char nama[100], hargat[50], stok[50], kodes[50], hasil[200],simpan[100][200];
   	int i;
   	printf("Masukkan Kode Barang :");
   	scanf("%s",&kodes);
   	int kodees = atoi(kodes);
   	if(verif(kodes) != true){
   		printf("Kode Salah !\n");
   		system("pause");
   		updateHarga();
	}
	
   	printf("Masukkan Harga Barang : ");
   	scanf("%s",&hargat);
   	int hargaat = atoi(hargat);
   	if (hargaat < 1000) hargaat = 1000;
   	else if (hargaat > 9999999) hargaat = 9999999;
   	
   	printf("============================================\n");
		getData();
		bool Sukses = false;
		char namaBarang[100];
		int hargaBarang;
		for (i = 0; i < jml_data_barang; i++) {
			char nama_brg[100];
			strcpy(nama_brg, data_barang[i][1]);
			int kode_brg = atoi(data_barang[i][0]);
            int harga_brg = atoi(data_barang[i][2]);
            int stok_brg = atoi(data_barang[i][3]);
			if(strcmp(data_barang[i][0],kodes) == 0 ){
				strcpy(namaBarang,data_barang[i][1]);
				hargaBarang = atoi(data_barang[i][2]);
				snprintf(simpan[i], sizeof simpan[i], "%s;%s;%d;%s;\n",data_barang[i][0],data_barang[i][1], hargaat, data_barang[i][3]);
			} else {
				snprintf(simpan[i], sizeof simpan[i], "%s;%s;%s;%s;\n",data_barang[i][0],data_barang[i][1], data_barang[i][2], data_barang[i][3]);
			} 
        }
        FILE *fp = fopen(file_name, "w"); //reset file jadi kosong
		fclose(fp);
        for(i=0;i<jml_data_barang;i++){
        	if(addToFile(simpan[i])){
				Sukses = true;
			}	
		}
        if (Sukses) {
			printf("Sukses Update Harga barang %s dari Rp.%d menjadi Rp.%d!\n",namaBarang,hargaBarang,hargaat);
		} else {
			printf("Gagal Update Harga barang %s dari Rp.%d menjadi Rp.%d!",namaBarang);
		}
        
	
	
	printf("============================================\n");
	system("pause");
    menu_utama();
}

int verif_tr(char kode[50],char jumlah[50]){
	getData();
	int i;
	bool ver = false;
		for (i = 0; i < jml_data_barang; i++) {
			char nama_brg[100];
			strcpy(nama_brg, data_barang[i][1]);
			int kode_brg = atoi(data_barang[i][0]);
            int harga_brg = atoi(data_barang[i][2]);
            int stok_brg = atoi(data_barang[i][3]);
			if(strcmp(data_barang[i][0],kode) == 0){
				if(atoi(jumlah) <= atoi(data_barang[i][3])+temp_stok[atoi(data_barang[i][0])]){
					ver = true;
					temp_stok[atoi(data_barang[i][0])] -= atoi(jumlah); 
				}
			}
        }
        return ver;
}

void view_tr(char judul[50]){
	getData();
    system("@cls||clear");
    printf("============================================\n");
   	printf("Menu %s\n",judul);
   	printf("============================================\n");
    if (jml_data_barang > 0) {
        printf("Kode\tNama Barang\tHarga\n");
   		printf("============================================\n");
        int i;
		for (i = 0; i < jml_data_barang; i++) {
			char nama_brg[100];
			strcpy(nama_brg, data_barang[i][1]);
			if (strlen(nama_brg) > 15) {
		   		strcpy(nama_brg, substring(nama_brg, 1, 15));
			} else if (strlen(nama_brg) < 8) {
		   		snprintf(nama_brg, sizeof nama_brg, "%s%s", data_barang[i][1], "\t");
			}
			int kode_brg = atoi(data_barang[i][0]);
            int harga_brg = atoi(data_barang[i][2]);
            int stok_brg = atoi(data_barang[i][3]);
			if(kode_brg != 0){
				printf("%d\t%s\t%d \n",kode_brg,nama_brg,harga_brg);
			} else {
				
			}
            
        }
    } else {
        printf("Tidak ada data barang!\n");
    }
    printf("============================================\n");
}

void potongstok(int kodene,int jumlah_beli){
	getData();
	int i,l=0;
	
	char kalimat[100][200];
	for(i=0;i<jml_data_barang;i++){
		if(kodene == atoi(data_barang[i][0])){
			int potong = atoi(data_barang[i][3])-jumlah_beli;
			snprintf(kalimat[i], sizeof kalimat[i],"%s;%s;%s;%i;\n", data_barang[i][0], data_barang[i][1],data_barang[i][2], potong);
		} else {
			snprintf(kalimat[i],sizeof kalimat[i], "%s;%s;%s;%s;\n", data_barang[i][0], data_barang[i][1],data_barang[i][2], data_barang[i][3]);
		}
	}
	FILE *fp = fopen(file_name, "w");//reset file jadi kosong
	fclose(fp);
	for(i=0;i<jml_data_barang;i++){
		addToFile(kalimat[i]);
	}
}

void transaksi(){
	system("color A");
	view_tr("Transaksi");
	char kode[50],jumlah[50],pilihan,namae[50][200],fileName[200],last;
	int hargae[50],stoke[50],totale[50];
	int total_brg=1,l=1,i=0,j=0,k;
	getData();
	char history[50][200];
	memset(kode_beli,0,sizeof(kode_beli));
   	memset(jumlah_beli,0,sizeof(jumlah_beli));
	while (l>0){
		l--;
		printf("Masukkan Kode barang = ");
		scanf("%s",&kode);
		kode_beli[i] = atoi(kode);
				
		printf("Masukkan Jumlah barang = ");
		scanf("%s",&jumlah);
		jumlah_beli[i] = atoi(jumlah);
		
		if(verif_tr(kode,jumlah) != false){
			printf("Tambah data (y/t) =");
			scanf(" %c",&pilihan);
			if(pilihan == 'y' || pilihan == 'Y'){
				l++; i++;
				total_brg++;
			} else if(pilihan == 't' || pilihan == 'T'){
				
			} else {
				printf("Pilihan Salah !\n");
				system("pause");
				transaksi();
			}
		} else {
			printf("Data salah atau Kurang\n");
			system("pause");
			transaksi();
		}	
	}
	i = 0;
	printf("============================================\n");
	    
	char nama_brg[100],tampung[100][200],struk[100][700];
	int kodene[50];
	bool ada =false;
	for (k = 0; k < total_brg; k++) {
		for (i = 0; i < jml_data_barang; i++) {
			int kode_brg = atoi(data_barang[i][0]);
			int harga_brg = atoi(data_barang[i][2]);
	        int stok_brg = atoi(data_barang[i][3]);
			if(atoi(data_barang[i][0]) == kode_beli[k]){
				strcpy(namae[k],data_barang[i][1]);
				strcpy(nama_brg, namae[k]);
				hargae[k] =  atoi(data_barang[i][2]);
				stoke[k] =  atoi(data_barang[i][3]);
				kodene[k] = atoi(data_barang[i][0]);
			}
		}
		
	}
	int total_hrg[10],bayar,kembalian,keseluruhan=0;
	system("cls");
	printf("============================================\n");
	printf("\t\tKentank Shop\n");
	printf("\tJalan Dosoman Gg Elang no 15\n");
	printf("============================================\n");
	printf("Nama Barang\tHarga\tJumlah\tTotal Harga\t\n");
	printf("============================================\n");
	for(i=0;i<total_brg;i++){
		total_hrg[i] = hargae[i]*jumlah_beli[i]; 
		strcpy(nama_brg, namae[i]);
		if (strlen(nama_brg) > 15) {
	   		strcpy(nama_brg, substring(nama_brg, 1, 15));
		} else if (strlen(nama_brg) < 8) {
	   		snprintf(nama_brg, sizeof nama_brg, "%s%s", nama_brg, "\t");
		}
		printf("%s\t%d\t%d\tRp.%d\n",nama_brg,hargae[i],jumlah_beli[i],total_hrg[i]);
		keseluruhan = keseluruhan + total_hrg[i];
	}
	printf("============================================\n");
	printf("Total =\t\t\t\tRp.%i\n",keseluruhan);
	printf("Bayar =\t\t\t\tRp.");
	scanf(" %i",&bayar);
	if(bayar < keseluruhan){
		printf("Uang Pembayaran Kurang!\n");	
		printf("============================================\n");
		system("pause");
		main();
	} else if(bayar>=keseluruhan){
		getTime();
		// Mendapatkan info DateTime Terkini
	struct tm *Sys_T;
 	char datetimeku[100],tanggal[20],waktu[20];
    time_t Tval;
    Tval = time(NULL);
    Sys_T = localtime(&Tval); 
    snprintf(datetimeku, sizeof datetimeku,"%d%.2d%.2d%.2d%.2d%.2d",1900+Sys_T->tm_year,Sys_T->tm_mon+1,Sys_T->tm_mday,Sys_T->tm_hour,Sys_T->tm_min,Sys_T->tm_sec);
	snprintf(tanggal, sizeof tanggal,"%.2d/%.2d/%.4d",Sys_T->tm_mday,Sys_T->tm_mon+1,1900+Sys_T->tm_year);
	snprintf(waktu, sizeof waktu,"%.2d:%.2d:%.2d",Sys_T->tm_hour,Sys_T->tm_min,Sys_T->tm_sec);
		// Menghitung Kembalian
	kembalian = bayar - keseluruhan;
		// Proses potong stok
	for(i=0;i<jml_data_barang;i++){
		potongstok(kodene[i],jumlah_beli[i]);
	}
	// cetak Struk	
	snprintf(struk[0], sizeof struk[0],"\t\tKentank Shop\n\tJalan Dosoman Gg Elang no 15\n============================================\n");
	snprintf(struk[1], sizeof struk[1],"Tanggal\t\t\t\t%s\n",tanggal);
	snprintf(struk[2], sizeof struk[2],"Waktu\t\t\t\t%s\n",waktu);
	snprintf(struk[3], sizeof struk[3],"Kasir\t\t\t\t%s\n",username);
	snprintf(struk[4], sizeof struk[4],"============================================\nNama Barang\tHarga\tJumlah\tTotal Harga\t\n============================================\n");
	l=0;
	for(i=0;i<total_brg;i++){
		total_hrg[i] = hargae[i]*jumlah_beli[i]; 
		strcpy(nama_brg, namae[i]);
		if (strlen(nama_brg) > 15) {
	   		strcpy(nama_brg, substring(nama_brg, 1, 15));
		} else if (strlen(nama_brg) < 8) {
	   		snprintf(nama_brg, sizeof nama_brg, "%s%s", nama_brg, "\t");
		}
		snprintf(struk[l+5], sizeof struk[l+5],"%s\t%i\t%i\tRp.%i\n", nama_brg, hargae[i],jumlah_beli[i],total_hrg[i] );
		snprintf(history[i], sizeof history[i],"%s;%s;%i;%i;%s;%s;\n", datetimeku,namae[i],jumlah_beli[i],total_hrg[i],uname,currentTime );
		l++;
			addToHistory(history[i]);
		
	}
	snprintf(struk[l+6], sizeof struk[l+6],"============================================\n");
	snprintf(struk[l+7], sizeof struk[l+7],"Total =\t\t\t\tRp.%i\n",keseluruhan);
	snprintf(struk[l+8], sizeof struk[l+8],"Bayar =\t\t\t\tRp.%i\n",bayar);
	snprintf(struk[l+9], sizeof struk[l+9],"Kembalian =\t\t\tRp.%i\n",kembalian);
	snprintf(struk[l+10], sizeof struk[l+10],"============================================\n");
	snprintf(struk[l+11], sizeof struk[l+11],"========Terimakasih Telah berbelanja========\n");
	snprintf(struk[l+12], sizeof struk[l+12],"\t\t#DiRumahAja\n");
	strcat(datetimeku,".txt");
	strcat(fileName,datetimeku);	
	FILE *fp;
		fp = fopen(fileName, "w"); //reset file jadi kosong
		fclose(fp);
	for(i=0;i<l+13;i++){
		addNewFile(struk[i],fileName);
	}	
	printf("Kembalian =\t\t\tRp.%i\n",kembalian);
	printf("============================================\n");	
	printf("========Terimakasih Telah berbelanja========\n");
	printf("Cetak Struk? (y/t)");
	scanf(" %c",&last);
		if(last == 'y' || last == 'Y'){
			system("color F0");
			cetak(fileName);
		} else if(last == 't'|| last == 'T'){
			main();
		} else {
			main();
		}
	}
}

int cetak(char fileName[]){
	char ch;
	system("cls");
   	FILE *fp;
	fp = fopen(fileName, "r");

	if (fp == NULL) {
      printf("Gagal membuka file %s", fileName);
      exit(EXIT_FAILURE);
   	}
	printf("Membuka isi %s : \n\n",fileName);
	
   	while((ch = fgetc(fp)) != EOF) {
   		printf("%c", ch);
	}

   fclose(fp);
   system("pause");
   main();
}

int addNewFile(char inputan[],char fileName[]) {
	FILE *fp = fopen(fileName,"a+");
	if (fp == NULL) {
		return false;
	} else {
		fputs(inputan, fp);
	}
	fclose(fp);
	return true;
}

void hapusData() {
	system("color A");
	system("@cls||clear");
	printf("============================================\n");
   	printf("Menu Hapus Data Barang\n");
   	printf("============================================\n");
   	char kode_hapus[100];
   	printf("Masukkan Kode Barang : ");
   	scanf("%s",&kode_hapus);
	if (jml_data_barang > 0) {
		FILE *fp = fopen(file_name, "r");
	    char line[200];
		   
		if (fp == NULL) {
			printf("Gagal membuka file %s", file_name);
			exit(EXIT_FAILURE);
		} else {
			bool ada = false, ada2 = false;
			int i = 0, j = 0, k = 0;
			char tampung[100][200];
			while (fgets(line, sizeof(line), fp) != NULL) {
				char *token = strtok(line, delim);
	    		j = 0;
				ada = false;
				while (token != NULL) {
					if (j == 0) {
						if (strcmp(data_barang[i][j],kode_hapus) == 0) {
							ada = true;
							ada2 = true; //memastikan jika ketemu
						}
					}
					token = strtok(NULL, delim);
					j++;
				}
				
				if (!ada) {
					int KodeKu = atoi(data_barang[i][0]);
					if(KodeKu > 0){
						snprintf(tampung[k], sizeof tampung[k], "%s;%s;%s;%s;\n", data_barang[i][0], data_barang[i][1], data_barang[i][2], data_barang[i][3]);
						k++;
					} else {
						
					}
				}
				i++;
			}
			fclose(fp);
			printf("============================================\n");
			if (ada2) {
				fp = fopen(file_name, "w"); //reset file jadi kosong
				fclose(fp);
				if (k > 0) {
					for (i = 0; i < k; i++) {
						addToFile(tampung[i]);
					}	
				}
				printf("Sukses hapus (%s) dari data barang!\n",kode_hapus);
			} else {
				printf("Nama barang (%s) tidak ditemukan!\n",kode_hapus);
			}
		}
   	} else {
   		printf("============================================\n");
   		printf("Tidak ada data barang!\n");
    }
    
    printf("============================================\n");
    system("pause");
    menu_utama();
}

void menu(int pil) {
	if (pil == 1) viewData();
	else if (pil == 2) tambahData();
	else if (pil == 3) hapusData();
	else if (pil == 4) updateHarga();
}

int addToHistory(char inputan[]) {
	FILE *fp = fopen("history.txt","a+");
	if (fp == NULL) {
		return false;
	} else {
		fputs(inputan, fp);
	}
	fclose(fp);
	return true;
}

int menu_utama() {
	system("color F4");
	int pilihan = 0;
	while (pilihan == 0) {
		system("@cls||clear");
		printf("============================================\n");
		printf("\tMENU UTAMA\n");
		printf("============================================\n");
		printf("1. Lihat Data Barang\n");
		printf("2. Tambah Data Barang\n");
		printf("3. Hapus Data Barang\n");
		printf("4. Update Harga Barang\n");
		if(strcmp(level_log,"admin") == 0){
			printf("5. Menu Admin\n");
			printf("6. Transaksi\n");
			printf("7. Logout\n");
			printf("8. EXIT\n");
			
			printf("Pilih Menu : ");
			scanf("%d",&pilihan);
			if (pilihan <= 0 || pilihan > 8) {
				pilihan = 0;
				system("@cls||clear");
				printf("Pilihan Menu Salah!");
				system("pause");
			}
		} else {
			printf("5. Transaksi\n");
			printf("6. Logout\n");
			printf("7. Exit\n");
			
			printf("Pilih Menu : ");
			scanf("%d",&pilihan);
			if (pilihan <= 0 || pilihan > 7) {
				pilihan = 0;
				system("@cls||clear");
				printf("Pilihan Menu Salah!");
				system("pause");
			}
		}
		
	}
	if(strcmp(level_log,"admin") == 0){
		if (pilihan == 5) menu_user();
		else if (pilihan == 6) transaksi();
		else if (pilihan == 7) logout();
		else if (pilihan == 8) exit(EXIT_SUCCESS);
		else menu(pilihan);
	} else {
		if (pilihan == 5) transaksi();
		else if (pilihan == 6) logout();
		else if (pilihan == 7)  exit(EXIT_SUCCESS);
		else menu(pilihan);
	}
	
	
}

void getUser() {
	FILE *fp = fopen(file_user, "r");
    char line[200];
	
	memset(data_user,0,sizeof(data_user));
    jml_data_user = 0;  
	   
	if (fp == NULL) {
		printf("Gagal membuka file %s", file_user);
		exit(EXIT_FAILURE);
	} else {
		int i = 0;
		while (fgets(line, sizeof(line), fp) != NULL) {
			char *token = strtok(line, delim);
    		
    		int j = 0;
			while (token != NULL) {
				strcpy(data_user[i][j], token);
				token = strtok(NULL, delim);
				j++;
			}
			
			i++;
			jml_data_user++;
		}
	}
	fclose(fp);
}

void getHistory() {
	FILE *fp = fopen(file_history, "r");
    char line[200];
	
	memset(data_history,0,sizeof(data_history));
    jml_data_history = 0;  
	   
	if (fp == NULL) {
		printf("Gagal membuka file %s", file_history);
		exit(EXIT_FAILURE);
	} else {
		int i = 0;
		while (fgets(line, sizeof(line), fp) != NULL) {
			char *token = strtok(line, delim);
    		
    		int j = 0;
			while (token != NULL) {
				strcpy(data_history[i][j], token);
				token = strtok(NULL, delim);
				j++;
			}
			
			i++;
			jml_data_history++;
		}
	}
	fclose(fp);
}

void getTime(){
	struct tm *Sys_T;
    time_t Tval;
    Tval = time(NULL);
    Sys_T = localtime(&Tval); 
    snprintf(currentTime, sizeof currentTime,"%d-%.2d-%.2d %.2d:%.2d:%.2d",1900+Sys_T->tm_year,Sys_T->tm_mon+1,Sys_T->tm_mday,Sys_T->tm_hour,Sys_T->tm_min,Sys_T->tm_sec);
}

bool addUserFile(char inputan[]) {
	FILE *fp = fopen(file_user,"a+");
	if (fp == NULL) {
		return false;
	} else {
		fputs(inputan, fp);
	}
	fclose(fp);
	return true;
}

void view_user(char judul[50]){
	getUser();
    system("@cls||clear");
    printf("======================================================================================================================\n");
   	printf("\tMenu %s\n",judul);
   	printf("======================================================================================================================\n");
    if (jml_data_user > 0) {
        printf("ID\tNama Anggota\tUsername\tPassword\tLevel\tLast Login\t\tReg Date\n");
   		printf("======================================================================================================================\n");
        int i;
		for (i = 0; i < jml_data_user; i++) {
			
			
			id_user[i] = atoi(data_user[i][0]);
			strcpy(namaUser[i],data_user[i][1]);
			strcpy(username[i],data_user[i][2]);
			strcpy(password[i],data_user[i][3]);
			strcpy(level[i],data_user[i][4]);
			strcpy(last_login[i],data_user[i][5]);
			strcpy(reg_date[i],data_user[i][6]);
			
			if (strlen(namaUser[i]) > 15) {
		   		strcpy(namaUser[i], substring(namaUser[i], 1, 15));
			} else if (strlen(namaUser[i]) < 8) {
		   		snprintf(namaUser[i], sizeof namaUser[i], "%s%s", data_user[i][1], "\t");
			}
			
			if (strlen(username[i]) > 15) {
		   		strcpy(username[i], substring(username[i], 1, 15));
			} else if (strlen(username[i]) < 8) {
		   		snprintf(username[i], sizeof username[i], "%s%s", data_user[i][2], "\t");
			}
			if (strlen(password[i]) > 15) {
		   		strcpy(password[i], substring(password[i], 1, 15));
			} else if (strlen(username[i]) < 8) {
		   		snprintf(password[i], sizeof password[i], "%s%s", data_user[i][3], "\t");
			}
			printf("%i\t%s\t%s\t%s\t%s\t%s\t%s\n",id_user[i],namaUser[i],username[i],password[i],level[i],last_login[i],reg_date[i]);
			
        }
    } else {
        printf("Tidak ada data barang!\n");
    }
    printf("======================================================================================================================\n");
}

void viewUser() {
	system("color A");
    view_user("Lihat User");
    system("pause");
    main();
}


void login(){
	system("cls");
	printf("============================================\n");
	printf("\tLOGIN AREA\n");
	printf("============================================\n");
	printf("Masukkan Username : ");
	scanf("%s",&uname);
	printf("Masukkan Password : ");
	scanf("%s",&pass);
	if(cekUser(uname,pass) == true){
		user_login = true;
		printf("Login berhasil !\n");
		printf("Selamat Datang %s\n", namalog);
		system("pause");
		main();
	} else if(user_login != true){
		printf("Login Gagal !\n");
		system("pause");
		main();
	}
}

int cekReg(char uname[200],int kodee){
	int i;
	bool c = false;
	for(i=0;i<jml_data_user;i++){
		if(strcmp(uname,data_user[i][2]) == 0 || kodee == atoi(data_user[i][0])){
				c = true;
		}
	}
	return c;
}

int cekUser(char uname[], char pass[]){
	int i;
	getUser();
	getTime();
	char tampung[50][200];
	bool c = false;
	for(i=0;i<jml_data_user;i++){
		if(strcmp(uname,data_user[i][2]) == 0 && strcmp(pass,data_user[i][3]) == 0){
			c = true;
			getTime();
			strcpy(namalog,data_user[i][1]);
			strcpy(level_log,data_user[i][4]);
			snprintf(tampung[i], sizeof tampung[i],"%s;%s;%s;%s;%s;%s;%s;\n",data_user[i][0],data_user[i][1],data_user[i][2],data_user[i][3],data_user[i][4],currentTime,data_user[i][6]);
		} else {
			snprintf(tampung[i], sizeof tampung[i],"%s;%s;%s;%s;%s;%s;%s;\n",data_user[i][0],data_user[i][1],data_user[i][2],data_user[i][3],data_user[i][4],data_user[i][5],data_user[i][6]);
		}
	}
	
	if(c == true){
		FILE *fp = fopen(file_user, "w");
	fclose(fp);
		for(i=0;i<jml_data_user;i++){
			addUserFile(tampung[i]);
		}
	} 
	
	return c;
}

void tambahUser(){
	system("cls");
	printf("============================================\n");
	printf("\tTAMBAH USER\n");
	printf("============================================\n");
	char reg_uname[200],reg_pass[200],reg_nama[200],reg_level[200],hasil[200],kodeee[200];
	int reg_kode;
	printf("Masukkan Kode (3 angka) : ");
	scanf("%s",&kodeee);
	reg_kode = atoi(kodeee);
	if(reg_kode == 0 || reg_kode<100 || strlen(kodeee) != 3){
		printf("kode salah");
		system("pause");
		tambahUser();
	}
	printf("Masukkan Username : ");
	scanf("%s",&reg_uname);
	if(cekReg(reg_uname,reg_kode) != true){ // barang tidak ada
		printf("Masukkan Password : ");
		scanf("%s",&reg_pass);
		printf("Masukkan Nama : ");
		scanf("%s",&reg_nama);
		printf("Masukkan Level : ");
		scanf("%s",&reg_level);
		if(strcmp(reg_level,"admin") != 0 || strcmp(reg_level,"member") != 0){
			strcpy(reg_level,"member");
		}
	} else {
		printf("Error ! data sudah ada \n");
		system("pause");
		tambahUser();
	}
		getTime();
		snprintf(hasil, sizeof hasil, "%d;%s;%s;%s;%s;%s;%s;\n",reg_kode,reg_nama,reg_uname,reg_pass,reg_level,currentTime,currentTime);
		if (addUserFile(hasil)) {
			printf("Sukses tambah data barang!\n");
		} else {
			printf("Gagal tambah data barang!\n");
		}
		system("pause");
	main();
	
}

void hapusUser() {
	system("color A");
	system("@cls||clear");
	printf("============================================\n");
   	printf("Menu Hapus Data Barang\n");
   	printf("============================================\n");
   	char uname_hapus[100];
   	printf("Masukkan Username untuk dihapus : ");
   	scanf("%s",&uname_hapus);
	if (jml_data_user > 0) {
		FILE *fp = fopen(file_user, "r");
	    char line[200];
		   
		if (fp == NULL) {
			printf("Gagal membuka file %s", file_user);
			exit(EXIT_FAILURE);
		} else {
			bool ada = false, ada2 = false;
			int i = 0, j = 0, k = 0;
			char tampung[100][200];
			while (fgets(line, sizeof(line), fp) != NULL) {
				char *token = strtok(line, delim);
	    		j = 0;
				ada = false;
				while (token != NULL) {
					if (j == 2) {
						if (strcmp(data_user[i][j],uname_hapus) == 0) {
							ada = true;
							ada2 = true; //memastikan jika ketemu
						}
					}
					token = strtok(NULL, delim);
					j++;
				}
				
				if (!ada) {
					int KodeU = atoi(data_user[i][0]);
					if(KodeU > 0){
						snprintf(tampung[k], sizeof tampung[k],"%s;%s;%s;%s;%s;%s;%s;\n",data_user[i][0],data_user[i][1],data_user[i][2],data_user[i][3],data_user[i][4],data_user[i][5],data_user[i][6]);
						k++;
					} else {
						
					}
				}
				i++;
			}
			fclose(fp);
			printf("============================================\n");
			if (ada2) {
				fp = fopen(file_user, "w"); //reset file jadi kosong
				fclose(fp);
				if (k > 0) {
					for (i = 0; i < k; i++) {
						addUserFile(tampung[i]);
					}	
				}
				printf("Sukses hapus (%s) dari data barang!\n",uname_hapus);
			} else {
				printf("Nama barang (%s) tidak ditemukan!\n",uname_hapus);
			}
		}
   	} else {
   		printf("============================================\n");
   		printf("Tidak ada data barang!\n");
    }
    
    printf("============================================\n");
    system("pause");
    menu_user();
}

void History_Tr(){
	system("cls");
	printf("========================================================================================\n");
	printf("\tMenu History Transaksi\n");
	printf("========================================================================================\n");
	
	getHistory();
	if (jml_data_history > 0) {
       printf("No\tInvoice\t\tNama Barang\tJumlah\tHarga\tKasir\tTanggal\n");
   		printf("========================================================================================\n");
        int i;
		for (i = 0; i < jml_data_history; i++) {

			char invoice[200];
			strcpy(invoice,data_history[i][0]);
            char nama_brg[200];
            strcpy(nama_brg,data_history[i][1]);
            char nama_kasir[200];
            strcpy(nama_kasir,data_history[i][4]);
            char tanggal_beli[200];
            strcpy(tanggal_beli,data_history[i][5]);
            if (strlen(nama_brg) > 15) {
		   		strcpy(nama_brg, substring(nama_brg, 1, 15));
			} else if (strlen(nama_brg) < 8) {
		   		snprintf(nama_brg, sizeof nama_brg, "%s%s",nama_brg, "\t");
			}
			int jumlah_brg = atoi(data_history[i][2]);
            int harga_brg = atoi(data_history[i][3]);
			if(atoi(data_history[i][0]) != 0){
				printf("%i\t%s\t%s\t%d\t%d\t%s\t%s \n",i+1,invoice,nama_brg,jumlah_brg,harga_brg,nama_kasir,tanggal_beli);
			} else {
				
			}
            
        }
        int lihat;
        printf("Lihat Struk No :");
        scanf("%i",&lihat);
        char invoiceid[200];
        bool history_ada = false;
        for (i = 0; i < jml_data_history; i++) {
            if(i == lihat-1){
            	strcpy(invoiceid,data_history[i][0]);
            	strcat(invoiceid,".txt");
            	history_ada = true;
			}
        }
        if(history_ada == true){
        	cetak(invoiceid);
		} else {
			printf("Data tidak ditemukan !\n");
			system("pause");
			History_Tr();
		}
        
        
        
    } else {
        printf("Tidak ada History Belanja!\n");
    }
    
    
    system("pause");
    menu_user();
}


void menuU(int pil) {
	if (pil == 1) viewUser();
    else if (pil == 2) tambahUser();
	else if (pil == 3) hapusUser();
	else if (pil == 4) History_Tr();
}

int menu_user(){
	system("color F4");
	int pilihan = 0;
	while (pilihan == 0) {
		system("@cls||clear");
		printf("============================================\n");
		printf("\tMENU ADMIN\n");
		printf("============================================\n");
		printf("1. Lihat Data User\n");
		printf("2. Tambah Data User\n");
		printf("3. Hapus Data User\n");
		printf("4. History Transaksi\n");
		printf("5. Menu Utama\n");
		printf("Pilih Menu : ");
		scanf("%d",&pilihan);
		if (pilihan <= 0 || pilihan > 5) {
			pilihan = 0;
			system("@cls||clear");
			printf("Pilihan Menu Salah!");
			system("pause");
		}
	}
	if (pilihan == 5) menu_utama();
	else menuU(pilihan);
}

int logout(){
	user_login = false;
	system("cls");
	printf("Anda Berhasil Logout..\n");
	system("pause");
	main();
}

int main() {
	system("color 0F");
	memset(temp_stok,0,sizeof temp_stok);
	getData();
	if(user_login == true){
		menu_utama();
	} else if(user_login != true){
		loading(34,14);
		login();	
	}
}

int loading(int x,int y);
void gotoxy(int x,int y){
	HANDLE handle;
	COORD coord;
	coord.X =x;
	coord.Y =y;
	handle  = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle,coord);
}
int loading(int x,int y){
	system("cls");
	int i;
	gotoxy(x,y-1);printf("Loading...");
	for(i=x;i<=x+19;i++){
	    gotoxy(i,y);
		printf("%c",196);
		gotoxy(i,y+1);
		printf("%c",196);	
	}
	for(i=y;i<=y+1;i++){
	    gotoxy(x,i);
		printf("%c",179);
		gotoxy(x+19,i);
		printf("%c",179);	
	}
	gotoxy(x,y);
	printf("%c",218);
	gotoxy(x+19,y);
	printf("%c",191);
	gotoxy(x,y+1);
	printf("%c",192);
	gotoxy(x+19,y+1);
	printf("%c",217);
	for ( i = x; i<=x+19;i++){
		gotoxy(i,y);
		printf("%c",220);
		gotoxy(i,y+1);
		printf("%c",223);
		Sleep(30);
	}
	system("cls");
}


