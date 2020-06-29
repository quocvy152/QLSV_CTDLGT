#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
#include <windows.h>
#include "library.h"

#define MAXLTC 100
#define MAXLOP 50

#define UP 72
#define DOWN 80
#define RIGHT 77
#define LEFT 75
#define ENTER 13
#define ESC 27
#define BACKSPACE 8
#define SPACE 32

// cac chi so can bang balFac = R - L
#define LH -1
#define RH 1
#define EH 0

using namespace std;

//============== DE TAI QUAN LI DIEM SINH VIEN THEO HE TIN CHI ===============

//--------DANH SACH MON HOC---------
struct MH {
	string maMH;
	string tenMH;
	float soTCLT;
	float soTCTH;
};

struct NodeMH {
	MH data;
	int balFactor;
	NodeMH *pLeft;
	NodeMH *pRight;
};
typedef NodeMH *MH_TREE;

//-------- DANH SACH SINH VIEN -------
struct SinhVien {
	string mssv;
	string ho;
	string ten;
	string phai;
	string sdt;
	string maLop;
};

struct NodeSV {
	SinhVien data;
	struct NodeSV *next; 
};
typedef NodeSV *SVPTR;

//-----------QUAN LI LOP------------
struct Lop {
	string maLop;
	string tenLop;
	int nienKhoa;
	SVPTR DSSV;
};

struct ListLop {
	int n;
	Lop dsLop[MAXLOP];
};

//----------DS DANG KI----------
struct DK {
	string mssv;
	float diem = 0;
};

struct NodeDK {
	DK data;
	NodeDK *next;
};
typedef NodeDK *DKPTR;

//----------DS LOP TIN CHI----------
struct LopTC {
	int maLopTC;
	string maMH;
	int nienKhoa;
	int hocKy;
	int nhom;
	int nSvMax;
	int nSvMin;
	bool huyLop;
	DKPTR DSDK = NULL;
};

struct DSLopTC {
	int n;
	LopTC *nodeLopTC[MAXLTC];
};

// ham bat phim
int GetKey() {
	char key;
	key = getch();
	if (key == -32 || key == 0)
		return getch();
	else return key;
}

// ham thong bao
void Notify(char *c, int x, int y, int color) {
	int currentX = wherex(); int currentY = wherey();
	gotoxy(x, y);
	TextColor(color);
	gotoxy(x, y); cout << "     " << c << "     ";
	Sleep(1200);
	while(kbhit()) {
		getch();
	}
	TextColor(0); 
	gotoxy(x, y);
	for (int i = 0; i <= strlen(c); i++)
		cout << "   ";
	TextColor(7);
	gotoxy(currentX, currentY);
}

//================================= MENU =========================================

// menu chinh
char MenuChinh[6][40] = {
	"   QUAN LY LOP TIN CHI  ",
	"   QUAN LY LOP HOC      ",
	"   QUAN LY SINH VIEN    ",
	"   QUAN LY MON HOC      ",
	"   QUAN LY DANG KI      ",
	"   THOAT                "
};

// menu lop tin chi
char MenuLTC[4][40] = {
	"   THEM LOP TIN CHI           ",
	"   XEM DANH SACH LOP TIN CHI  ",
	"   XOA LOP TIN CHI            ",
	"   HIEU CHINH LOP TIN CHI     "
};

// menu lop hoc
char MenuLop[2][40] = {
	"   XEM DANH SACH LOP           ",
	"   XEM DIEM TRUNG BINH         "
};

// menu sinh vien
char MenuSV[4][40] = {
	"   NHAP DANH SACH SINH VIEN    ",
	"   XOA SINH VIEN               ",
	"   HIEU CHINH SINH VIEN        ",
	"   XEM DANH SACH SINH VIEN     "
};

// menu mon hoc
char MenuMH[4][40] {
	"   THEM MON HOC                ",
	"   XOA MON HOC                 ",
	"   HIEU CHINH MON HOC          ",
	"   XEM DANH SACH MON HOC       "
};

// menu dang ki
char MenuDK[5][40] = {
	"   DANG KI LOP TIN CHI         ",
	"   XEM DANH SACH DANG KI       ",
	"   XEM DIEM LOP TIN CHI        ",
	"   NHAP DIEM                   ",
	"   HUY LOP TIN CHI             "
};
//==================================================================================

//======================== KIEM TRA VA SUA DOI PHAN NHAP LIEU ======================
bool isNumberChar(char c) {
	if (c < '0' || c > '9')
		return false;
	return true;
}

bool isUpperCase(char c) {
	if(c >= 'A' && c <= 'Z')
		return true;
	return false;
}

// ham chuyen doi chuoi sang so nguyen
int stringToNumber(string str) {
	int Sum = 0;
	int mu = str.length() - 1;
	for (int i = 0; i < str.length(); i++)
		Sum += ((str[i] - 48) * pow(10, mu-- * 1.0));
	return Sum;
}

int NhapSoNguyen() {
	string str;
	char c;
	
isEmptyString:
	c = getch(); // nhap ki tu dau tien
	// vòng lap vo tan cho den khi bam ENTER
	while ((int)c != ENTER) {
		if (int(c) == BACKSPACE) {
			// neu do dai chuoi bang ko thi khong xoa tiep
			if (str.length() != 0) {
				// xoa ki tu cuoi trong chuoi string
				str.erase(str.begin() + (str.length() - 1));
				
				// khi bam BACKSPACE thi se ghi de tung ki tu cua chuoi hien tai
				cout << "\b \b"; 
			}	
		}
		// neu la so thi cout ra va day vo chuoi
		if(isNumberChar(c)) {
			cout << c;
			str.push_back(c);
		} else {
			// neu khong phai so thi khong cout ra nhung van day vo chuoi roi xoa di
			str.push_back(c);
			str.erase(str.begin() + str.length() - 1);
		}
		// neu bang ESC return -1
		if(int(c) == ESC) 
			return -1;
		c = getch();
	}
	if(str == "")
	{
		Notify("   KHONG DUOC BO TRONG!   ", 75, 43, 79);
		goto isEmptyString;
	}
	cout << endl;
	return stringToNumber(str);
}

// ham nhap diem so thuc
float NhapDiemThuc() {
	string str;
	char c;
	
isEmptyString:
	c = getch(); // nhap ki tu dau tien
	// vòng lap vo tan cho den khi bam ENTER
	while ((int)c != ENTER) {
		if (int(c) == BACKSPACE) {
			// neu do dai chuoi bang ko thi khong xoa tiep
			if (str.length() != 0) {
				// xoa ki tu cuoi trong chuoi string
				str.erase(str.begin() + (str.length() - 1));
				
				// khi bam BACKSPACE thi se ghi de tung ki tu cua chuoi hien tai
				cout << "\b \b"; 
			}	
		}
		// neu la so thi cout ra va day vo chuoi
		if(isNumberChar(c) || c == '.') {
			cout << c;
			str.push_back(c);
		} else {
			// neu khong phai so thi khong cout ra nhung van day vo chuoi roi xoa di
			str.push_back(c);
			str.erase(str.begin() + str.length() - 1);
		}
		if(int(c) == ESC) 
			return -1;
		c = getch();
	}
	if(str == "")
	{
		Notify("   KHONG DUOC BO TRONG!   ", 75, 43, 79);
		goto isEmptyString;
	}
	cout << endl;
	return atof(str.c_str());
}

string ChuanHoaMSSV(string &mssv) {
	// N 18 D C C    N  -> N18DCCN
	// xoa khoang trang dau
	while(mssv[0] == ' ') {
		mssv.erase(mssv.begin() + 0);
	}
	// xoa khoang trang cuoi
	while(mssv[mssv.length() - 1] == ' ') {
		mssv.erase(mssv.begin() + mssv.length() - 1);
	}
	for(int i = 0; i < mssv.length(); i++) {
		if(mssv[i] == ' ') {
			mssv.erase(mssv.begin() + i);
			i--;
		}
	}
	return mssv;
}

string XoaKhoangTrangThua(string &str) {
	// xoa khoang trang dau
	while(str[0] == ' ') {
		str.erase(str.begin() + 0);
	}
	// xoa khoang trang cuoi
	while(str[str.length() - 1] == ' ') {
		str.erase(str.begin() + str.length() - 1);
	}
	for(int i = 0; i < str.length(); i++) {
		if(str[i] == ' ' && str[i + 1] == ' ') {
			str.erase(str.begin() + i);
			i--;
		}
	}
	return str;
}

// flag == 1 nhap chuoi so
// flag == 2 chi cho nhap chu va co nhan khoang trang
// flag == 3 nhan ca chu va chuoi so khong nhan ki tu khac
// flag == 4 nhap ma lop 
// flag == 5 chi nhan chu
string EnterData(int flag) {
	string str;
	char c;
	
isEmptyString:
	c = getch(); // nhap ki tu dau tien
	// vòng lap vo tan cho den khi bam ENTER
	while ((int)c != ENTER) {
		if (int(c) == BACKSPACE) {
			// neu do dai chuoi bang ko thi khong xoa tiep
			if (str.length() != 0) {
				// xoa ki tu cuoi trong chuoi string
				str.erase(str.begin() + (str.length() - 1));
				
				// khi bam BACKSPACE thi se ghi de tung ki tu cua chuoi hien tai
				cout << "\b \b"; 
			}	
		}
		// nhap chuoi so (sdt)
		if(flag == 1) 
		{
			// neu la so thi cout ra va day vo chuoi
			if(isNumberChar(c)) {
				cout << c;
				str.push_back(c);
			}
			c = getch();
		}
		// chi nhan chu va khoang trang
		else if(flag == 2)
		{
			if(int(c) == -32) 
			{
				c = getch();
				if(int(c) == UP || int(c) == DOWN || int(c) == RIGHT || int(c) == LEFT)  {
					// vi UP, DOWN, LEFT, RIGHT van la chu nen loai bo
					c = getch();
					continue;
				}
			}
			if(isUpperCase(c) || c == SPACE) {
				cout << c;
				str.push_back(c);
			} else if (c >= 'a' && c <= 'z') {
				c = c - 32;
				cout << c;
				str.push_back(c);
			}
			c = getch();
		}
		// nhan ki tu vua chu vua so
		else if(flag == 3) 
		{
			if(int(c) == -32) 
			{
				c = getch();
				if(int(c) == UP || int(c) == DOWN || int(c) == RIGHT || int(c) == LEFT)  {
					// vi UP, DOWN, LEFT, RIGHT van la chu nen loai bo
					c = getch();
					continue;
				}
			}
			if(isUpperCase(c) || isNumberChar(c)) {
				cout << c;
				str.push_back(c);
			} else if (c >= 'a' && c <= 'z') {
				c = c - 32;
				cout << c;
				str.push_back(c);
			}
			c = getch();
		}
		// nhap ma lop
		else if(flag == 4) 
		{
			if(int(c) == -32) 
			{
				c = getch();
				if(int(c) == UP || int(c) == DOWN || int(c) == RIGHT || int(c) == LEFT)  {
					// vi UP, DOWN, LEFT, RIGHT van la chu nen loai bo
					c = getch();
					continue;
				}
			}
			if(isUpperCase(c) || isNumberChar(c) || c == '-') {
				cout << c;
				str.push_back(c);
			} else if (c >= 'a' && c <= 'z') {
				c = c - 32;
				cout << c;
				str.push_back(c);
			}
			c = getch();
		}
		// chi nhan chu 
		else if(flag == 5) {
			if(int(c) == -32) 
			{
				c = getch();
				if(int(c) == UP || int(c) == DOWN || int(c) == RIGHT || int(c) == LEFT)  {
					// vi UP, DOWN, LEFT, RIGHT van la chu nen loai bo
					c = getch();
					continue;
				}
			}
			if(isUpperCase(c)) {
				cout << c;
				str.push_back(c);
			} else if (c >= 'a' && c <= 'z') {
				c = c - 32;
				cout << c;
				str.push_back(c);
			}
			c = getch();
		}
		// nhap ma so sinh vien tach flag 6 voi flag 3 vi dieu kien dung khi nhap ma so sinh vien
		else if(flag == 6) 
		{
			if(int(c) == -32) 
			{
				c = getch();
				if(int(c) == UP || int(c) == DOWN || int(c) == RIGHT || int(c) == LEFT)  {
					// vi UP, DOWN, LEFT, RIGHT van la chu nen loai bo
					c = getch();
					continue;
				}
			}
			if(isUpperCase(c) || c == SPACE || isNumberChar(c)) {
				cout << c;
				str.push_back(c);
			} else if (c >= 'a' && c <= 'z') {
				c = c - 32;
				cout << c;
				str.push_back(c);
			}
			c = getch();
		}
		if(int(c) == ESC) {
			return "-1";
		}
	}
	// vi flag == 6 co the nhan khoang trang de ket thuc viec nhap sinh vien nen neu ko tach ra se bi vuong cho khong duoc bo trong
	if(flag == 6)
	{
		cout << endl;
		return str;
	}
	else // neu bo trong
	{
		if(str == "")
		{
			Notify("   KHONG DUOC BO TRONG!   ", 75, 43, 79);
			goto isEmptyString;
		}
	}
	cout << endl;
	return str;
}
//====================================================================================

//================================ QUAN LI LOP TIN CHI ===============================

int SearchMLTC(DSLopTC DSLTC, int maLopTC) {
	for(int i = 0; i < DSLTC.n; i++)
		if(DSLTC.nodeLopTC[i]->maLopTC == maLopTC)
			return i;
	return -1;
}

bool isFullLTC(DSLopTC DSLTC) {
	return (DSLTC.n == MAXLTC ? true : false);
}

// ham khoi tao lop tin chi
void InitializeLTC(DSLopTC &DSLTC) {
	DSLTC.n = 0;
}

bool isEmptyLTC(DSLopTC DSLTC) {
	return DSLTC.n == 0 ? true : false;
}

