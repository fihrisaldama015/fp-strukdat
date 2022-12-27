#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int Keluhan;
    char Nama[20];
    struct node *next;
};
typedef struct node node;

struct data {
    char Nama[20];
    char Jenis[20];
    int umur;
	int Keluhan;
    struct data *next,*prev;
};
typedef struct data data;

struct antrian {
  struct node *front;
  int count;
  struct node *rear;
};
typedef struct antrian antrian;

antrian bukaAntrian(void);
void AddPatient(node **head, antrian *antrian, data **history);
void ProcessPatient(node **head, antrian *antrian);
void traverse(node *head, antrian *antrian);
void showHistory(data *history);

int main()
{
  char selectMenu, lanjut;
  node *head;
  head = NULL;
  data *history;
  history = NULL;
  antrian antrian;
  antrian = bukaAntrian();
  do{
    system("cls");
    printf("||=========================================================||\n");
    printf("|                       FINAL PROJECT                       |\n");
    printf("||=========================================================||\n");
    printf("|  APLIKASI RUMAH SAKIT                                     |\n");
    printf("|  -    Rawat Inap atau Rawat Jalan                         |\n");
    printf("|  -    Dokter (4)                                          |\n");
    printf("|  -    Jenis kamar (VIP, kelas 1, kelas 2, kelas 3)        |\n");
    printf("|  -    Lama waktu rawat inap                               |\n");
    printf("|  -    Data pasien                                         |\n");
    printf("|  -    Biaya dokter, kamar, obat                           |\n");
    printf("||=========================================================||\n");
    printf("Tekan Y untuk melanjukan : "); scanf("%s", &lanjut);
    if (lanjut=='y'||lanjut=='Y') goto menu1;
	else 
	{
		printf("                      TERIMA KASIH                           \n");
		system("exit");
		break;
	}
    
    menu1:
	system("cls");
	printf(" ==================================================================================== \n");
	printf("|                            RUMAH SAKIT UPN VETERAN JAWA TIMUR                      |\n");
	printf("|   Jl. Rungkut Madya No.1, Gn. Anyar, Kec. Gn. Anyar, Kota SBY, Jawa Timur 60294    |\n");
	printf("|                  email: RSUPNVJT@college.go.id   Website: www.rsupnvjt.com         |\n");
	printf(" ------------------------------------------------------------------------------------ \n");
	printf("  Syarat untuk mendapatkan pelayanan perawatan di Rumah Sakit UPN Veteran Jawa Timur\n");
	printf("  Anda harus mengisi semua form berikut secara berurut (wajib). Terima kasih.\n");
	printf("  1. Masukan Antrian\n");      
	printf("  2. Proses Antrian\n");
	printf("  3. Tampilkan Antrian\n");
	printf("  4. Tampilkan History Pasien\n");
	printf("Masukkan Pilihan (ketik 'q' untuk keluar) : "); 
	fflush(stdin); scanf("%c", &selectMenu);
	if (selectMenu == '1')
        AddPatient(&head, &antrian, &history);
    else if (selectMenu == '2')
        ProcessPatient(&head, &antrian);
    else if (selectMenu == '3')
        traverse(head, &antrian);
    else if (selectMenu == '4')
        showHistory(history);
  } while (selectMenu != 'q');
}

antrian bukaAntrian(void){
  antrian head;
  head.count = 0;
  head.front = NULL;
  head.rear = NULL;
  return(head);
}