int InsertLTC(DSLopTC &DSLTC, LopTC lopTC, int index) {
	// kiem tra xem da full hay chua
	if(isFullLTC(DSLTC)) 
		return 0;
	else {
		// Insert Last
		DSLTC.nodeLopTC[index] = new LopTC;
		*DSLTC.nodeLopTC[index] = lopTC;
		DSLTC.n++;
		return 1;
	}
}

// ghi file danh sach lop tin chi
void WriteFileDSLTC(DSLopTC DSLTC) 
{
	ofstream outFile;
	outFile.open("DSLTC.txt", ios::out);
	for(int i = 0; i < DSLTC.n; i++) {
		outFile << DSLTC.nodeLopTC[i]->maLopTC << endl;
		outFile << DSLTC.nodeLopTC[i]->maMH << endl;
		outFile << DSLTC.nodeLopTC[i]->nienKhoa << endl;
		outFile << DSLTC.nodeLopTC[i]->hocKy << endl;
		outFile << DSLTC.nodeLopTC[i]->nhom << endl;
		outFile << DSLTC.nodeLopTC[i]->nSvMax << endl;
		outFile << DSLTC.nodeLopTC[i]->nSvMin << endl;
		// if nay dung de loai bo dong khoang trang cuoi file
		if(i == DSLTC.n - 1)
			outFile << DSLTC.nodeLopTC[i]->huyLop;
		else outFile << DSLTC.nodeLopTC[i]->huyLop << endl;
	}
	outFile.close();
}

// tim ma mon hoc
MH_TREE SearchMaMH(MH_TREE &DSMH, string maMH) {
	if(DSMH != NULL) {
		if(DSMH->data.maMH == maMH)
			return DSMH;
		
		else if(DSMH->data.maMH > maMH)
			return SearchMaMH(DSMH->pLeft, maMH);
			
		else
			return SearchMaMH(DSMH->pRight, maMH);
			
	} else return NULL;
}

// kiem tra xem co trung nien khoa, hoc ki, nhom khong
bool trungTTLTC(DSLopTC DSLTC, string maMH, int nienKhoa, int hocKy, int nhom) {
	for(int i = 0; i < DSLTC.n; i++)
		if(DSLTC.nodeLopTC[i]->maMH == maMH && DSLTC.nodeLopTC[i]->nienKhoa == nienKhoa && DSLTC.nodeLopTC[i]->hocKy == hocKy && DSLTC.nodeLopTC[i]->nhom == nhom)
			return true;
	return false;
}

// return -1 thoat
int NhapLTC(MH_TREE DSMH, DSLopTC DSLTC, LopTC &lopTC) {
	fflush(stdin);
	if(DSLTC.n == 0) {
		lopTC.maLopTC = DSLTC.n + 1;
	} else { // so luong lop tin chi lon hon 0 thi cap ma TC bang thang cuoi cong 1
		lopTC.maLopTC = DSLTC.nodeLopTC[DSLTC.n - 1]->maLopTC + 1;
	}
	
	KhungThemLTC(lopTC.maLopTC);
	
	MH_TREE infoMH;
	do {
		gotoxy(89, 15); lopTC.maMH = EnterData(3);
		if(lopTC.maMH == "-1") {
			return -1;
		}
		// kiem tra xem ma mon hoc co nam trong danh sach mon hoc hay khong
		infoMH = SearchMaMH(DSMH, lopTC.maMH);
		if(!infoMH) {
			Notify("MA MON HOC KHONG TON TAI!", 75, 43, 79);
			gotoxy(89, 15); cout << "          ";
		}
	} while(!infoMH);
	
	bool checkTrungTT;
	do {
		gotoxy(89, 16); lopTC.nienKhoa = NhapSoNguyen();
		if(lopTC.nienKhoa == -1) { 
			return -1;
		}
		gotoxy(89, 17); lopTC.nhom = NhapSoNguyen();
		if(lopTC.nhom == -1) {
			return -1;
		}
		gotoxy(89, 18); lopTC.hocKy = NhapSoNguyen();
		if(lopTC.hocKy == -1) { 
			return -1;
		}
		
		checkTrungTT = trungTTLTC(DSLTC, lopTC.maMH, lopTC.nienKhoa, lopTC.hocKy, lopTC.nhom);
		if(checkTrungTT) {
			Notify("NIEN KHOA, HOC KY, NHOM KHONG DUOC GIONG HOAN TOAN GIONG VOI NIEN KHOA, HOC KY, NHOM CUA LOP TIN CHI DA CO", 65, 43, 79);
			gotoxy(89, 16); cout << "       ";
			gotoxy(89, 17); cout << "       ";
			gotoxy(89, 18); cout << "       ";
		}
	} while(checkTrungTT);
	
	// kiem tra xem so sinh vien max co lon hon so sinh vien min khong
	do { 
		gotoxy(89, 19); lopTC.nSvMax = NhapSoNguyen(); 
		if(lopTC.nSvMax == -1)
			return -1;
		gotoxy(89, 20); lopTC.nSvMin = NhapSoNguyen();
		if(lopTC.nSvMin == -1)
			return -1;
		if(lopTC.nSvMax < lopTC.nSvMin) {
			Notify("SO SINH VIEN MAX PHAI LON HON SO SINH VIEN MIN!", 75, 43, 79);
			gotoxy(89, 19); cout << "    ";
			gotoxy(89, 20); cout << "    ";
		}
	} while(lopTC.nSvMax < lopTC.nSvMin);
	
	// vua nhap chua co sinh vien dang ki thi huy lop bang true
	lopTC.huyLop = true;
	// nhap thanh cong khong bam ESC
	return 1;
}

// sap xep lop tin chi theo ma lop tin chi tang dan
void SapXepLTC(DSLopTC &DSLTC) {
	for(int i = 0; i < DSLTC.n - 1; i++) {
		for(int j = i + 1; j < DSLTC.n; j++) {
			if(DSLTC.nodeLopTC[i]->maLopTC > DSLTC.nodeLopTC[j]->maLopTC) {
				LopTC *lopTemp = DSLTC.nodeLopTC[i];
				DSLTC.nodeLopTC[i] = DSLTC.nodeLopTC[j];
				DSLTC.nodeLopTC[j] = lopTemp;
			}
		}
	}
}

void XuatLTC(DSLopTC DSLTC) {
	SapXepLTC(DSLTC);
	int key;
	int row = 0; int trang = 0; int tongTrang = 0;
	while(1) {
		if(DSLTC.n == 0) {
			Notify("DANH SACH LOP TIN CHI RONG!", 77, 43, 79);
		}
		else {
			if(DSLTC.n < 15) {
				trang = 0;
				tongTrang = 1;
			} else {
				tongTrang = (DSLTC.n - 1) / 15 + 1;
			}
		}
		int stt = 1; row = 0;
		XoaKhungXuatLTC(); KhungXuatLTC();
		for(int i = trang * 15; i < 15 + trang * 15 && i < DSLTC.n; i++) 
		{
			stt = i + 1;
			gotoxy(55, 12 + row); cout << stt; 
			gotoxy(64, 12 + row); cout << DSLTC.nodeLopTC[i]->maLopTC;
			gotoxy(75, 12 + row); cout << DSLTC.nodeLopTC[i]->maMH;
			gotoxy(93, 12 + row); cout << DSLTC.nodeLopTC[i]->nienKhoa;
			gotoxy(109, 12 + row); cout << DSLTC.nodeLopTC[i]->nhom;
			gotoxy(119, 12 + row); cout << DSLTC.nodeLopTC[i]->hocKy;
			gotoxy(131, 12 + row); cout << DSLTC.nodeLopTC[i]->nSvMax;
			gotoxy(142, 12 + row); cout << DSLTC.nodeLopTC[i]->nSvMin;
			row++;
		} 
		HienThiTrang(trang + 1, tongTrang, 141, 30);
		key = GetKey();
		if((key == RIGHT || key == DOWN) && trang < tongTrang - 1) 
			trang++;
		if((key == LEFT || key == UP) && trang > 0)
			trang--;
		if(key == ESC) {
			system("cls");
			return;
		}
	}
}

// ham them lop tin chi
void ThemLopTC(MH_TREE DSMH, DSLopTC &DSLTC) {
	LopTC lop;
	if(isFullLTC(DSLTC)) 
		Notify("DANH SACH LOP TIN CHI DAY!", 75, 43, 79);
	else {
		int checkEnter = NhapLTC(DSMH, DSLTC, lop);
		if(checkEnter == -1) {
			Notify("KET THUC VIEC NHAP!", 75, 43, 79);
			return;
		} else {
			InsertLTC(DSLTC, lop, DSLTC.n);
			WriteFileDSLTC(DSLTC);
			Notify("THEM THANH CONG!", 85, 43, 47);			
		}
	}
	system("cls");
}

// ham huy lop neu khong co sinh vien dang ki thi cho huy lop == true va nguoc lai
void CapNhatHuyLop(DSLopTC &DSLTC, int vtLTC) {
	if (DSLTC.nodeLopTC[vtLTC]->DSDK == NULL) 
		DSLTC.nodeLopTC[vtLTC]->huyLop = true;
	else DSLTC.nodeLopTC[vtLTC]->huyLop = false;
}

// ham xoa 1 node lop tin chi
void DeleteNodeLTC(DSLopTC &DSLTC, int index) {
	if(index < 0 || index > DSLTC.n || isEmptyLTC(DSLTC)) 
		return;
	else {
		delete DSLTC.nodeLopTC[index];
		for (int temp = index + 1; temp < DSLTC.n; temp++)
			DSLTC.nodeLopTC[temp - 1] = DSLTC.nodeLopTC[temp];
		DSLTC.n--;
		//tranh tinh trang con tro bi treo
		DSLTC.nodeLopTC[DSLTC.n] = NULL;
	}
	return;
}

// ham xoa mot lop tin chi 
void DeleteLopTC(DSLopTC &DSLTC) {
	int MaLopTCCanXoa; int vt;
	int key;
	do {
		gotoxy(2, 10); cout << "NHAP MA LOP TIN CHI CAN XOA: ";
		MaLopTCCanXoa = NhapSoNguyen();
		if(MaLopTCCanXoa == -1) {
			Notify("KET THUC VIEC XOA!", 75, 43, 79);
			return;
		}
		vt = SearchMLTC(DSLTC, MaLopTCCanXoa);
	
		if(vt < 0) {
			gotoxy(31, 10); cout << "             ";
			Notify("MA LOP TIN CHI KHONG TON TAI !", 75, 43, 79);	
		}
		else {
			// cap nhat lai bien huy lop xem co sinh vien dang ki hay chua
			CapNhatHuyLop(DSLTC, vt);
			
			// kiem tra xem co duoc huy lop hay khong 
			// huyLop == true chua co sinh vien dang ki thi duoc huy 
			if(DSLTC.nodeLopTC[vt]->huyLop) {
				DeleteNodeLTC(DSLTC, vt);
				WriteFileDSLTC(DSLTC);
				Notify("XOA LOP TIN CHI THANH CONG!", 75, 43, 47);
			}
			// huyLop == false tuc la da co sinh vien dang ki lop tin chi nen khong duoc xoa
			else
				Notify("LOP TIN CHI DA CO SINH VIEN DANG KI!", 75, 43, 79);
		}
	} while(vt < 0);
}

// ham hieu chinh lop tin chi
void UpdateLopTC(MH_TREE &DSMH, DSLopTC &DSLTC) {
	MH_TREE p;
	TextColor(7);
	int key;
	
	while(1) {
		gotoxy(2, 10); cout << "NHAP MA LOP TIN CHI MUON HIEU CHINH: ";
		
		int maLopTC = NhapSoNguyen();
		if(maLopTC == -1) {
			Notify("KET THUC VIEC HIEU CHINH", 75, 43, 79);
			return; 
		}
		int vt = SearchMLTC(DSLTC, maLopTC);
		
		if(vt < 0) {
			gotoxy(39, 10); cout << "                        ";
			Notify("MA LOP TIN CHI KHONG TON TAI!", 75, 43, 79);
		}
		else {
			KhungCapNhatLTC(DSLTC.nodeLopTC[vt]->maLopTC);
			rewind(stdin);
			do {
				gotoxy(89, 15); DSLTC.nodeLopTC[vt]->maMH = EnterData(3);
				if(DSLTC.nodeLopTC[vt]->maMH == "-1") {
					Notify("KET THUC VIEC HIEU CHINH", 75, 43, 79);
					return; 
				}
				
				p = SearchMaMH(DSMH, DSLTC.nodeLopTC[vt]->maMH);
				
				if(!p) {
					Notify("MA MON HOC KHONG TON TAI!", 75, 43, 79);
					gotoxy(89, 15); cout << "          ";
				}
			} while(!p);
			
			LopTC lop;
			
			bool checkTrungTT;
			
			do {
				gotoxy(89, 16); lop.nienKhoa = NhapSoNguyen();
				if(lop.nienKhoa == -1) {
					Notify("KET THUC VIEC HIEU CHINH", 75, 43, 79);
					return;
				}
				gotoxy(89, 17); lop.nhom = NhapSoNguyen();
				if(lop.nhom == -1) {
					Notify("KET THUC VIEC HIEU CHINH", 75, 43, 79);
					return;
				}
				gotoxy(89, 18); lop.hocKy = NhapSoNguyen();
				if(lop.hocKy == -1) {
					Notify("KET THUC VIEC HIEU CHINH", 75, 43, 79);
					return;
				}
				
				checkTrungTT = trungTTLTC(DSLTC, DSLTC.nodeLopTC[vt]->maMH, lop.nienKhoa, lop.hocKy, lop.nhom);
				
				if(checkTrungTT) {
					Notify("NIEN KHOA, HOC KY, NHOM KHONG DUOC GIONG VOI NIEN KHOA, HOC KY, NHOM CUA LOP TIN CHI DA CO", 60, 43, 79);
					gotoxy(89, 16); cout << "          ";
					gotoxy(89, 17); cout << "          ";
					gotoxy(89, 18); cout << "          ";
				}
			} while(checkTrungTT);
			
			// gan lai thong tin nien khoa, hoc ky, nhom cua lop in chi
			DSLTC.nodeLopTC[vt]->nienKhoa = lop.nienKhoa;
			DSLTC.nodeLopTC[vt]->hocKy = lop.hocKy;
			DSLTC.nodeLopTC[vt]->nhom = lop.nhom;
			
			// kiem tra xem so sinh vien max co lon hon so sinh vien min khong
			do {
				gotoxy(89, 19); DSLTC.nodeLopTC[vt]->nSvMax = NhapSoNguyen();
				if(DSLTC.nodeLopTC[vt]->nSvMax == -1) {
					Notify("KET THUC VIEC HIEU CHINH", 75, 43, 79);
					return;
				}
				gotoxy(89, 20); DSLTC.nodeLopTC[vt]->nSvMin = NhapSoNguyen();
				if(DSLTC.nodeLopTC[vt]->nSvMin == -1) {
					Notify("KET THUC VIEC HIEU CHINH", 75, 43, 79);
					return;
				}
				
				if(DSLTC.nodeLopTC[vt]->nSvMax < DSLTC.nodeLopTC[vt]->nSvMin) {
					Notify("SO SINH VIEN MAX PHAI LON HON SO SINH VIEN MIN!", 75, 43, 79);
					gotoxy(89, 19); cout << "        ";
					gotoxy(89, 20); cout << "        ";
				}
			} while(DSLTC.nodeLopTC[vt]->nSvMax < DSLTC.nodeLopTC[vt]->nSvMin);
			
			WriteFileDSLTC(DSLTC);
			Notify("HIEU CHINH MA LOP TIN CHI THANH CONG!", 75, 43, 47);
			return;
		}
	}
	system("cls");
}
//============================================================================

//======================== QUAN LY SINH VIEN ===================================

int SearchMaLop(ListLop ds, string maLop, int n) {
	for(int i = 0; i < n; i++)
		if(ds.dsLop[i].maLop == maLop)
			return i;
	return -1;
}

// ghi file danh sach lop
void WriteFileDSL(ListLop DSL) {
	int n = 0;
	ofstream outFile;
	outFile.open("DSL.txt", ios::out);
	while(n < DSL.n) {
		outFile << DSL.dsLop[n].maLop << endl;
		outFile	<< DSL.dsLop[n].tenLop << endl;
		outFile << DSL.dsLop[n].nienKhoa << endl;
		n++;
	}
	outFile.close();
}

// ghi file danh sach sinh vien
void WriteFileDSSV(ListLop DSL) {
	ofstream outFile;
	outFile.open("DSSV.txt", ios::out);
	for(int i = 0; i < DSL.n; i++) {
		// neu danh sach sinh vien cua lop do rong thi khong can ghi vao file
		if(DSL.dsLop[i].DSSV != NULL) {
			outFile << DSL.dsLop[i].maLop << endl;
			for(SVPTR sv = DSL.dsLop[i].DSSV;  sv != NULL; sv = sv->next) {
				outFile << sv->data.mssv << endl;
				outFile << sv->data.ho << endl;
				outFile << sv->data.ten << endl;
				outFile << sv->data.phai << endl;
				outFile << sv->data.sdt << endl;
			}
		}
	}
	outFile.close();
}

// ham kiem tra vi tri theo ma lop neu khong hop le se nhap den khi tra ve vi tri hop le
int CheckViTriLop(ListLop DSL) {
	string maLop; int vt;
	do {
		TextColor(7);
		gotoxy(2, 12); cout << "NHAP MA LOP: ";
		maLop = EnterData(4);
		if(maLop == "-1") { // bam ESC
			return -1;
		}
		vt = SearchMaLop(DSL, maLop, DSL.n);
		if(vt < 0) {
			gotoxy(15, 12); cout << "                   ";
			Notify("MA LOP KHONG TON TAI!", 75, 43, 79);
		}
	} while(vt < 0);
	return vt;
}

void XuatDSL(ListLop DSL) {
	int key;
	int trang = 0; int tongTrang = 0; int row = 0;
	while(1) {
		if(DSL.n == 0) {
			Notify("DANH SACH LOP RONG!", 80, 43, 79);
		} else {
			if(DSL.n < 15) {
				trang = 0;
				tongTrang = 1;
			}
			// danh sach lop co nhieu hon 15 lop 
			else {
				tongTrang = (DSL.n - 1) / 15 + 1;
			}
		}
		XoaKhungDSL(); KhungXuatDSLOP();
		int stt = 1; row = 0;
		for(int i = trang * 15; i < 15 + trang * 15 && i < DSL.n; i++) {
			stt = i + 1;
			gotoxy(55, 12 + row); cout << stt;
			gotoxy(65, 12 + row); cout << DSL.dsLop[i].maLop;
			gotoxy(94, 12 + row); cout << DSL.dsLop[i].tenLop;
			gotoxy(137, 12 + row); cout << DSL.dsLop[i].nienKhoa;
			row++;
		}
		HienThiTrang(trang + 1, tongTrang, 143, 30);
		key = GetKey();
		if((key == RIGHT || key == DOWN) && trang < tongTrang - 1) 
			trang++;
		if((key == LEFT || key == UP) && trang > 0)
			trang--;
		if(key == ESC) {
			system("cls");
			return;
		}
	}
}

void InsertSVLast (SVPTR &DSSV, SinhVien sv) {
	SVPTR p;
	p = new NodeSV;
	p->data = sv;
	p->next = NULL;
	if(DSSV == NULL)
		DSSV = p;
	else {
		SVPTR q;
		for(q = DSSV; q->next != NULL; q = q->next);
		q->next = p;
	}
}

bool isExistMSSV(ListLop DSL, string mssv) {
	for(int i = 0; i < DSL.n; i++)
		for(SVPTR p = DSL.dsLop[i].DSSV; p != NULL; p = p->next)
			if(p->data.mssv == mssv)
				return true;
	return false;
}

// them bien vi tri de tu dong nhap ma lop cho moi sinh vien
int NhapSV(SinhVien &sv, ListLop DSL, int ViTri, int &row, int stt) {
	bool checkTrung;
	string mssv;
	
	KhungNhapSV();
	
	while(1) {
		gotoxy(55, row); cout << stt;
		do {
			gotoxy(65, row); mssv = EnterData(6);
			if(mssv == "-1")
				return 0; // dung viec nhap lai
			ChuanHoaMSSV(mssv);
			if(mssv == "") return 0;
			checkTrung = isExistMSSV(DSL, mssv);
			if(checkTrung) {
				Notify("MA SO SINH VIEN DA TON TAI!", 75, 43, 79);
				gotoxy(65, row); cout << "                 ";
			}
		} while(checkTrung);
		sv.mssv = mssv;
		
		do {
			gotoxy(90, row); sv.ho = EnterData(2);
			XoaKhoangTrangThua(sv.ho);
			if(sv.ho == "") {
				Notify("KHONG DUOC BO TRONG!", 75, 43, 79);
			}
		} while(sv.ho == "");
		
		
		if(sv.ho == "-1")
			return 0;
		gotoxy(121, row); sv.ten = EnterData(5);
		if(sv.ten == "-1")
			return 0;
		
		do {
			gotoxy(138, row); sv.phai = EnterData(5); 
			if(sv.phai != "NAM" && sv.phai != "NU") {
				Notify("GIOI TINH PHAI LA NAM HOAC NU!", 75, 43, 79);
				gotoxy(138, row); cout << "      ";
			}
		}
		while(sv.phai != "NAM" && sv.phai != "NU");
		gotoxy(149, row); sv.sdt = EnterData(1);
		sv.maLop = DSL.dsLop[ViTri].maLop;
		return 1;
	}
}

void NhapDSSV(ListLop &DSL) {
	int ViTri = CheckViTriLop(DSL);
	if(ViTri == -1) {
		Notify("KET THUC VIEC NHAP!", 75, 43, 79);
		return;
	}
	int row = 11;
	TextColor(116);
	gotoxy(72, 31); cout << "                                                                           ";
	gotoxy(72, 32); cout << "   QUA TRINH NHAP SINH VIEN MOI SE KET THUC KHI BAN NHAP VAO CHUOI RONG!   ";
	gotoxy(72, 33); cout << "                                                                           ";
	TextColor(7);
	
	int stt = 0;
	while(1) {
		SinhVien svTemp;

		if(NhapSV(svTemp, DSL, ViTri, ++row, ++stt) == 0) {
			if(row == 12) // van chua nhap 1 sinh vien nao
				Notify("BAN DA KET THUC VIEC NHAP! LUU FILE KHONG THANH CONG", 70, 43, 79);
			// row > 12
			else 
			{ 
				WriteFileDSSV(DSL);
				Notify("THEM DANH SACH SINH VIEN THANH CONG!", 75, 43, 47);
				Notify("BAN DA KET THUC VIEC NHAP!", 75, 43, 79);
			}				
			return;
		}
		InsertSVLast(DSL.dsLop[ViTri].DSSV, svTemp);
		Notify("THEM SINH VIEN THANH CONG!", 75, 43, 47);	
	} 
}

int countDSSV(SVPTR DSSV) {
	int count = 0;
	for(SVPTR p = DSSV; p != NULL; p = p->next) {
		count += 1;
	}
	return count;
}

void XuatDSSV(SVPTR DSSV) {
	int key;
	int row = 0;
	int trang = 0; int tongTrang = 0;
	int soluongSV = countDSSV(DSSV);
	
	SinhVien* sv = new SinhVien[soluongSV];
	int nSV = 0;
	for(SVPTR p = DSSV; p != NULL; p = p->next) {
		sv[nSV] = p->data;
		nSV++;
	}
	
	while(1) {
		if(soluongSV < 15) {
			trang = 0; 
			tongTrang = 1;
		} else {
			tongTrang = (soluongSV - 1) / 15 + 1;
		}
		XoaKhungDSSV(); KhungXuatDSSV();
		int stt = 0; row = 0;
		for(int i = trang * 15; i < 15 + trang * 15 && i < soluongSV; i++) {
			row++; stt = i + 1;
			gotoxy(55, 11 + row); cout << stt; 
			gotoxy(66, 11 + row); cout << sv[i].mssv;
			gotoxy(91, 11 + row); cout << sv[i].ho;
			gotoxy(121, 11 + row); cout << sv[i].ten;
			gotoxy(139, 11 + row); cout << sv[i].phai;
			gotoxy(149, 11 + row); cout << sv[i].sdt;
		}
		HienThiTrang(trang + 1, tongTrang, 158, 29);
		key = GetKey();
		if((key == RIGHT || key == DOWN) && trang < tongTrang - 1) 
			trang++;
		if((key == LEFT || key == UP) && trang > 0)
			trang--;
		if(key == ESC) {
			delete[] sv;
			return;	
		}
	}
}

// xoa sinh vien theo mssv
int DeleteInfo(SVPTR &DSSV, string mssv) {
	SVPTR p;
	if(DSSV == NULL) 
		return 0;
	if(DSSV->data.mssv == mssv) {
		p = DSSV;
		DSSV = p->next;
		delete p;
		return 1;
	}

	for(p = DSSV; p->next != NULL && p->next->data.mssv != mssv; p = p->next);
	if(p->next != NULL) {
		SVPTR q;
		q = p->next;
		p->next = q->next;
		delete q;
		return 1;
	}
}

// ham sap xep ho ten tang dan
void SapXepHoTenTangDan(SVPTR &DSSV) {
	SVPTR p, q;
	SinhVien svTemp;
	for(p = DSSV; p->next != NULL; p = p->next) {
		for(q = p->next; q != NULL; q = q->next) {
			// neu ho lon hon thi doi cho
			if(p->data.ten > q->data.ten) {
				svTemp = p->data;
				p->data = q->data;
				q->data = svTemp;
			// neu ho trung nhau thi sap xep theo ten
			} else if(p->data.ten == q->data.ten) {
				if(p->data.ho > q->data.ho) {
					svTemp = p->data;
					p->data = q->data;
					q->data = svTemp;
				}
			}
		}
	}
}

void XuatSVTangDanTheoHoTen(ListLop DSL) {
	int key;
	int ViTri = CheckViTriLop(DSL);
	if(ViTri == -1) {
		Notify("KET THUC VIEC NHAP!", 75, 43, 79);
		return;
	} else {
			if(DSL.dsLop[ViTri].DSSV == NULL) {
			Notify("DANH SACH SINH VIEN TRONG LOP RONG!", 75, 43, 79);
		} else {
			SapXepHoTenTangDan(DSL.dsLop[ViTri].DSSV);
			gotoxy(52, 2); cout << "TEN LOP: " << DSL.dsLop[ViTri].tenLop;
			gotoxy(52, 3); cout << "MA LOP : " << DSL.dsLop[ViTri].maLop;
			XuatDSSV(DSL.dsLop[ViTri].DSSV);
		}
	}
}

// ham tim va tra ve sinh vien nam trong danh sach
SVPTR SearchMSSV(SVPTR DSSV, string mssv) {
	for(SVPTR p = DSSV; p != NULL; p = p->next)
		if(p->data.mssv == mssv)
			return p;
	return NULL;
}

// ham kiem tra xem sinh vien co dang ki lop tin chi nao chua
bool SVDK(DSLopTC DSLTC, string mssv) {
	for(int i = 0; i < DSLTC.n; i++) {
		for(DKPTR p = DSLTC.nodeLopTC[i]->DSDK; p != NULL; p = p->next) {
			if(p->data.mssv == mssv)
				return true;
		}
	}
	return false;
}