//========================================================
void AddPatient(node **head, antrian *antrian, data **history)
{
    node *pNew, *pCur, *KeluhanKecil, *Masuk;
	data  *pNewHistory, *pTailHistory;
    int Keluhan, umur;
    char Nama[20], gender[20];
    int bolehMasuk = 1, KeluhanLebihKecil = 0;
    system("cls");
    pNew = (node *)malloc(sizeof(node));
    pNewHistory = (data *)malloc(sizeof(data));

	printf("Masukkan Keluhan : ");
	printf("\n1.Umum  ");
	printf("\n2.IGD  ");
	printf("\n3.UGD \n");
	fflush(stdin);scanf("%i",&Keluhan);

	system("cls");
	printf("Data Pasien\n"); 
	printf("Nama Pasien : "); fflush(stdin);scanf(" %s", &Nama);
	printf("Umur : "); fflush(stdin);scanf("%i", &umur);
	printf("Gender [L/P] : "); fflush(stdin);scanf("%s", &gender);
	printf("\nPendaftaran Berhasil!\n");

	if (*head == NULL)
	{
		strcpy(pNew->Nama, Nama);
		pNew->Keluhan = Keluhan;
		pNew->next = NULL;
		*head = pNew;

		strcpy(pNewHistory->Nama, Nama);
		strcpy(pNewHistory->Jenis, gender);
		pNewHistory->Keluhan = Keluhan;
		pNewHistory->umur = umur;
		pNewHistory->next = NULL;
		pNewHistory->prev = NULL;
		*history = pNewHistory;
		antrian->count += 1;
		if(antrian->front == NULL)
		{
			antrian->rear = pNew;
			antrian->front = pNew;
		}
		else
		{
			antrian->rear = pNew;
		}
	}
	else
	{
		pTailHistory = *history;
		while (pTailHistory->next != NULL) pTailHistory = pTailHistory -> next;
		strcpy(pNewHistory->Nama, Nama);
		strcpy(pNewHistory->Jenis, gender);
		pNewHistory->Keluhan = Keluhan;
		pNewHistory->umur = umur;
		pNewHistory->next = NULL;
		pNewHistory->prev = pTailHistory;
		pTailHistory->next = pNewHistory;

		pCur = *head;
		while (pCur->next != NULL) pCur = pCur -> next;

		Masuk = *head;
		KeluhanKecil = *head;
		while (KeluhanKecil != NULL)
		{
			if(KeluhanKecil->Keluhan < Keluhan)
			{
				KeluhanLebihKecil = 1;
				break;
			}
			else 
			{
				Masuk = KeluhanKecil;
				KeluhanKecil = KeluhanKecil -> next;
			}
		}
		if (pNew != NULL)
		{
			if(bolehMasuk)
			{
				printf("Boleh masuk !\n");
				strcpy(pNew->Nama, Nama);
				pNew->Keluhan = Keluhan;
				antrian->count += 1;
				if(KeluhanLebihKecil)
				{
					pNew->next = KeluhanKecil;
					if(Masuk == KeluhanKecil)
					{
						*head = pNew;
						antrian->front = pNew;
					} 
					else Masuk->next = pNew;
				}
				else
				{
					pNew->next = NULL;
					pCur->next = pNew;
					antrian->rear = pNew;
				}
			}
			else printf("Tidak boleh masuk !\n");
		}
		else printf("\nERR: NOT ENOUGH MEMORY!");
	}
	getch();
}
  