void XoaSVLop(DSLopTC DSLTC, ListLop &DSL) {
	string mssv;
	int ViTri = CheckViTriLop(DSL);
	if(ViTri == -1) {
		Notify("KET THUC VIEC NHAP!", 75, 43, 79);
		return;
	} else {
		if(DSL.dsLop[ViTri].DSSV == NULL) {
			Notify("DANH SACH SINH VIEN TRONG LOP RONG!", 75, 43, 79);
		} else {
			rewind(stdin);
			gotoxy(2, 13); cout << "Nhap MSSV muon xoa: ";
			mssv = EnterData(3);
			if(mssv == "-1") {
				Notify("KET THUC VIEC NHAP!", 75, 43, 79);
				return;
			}
			SVPTR pSinhVien = SearchMSSV(DSL.dsLop[ViTri].DSSV, mssv);
			if(!pSinhVien)
				Notify("MA SO SINH VIEN KHONG TON TAI!", 75, 43, 79);
			else {
				// bien kiem tra xem sinh vien nay da dang ki lop tin chi nao chua
				bool isDK = SVDK(DSLTC, pSinhVien->data.mssv);
				
				if(isDK) {
					Notify("SINH VIEN DA DANG KI MON! KHONG DUOC XOA!", 75, 43, 79);
					return;
				} else {
					DeleteInfo(DSL.dsLop[ViTri].DSSV, mssv);
					WriteFileDSSV(DSL);
					Notify("XOA SINH VIEN THANH CONG!", 75, 43, 47);
				}
			}
		}
		system("cls");
	}
}

void UpdateSVLop(ListLop &DSL) {
	string mssv;
	int ViTri = CheckViTriLop(DSL);
	if(ViTri == -1) {
		Notify("KET THUC VIEC NHAP!", 75, 43, 79);
		return;
	} else {
		if(DSL.dsLop[ViTri].DSSV == NULL) {
			Notify("DANH SACH SINH VIEN TRONG LOP RONG!", 75, 43, 79);
		} else {
			rewind(stdin);
			gotoxy(2, 13); cout << "Nhap MSSV can hieu chinh: ";
			mssv = EnterData(3);
			if(mssv == "-1") {
				Notify("KET THUC VIEC NHAP!", 75, 43, 79);
				return;
			}
			SVPTR pSinhVien = SearchMSSV(DSL.dsLop[ViTri].DSSV, mssv);
			if(!pSinhVien) {
				Notify("MA SO SINH VIEN KHONG TON TAI!", 75, 43, 79);
				return;
			}
			else {
				KhungCapNhatSV(); 
				do {
					gotoxy(84, 14); pSinhVien->data.ho = EnterData(2);
					if(pSinhVien->data.ho == "-1") {
						Notify("KET THUC VIEC NHAP!", 75, 43, 79);
						return;
					}
					XoaKhoangTrangThua(pSinhVien->data.ho);
					if(pSinhVien->data.ho == "") {
						Notify("KHONG DUOC BO TRONG!", 75, 43, 79);
					}
				} while(pSinhVien->data.ho == "");
				
				gotoxy(84, 15); pSinhVien->data.ten = EnterData(5);
				if(pSinhVien->data.ten == "-1") {
					Notify("KET THUC VIEC NHAP!", 75, 43, 79);
					return;
				}
				
				gotoxy(84, 16); pSinhVien->data.mssv = EnterData(3);
				if(pSinhVien->data.mssv == "-1") {
					Notify("KET THUC VIEC NHAP!", 75, 43, 79);
					return;
				}
				
				gotoxy(84, 17); pSinhVien->data.sdt = EnterData(1);
				if(pSinhVien->data.sdt == "-1") {
					Notify("KET THUC VIEC NHAP!", 75, 43, 79);
					return;
				}
			}
			WriteFileDSSV(DSL);
			Notify("HIEU CHINH THONG TIN SINH VIEN THANH CONG!", 75, 43, 47);
		}
		system("cls");
	}
}
//====================================================================================

//============================== QUAN LI DANG KI =====================================

// ghi file danh sach dang ky
void WriteFileDSDK(DSLopTC DSLTC) {
	ofstream outFile;
	outFile.open("DSDK.txt", ios::out);
	for(int i = 0; i < DSLTC.n; i++) {
		// danh sach dang ki co sinh vien moi ghi vao file
		if(DSLTC.nodeLopTC[i]->DSDK != NULL) {
			outFile << DSLTC.nodeLopTC[i]->maLopTC << endl;
			for(DKPTR p = DSLTC.nodeLopTC[i]->DSDK; p != NULL; p = p->next) {
				outFile << p->data.mssv << endl;
				outFile << p->data.diem << endl;
			}
		}
	}
	outFile.close();
}

// dem so sinh vien da dang ki lop tin chi
int countSVDK(DSLopTC DSLTC, int vt) {
	int count = 0;
	for(DKPTR p = DSLTC.nodeLopTC[vt]->DSDK; p != NULL; p = p->next)
		count += 1;
	return count;
}

// ham them 1 node vao cuoi
void InsertNodeDK (DKPTR &DSDK, DK dk) {
	DKPTR p;
	p = new NodeDK;
	p->data = dk;
	p->next = NULL;
	
	if(DSDK == NULL)
		DSDK = p;
	else {
		DKPTR q;
		// duyet ve node cuoi
		for(q = DSDK; q->next != NULL; q = q->next);
		q->next = p;
	}
}

// chuyen danh sach dang ki cua mot lop thanh mang tuyen tinh kieu sinh vien de sap xep theo ten ho tang dan
void ConvertSVDKToArrSV(DKPTR &DSDK, ListLop DSL, SinhVien *sv, int &n) {
	for(DKPTR p = DSDK; p != NULL; p = p->next) {
		// voi moi mssv dang ki cua LTC thi se vo tung lop de kiem thong tin sinh vien do va dua vao mang sinh vien
		for(int i = 0; i < DSL.n; i++) {
			SVPTR svTemp;
			svTemp = SearchMSSV(DSL.dsLop[i].DSSV, p->data.mssv);
			if(svTemp != NULL) {
				sv[n++] = svTemp->data;
				break;
			}
		}
	}
}

// ham sap xep ho ten tang dan
void SapXepSVDK(SinhVien *sv, int n) {
	for(int i = 0; i < n - 1; i++) {
		for(int j = i + 1; j < n; j++) {
			// neu ten lon hon thi doi cho
			if(sv[i].ten > sv[j].ten) {
				SinhVien svTemp = sv[i];
				sv[i] = sv[j];
				sv[j] = svTemp;
			// neu ten trung nhau thi sap xep theo ho
			} else if(sv[i].ten == sv[j].ten) {
				if(sv[i].ho > sv[j].ho) {
					SinhVien svTemp = sv[i];
					sv[i] = sv[j];
					sv[j] = svTemp;
				}
			}
		}
	}
}

// return -1 thoat
int XuatTTSVDK(SinhVien *sv, int n) {
	int stt = 0; int key;
	int trang = 0; int tongTrang = 0;
	while(1) {
		if(n < 15) {
			trang = 0; tongTrang = 1;
		} else {
			tongTrang = (n - 1) / 15 + 1;
		}
		XoaKhungDSSV(); KhungXuatDSDKLTC();
		stt = 0; int row = 0;
		for(int i = trang * 15; i < 15 + trang * 15 && i < n; i++) {
			stt = i + 1;
			gotoxy(55, 12 + row); cout << stt;
			gotoxy(65, 12 + row); cout << sv[i].mssv;
			gotoxy(88, 12 + row); cout << sv[i].ho;
			gotoxy(120, 12 + row); cout << sv[i].ten;
			gotoxy(137, 12 + row); cout << sv[i].phai;
			gotoxy(149, 12 + row); cout << sv[i].sdt;
			row++;
		}
		HienThiTrang(trang + 1, tongTrang, 157, 29);
		key = GetKey();
		if((key == DOWN || key == RIGHT) && trang < tongTrang - 1)
			trang++;
		if((key == UP || key == LEFT) && trang > 0)
			trang--;
		if(key == ESC) {
			return -1;
		}
	}
}

// Xuat danh sach sinh vien dang ki
void XuatDSDKLopTC(DSLopTC DSLTC, ListLop DSL) 
{
	int key;
	int maLopTC; int vtLTC;
	
	do {
		gotoxy(0, 13); cout << "NHAP MA LOP TIN CHI CAN XEM DANH SACH: ";
		maLopTC = NhapSoNguyen();
		if(maLopTC == -1) {
			Notify("KET THUC VIEC NHAP!", 75, 43, 79);
			return;
		}
		vtLTC = SearchMLTC(DSLTC, maLopTC);
		if(vtLTC < 0) {
			Notify("MA LOP TIN CHI KHONG TON TAI!", 75, 43, 79);
			gotoxy(38, 13); cout << "                                       ";
		}
	} while(vtLTC < 0);
	
	// in thong tin lop tin chi
	gotoxy(52, 1); cout << "NIEN KHOA : " << DSLTC.nodeLopTC[vtLTC]->nienKhoa;
	gotoxy(52, 2); cout << "HOC KY    : " << DSLTC.nodeLopTC[vtLTC]->hocKy;
	gotoxy(52, 3); cout << "NHOM      : " << DSLTC.nodeLopTC[vtLTC]->nhom;
	gotoxy(52, 4); cout << "MA MH     : " << DSLTC.nodeLopTC[vtLTC]->maMH;
	
	while(1) {
		if(DSLTC.nodeLopTC[vtLTC]->DSDK == NULL)
			Notify("CHUA CO SINH VIEN DANG KI!", 75, 43, 79);
	
	 	int totalSVDK = countSVDK(DSLTC, vtLTC);
		SinhVien *sv = new SinhVien[totalSVDK];
		
		int n = 0;
		// chuyen danh sach dang ki thanh mot mang thong tin sinh vien
		ConvertSVDKToArrSV(DSLTC.nodeLopTC[vtLTC]->DSDK, DSL, sv, n);
		
		SapXepSVDK(sv, n);
		
		int checkESC = XuatTTSVDK(sv, n);
		if(checkESC == -1) {
			delete[] sv;
			return;			
		}
	}
}

// tim sinh vien theo tung lop
SVPTR SearchSVAllClass(ListLop DSL, string mssv) {
	// for dau chay tung lop
	for(int i = 0; i < DSL.n; i++)
		// for sau chay danh sach sinh vien cua tung lop
		for(SVPTR p = DSL.dsLop[i].DSSV; p != NULL; p = p->next)
			if(p->data.mssv == mssv) 
				return p;
	return NULL;
}

// xuat thong tin cac lop tin chi da mo
void XuatTTLopTC(MH_TREE DSMH, DSLopTC DSLTC, int nienKhoa, int hocKy) {
	KhungXuatLTCDaMo();
	int stt = 1;
	int row = 0;
	for(int i = 0; i < DSLTC.n; i++) {
		if(DSLTC.nodeLopTC[i]->nienKhoa == nienKhoa && DSLTC.nodeLopTC[i]->hocKy == hocKy) {
			
			// so sinh vien da dang ki trong lop tin chi nay
			int totalSVDK = countSVDK(DSLTC, i);
			
			// tim thong tin mon hoc de lay ra ten cua mon hoc
			MH_TREE infoMH = SearchMaMH(DSMH, DSLTC.nodeLopTC[i]->maMH);
			
			gotoxy(55, 21 + row); cout << stt++;
			gotoxy(63, 21 + row); cout << DSLTC.nodeLopTC[i]->maLopTC;
			gotoxy(71, 21 + row); cout << DSLTC.nodeLopTC[i]->maMH;
			gotoxy(89, 21 + row); cout << infoMH->data.tenMH;
			gotoxy(132, 21 + row); cout << DSLTC.nodeLopTC[i]->nienKhoa;
			gotoxy(145, 21 + row); cout << DSLTC.nodeLopTC[i]->nhom;
			gotoxy(153, 21 + row); cout << DSLTC.nodeLopTC[i]->hocKy;
			gotoxy(161, 21 + row); cout << totalSVDK;
			gotoxy(173, 21 + row); cout << DSLTC.nodeLopTC[i]->nSvMax - totalSVDK;
			row++;
		}
	}
}

// mang MTCDaMo luu tru nhung ma lop tin chi da mo
void LTCDaMo(DSLopTC DSLTC, int MTCDaMo[], int &n, int nienKhoa, int hocKy) {
	n = 0;
	for(int i = 0; i < DSLTC.n; i++)
		if(DSLTC.nodeLopTC[i]->nienKhoa == nienKhoa && DSLTC.nodeLopTC[i]->hocKy == hocKy)
			MTCDaMo[n++] = DSLTC.nodeLopTC[i]->maLopTC;
}


bool isExistMLTC(int MTCDaMo[], int n, int maLTC) {
	for(int i = 0; i < n; i++)
		if(MTCDaMo[i] == maLTC)
			return true;
	return false;
}

// kiem tra xem sinh vien da dang ki hoc mon hoc nay chua 
bool TrungMSSV_DSDK_DSMH(DSLopTC DSLTC, string mssv, string maMH) {
	// vao tung lop tin chi xem lop tin chi nao co ma mon hoc can kiem tra danh sach danh ki
	for(int i = 0; i < DSLTC.n; i++) {
		if(DSLTC.nodeLopTC[i]->maMH == maMH) {
			// xem danh sach dang ki do sinh vien da dang ki hoc chua
			for(DKPTR p = DSLTC.nodeLopTC[i]->DSDK; p != NULL; p = p->next)
				if(p->data.mssv == mssv)
					return true;
		}
	}
	return false;
}

// ham them ma so sinh vien dang ki lop tin chi vao danh sach dk cua lop tin chi do
void InserstMSSV_ToDSDK (DSLopTC &DSLTC, int maLTC, string mssv) {
	DK dk;
	
	int vt = SearchMLTC(DSLTC, maLTC);
	
	dk.mssv = mssv;
	dk.diem = 0;
	
	InsertNodeDK(DSLTC.nodeLopTC[vt]->DSDK, dk);
}