void ProcessPatient(node **head, antrian *antrian)
{
    int data_target;
	int pil, kamar, bidok, biob, tot, lama, bikam, tarif, dokter;
    node *pCur;
    system("cls");
    traverse(*head, antrian);
    printf("\nMemproses Antrian Terdepan\n");
    printf("========================================\n\n");
	pCur=*head;
	if (pCur->Keluhan == 1)
	{
		printf("1. Rawat Jalan\n");
		printf("2. Rawat Inap\n");
		printf("Masukkan Pilihan : "); scanf("%i", &pil);

		if ( pil == 1)
		{
			printf("Biaya Dokter : "); scanf("%i", &bidok);
			printf("Biaya Obat : "); scanf("%i", &biob);
			tot = bidok + biob;
			printf("Total Tagihan : %i", tot);
		}
		else if (pil == 2)
		{
			printf("Lama Menginap (malam) : "); scanf("%i", &lama);
			printf(" _____________________________________________\n");
			printf(" | No.|   Jenis Kamar                        |\n");
			printf(" |____|______________________________________|\n");
			printf(" | 1  |   VIP                                |\n");
			printf(" | 2  |   Kelas I                            |\n");
			printf(" | 3  |   Kelas II                           |\n");
			printf(" | 4  |   Kelas III                          |\n");
			printf(" |____|______________________________________|\n");
			printf(" Pilihan Anda[1/2/3/4]= "); scanf("%i", &kamar);
			if (kamar == 1) tarif = 3500000;
			else if (kamar == 2) tarif = 2000000;
			else if (kamar == 3) tarif = 1350000;
			else if (kamar == 4) tarif = 850000;
			bikam = tarif * lama;
			printf("Tarif kamar per malam Rp. %i,-", tarif);
			printf("\nTagihan Kamar : %i", bikam);
			printf("\n _____________________________________________\n");
			printf(" | No.|   Pelayanan Spesialis                |\n");
			printf(" |____|______________________________________|\n");
			printf(" | 1  |   Spesialis Bedah                    |\n");
			printf(" | 2  |   Spesialis Jantung                  |\n");
			printf(" | 3  |   Spesialis Orthopedi                |\n");
			printf(" | 4  |   Spesialis Penyakit Dalam           |\n");
			printf(" |____|______________________________________|\n");
			printf(" Pelayanan yang Anda butuhkan[1/2/3/4]= "); scanf("%i", &dokter);
			printf("\n");
			if (dokter == 1)
			{
				bidok = lama * 1800000;
				printf(" ---------------------------------------------------------------\n");
				printf("                  RUMAH SAKIT UPN VETERAN JAWA TIMUR            \n");
				printf(" ---------------------------------------------------------------\n");
				printf(" Pelayanan Spesialis Bedah\n");
				printf(" |#############|    dr.H Agoes Sarnanto I, Sp.B\n");
				printf(" |             |    Spesialis:\n");
				printf(" |             |    Bedah Umum\n");
				printf(" |    PHOTO    |\n");
				printf(" |             |\n");
				printf(" |             |\n");
				printf(" |             |\n");
				printf(" |#############|\n");
				printf(" Biaya perawatan untuk 1 kali pengecekan dokter (per hari 2x cek)\n");
				printf(" Rp. 1.800.000- (belum termasuk biaya obat dan kamar)\n");
				printf(" ---------------------------------------------------------------\n");
			}
			else if (dokter == 2)
			{
				bidok = lama * 1600000;
				printf(" ---------------------------------------------------------------\n");
				printf("                  RUMAH SAKIT UPN VETERAN JAWA TIMUR            \n");
				printf(" ---------------------------------------------------------------\n");
				printf(" Pelayanan Spesialis Jantung\n");
				printf(" |#############|    dr.Haikal Maswari, Sp.JP\n");
				printf(" |             |    Spesialis:\n");
				printf(" |             |    Penyakit Jantung\n");
				printf(" |    PHOTO    |\n");
				printf(" |             |\n");
				printf(" |             |\n");
				printf(" |             |\n");
				printf(" |#############|\n");
				printf(" Biaya perawatan untuk 1 kali pengecekan dokter (per hari 2x cek)\n");
				printf(" Rp. 1.600.000- (belum termasuk biaya obat dan kamar)\n");
				printf(" ---------------------------------------------------------------\n");
			}
			else if (dokter == 3)
			{
				bidok = lama * 1500000;
				printf(" ---------------------------------------------------------------\n");
				printf("                  RUMAH SAKIT UPN VETERAN JAWA TIMUR            \n");
				printf(" ---------------------------------------------------------------\n");
				printf(" Pelayanan Spesialis Orthopedi\n");
				printf(" |#############|    dr.Miesya Andien, Sp.OT\n");
				printf(" |             |    Spesialis:\n");
				printf(" |             |    Orthopedi\n");
				printf(" |    PHOTO    |\n");
				printf(" |             |\n");
				printf(" |             |\n");
				printf(" |             |\n");
				printf(" |#############|\n");
				printf(" Biaya perawatan untuk 1 kali pengecekan dokter (per hari 2x cek)\n");
				printf(" Rp. 1.500.000- (belum termasuk biaya obat dan kamar)\n");
				printf(" ---------------------------------------------------------------\n");
			}
			else if (dokter == 4)
			{
				bidok = lama * 1350000;
				printf(" ---------------------------------------------------------------\n");
				printf("                  RUMAH SAKIT UPN VETERAN JAWA TIMUR            \n");
				printf(" ---------------------------------------------------------------\n");
				printf(" Pelayanan Spesialis Penyakit Dalam\n");
				printf(" |#############|    Prof.dr.Arini Kasyim,Sp.PD-KPTI\n");
				printf(" |             |    Spesialis:\n");
				printf(" |             |    Penyakit dalam\n");
				printf(" |    PHOTO    |\n");
				printf(" |             |\n");
				printf(" |             |\n");
				printf(" |             |\n");
				printf(" |#############|\n");
				printf(" Biaya perawatan untuk 1 kali pengecekan dokter (per hari 2x cek)\n");
				printf(" Rp. 1.350.000- (belum termasuk biaya obat dan kamar)\n");
				printf(" ---------------------------------------------------------------\n");
			}
			else
			{
				printf("Pilihan tidak ada!\n");
			}
			printf("Biaya Obat : "); scanf("%i", &biob);
			tot = biob + bidok + bikam;
			printf("Total Tagihan : %i", tot);
		}
	}
	if(*head!=NULL)
	{
		antrian->count -= 1;
		if(pCur->next!=NULL)
		{
			*head=pCur->next;
			antrian->front = pCur->next;
		}
		else 
		{
			*head=NULL;
			antrian->front = NULL;
			antrian->rear = NULL;
		}
		free(pCur);
	}
	else printf("The Queue Is Empty!");
	getch();
    traverse(*head, antrian);
}