// ham dang ki hoc lop tin chi
void DKLopTC(MH_TREE DSMH, DSLopTC &DSLTC, ListLop DSL) {
	string mssv; SVPTR sv;
	
	do {
		rewind(stdin);
		gotoxy(2, 10); cout << "Nhap vao ma so sinh vien cua ban: ";
		gotoxy(37, 10); mssv = EnterData(3);
		if(mssv == "-1") {
			Notify("KET THUC VIEC NHAP!", 75, 43, 79);
			return;
		}
		
		sv = SearchSVAllClass(DSL, mssv);
		
		if(sv == NULL) {
			Notify("MA SO SINH VIEN KHONG TON TAI!", 75, 43, 79);
			gotoxy(37, 10); cout << "                   ";
		}
	} while(sv == NULL);

	// in thong tin cua sinh vien
	KhungDKLTC();
	gotoxy(73, 5); cout << "MSSV : " << sv->data.mssv;
	gotoxy(73, 6); cout << "HO   : " << sv->data.ho;
	gotoxy(73, 7); cout << "TEN  : " << sv->data.ten;
	gotoxy(73, 8); cout << "PHAI : " << sv->data.phai;

	int nienKhoa, hocKy;
	// n la so phan tu cua mang cac lop tin chi da mo trong nien khoa hoc ki do
	int nLop;
	int MTCDaMo[DSLTC.n];
	
	do {
		gotoxy(2, 12); cout << "Nhap Nien Khoa: ";
		gotoxy(18, 12); nienKhoa = NhapSoNguyen();
		if(nienKhoa == -1) {
			Notify("KET THUC VIEC NHAP!", 75, 43, 79);
			return;
		}
		gotoxy(2, 13); cout << "Nhap Hoc Ky   : ";
		gotoxy(18, 13); hocKy = NhapSoNguyen();
		if(hocKy == -1) {
			Notify("KET THUC VIEC NHAP!", 75, 43, 79);
			return;
		}
		
		// tim xem nien khoa va hoc ki user nhap vao co lop tin chi nao da mo chua
		LTCDaMo(DSLTC, MTCDaMo, nLop, nienKhoa, hocKy);
		
		if(nLop == 0) {
			Notify("KHONG CO LOP TIN CHI NAO DUOC MO TRONG THOI GIAN NAY!", 75, 43, 79);
			gotoxy(18, 12); cout << "            ";
			gotoxy(18, 13); cout << "            ";
		} 
		else
			XuatTTLopTC(DSMH, DSLTC, nienKhoa, hocKy);
	} while(nLop == 0);
	
	/* bien kiem tra xem ma lop tin chi nhap vao co nam trong danh lop tin 
	chi duoc mo trong nien khoa va hoc ki can tim chua */
	bool ExistLTC;
	int maLTC; 
	
	do {
		gotoxy(2, 17); cout << "NHAP MA LOP TIN CHI MUON DANG KI: ";
		gotoxy(37, 17); maLTC = NhapSoNguyen();
		if(maLTC == -1) {
			Notify("KET THUC VIEC NHAP!", 75, 43, 79);
			return;
		}
		ExistLTC = isExistMLTC(MTCDaMo, nLop, maLTC);
		if(!ExistLTC) {
			Notify("MA LOP TIN CHI KHONG DUNG!", 75, 43, 79);
		}
	} while(!ExistLTC);
	
	// de lay duoc ma mon hoc ma sinh vien muon dang ki
	int vt = SearchMLTC(DSLTC, maLTC);
	
	bool isExistMSSV = TrungMSSV_DSDK_DSMH(DSLTC, mssv, DSLTC.nodeLopTC[vt]->maMH);
	
	if(isExistMSSV) {
		Notify("SINH VIEN DA DANG KI, KHONG THE DANG KI DUOC NUA!", 70, 43, 79);
		return;
	}
	else {
		InserstMSSV_ToDSDK(DSLTC, maLTC, mssv);
		WriteFileDSDK(DSLTC);
		Notify("DANG KI THANH CONG!", 75, 43, 47);
	}
}

// xuat cac lop tin chi co so sinh vien dang ki be hoc so sinh vien min
void Check_SVDK_SVMIN(DSLopTC DSLTC, int &n) {
	int stt = 0;
	for(int i = 0; i < DSLTC.n; i++) {
		
		int totalSVDK = countSVDK(DSLTC, i);

		if(DSLTC.nodeLopTC[i]->nSvMin > totalSVDK)
			n += 1;
	}
}

// luu cac ma lop tin chi co SVDK be hon sinh vien min
void arrLTC_SVDK_SVMIN(DSLopTC DSLTC, int arrMLTC[], int n) {
	for(int i = 0; i < DSLTC.n; i++) {
		int totalSVDK = countSVDK(DSLTC, i);
		
		if(DSLTC.nodeLopTC[i]->nSvMin > totalSVDK)
			arrMLTC[--n] = DSLTC.nodeLopTC[i]->maLopTC;
	}
}

// ham xoa cac lop tin chi co sinh vien dang ki be hon sinh vien
void deleteLTC_SVDK_SVMIN(DSLopTC &DSLTC, int arrLTC[], int n) {
	for(int i = 0; i <= n; i++) {
		int vt = SearchMLTC(DSLTC, arrLTC[i]);
		DeleteNodeLTC(DSLTC, vt);
	}
}

int Xuat_SVDK_SVMIN(DSLopTC DSLTC, int arrLTC[], int n) {
	int key; int row = 0;
	int trang = 0; int tongTrang = 0;
	while(1) {
		if(n < 15) {
			trang = 0;
			tongTrang = 1;
		} else {
			tongTrang = (n - 1) / 15 + 1;
		}
		int stt = 1; row = 0;
		XoaKhungXuatLTC_KTDK(); KhungXuatLTC_KTDK();
		for(int i = trang * 15; i < 15 + trang * 15 && i < n; i++) {
			// vi mang arrLTC luu lai ma tin chi cua cac lop svdk < svmin nen di tim vt cua lop tin chi co ma tin chi do de lay data
			int vtLTC = SearchMLTC(DSLTC, arrLTC[i]);
			int totalSVDK = countSVDK(DSLTC, vtLTC);
			
			gotoxy(55, 16 + row); cout << stt + i; 
			gotoxy(64, 16 + row); cout << DSLTC.nodeLopTC[vtLTC]->maLopTC;
			gotoxy(77, 16 + row); cout << DSLTC.nodeLopTC[vtLTC]->maMH;
			gotoxy(98, 16 + row); cout << DSLTC.nodeLopTC[vtLTC]->nienKhoa;
			gotoxy(113, 16 + row); cout << DSLTC.nodeLopTC[vtLTC]->nhom;
			gotoxy(124, 16 + row); cout << DSLTC.nodeLopTC[vtLTC]->hocKy;
			gotoxy(134, 16 + row); cout << DSLTC.nodeLopTC[vtLTC]->nSvMax;
			gotoxy(143, 16 + row); cout << DSLTC.nodeLopTC[vtLTC]->nSvMin;
			gotoxy(154, 16 + row); cout << totalSVDK;
			row++;
		}
		HienThiTrang(trang + 1, tongTrang, 154, 34);
		key = GetKey();
		if((key == RIGHT || key == DOWN) && trang < tongTrang - 1) 
			trang++;
		if((key == LEFT || key == UP) && trang > 0)
			trang--;
		if(key == 'C' || key == 'c') 
			return -2; // return -2 de dung xem danh sach lop tin chi ko du dieu kien de tiep tuc viec xoa
		if(key == ESC)
			return -1;
	}
}

void autoDeleteLTC(DSLopTC &DSLTC) {
	char key; 
	int n = -1; // so luong lop tin chi co svdk < svMin
	Check_SVDK_SVMIN(DSLTC, n); // kiem tra xem co bao nhieu lop co so sinh vien dang ki be hon sinh vien min
	
	if(n == -1) {
		Notify("TAT CA CAC LOP DEU CO DU SINH VIEN DANG KI!", 75, 43, 79);
		return;
	} else {
		// mang nay dung de luu ma nhung lop tin
		// chi co so sinh vien dang ki be hon sinh vien min
		int arrLTC[n];
		arrLTC_SVDK_SVMIN(DSLTC, arrLTC, n);
		
		while(1) {
			int checkContinue = Xuat_SVDK_SVMIN(DSLTC, arrLTC, n);
			// bien kiem tra de dung lai viec xem danh sach khong du dieu kien de tiep tuc viec xoa
			if(checkContinue == -2) {
				goto isContinueDelete;
			} else if(checkContinue == -1) {
				Notify("KET THUC VIEC XOA", 75, 43, 79);
				return;
			}
isContinueDelete:
			gotoxy(55, 43); cout << "LUA CHON CUA BAN: " << endl;
			gotoxy(72, 43); key = GetKey(); 
			if(key == ESC) {
				Notify("KET THUC VIEC NHAP!", 75, 43, 79);
				return;
			}
			cout << key;
			
			if(key == 'y' || key == 'Y') {
				deleteLTC_SVDK_SVMIN(DSLTC, arrLTC, n);
				WriteFileDSLTC(DSLTC);
				Notify("TU DONG HUY CAC LOP KHONG DU DIEU KIEN THANH CONG!", 75, 43, 47);
				return;
			} else if(key == 'n' || key == 'N') {
				Notify("BAN DA DUNG VIEC HUY LOP!", 75, 43, 79);
				return;
			}
			else {
				Notify("KI TU KHONG HOP LE!", 75, 43, 79);
				gotoxy(72, 37); cout << "     ";
			}	
		}
	}
}

int SearchLTCByInfo(DSLopTC DSLTC, int nienKhoa, int hocKy, int nhom, string maMH) {
	for(int i = 0; i < DSLTC.n; i++)
		if(DSLTC.nodeLopTC[i]->nienKhoa == nienKhoa && DSLTC.nodeLopTC[i]->hocKy == hocKy && DSLTC.nodeLopTC[i]->nhom == nhom && DSLTC.nodeLopTC[i]->maMH == maMH)
			return i;
	return -1;
}

// ham nhap thong tin lop tin chi de tim lop tin chi do
int NhapTTLopTC(DSLopTC DSLTC, ListLop DSL) {
	int nienKhoa, hocKy, nhom;
	string maMH;
	KhungNhapTTLTC();
	
	gotoxy(89, 14); nienKhoa = NhapSoNguyen();
	if(nienKhoa == -1)
		return -2;
	
	gotoxy(89, 15); hocKy = NhapSoNguyen();
	if(hocKy == -1)
		return -2;
	
	gotoxy(89, 16); nhom = NhapSoNguyen();
	if(nhom == -1)
		return -2;
	
	gotoxy(89, 17); maMH = EnterData(3);
	if(maMH == "-1")
		return -2;
	
	int vtLTC = SearchLTCByInfo(DSLTC, nienKhoa, hocKy, nhom, maMH);
	
	XoaKhungNhapLTC();
	return vtLTC;
}

// tim info cua sinh vien da dang ki lop tin chi do
DKPTR SearchInfoSVDK(DKPTR DSDK, string mssv) {
	for(DKPTR svDK = DSDK; svDK != NULL; svDK = svDK->next)
		if(svDK->data.mssv == mssv)
			return svDK;
	return NULL;
}

// in bang diem cua cac sinh vien trong mot lop tin chi
void InBangDiemLTC(DSLopTC DSLTC, ListLop DSL, MH_TREE DSMH) {
	int vtLTC = NhapTTLopTC(DSLTC, DSL);
	if(vtLTC == -2) {
		Notify("KET THUC VIEC NHAP!", 75, 43, 79);
		return;
	} else {
		if(vtLTC == -1) {
			Notify("KHONG TON TAI LOP TIN CHI THOA DIEU KIEN!", 75, 43, 79);
			XoaKhungNhapLTC();
			return;
		}
		if(DSLTC.nodeLopTC[vtLTC]->DSDK == NULL)
			Notify("LOP TIN CHI KHONG CO SINH VIEN DANG KI!", 75, 43, 79);
		else {
			MH_TREE infoSub = SearchMaMH(DSMH, DSLTC.nodeLopTC[vtLTC]->maMH);
			
			gotoxy(60, 2); cout << "NIEN KHOA: " << DSLTC.nodeLopTC[vtLTC]->nienKhoa;
			gotoxy(60, 3); cout << "HOC KY   : " << DSLTC.nodeLopTC[vtLTC]->hocKy;
			gotoxy(60, 4); cout << "NHOM     : " << DSLTC.nodeLopTC[vtLTC]->nhom;
			
			int soluongSV = 0; 
			soluongSV = countSVDK(DSLTC, vtLTC);
			int nSV = 0;
			SVPTR sv;
			// chuyen sang mang thong tin sinh vien
			SinhVien* arrSV = new SinhVien[soluongSV + 1];
			int i = 0;
			for(DKPTR p = DSLTC.nodeLopTC[vtLTC]->DSDK; p != NULL; p = p->next) {
				for(int i = 0; i < DSL.n; i++) {
					sv = SearchMSSV(DSL.dsLop[i].DSSV, p->data.mssv);
					if(sv != NULL) {
						arrSV[nSV] = sv->data; nSV++;
						break;	
					}						
				}
			}
			
			SapXepSVDK(arrSV, nSV);
			
			int key;
			int trang = 0; int tongTrang = 0;
			int row; int stt = 0;
			while(1) {
				if(soluongSV < 15) {
					trang = 0;
					tongTrang = 1;
				} else {
					tongTrang = (soluongSV - 1) / 15 + 1;
				}
				row = 0; stt = 0;
				XoaKhungNhapDiem(); KhungNhapDiem(infoSub->data.tenMH);
				for(int i = trang * 15; i < 15 + trang * 15 && i < soluongSV; i++) {
					DKPTR infoSVDK = SearchInfoSVDK(DSLTC.nodeLopTC[vtLTC]->DSDK, arrSV[i].mssv);
					
					stt = i + 1;
					gotoxy(63, row + 14); cout << stt;
					gotoxy(71, row + 14); cout << arrSV[i].mssv;
					gotoxy(98, row + 14); cout << arrSV[i].ho;
					gotoxy(128, row + 14); cout << arrSV[i].ten;
					gotoxy(146, row + 14); cout << infoSVDK->data.diem;
					row++;
				}
				HienThiTrang(trang + 1, tongTrang, 148, 33);
				key = GetKey();
				if((key == DOWN || key == RIGHT) && trang < tongTrang - 1)
					trang++;
				if((key == UP || key == LEFT) && trang > 0)
					trang--;
				if(key == ESC) {
					return;
				}
			}	
			delete[] arrSV;
		}
	}
}

// nhap diem cho mot lop tin chi
void NhapDiem(DSLopTC DSLTC, ListLop DSL, MH_TREE DSMH) {
	int vtLTC = NhapTTLopTC(DSLTC, DSL);
	if(vtLTC == -2) {
		Notify("KET THUC VIEC NHAP!", 75, 43, 79);
		return;
	} else {
		if(vtLTC == -1) {
			Notify("KHONG TON TAI LOP TIN CHI THOA DIEU KIEN!", 75, 43, 79);
			XoaKhungNhapLTC();
			return;
		}
		if(DSLTC.nodeLopTC[vtLTC]->DSDK == NULL)
			Notify("LOP TIN CHI KHONG CO SINH VIEN DANG KI!", 75, 43, 79);
		else {
			// tim thong tin mon hoc
			MH_TREE infoSub = SearchMaMH(DSMH, DSLTC.nodeLopTC[vtLTC]->maMH);
			
			gotoxy(60, 2); cout << "NIEN KHOA: " << DSLTC.nodeLopTC[vtLTC]->nienKhoa;
			gotoxy(60, 3); cout << "HOC KY   : " << DSLTC.nodeLopTC[vtLTC]->hocKy;
			gotoxy(60, 4); cout << "NHOM     : " << DSLTC.nodeLopTC[vtLTC]->nhom;
			
			int trang = 0, tongTrang = 0, soluongSV = 0;
			int nSV = 0, nDiem = 0, row = 0; // nSV vi tri phan tu sinh vien
			
			soluongSV = countSVDK(DSLTC, vtLTC);
			if (soluongSV == 0)
				Notify("CHUA CO DU LIEU SINH VIEN", 75, 43, 79);
			else {
				if (soluongSV < 15)
				{
					tongTrang = 1;
					trang = 0;
				}
				else
					tongTrang = ((soluongSV - 1) / 15 + 1);
			}
			
			SVPTR sv;
			// chuyen sang mang thong tin sinh vien
			SinhVien* arrSV = new SinhVien[soluongSV + 1];
			DK* Diem = new DK[soluongSV + 1]; // chua diem cua sinh vien
			
			// tu mssv cua dsdk se tim data cua sinh vien trong dssv cup lop roi do vao mang kieu sinh vien
			for(DKPTR p = DSLTC.nodeLopTC[vtLTC]->DSDK; p != NULL; p = p->next) {
				for(int i = 0; i < DSL.n; i++) {
					sv = SearchMSSV(DSL.dsLop[i].DSSV, p->data.mssv);
					if(sv != NULL) {
						arrSV[nSV] = sv->data; nSV++;
						break;
					}				
				}
			}
			
			SapXepSVDK(arrSV, nSV);
			
			//dua du lieu diem vao danh sach sinh vien
			for (int i = 0; i < nSV; i++) {
				for (DKPTR p = DSLTC.nodeLopTC[vtLTC]->DSDK; p != NULL; p = p->next) {
					if (p->data.mssv == arrSV[i].mssv) {
						Diem[i].diem = p->data.diem;
					}
				}
			}
			
			int y = 14; // vi tri hang nhap cua thang dau tien bang
			
			int key; int stt;
			stt = 0;
Reset:
			row = 0;
			XoaKhungNhapDiem(); KhungNhapDiem(infoSub->data.tenMH);
			for(int i = trang * 15; i < 15 + trang * 15 && i < soluongSV; i++) {
				DKPTR infoSVDK = SearchInfoSVDK(DSLTC.nodeLopTC[vtLTC]->DSDK, arrSV[i].mssv);
				
				stt = i + 1;
				gotoxy(63, row + 14); cout << stt;
				gotoxy(71, row + 14); cout << arrSV[i].mssv;
				gotoxy(98, row + 14); cout << arrSV[i].ho;
				gotoxy(128, row + 14); cout << arrSV[i].ten;
				gotoxy(146, row + 14); cout << infoSVDK->data.diem;
				row++;
			}
			HienThiTrang(trang + 1, tongTrang, 148, 33);
			while(1) {
				key = GetKey();
				if ((key == RIGHT) && trang < tongTrang - 1)
				{
					trang++;
					nDiem = nDiem + 15;
					if (nDiem > soluongSV) //Neu lat qua trang va vuot qua so luong sinh vien
					{
						nDiem = soluongSV - 1;
						y = nDiem % 15 + 14;
					}
					goto Reset;
				}
				if ((key == LEFT) && trang > 0)
				{
					trang--;
					nDiem = nDiem - 15;
					goto Reset;
				}
				if (key == UP && y > 14)
				{
					nDiem--;
					gotoxy(146, --y); cout << "   ";
					gotoxy(146, y); Diem[nDiem].diem = NhapDiemThuc();
					gotoxy(146, y);
				}
				if (key == DOWN && y < 28 && nDiem < nSV - 1)
				{
					nDiem++;
					gotoxy(146, ++y); cout << "   ";
					gotoxy(146, y); Diem[nDiem].diem = NhapDiemThuc();
					gotoxy(146, y); 
				}
				if (key == ESC)
				{
					for(DKPTR p = DSLTC.nodeLopTC[vtLTC]->DSDK; p != NULL; p = p->next) {
						for(int i = 0; i < nSV; i++) {
							if(p->data.mssv == arrSV[i].mssv) {
								p->data.diem = Diem[i].diem;
							}
						}
					}
					WriteFileDSDK(DSLTC);
					Notify("LUU VAO FILE THANH CONG!", 75, 43, 47);
					delete[] arrSV; delete[] Diem; system("cls"); 
					return;
				}
			}
		}
	}
}
//==================================================================================

//=========================== QUAN LY MON HOC ======================================

// duyet cay AVL theo thu tu tang dan (Left Node Right - LNR)
int CountNode(MH_TREE root, int &count) {
	if(root != NULL)
		return CountNode(root->pLeft, count) + CountNode(root->pRight, count) + 1;	
	else return 0;
}

// quay don Left-Left
void RorateLL (MH_TREE &T) {
	MH_TREE T1 = T->pLeft;
	T->pLeft = T1->pRight;
	T1->pRight = T;
	switch(T1->balFactor) {
		case LH: {
			T->balFactor = EH;
			T1->balFactor = EH;
			break;	
		}
		case EH: {
			T->balFactor = LH;
			T1->balFactor = RH;
			break;
		}
	}
	T = T1;
}

// quay don Right-Right
void RorateRR (MH_TREE &T) {
	MH_TREE T1 = T->pRight;
	T->pRight = T1->pLeft;
	T1->pLeft = T;
	switch(T1->balFactor) {
		case RH: {
			T->balFactor = EH;
			T1->balFactor = EH;
			break;	
		}
		case EH: {
			T->balFactor = RH;
			T1->balFactor = LH;
			break;
		}
	}
	T = T1;
}

// quay kep Right-Left
void RorateRL(MH_TREE &T) {
	MH_TREE T1 = T->pRight;
	MH_TREE T2 = T1->pLeft;
	T->pRight = T2->pLeft;
	T2->pLeft = T;
	T1->pLeft = T2->pRight;
	T2->pRight = T1;
	switch(T2->balFactor) {
		case LH: {
			T->balFactor = EH;
			T1->balFactor = RH;
			break;
		}
		case EH: {
			T->balFactor = EH;
			T1->balFactor = EH;
			break;
		}
		case RH: {
			T->balFactor = LH;
			T1->balFactor = EH;
			break;
		}
	}
	T2->balFactor = EH;
	T = T2;
}

// quay kep Left-Right
void RorateLR(MH_TREE &T) {
	MH_TREE T1 = T->pLeft;
	MH_TREE T2 = T1->pRight;
	T->pLeft = T2->pRight;
	T2->pRight = T;
	T1->pRight = T2->pLeft;
	T2->pLeft = T1;
	switch(T2->balFactor) {
		case LH: {
			T->balFactor = RH;
			T1->balFactor = EH;
			break;
		}
		case EH : {
			T1->balFactor = EH;
			T->balFactor = EH;
			break;
		}
		case RH: {
			T->balFactor = EH;
			T1->balFactor = LH;
			break;
		}
	}
	T2->balFactor = EH;
	T = T2;
}

// can bang cac truong hop lech trai
int balanceLeft(MH_TREE &T) {
	MH_TREE T1 = T->pLeft;
	switch(T1->balFactor) {
		case LH: RorateLL(T); return 2; // return 2 nhanh T cu co chi so can bang la EH
		case EH: RorateLL(T); return 1; // return 1 nhanh T cu co chi so can bang khac EH
		case RH: RorateLR(T); return 2; 
	}
	return 0;
}

// can bang cac truong hop lech phai
int balanceRight(MH_TREE &T) {
	MH_TREE T1 = T->pRight;
	switch(T1->balFactor) {
		case LH: RorateRL(T); return 2; // return 2 nhanh T cu co chi so can bang la EH
		case EH: RorateRR(T); return 1; // return 1 nhanh T cu co chi so can bang khac EH
		case RH: RorateRR(T); return 2;
	}
	return 0;
}

MH_TREE CreateNodeAVLMH(MH monhoc) {
	MH_TREE p = new NodeMH;
	
	if(!p) exit(1); // khong du bo nho
	
	p->data = monhoc;
	p->balFactor = EH;
	p->pLeft = NULL;
	p->pRight = NULL;
	return p;
}

// them mon hoc vao cay nhi phan tim kiem can bang
int InsertNodeMH(MH_TREE &T, MH monhoc) {
	// res kiem tra xem them thanh cong hay khong
	// va xem cay bi lech ve huong nao
	int res; 
	if(T) {
		if(T->data.maMH == monhoc.maMH) return 0; // return 0 gap lai node cu
		if(T->data.maMH > monhoc.maMH) {
			
			res = InsertNodeMH(T->pLeft, monhoc);
			
			if(res < 2) return res;
			
			switch(T->balFactor) {
				case RH: T->balFactor = EH; return 1; // return 1 la them thanh cong vao chieu cao cay ko bi thay doi
				case EH: T->balFactor = LH; return 2; // return 2 sau khi them chieu cao cay bi tang va phai can bang lai chi so
				case LH: balanceLeft(T); return 1; // return 1 la them thanh cong vao chieu cao cay ko bi thay doi
			}
		}
		else {
			
			res = InsertNodeMH(T->pRight, monhoc);
			
			if(res < 2) return res;
			
			switch(T->balFactor) {
				case LH: T->balFactor = EH; return 1; // khong can cap nhat lai chi so can bang
				case EH: T->balFactor = RH; return 2; // phai cap nhat lai chi so can bang
				case RH: balanceRight(T); return 1;
			}
		}
	}
	T = CreateNodeAVLMH(monhoc);
	return 2;
}

// tim node the mang (tim phan tu trai nhat cua cay con phai)
int SearchStandFor(MH_TREE &p, MH_TREE &q) {
	int res;
	if(q->pLeft) {
		res = SearchStandFor(p, q->pLeft);
		
		if(res < 2) return res;
		
		switch(q->balFactor) {
			case LH: q->balFactor = EH; return 2; // chieu cao lai thay doi
			case EH: q->balFactor = RH; return 1;
			case RH: return balanceRight(q);
		}
	} else { 
		p->data = q->data;
		p = q;
		q = q->pRight;
		return 2;
	}
}

// ham xoa 1 node MH
int DelNode(MH_TREE &T, string maMH) {
	int res;
	if(T == NULL) return 0; // khong tim thay node can xoa 
	if(T->data.maMH > maMH) {
		res = DelNode(T->pLeft, maMH);
		
		if(res < 2) return res;
		
		switch(T->balFactor) {
			case LH: T->balFactor = EH; return 2;
			case EH: T->balFactor = RH; return 1;
			case RH: return balanceRight(T);
		}
	} else if(T->data.maMH < maMH) {
		res = DelNode(T->pRight, maMH);
		
		if(res < 2) return res;
		
		switch(T->balFactor) {
			case RH: T->balFactor = EH; return 2;
			case EH: T->balFactor = LH; return 1;
			case LH: return balanceLeft(T);
		}
	// T->data.tenMH == MH.tenMH
	} else {
		MH_TREE p = T;
		if(T->pLeft == NULL) {
			T = T->pRight; 
			return 2; // chieu cao cay thay doi cap nhat lai chi so can bang
		}
		else if(T->pRight == NULL) { 
			T = T->pLeft; 
			return 2; // chieu cao cay thay doi cap nhat lai chi so can bang
		}
		// ca hai nhanh trai va phai deu khac NULL
		else {
			MH_TREE p = T;
			
			res = SearchStandFor(p, T->pRight);
			
			if(res < 2) return res;
			
			switch(T->balFactor) {
				case RH: T->balFactor = EH; return 2; // return 2 chieu cao cay co su thay doi
				case EH: T->balFactor = LH; return 1; // khong co su thay doi ve chieu cao
				case LH: return balanceLeft(T);
			}
		}
		delete p; return res;
	}
}