void traverse(node *head, antrian *antrian)
{
	system("cls");
	node *pWalker;
	pWalker = head;
	if(head != NULL)
	{	
		printf("=============================\n");
		printf("Jumlah Antrian = %i\n", antrian->count);
		printf("Antrian Pertama = %s\n", antrian->front->Nama);
		printf("Antrian Terakhir = %s\n", antrian->rear->Nama);
		printf("=============================\n");
		int i = 1;
		while (pWalker != NULL)
		{
			printf("\n===== %i =====", i);
			printf("\nNama Pasien  :%s", pWalker->Nama);
			printf("\nNilai Urgensi :%d", pWalker->Keluhan);
			printf("\n=============\n");
			pWalker = pWalker -> next;
			i++;
		}
		printf("\n=============================\n");
	}
	else
	{
		printf("Antrian Kosong / Belum Buka\n");
		printf("=============================\n");
		printf("Jumlah Antrian = %i\n", antrian->count);
		printf("=============================\n");
	} 
	getch();
}

void showHistory(data *history)
{
	system("cls");
	data *pWalker;
	pWalker = history;
	if(history != NULL)
	{	
		int pilih;
		while (pWalker != NULL)
		{
			printf("=============================\n");
			printf("        HISTORY PASIEN       \n");
			printf("=============================\n");
			printf("\n=============");
			printf("\nNama Pasien  :%s", pWalker->Nama);
			printf("\nJenis Kelamin :%s", pWalker->Jenis);
			printf("\nUmur :%i", pWalker->umur);
			printf("\nUrgensi :%s", pWalker->Keluhan == 1 ? "Umum" : pWalker->Keluhan == 2 ? "IGD" : "UGD");
			printf("\n=============\n");
			printf("\n=============================\n");
			pilihOperasi:
			printf("Pilih Operasi\n");
			if (pWalker->next != NULL) printf("1. Next Data\n");
			if (pWalker->prev != NULL) printf("2. Prev Data\n");
			printf("3. Done\n");
			scanf("%i", &pilih);
			if (pWalker->next == NULL && pilih == 1)
			{
				printf("Tidak ada data setelah ini!\n");
				goto pilihOperasi;
			}
			if (pWalker->prev == NULL && pilih == 2)
			{
				printf("Tidak ada data sebelum ini!\n");
				goto pilihOperasi;
			}
			if(pilih == 1) pWalker = pWalker -> next;
			else if(pilih == 2) pWalker = pWalker -> prev;
			else if(pilih == 3) return;
			system("cls");
		}
	}
	else
	{
		printf("Antrian Kosong / Belum Buka\n");
	} 
	getch();
}