// ghi file theo NLR (khong luu theo LNR hay RNL vi khi do cay se bi lech ve het mot ben khi doc file ra se thanh cay suy bien)
void WriteFile_NLR(ofstream &File, MH_TREE DSMH) {
	if(DSMH != NULL) {
		File << DSMH->data.maMH << endl;
		File << DSMH->data.tenMH << endl;
		File << DSMH->data.soTCLT << endl;
		File << DSMH->data.soTCTH << endl;
		WriteFile_NLR(File, DSMH->pLeft);
		WriteFile_NLR(File, DSMH->pRight);
	}
}

// ghi file danh sach thong tin mon hoc
void WriteFileDSMH(MH_TREE &DSMH) {
	ofstream outFile;
	outFile.open("DSMH.txt", ios::out);
	WriteFile_NLR(outFile, DSMH);
	outFile.close();
}

// luu data mon hoc vao mang tuyen tinh
void ConvertArray(MH_TREE &DSMH, MH *monhoc, int &n) {
	if(DSMH != NULL) {
		monhoc[n++] = DSMH->data;
		ConvertArray(DSMH->pLeft, monhoc, n);
		ConvertArray(DSMH->pRight, monhoc, n);
	}
}

void XuatThongTinMH(MH *monhoc, int TongMH) {
	int key;
	int trang = 0; int tongTrang = 0;
	int row;
	while(1) {
		if(TongMH == 0) {
			Notify("DANH SACH MON HOC RONG!", 75, 43, 79);
		} else {
			if(TongMH < 15) {
				trang = 0;
				tongTrang = 1;
			} else {
				tongTrang = (TongMH - 1) / 15 + 1;
			}
		}
		int stt = 0; row = 0;
		XoaKhungDSL(); KhungXuatDSMH();
		for(int i = trang * 15; i < 15 + trang * 15 && i < TongMH; i++) {
			stt = i + 1;
			gotoxy(58, 12 + row); cout << stt;
			gotoxy(70, 12 + row); cout << monhoc[i].maMH;
			gotoxy(90, 12 + row); cout << monhoc[i].tenMH;
			gotoxy(136, 12 + row); cout << monhoc[i].soTCLT;
			gotoxy(147, 12 + row); cout << monhoc[i].soTCTH;
			row++;
		}
		HienThiTrang(trang + 1, tongTrang, 148, 29);
		key = GetKey();
		if((key == RIGHT || key == DOWN) && trang < tongTrang - 1) 
			trang++;
		if((key == LEFT || key == UP) && trang > 0)
			trang--;
		if(key == ESC)
			return;
	}
}

// sap xep theo ho ten bang selection sort
void SapXepMHTheoTen(MH *monhoc, int TongMH) {
	for(int i = 0; i < TongMH - 1; i++) {
		for(int j = i + 1; j < TongMH; j++) {
			if(monhoc[i].tenMH > monhoc[j].tenMH) {
				MH monhocTemp = monhoc[i];
				monhoc[i] = monhoc[j];
				monhoc[j] = monhocTemp; 
			}
		}
	}
}

// xuat thong tin cua mon hoc
void XuatDSMH(MH_TREE DSMH) {
	int key;
	int count = 0; int n = 0;
	int TongMH = CountNode(DSMH, count);
	MH *monhoc = new MH[TongMH];
	
	ConvertArray(DSMH, monhoc, n);
	
	SapXepMHTheoTen(monhoc, TongMH);
	
	XuatThongTinMH(monhoc, TongMH);
	delete[] monhoc;
}

bool isExistMH(MH_TREE DSMH, string maMH) {
	if(DSMH != NULL) {
		if(DSMH->data.maMH == maMH)
			return true;
		
		else if(DSMH->data.maMH > maMH)
			return SearchMaMH(DSMH->pLeft, maMH);
			
		else
			return SearchMaMH(DSMH->pRight, maMH);
	} else return false;
}

// them mot mon hoc moi vao danh sach
void ThemMonHoc(MH_TREE &DSMH) {
	MH monhoc;	
	MH_TREE p;
	
	KhungThemMH();
	
	do {
		gotoxy(86, 14); monhoc.maMH = EnterData(3);
		if(monhoc.maMH == "-1") {
			Notify("KET THUC VIEC NHAP!", 75, 43, 79);
			return;
		}
		
		p = SearchMaMH(DSMH, monhoc.maMH);
		
		if(p != NULL) {
			Notify("MA MON HOC DA TON TAI!", 75, 43, 79);
			gotoxy(86, 14); cout << "                ";
		}
	} while(p != NULL);
	
	gotoxy(86, 15); monhoc.tenMH = EnterData(6);
	XoaKhoangTrangThua(monhoc.tenMH);
	if(monhoc.tenMH == "-1") {
		Notify("KET THUC VIEC NHAP!", 75, 43, 79);
		return;
	}
	gotoxy(86, 16); monhoc.soTCLT = NhapSoNguyen();
	if(monhoc.soTCLT == -1) {
		Notify("KET THUC VIEC NHAP!", 75, 43, 79);
		return;
	}
	gotoxy(86, 17); monhoc.soTCTH = NhapSoNguyen();
	if(monhoc.soTCTH == -1) {
		Notify("KET THUC VIEC NHAP!", 75, 43, 79);
		return;
	}
	
	InsertNodeMH(DSMH, monhoc);
	
	WriteFileDSMH(DSMH);
	Notify("THEM MON HOC THANH CONG!", 75, 43, 47);
}

// ham kiem tra xem lop tin chi co ma mon hoc can xoa da co sinh vien dang ki chua
bool isExistSVDK(DSLopTC DSLTC, string maMH) {
	for(int i = 0; i < DSLTC.n; i++)
		if(DSLTC.nodeLopTC[i]->maMH == maMH)
			if(DSLTC.nodeLopTC[i]->DSDK != NULL)
				return true;
	return false;
}

// tra ve vi tri cua lop tin chi co ma mon hoc can tim
int SearchLTC_MMH(DSLopTC DSLTC, string maMH) {
	for(int i = 0; i < DSLTC.n; i++)
		if(DSLTC.nodeLopTC[i]->maMH == maMH)
			return i;
	return -1;
}

// ham gan vi tri cua cac lop tin chi co ma mon hoc can chinh sua
void GanViTriLTC_MMH(DSLopTC DSLTC, int arrViTri[], int &n, string maMH) {
	for(int i = 0; i < DSLTC.n; i++)
		if(DSLTC.nodeLopTC[i]->maMH == maMH)
			arrViTri[n++] = i; 
}

// ham gan cac ma lop tin chi trung voi ma mon hoc
void GanMLTC_MMH(DSLopTC DSLTC, int arrMLTC[], int n, string maMH) {
	n = 0;
	for(int i = 0; i < DSLTC.n; i++)
		if(DSLTC.nodeLopTC[i]->maMH == maMH)
			arrMLTC[n++] = DSLTC.nodeLopTC[i]->maLopTC;
}

// dem so lop tin chi co ma mon hoc trung voi ma mon hoc can xoa
void DemMLTC_MMH(DSLopTC DSLTC, int &n, string maMH) {
	for(int i = 0; i < DSLTC.n; i++)
		if(DSLTC.nodeLopTC[i]->maMH == maMH)
			n++;
}

// ham xoa mot mon hoc
void DeleteMH(MH_TREE &DSMH, DSLopTC &DSLTC) {
	string maMH;
	MH_TREE p;
	
	do {
		fflush(stdin);
		gotoxy(2, 10); cout << "Nhap ma mon hoc can xoa: ";
		maMH = EnterData(3);
		if(maMH == "-1") {
			Notify("KET THUC VIEC NHAP!", 75, 43, 79);
			return;
		}
		
		p = SearchMaMH(DSMH, maMH);
		
		if(!p) {
			Notify("KHONG TIM THAY MON HOC!", 75, 43, 79);
			gotoxy(27, 10); cout << "           ";
		}
	} while(!p);
	
	// kiem tra xem cac lop tin chi co ma mon hoc can xoa da co sinh vien dang ki chua
	bool checkExistSVDK = isExistSVDK(DSLTC, maMH);
	
	if(checkExistSVDK)
		Notify("MON HOC DA CO DANH SACH DANG KI, KHONG THE XOA!", 75, 43, 79);
	else {
		int n = 0;
		DemMLTC_MMH(DSLTC, n, maMH);
		int arrMLTC[n];
		// gan ma lop tin chi co ma mon hoc trung voi ma mon hoc can xoa
		GanMLTC_MMH(DSLTC, arrMLTC, n, maMH);
		
		// xoa mon hoc thi phai xoa luon lop tin chi co ma mon hoc giong ma mon hoc da xoa
		DelNode(DSMH, maMH);

		for(int i = 0; i < n; i++) {
			int vt = SearchMLTC(DSLTC, arrMLTC[i]);
			DeleteNodeLTC(DSLTC, vt);
		}
		
		WriteFileDSMH(DSMH);
		WriteFileDSLTC(DSLTC);
		Notify("XOA MON HOC THANH CONG!", 75, 43, 47);
	}
}

// cap nhat mon hoc
void UpdateMH(MH_TREE &DSMH, DSLopTC &DSLTC) {
	string maMH; 
	MH monhoc; MH_TREE p;
	
	do {
		rewind(stdin);
		gotoxy(2, 10); cout << "Nhap Ma Mon Hoc Can Chinh Sua: ";
		gotoxy(33, 10); maMH = EnterData(3);
		if(maMH == "-1") {
			Notify("KET THUC VIEC NHAP!", 75, 43, 79);
			return;
		}
		
		p = SearchMaMH(DSMH, maMH);
		
		if(!p) {
			Notify("KHONG TIM THAY MON HOC!", 75, 43, 79);
			gotoxy(33, 10); cout << "               ";
		}
	} while(!p);
	
	KhungCapNhatMH();
	
	rewind(stdin);
	do {
		gotoxy(86, 14); monhoc.maMH = EnterData(3);
		if(monhoc.maMH == "-1") {
			Notify("KET THUC VIEC NHAP!", 75, 43, 79);
			return;
		}
		
		// neu ma mon hoc cap nhat moi van bang ma mon hoc cu thi van duoc nen break de tiep tuc cac lenh sau
		if(monhoc.maMH == maMH) 
			break;
		else {
			p = SearchMaMH(DSMH, monhoc.maMH);
		
			if(p != NULL) {
				Notify("MA MON HOC DA TON TAI!", 75, 43, 79);
				gotoxy(86, 14); cout << "                ";
			}
		}
	} while(p != NULL);
	
	gotoxy(86, 15); monhoc.tenMH = EnterData(6);
	XoaKhoangTrangThua(monhoc.tenMH);
	if(monhoc.tenMH == "-1") {
		Notify("KET THUC VIEC NHAP!", 75, 43, 79);
		return;
	}
	
	gotoxy(86, 16); monhoc.soTCLT = NhapSoNguyen();
	if(monhoc.soTCLT == -1) {
		Notify("KET THUC VIEC NHAP!", 75, 43, 79);
		return;
	}
	
	gotoxy(86, 17); monhoc.soTCTH = NhapSoNguyen();
	if(monhoc.soTCTH == -1) {
		Notify("KET THUC VIEC NHAP!", 75, 43, 79);
		return;
	}
	
	// mang de luu vi tri cac lop tin chi co ma mon hoc trung voi ma mon hoc chinh sua
	int n = 0;
	int arrViTri[n];
		
	// chinh sua ma mon hoc o cho mon hoc cung phai sua ma mon hoc o lop tin chi
	GanViTriLTC_MMH(DSLTC, arrViTri, n, maMH);
	
	for(int i = 0; i < n; i++) {
		DSLTC.nodeLopTC[arrViTri[i]]->maMH = monhoc.maMH;
	}
	
	/* khi cap nhat lai ma mon hoc co the se sai voi dieu kien cua cay nhi phan
	can bang nen xoa no di va them lai node moi luon */
	DelNode(DSMH, maMH);
	InsertNodeMH(DSMH, monhoc);
	
	WriteFileDSLTC(DSLTC);
	WriteFileDSMH(DSMH);
	Notify("CAP NHAT MON HOC THANH CONG!", 75, 43, 47);
}
//====================================================================================

//============================== PHAN XUAT CAC BANG DIEM =============================

//======================== XUAT BANG DIEM TRUNG BINH CUA MOT LOP ======================

// xuat diem trung binh cua cac sinh vien trong mot lop hoc
void XuatDiemTB(DSLopTC DSLTC, ListLop DSL, MH_TREE DSMH) {
	string maLop; int vtLop;
	int key;
	
	do {
		TextColor(7);
		gotoxy(2, 12); cout << "NHAP MA LOP: ";
		maLop = EnterData(4);
		if(maLop == "-1") {
			Notify("KET THUC VIEC NHAP!", 75, 43, 79);
			return;
		}
		
		vtLop = SearchMaLop(DSL, maLop, DSL.n);
		
		if(vtLop == -1) {
			TextColor(79);
			Notify("LOP HOC KHONG TON TAI", 5, 25, 79);
			gotoxy(5, 25); 
			TextColor(7);
			gotoxy(13, 12); cout << "                  ";
		}
	} while(vtLop == -1);
	
	int trang = 0; int tongTrang = 0; int soluongSV = 0;
	int nSV = 0; // dem so luon sinh vien
	
	soluongSV = countDSSV(DSL.dsLop[vtLop].DSSV);
	if(soluongSV == 0) {
		Notify("DANH SACH SINH VIEN TRONG LOP RONG!", 75, 43, 79);
	} else {
		if(soluongSV < 15) {
			trang = 0;
			tongTrang = 1;
		} else {
			tongTrang = (soluongSV - 1) / 15 + 1;
		}
	}
	
	// do thong tin sinh vien vao mang sinh vien de sap xep va phan trang
	SinhVien* sv = new SinhVien[soluongSV + 1];
	for(SVPTR p = DSL.dsLop[vtLop].DSSV; p != NULL; p = p->next) {
		sv[nSV] = p->data;
		nSV++;
	}
	
	// sap xep sinh vien
	SapXepSVDK(sv, nSV);
	
	 // mang diem de luu diem cua sinh vien
	float diem[nSV];
	
	for(int i = 0; i < nSV; i++) {
		float tongDiemNhanSTC = 0.0; float tongSTC = 0.0;
		for(int j = 0; j < DSLTC.n; j++) { // vo tung lop tin chi de xem sinh vien do dang ki hoc lop nao de lay diem
			for(DKPTR p = DSLTC.nodeLopTC[j]->DSDK; p != NULL; p = p->next) {
				if(p->data.mssv == sv[i].mssv) {
					// tim hong tin mon hoc de lay tin chi
					MH_TREE infoMH = SearchMaMH(DSMH, DSLTC.nodeLopTC[j]->maMH);
					tongDiemNhanSTC += (p->data.diem * (infoMH->data.soTCLT + infoMH->data.soTCTH));
					tongSTC += (infoMH->data.soTCLT + infoMH->data.soTCTH);
				}
			}
		}
		// neu sinh vien ko dang ki lop tin chi nao thi 0 / 0 = nan nen them dieu kien nay
		if(tongDiemNhanSTC == 0 && tongSTC == 0)
			diem[i] = 0.0;		
		else
			diem[i] = roundf((tongDiemNhanSTC / tongSTC) * 100) / 100;
	}
	
	while(1) {
		gotoxy(53, 2); cout << "LOP   : " << DSL.dsLop[vtLop].tenLop;
		gotoxy(53, 3); cout << "MA LOP: " << DSL.dsLop[vtLop].maLop;
		
		XoaKhungXuatLTC(); KhungXuatDiemTBLop();
		int stt = 0; int row = 0; // dem so dong
		for(int i = trang * 15; i < 15 + trang * 15 && i < soluongSV; i++) {
			row += 1; stt = i + 1;
			
			gotoxy(55, 11 + row); cout << stt;
			gotoxy(65, 11 + row); cout << sv[i].mssv;
			gotoxy(88, 11 + row); cout << sv[i].ho;
			gotoxy(123, 11 + row); cout << sv[i].ten;
			gotoxy(140, 11 + row); cout << diem[i];
		}
		HienThiTrang(trang + 1, tongTrang, 142, 29);
		key = GetKey();
		if((key == RIGHT || key == DOWN) && trang < tongTrang - 1) 
			trang++;
		if((key == LEFT || key == UP) && trang > 0)
			trang--;
		if(key == ESC) {
			delete[] sv;
			system("cls");
			return;
		}
	}
}
//=====================================================================================

//======================== XUAT BANG DIEM TONG KET CAC MON ============================

// bang diem tong ket cac mon cua cac sinh vien thuoc mot lop
/*void XuatBangDiemTK(MH_TREE DSMH, DSLopTC DSLTC, ListLop DSL) {
}*/

//=====================================================================================

//=========================== DOC FILE VA GHI FILE ==============================

// Doc File Danh Sach Lop Tin Chi
void ReadFileDSLTC(DSLopTC &DSLTC) 
{
	ifstream inFile;
	inFile.open("DSLTC.txt", ios::in);
	if(inFile.fail()) {
		Notify("FILE DANH SACH LOP TIN CHI KHONG TON TAI!", 25, 20, 79);
		return;
	}
	
	LopTC lopTC;
	
	// inFile.good() neu inFile.eof() && inFile.bad() && inFile.fail() cung tra ve false
	while(inFile.good()) 
	{
		inFile >> lopTC.maLopTC;
		inFile.ignore(); // loai bo ki tu trong bo nho dem
		getline(inFile, lopTC.maMH);
		inFile >> lopTC.nienKhoa;
		inFile >> lopTC.hocKy;
		inFile >> lopTC.nhom;
		inFile >> lopTC.nSvMax;
		inFile >> lopTC.nSvMin;
		inFile >> lopTC.huyLop;
				
		// nhap thong tin lop tin chi xong thi Insert vao danh sach lop tin chi
		InsertLTC(DSLTC, lopTC, DSLTC.n);
	}
	inFile.close();
}

// Doc File Danh Sach Lop
void ReadFileLop(ListLop &DSL)
{
	ifstream inFile;
	inFile.open("DSLOP.txt", ios::in);
	if(inFile.fail()) {
		Notify("FILE DANH SACH LOP KHONG TON TAI!", 25, 20, 79);
		return;
	}
	
	Lop lopTemp;
	DSL.n = 0;
	while(inFile.good()) {
		getline(inFile, DSL.dsLop[DSL.n].maLop);
		getline(inFile, DSL.dsLop[DSL.n].tenLop);
		inFile >> DSL.dsLop[DSL.n].nienKhoa;
		inFile.ignore();
		// khoi tao con tro First DSSV
		DSL.dsLop[DSL.n].DSSV = NULL;
		DSL.n++;
	}
	
	inFile.close();
}

// Doc file sinh vien
void ReadFileSV(ListLop &DSL) 
{
	ifstream inFile;
	int vitriTemp, vitri;
	string data;
	inFile.open("DSSV.txt", ios::in);
	if(!inFile)
		return;
	while(inFile.good()) {
		SinhVien sv;
		getline(inFile, data);
		if(data.size() == 0) 
			break;
		vitriTemp = SearchMaLop(DSL, data, DSL.n);
		// tuc la tim thay
		if(vitriTemp != -1) 
			vitri = vitriTemp;
		// neu no khong phai ma lop thi nhap thong tin cua sinh vien do
		else {
			sv.mssv = data;
			getline(inFile, data); sv.ho = data;
			getline(inFile, data); sv.ten = data;
			getline(inFile, data); sv.phai = data;
			getline(inFile, data); sv.sdt = data;
			
			// sau khi doc xong het thong tin sinh vien thi them sinh vien moi vao 
			InsertSVLast(DSL.dsLop[vitri].DSSV, sv);
		}
	}
	inFile.close();
}

// doc file danh sach dang ki
void ReadFileDK(DSLopTC &DSLTC) 
{
	ifstream inFile;
	string data;
	char tempChar[2];
	int vitri, vitriTemp, maLopTC;
	inFile.open("DSDK.txt", ios::in);
	if(!inFile) return;
	while(inFile.good())
	{
		DK svDK;
		getline(inFile, data);
		if (data.size() == 0)
			break;
		maLopTC = stringToNumber(data);
		vitriTemp = SearchMLTC(DSLTC, maLopTC);
		if(vitriTemp != -1)
			vitri = vitriTemp;
		else {
			svDK.mssv = data;	
			
			// data la 1 string nen can chuyen doi sang so
			// nhung diem co the la so thuc nen ko dung ham stringToNum vi tra ve int
			getline(inFile, data);
			strcpy(tempChar, data.c_str());
			
			// dung atof chuyen mot chuoi sang float
			svDK.diem = atof(tempChar);
		
			InsertNodeDK(DSLTC.nodeLopTC[vitri]->DSDK, svDK);
		}
	}
	inFile.close();
}

// doc file mon hoc
void ReadFileMH(MH_TREE &DSMH) {
	ifstream inFile;
	string data;
	char num[2];
	inFile.open("DSMH.txt", ios::in);
	if(inFile.fail()) 
		Notify("FILE KHONG TON TAI!", 25, 20, 79);
	while(inFile.good()) {
		MH monhoc;
		
		getline(inFile, data); 
		// co file nhung chua co du lieu
		if(data.size() == 0)
			break;

		monhoc.maMH = data;
		getline(inFile, data); monhoc.tenMH = data;
		getline(inFile, data); strcpy(num, data.c_str()); monhoc.soTCLT = atof(num);
		getline(inFile, data); strcpy(num, data.c_str()); monhoc.soTCTH = atof(num);
		
		InsertNodeMH(DSMH, monhoc);
	}
	inFile.close();
}
//==================================================================================

int MenuDong(char MenuChinh[][40], int item) {
	int row;
	// dang o vi tri nao cua menu
	int thaotac = 0;
	int mau[8];
	for(int i = 0; i < item; i++)
		mau[i] = 7;
	mau[0] = 9;
	clrscr();
	gotoxy(9, 0); cout << "    MENU    ";
	KhungHuongDan();
	// vong while lap vo han cho toi khi tra ve cai gi do
	while (1) {
		for (int i = 0; i < item; i++)
		{
			TextColor(mau[i]); 
			gotoxy(0, 2 + i); cout  << char(16) << " " << MenuChinh[i] << " " << char(17);
		}
		int key = GetKey();
		switch (key)
		{
			case UP:
			case LEFT:
			{
				if (thaotac == 0)
					thaotac = item - 1;
				else
					thaotac--;
				break;
			}
			case DOWN:
			case RIGHT:
			{
				if (thaotac == item - 1)
					thaotac = 0;
				else
					thaotac++;
				break;
			}
			case ESC:
			{
				XoaKhungHuongDan();
				return thaotac = 27;
			}
			case ENTER:
			{
				XoaKhungHuongDan();
				return thaotac + 1;
			}
		}
		for (int i = 0; i < item; i++)
			mau[i] = 7;
		mau[thaotac] = 9;
	}
}

void GiaiPhongMH(MH_TREE &DSMH) {
	if(DSMH != NULL) {
		GiaiPhongMH(DSMH->pLeft);
		GiaiPhongMH(DSMH->pRight);
		delete DSMH;
		DSMH = NULL;
	}
}

void GiaiPhong(ListLop &DSL, MH_TREE &DSMH, DSLopTC &DSLTC) {
	//giai phong bo nho lop
	for (int i = 0; i < DSL.n; i++) {
		for (SVPTR p = DSL.dsLop[i].DSSV; p != NULL; p = p->next)
			delete p;
	}
	//giai phong bo nho lop tin chi
	for (int j = 0; j < DSLTC.n; j++) {
		for (DKPTR q = DSLTC.nodeLopTC[j]->DSDK; q != NULL; q = q->next) {
			delete q;
		}
		delete DSLTC.nodeLopTC[j];
	}
	GiaiPhongMH(DSMH); //Giai phong bo nho Cay Nhi Phan
}

void MenuXuLi() {
	TextColor(7);
	MH_TREE DSMH = NULL;
	DSLopTC DSLTC;
	ListLop DSL;
	MH_TREE T;
	InitializeLTC(DSLTC);
	ReadFileDSLTC(DSLTC);
	ReadFileMH(DSMH);
	ReadFileLop(DSL);
	ReadFileSV(DSL);
	ReadFileDK(DSLTC);
	
	while(1) {
		clrscr();
		int tungDo = 0;
		
menuChinh:
		int thaotac = MenuDong(MenuChinh, 6);
		
		switch(thaotac) 
		{
			case 1: {
menuLTC:
				int thaotac = MenuDong(MenuLTC, 4);		
				if(thaotac == 1) {
					ThemLopTC(DSMH, DSLTC);
					goto menuLTC;
				}
				if(thaotac == 2) {
					XuatLTC(DSLTC);
					goto menuLTC;
				}
				if(thaotac == 3) {
					if(DSLTC.n == 0)
						Notify("DANH SACH RONG KHONG THE XOA!", 75, 43, 79);
					else
						DeleteLopTC(DSLTC);
					goto menuLTC;
				}
				if(thaotac == 4) {
					UpdateLopTC(DSMH, DSLTC);
					goto menuLTC;
				}
				break;
			}	
			case 2: {
menuLop:
				int thaotac = MenuDong(MenuLop, 2);	
				if(thaotac == 1) {
					XuatDSL(DSL);
					goto menuLop;
				}
				if(thaotac == 2) {
					XuatDiemTB(DSLTC, DSL, DSMH);
					goto menuLop;
				}
				break;
			}
			case 3: {
menuSV: 
				int thaotac = MenuDong(MenuSV, 4);
				if(thaotac == 1) {
					NhapDSSV(DSL);
					goto menuSV;
				}
				if(thaotac == 2) {
					XoaSVLop(DSLTC, DSL);
					goto menuSV;
				}
				if(thaotac == 3) {
					UpdateSVLop(DSL);
					goto menuSV;
				}
				if(thaotac == 4) {
					XuatSVTangDanTheoHoTen(DSL);
					goto menuSV;
				}
				break;
			}
			case 4: {
menuMH: 
				int thaotac = MenuDong(MenuMH, 4);
				if(thaotac == 1) {
					ThemMonHoc(DSMH);
					goto menuMH;
				}
				if(thaotac == 2) {
					DeleteMH(DSMH, DSLTC);
					goto menuMH;
				}
				if(thaotac == 3) {
					UpdateMH(DSMH, DSLTC);
					goto menuMH;
				}
				if(thaotac == 4) {
					XuatDSMH(DSMH);
					goto menuMH;
				}
				break;
			}
			case 5: {
menuDK: 	
				int thaotac = MenuDong(MenuDK, 5);
				if(thaotac == 1) {
					DKLopTC(DSMH, DSLTC, DSL);
					goto menuDK;
				}
				if(thaotac == 2) {
					XuatDSDKLopTC(DSLTC, DSL);
					goto menuDK;
				}
				if(thaotac == 3) {
					InBangDiemLTC(DSLTC, DSL, DSMH);
					goto menuDK;
				}
				if(thaotac == 4) {
					NhapDiem(DSLTC, DSL, DSMH);
					goto menuDK;
				}
				if(thaotac == 5) {
					autoDeleteLTC(DSLTC);
					goto menuDK;
				}
				break;
			}
			default: {
				TextColor(7);
				GiaiPhong(DSL, DSMH, DSLTC);
				return;
			}
		}
	}
}

int main() {
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	MenuXuLi();
	return 0;
}
