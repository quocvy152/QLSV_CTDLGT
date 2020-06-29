#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <string.h>
#include <windows.h>

using namespace std;

void gotoxy(short x,short y)
{
    HANDLE hConsoleOutput;
    COORD Cursor_an_Pos = { x,y};
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput , Cursor_an_Pos);
}  

int wherex( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}

int wherey( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}

void TextColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void clreol( ) {
	COORD coord;
	DWORD written;
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	coord.X = info.dwCursorPosition.X;
	coord.Y = info.dwCursorPosition.Y;
	FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ',
		info.dwSize.X - info.dwCursorPosition.X * info.dwCursorPosition.Y, coord, &written);
	gotoxy (info.dwCursorPosition.X , info.dwCursorPosition.Y );
}

void clrscr() {
	system("cls");
}

void HienThiTrang(int trang, int tongtrang, int x, int y) {
	TextColor(6);	gotoxy(x, y); cout << " Trang:        ";
	gotoxy(x + 8, y); cout << trang << "/" << tongtrang;
	TextColor(7);
}

void KhungXuatLTC() {
	TextColor(241);
	gotoxy(84, 4); cout << "                                 ";
	gotoxy(84, 5); cout << "      DANH SACH LOP TIN CHI      ";
	gotoxy(84, 6); cout << "                                 ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 52; i <= 148; i++) {
		gotoxy(i, 9); cout << char(205);
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 27); cout << char(205);
	}
	
	for(int i = 10; i <= 26; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(52, i); cout << char(186);
		gotoxy(149, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(59, i); cout << char(186);
		gotoxy(69, i); cout << char(186);
		gotoxy(87, i); cout << char(186);
		gotoxy(104, i); cout << char(186); 
		gotoxy(113, i); cout << char(186); 
		gotoxy(126, i); cout << char(186);
		gotoxy(137, i); cout << char(186);
	}   
	
	// ve cac goc vuong
	gotoxy(149, 9); cout << char(187);
	gotoxy(149, 11); cout << char(185);
	gotoxy(149, 27); cout << char(188);
	
	gotoxy(52, 9); cout << char(201);
	gotoxy(52, 11); cout << char(204);
	gotoxy(52, 27); cout << char(200);
	
	gotoxy(59, 11); cout << char(206);
	gotoxy(69, 11); cout << char(206);
	gotoxy(87, 11); cout << char(206);
	gotoxy(104, 11); cout << char(206); 
	gotoxy(113, 11); cout << char(206); 
	gotoxy(126, 11); cout << char(206);
	gotoxy(137, 11); cout << char(206);
	
	gotoxy(59, 9); cout << char(203);   gotoxy(59, 27); cout << char(202);
	gotoxy(69, 9); cout << char(203);	gotoxy(69, 27); cout << char(202);
	gotoxy(87, 9); cout << char(203);	gotoxy(87, 27); cout << char(202);
	gotoxy(104, 9); cout << char(203); 	gotoxy(104, 27); cout << char(202);
	gotoxy(113, 9); cout << char(203); 	gotoxy(113, 27); cout << char(202);
	gotoxy(126, 9); cout << char(203);	gotoxy(126, 27); cout << char(202);
	gotoxy(137, 9); cout << char(203);	gotoxy(137, 27); cout << char(202);
	
	gotoxy(54, 10); cout << "STT";
	gotoxy(62, 10); cout << "MA LOP";
	gotoxy(74, 10); cout << "MA MON HOC";
	gotoxy(92, 10); cout << "NIEN KHOA";
	gotoxy(107, 10); cout << "NHOM";
	gotoxy(117, 10); cout << "HOC KY";
	gotoxy(129, 10); cout << "SV MAX";
	gotoxy(141, 10); cout << "SV MIN";
	
	gotoxy(160, 19); TextColor(116); cout << "UP   :"; TextColor(12); cout <<" LEN";
	gotoxy(160, 20); TextColor(116); cout << "LEFT :"; TextColor(12); cout << " TRAI";
	gotoxy(160, 21); TextColor(116); cout << "RIGHT:"; TextColor(12); cout << " PHAI";
	gotoxy(160, 22); TextColor(116); cout << "DOWN :"; TextColor(12); cout << " XUONG";
	
	gotoxy(53, 28); TextColor(116); cout << "ESC: "; 
	gotoxy(60, 28); TextColor(12); cout << "Exit"; TextColor(7);
	
	gotoxy(165, 15); cout << char(30);
	gotoxy(163, 16); cout << char(17);
	gotoxy(167, 16); cout << char(16);
	gotoxy(165, 17); cout << char(31);
}

void KhungXuatDSLOP() {
	TextColor(241);
	gotoxy(84, 4); cout << "                                 ";
	gotoxy(84, 5); cout << "          DANH SACH LOP          ";
	gotoxy(84, 6); cout << "                                 ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 52; i <= 148; i++) {
		gotoxy(i, 9); cout << char(205);
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 27); cout << char(205);
	}
	
	for(int i = 10; i <= 26; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(52, i); cout << char(186);
		gotoxy(148, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(59, i); cout << char(186);
		gotoxy(83, i); cout << char(186);
		gotoxy(128, i); cout << char(186);
	}  
	
	// ve cac goc vuong
	gotoxy(148, 9); cout << char(187);
	gotoxy(148, 11); cout << char(185);
	gotoxy(148, 27); cout << char(188);
	
	gotoxy(52, 9); cout << char(201);
	gotoxy(52, 11); cout << char(204);
	gotoxy(52, 27); cout << char(200);
	
	gotoxy(59, 11); cout << char(206);
	gotoxy(83, 11); cout << char(206);
	gotoxy(128, 11); cout << char(206);
	
	gotoxy(59, 9); cout << char(203);
	gotoxy(83, 9); cout << char(203);
	gotoxy(128, 9); cout << char(203);
	
	gotoxy(59, 27); cout << char(202);
	gotoxy(83, 27); cout << char(202);
	gotoxy(128, 27); cout << char(202);
	
	gotoxy(54, 10); cout << "STT";
	gotoxy(68, 10); cout << "MA LOP";
	gotoxy(102, 10); cout << "TEN LOP";
	gotoxy(135, 10); cout << "NIEN KHOA";
	
	gotoxy(53, 28); TextColor(116); cout << "ESC: "; 
	gotoxy(60, 28); TextColor(12); cout << "Exit"; TextColor(7);
}

void KhungXuatDiemTBLop() {
	TextColor(241);
	gotoxy(84, 4); cout << "                                     ";
	gotoxy(84, 5); cout << "    BANG DIEM TRUNG BINH KHOA HOC    ";
	gotoxy(84, 6); cout << "                                     ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 52; i <= 148; i++) {
		gotoxy(i, 9); cout << char(205);
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 27); cout << char(205);
	}
	
	for(int i = 10; i <= 26; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(52, i); cout << char(186);
		gotoxy(148, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(59, i); cout << char(186);
		gotoxy(83, i); cout << char(186);
		gotoxy(113, i); cout << char(186);
		gotoxy(135, i); cout << char(186);
	} 
	
	// ve cac goc vuong
	gotoxy(148, 9); cout << char(187);
	gotoxy(148, 11); cout << char(185);
	gotoxy(148, 27); cout << char(188);
	
	gotoxy(52, 9); cout << char(201);
	gotoxy(52, 11); cout << char(204);
	gotoxy(52, 27); cout << char(200);
	
	gotoxy(59, 11); cout << char(206);
	gotoxy(83, 11); cout << char(206);
	gotoxy(113, 11); cout << char(206);
	gotoxy(135, 11); cout << char(206);
	
	gotoxy(59, 9); cout << char(203);
	gotoxy(83, 9); cout << char(203);
	gotoxy(113, 9); cout << char(203);
	gotoxy(135, 9); cout << char(203);
	
	gotoxy(59, 27); cout << char(202);
	gotoxy(83, 27); cout << char(202);
	gotoxy(113, 27); cout << char(202);
	gotoxy(135, 27); cout << char(202);
	
	gotoxy(54, 10); cout << "STT";
	gotoxy(64, 10); cout << "MA SO SINH VIEN";
	gotoxy(96, 10); cout << "HO";
	gotoxy(123, 10); cout << "TEN";
	gotoxy(140, 10); cout << "DIEM";
	
	gotoxy(160, 19); TextColor(116); cout << "UP   :"; TextColor(12); cout <<" LEN";
	gotoxy(160, 20); TextColor(116); cout << "LEFT :"; TextColor(12); cout << " TRAI";
	gotoxy(160, 21); TextColor(116); cout << "RIGHT:"; TextColor(12); cout << " PHAI";
	gotoxy(160, 22); TextColor(116); cout << "DOWN :"; TextColor(12); cout << " XUONG";
	
	gotoxy(53, 28); TextColor(116); cout << "ESC: "; 
	gotoxy(60, 28); TextColor(12); cout << "Exit"; TextColor(7);
	
	gotoxy(165, 15); cout << char(30);
	gotoxy(163, 16); cout << char(17);
	gotoxy(167, 16); cout << char(16);
	gotoxy(165, 17); cout << char(31);
}

void KhungXuatDSSV() {
	TextColor(241);
	gotoxy(87, 4); cout << "                                     ";
	gotoxy(87, 5); cout << "         DANH SACH SINH VIEN         ";
	gotoxy(87, 6); cout << "                                     ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 52; i <= 164; i++) {
		gotoxy(i, 9); cout << char(205);
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 27); cout << char(205);
	}
	
	for(int i = 10; i <= 26; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(52, i); cout << char(186);
		gotoxy(164, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(59, i); cout << char(186);
		gotoxy(83, i); cout << char(186);
		gotoxy(113, i); cout << char(186);
		gotoxy(133, i); cout << char(186);
		gotoxy(145, i); cout << char(186);
	} 
	
	// ve cac goc vuong
	gotoxy(164, 9); cout << char(187);
	gotoxy(164, 11); cout << char(185);
	gotoxy(164, 27); cout << char(188);
	
	gotoxy(52, 9); cout << char(201);
	gotoxy(52, 11); cout << char(204);
	gotoxy(52, 27); cout << char(200);
	
	gotoxy(59, 11); cout << char(206);
	gotoxy(83, 11); cout << char(206);
	gotoxy(113, 11); cout << char(206);
	gotoxy(133, 11); cout << char(206);
	gotoxy(145, 11); cout << char(206);
	
	gotoxy(59, 9); cout << char(203);
	gotoxy(83, 9); cout << char(203);
	gotoxy(113, 9); cout << char(203);
	gotoxy(133, 9); cout << char(203);
	gotoxy(145, 9); cout << char(203);
	
	gotoxy(59, 27); cout << char(202);
	gotoxy(83, 27); cout << char(202);
	gotoxy(113, 27); cout << char(202);
	gotoxy(133, 27); cout << char(202);
	gotoxy(145, 27); cout << char(202);
	
	gotoxy(54, 10); cout << "STT";
	gotoxy(64, 10); cout << "MA SO SINH VIEN";
	gotoxy(97, 10); cout << "HO";
	gotoxy(122, 10); cout << "TEN";
	gotoxy(138, 10); cout << "PHAI";
	gotoxy(153, 10); cout << "SDT";
	
	gotoxy(168, 19); TextColor(116); cout << "UP   :"; TextColor(12); cout <<" LEN";
	gotoxy(168, 20); TextColor(116); cout << "LEFT :"; TextColor(12); cout << " TRAI";
	gotoxy(168, 21); TextColor(116); cout << "RIGHT:"; TextColor(12); cout << " PHAI";
	gotoxy(168, 22); TextColor(116); cout << "DOWN :"; TextColor(12); cout << " XUONG";
	
	gotoxy(53, 28); TextColor(116); cout << "ESC: "; 
	gotoxy(60, 28); TextColor(12); cout << "Exit"; TextColor(7);
	
	gotoxy(173, 15); cout << char(30);
	gotoxy(171, 16); cout << char(17);
	gotoxy(175, 16); cout << char(16);
	gotoxy(173, 17); cout << char(31);
}

void KhungXuatDSMH() {
	TextColor(241);
	gotoxy(87, 4); cout << "                                     ";
	gotoxy(87, 5); cout << "          DANH SACH MON HOC          ";
	gotoxy(87, 6); cout << "                                     ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 55; i <= 153; i++) {
		gotoxy(i, 9); cout << char(205);
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 27); cout << char(205);
	}
	
	for(int i = 10; i <= 26; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(55, i); cout << char(186);
		gotoxy(153, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(62, i); cout << char(186);
		gotoxy(86, i); cout << char(186);
		gotoxy(131, i); cout << char(186);
		gotoxy(142, i); cout << char(186);
	}  
	
	// ve cac goc vuong
	gotoxy(153, 9); cout << char(187);
	gotoxy(153, 11); cout << char(185);
	gotoxy(153, 27); cout << char(188);
	
	gotoxy(55, 9); cout << char(201);
	gotoxy(55, 11); cout << char(204);
	gotoxy(55, 27); cout << char(200);
	
	gotoxy(62, 11); cout << char(206);
	gotoxy(86, 11); cout << char(206);
	gotoxy(131, 11); cout << char(206);
	gotoxy(142, 11); cout << char(206);
	
	gotoxy(62, 9); cout << char(203);
	gotoxy(86, 9); cout << char(203);
	gotoxy(131, 9); cout << char(203);
	gotoxy(142, 9); cout << char(203);
	
	gotoxy(62, 27); cout << char(202);
	gotoxy(86, 27); cout << char(202);
	gotoxy(131, 27); cout << char(202);
	gotoxy(142, 27); cout << char(202);
	
	gotoxy(57, 10); cout << "STT";
	gotoxy(69, 10); cout << "MA MON HOC";
	gotoxy(104, 10); cout << "TEN MON HOC";
	gotoxy(135, 10); cout << "TCLT";
	gotoxy(146, 10); cout << "TCTH";
	
	gotoxy(160, 19); TextColor(116); cout << "UP   :"; TextColor(12); cout <<" LEN";
	gotoxy(160, 20); TextColor(116); cout << "LEFT :"; TextColor(12); cout << " TRAI";
	gotoxy(160, 21); TextColor(116); cout << "RIGHT:"; TextColor(12); cout << " PHAI";
	gotoxy(160, 22); TextColor(116); cout << "DOWN :"; TextColor(12); cout << " XUONG";
	
	gotoxy(57, 28); TextColor(116); cout << "ESC: "; 
	gotoxy(64, 28); TextColor(12); cout << "Exit"; TextColor(7);
	
	gotoxy(165, 15); cout << char(30);
	gotoxy(163, 16); cout << char(17);
	gotoxy(167, 16); cout << char(16);
	gotoxy(165, 17); cout << char(31);
}

void KhungXuatDSDKLTC() {
	TextColor(241);
	gotoxy(90, 4); cout << "                                     ";
	gotoxy(90, 5); cout << "    DANH SACH DANG KY LOP TIN CHI    ";
	gotoxy(90, 6); cout << "                                     ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 52; i <= 163; i++) {
		gotoxy(i, 9); cout << char(205);
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 27); cout << char(205);
	}
	
	for(int i = 10; i <= 26; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(52, i); cout << char(186);
		gotoxy(163, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(59, i); cout << char(186);
		gotoxy(83, i); cout << char(186);
		gotoxy(113, i); cout << char(186);
		gotoxy(132, i); cout << char(186);
		gotoxy(145, i); cout << char(186);
	} 
	
	// ve cac goc vuong
	gotoxy(163, 9); cout << char(187);
	gotoxy(163, 11); cout << char(185);
	gotoxy(163, 27); cout << char(188);
	
	gotoxy(52, 9); cout << char(201);
	gotoxy(52, 11); cout << char(204);
	gotoxy(52, 27); cout << char(200);
	
	gotoxy(59, 11); cout << char(206);
	gotoxy(83, 11); cout << char(206);
	gotoxy(113, 11); cout << char(206);
	gotoxy(132, 11); cout << char(206);
	gotoxy(145, 11); cout << char(206);
	
	gotoxy(59, 9); cout << char(203);
	gotoxy(83, 9); cout << char(203);
	gotoxy(113, 9); cout << char(203);
	gotoxy(132, 9); cout << char(203);
	gotoxy(145, 9); cout << char(203);
	
	gotoxy(59, 27); cout << char(202);
	gotoxy(83, 27); cout << char(202);
	gotoxy(113, 27); cout << char(202);
	gotoxy(132, 27); cout << char(202);
	gotoxy(145, 27); cout << char(202);
	
	gotoxy(54, 10); cout << "STT";
	gotoxy(64, 10); cout << "MA SO SINH VIEN";
	gotoxy(97, 10); cout << "HO";
	gotoxy(122, 10); cout << "TEN";
	gotoxy(137, 10); cout << "PHAI";
	gotoxy(153, 10); cout << "SDT";
	
	gotoxy(53, 28); TextColor(116); cout << "ESC: "; 
	gotoxy(60, 28); TextColor(12); cout << "Exit"; TextColor(7);
}

void KhungNhapDiem(string tenMH) {
	TextColor(241);
	gotoxy(90, 7); cout << "      BANG DIEM MON " << tenMH << "     ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 60; i <= 154; i++) {
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 13); cout << char(205);
		gotoxy(i, 31); cout << char(205);
	}
	
	for(int i = 12; i <= 30; i++) {
		// ve duong doc ben trai va phai
		gotoxy(60, i); cout << char(186);
		gotoxy(154, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(67, i); cout << char(186);
		gotoxy(86, i); cout << char(186);
		gotoxy(120, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
	} 
	
	// ve cac goc vuong
	gotoxy(154, 11); cout << char(187);
	gotoxy(154, 13); cout << char(185);
	gotoxy(154, 31); cout << char(188);
	
	gotoxy(60, 11); cout << char(201);
	gotoxy(60, 13); cout << char(204);
	gotoxy(60, 31); cout << char(200);
	
	gotoxy(67, 13); cout << char(206);
	gotoxy(86, 13); cout << char(206);
	gotoxy(120, 13); cout << char(206);
	gotoxy(140, 13); cout << char(206);
	
	gotoxy(67, 11); cout << char(203);
	gotoxy(86, 11); cout << char(203);
	gotoxy(120, 11); cout << char(203);
	gotoxy(140, 11); cout << char(203);
	
	gotoxy(67, 31); cout << char(202);
	gotoxy(86, 31); cout << char(202);
	gotoxy(120, 31); cout << char(202);
	gotoxy(140, 31); cout << char(202);
	
	gotoxy(62, 12); cout << "STT";
	gotoxy(74, 12); cout << "MSSV";
	gotoxy(105, 12); cout << "HO";
	gotoxy(130, 12); cout << "TEN";
	gotoxy(145, 12); cout << "DIEM";
	
	gotoxy(165, 15); cout << char(30);
	gotoxy(163, 16); cout << char(17);
	gotoxy(167, 16); cout << char(16);
	gotoxy(165, 17); cout << char(31);
	
	gotoxy(160, 19); cout << "UP   : LEN";
	gotoxy(160, 20); cout << "LEFT : TRAI";
	gotoxy(160, 21); cout << "RIGHT: PHAI";
	gotoxy(160, 22); cout << "DOWN : XUONG";
	
	gotoxy(61, 32); TextColor(116); cout << "ESC: "; 
	gotoxy(68, 32); TextColor(12); cout << "Exit"; TextColor(7);
}

void KhungNhapTTLTC() {
	gotoxy(90, 12); cout << " NHAP THONG TIN LOP TIN CHI ";
	
	for(int i = 70; i <= 140; i++) {
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 18); cout << char(205);
	}
	
	for(int i = 11; i <= 18; i++) {
		// ve duong doc ben trai va phai
		gotoxy(70, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
	} 
	
	gotoxy(140, 11); cout << char(187);
	gotoxy(140, 18); cout << char(188);
	
	gotoxy(70, 11); cout << char(201);
	gotoxy(70, 18); cout << char(200);
	
	gotoxy(72, 14); cout << "Nhap nien khoa: "; 
	gotoxy(72, 15); cout << "Nhap hoc ky   : "; 
	gotoxy(72, 16); cout << "Nhom          : "; 
	gotoxy(72, 17); cout << "Nhap ma MH    : "; 
}

void XoaKhungNhapLTC() {
	for(int i = 11; i <= 18; i++) {
		// ve duong doc ben trai va phai
		gotoxy(70, i); cout << "                                                                                     ";
	}
}

void KhungThemLTC(int maLTC) {
	gotoxy(85, 12); cout << " NHAP THONG TIN LOP TIN CHI MUON THEM ";
	
	// ve duong ngang
	for(int i = 70; i <= 140; i++) {
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 21); cout << char(205);
	}
	
	for(int i = 11; i <= 21; i++) {
		// ve duong doc ben trai va phai
		gotoxy(70, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
	} 
	
	gotoxy(140, 11); cout << char(187);
	gotoxy(140, 21); cout << char(188);
	
	gotoxy(70, 11); cout << char(201);
	gotoxy(70, 21); cout << char(200);
	
	gotoxy(72, 14); cout << "Ma LTC        : "; gotoxy(89, 14); cout << maLTC; 
	gotoxy(72, 15); cout << "Nhap ma MH    : "; 
	gotoxy(72, 16); cout << "Nhap nien khoa: "; 
	gotoxy(72, 17); cout << "Nham nhom     : "; 
	gotoxy(72, 18); cout << "Nhap hoc ky   : "; 
	gotoxy(72, 19); cout << "Nhap SV MAX   : ";
	gotoxy(72, 20); cout << "Nhap SV MIN   : ";
}

void KhungCapNhatLTC(int maLTC) {
	gotoxy(85, 12); cout << " NHAP THONG TIN LOP TIN CHI CAP NHAT MOI ";
	
	// ve duong ngang
	for(int i = 70; i <= 140; i++) {
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 21); cout << char(205);
	}
	
	for(int i = 11; i <= 21; i++) {
		// ve duong doc ben trai va phai
		gotoxy(70, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
	} 
	
	gotoxy(140, 11); cout << char(187);
	gotoxy(140, 21); cout << char(188);
	
	gotoxy(70, 11); cout << char(201);
	gotoxy(70, 21); cout << char(200);
	
	gotoxy(72, 14); cout << "Ma LTC        : "; gotoxy(89, 14); cout << maLTC; 
	gotoxy(72, 15); cout << "Nhap ma MH    : "; 
	gotoxy(72, 16); cout << "Nhap nien khoa: "; 
	gotoxy(72, 17); cout << "Nham nhom     : "; 
	gotoxy(72, 18); cout << "Nhap hoc ky   : "; 
	gotoxy(72, 19); cout << "Nhap SV MAX   : ";
	gotoxy(72, 20); cout << "Nhap SV MIN   : ";
}

void KhungNhapSV() {
	TextColor(241);
	gotoxy(87, 4); cout << "                                     ";
	gotoxy(87, 5); cout << "      NHAP DANH SACH SINH VIEN       ";
	gotoxy(87, 6); cout << "                                     ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 52; i <= 164; i++) {
		gotoxy(i, 9); cout << char(205);
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 27); cout << char(205);
	}
	
	for(int i = 10; i <= 26; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(52, i); cout << char(186);
		gotoxy(164, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(59, i); cout << char(186);
		gotoxy(83, i); cout << char(186);
		gotoxy(113, i); cout << char(186);
		gotoxy(133, i); cout << char(186);
		gotoxy(145, i); cout << char(186);
	} 
	
	// ve cac goc vuong
	gotoxy(164, 9); cout << char(187);
	gotoxy(164, 11); cout << char(185);
	gotoxy(164, 27); cout << char(188);
	
	gotoxy(52, 9); cout << char(201);
	gotoxy(52, 11); cout << char(204);
	gotoxy(52, 27); cout << char(200);
	
	gotoxy(59, 11); cout << char(206);
	gotoxy(83, 11); cout << char(206);
	gotoxy(113, 11); cout << char(206);
	gotoxy(133, 11); cout << char(206);
	gotoxy(145, 11); cout << char(206);
	
	gotoxy(59, 9); cout << char(203);
	gotoxy(83, 9); cout << char(203);
	gotoxy(113, 9); cout << char(203);
	gotoxy(133, 9); cout << char(203);
	gotoxy(145, 9); cout << char(203);
	
	gotoxy(59, 27); cout << char(202);
	gotoxy(83, 27); cout << char(202);
	gotoxy(113, 27); cout << char(202);
	gotoxy(133, 27); cout << char(202);
	gotoxy(145, 27); cout << char(202);
	
	gotoxy(54, 10); cout << "STT";
	gotoxy(64, 10); cout << "MA SO SINH VIEN";
	gotoxy(97, 10); cout << "HO";
	gotoxy(122, 10); cout << "TEN";
	gotoxy(138, 10); cout << "PHAI";
	gotoxy(153, 10); cout << "SDT";
}

void KhungCapNhatSV() {
	gotoxy(87, 12); cout << " NHAP THONG TIN SINH VIEN CAP NHAT MOI ";
	
	// ve duong ngang
	for(int i = 70; i <= 140; i++) {
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 19); cout << char(205);
	}
	
	for(int i = 11; i <= 19; i++) {
		// ve duong doc ben trai va phai
		gotoxy(70, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
	} 
	
	gotoxy(140, 11); cout << char(187);
	gotoxy(140, 19); cout << char(188);
	
	gotoxy(70, 11); cout << char(201);
	gotoxy(70, 19); cout << char(200);
	
	gotoxy(72, 14); cout << "Nhap ho  : ";
	gotoxy(72, 15); cout << "Nhap ten : ";
	gotoxy(72, 16); cout << "Nhap mssv: ";
	gotoxy(72, 17); cout << "Nhap SDT : ";
}

void KhungThemMH() {
	gotoxy(92, 12); cout << " NHAP THONG TIN MON HOC ";
	
	for(int i = 70; i <= 140; i++) {
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 18); cout << char(205);
	}
	
	for(int i = 11; i <= 18; i++) {
		// ve duong doc ben trai va phai
		gotoxy(70, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
	} 
	
	gotoxy(140, 11); cout << char(187);
	gotoxy(140, 18); cout << char(188);
	
	gotoxy(70, 11); cout << char(201);
	gotoxy(70, 18); cout << char(200);
	
	gotoxy(72, 14); cout << "Nhap ma MH  : "; 
	gotoxy(72, 15); cout << "Nhap ten MH : "; 
	gotoxy(72, 16); cout << "So TCLT     : "; 
	gotoxy(72, 17); cout << "So TCTH     : "; 
}

void KhungCapNhatMH() {
	gotoxy(89, 12); cout << " NHAP THONG TIN MON HOC CAP NHAT MOI ";
	
	for(int i = 70; i <= 140; i++) {
		gotoxy(i, 11); cout << char(205);
		gotoxy(i, 18); cout << char(205);
	}
	
	for(int i = 11; i <= 18; i++) {
		// ve duong doc ben trai va phai
		gotoxy(70, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
	} 
	
	gotoxy(140, 11); cout << char(187);
	gotoxy(140, 18); cout << char(188);
	
	gotoxy(70, 11); cout << char(201);
	gotoxy(70, 18); cout << char(200);
	
	gotoxy(72, 14); cout << "Nhap ma MH  : "; 
	gotoxy(72, 15); cout << "Nhap ten MH : "; 
	gotoxy(72, 16); cout << "So TCLT     : "; 
	gotoxy(72, 17); cout << "So TCTH     : "; 
}

void KhungDKLTC() {
	gotoxy(93, 3); cout << " THONG TIN SINH VIEN ";
	
	for(int i = 70; i <= 140; i++) {
		gotoxy(i, 2); cout << char(205);
		gotoxy(i, 10); cout << char(205);
	}
	
	for(int i = 2; i <= 10; i++) {
		// ve duong doc ben trai va phai
		gotoxy(70, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
	} 
	
	gotoxy(140, 2); cout << char(187);
	gotoxy(140, 10); cout << char(188);
	
	gotoxy(70, 2); cout << char(201);
	gotoxy(70, 10); cout << char(200);
}

void KhungXuatLTCDaMo() {
	TextColor(241);
	gotoxy(89, 14); cout << "                                       ";
	gotoxy(89, 15); cout << "      DANH SACH LOP TIN CHI DA MO      ";
	gotoxy(89, 16); cout << "                                       ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 52; i <= 180; i++) {
		gotoxy(i, 18); cout << char(205);
		gotoxy(i, 20); cout << char(205);
		gotoxy(i, 37); cout << char(205);
	}
	
	for(int i = 18; i <= 37; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(52, i); cout << char(186);
		gotoxy(180, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(58, i); cout << char(186);
		gotoxy(68, i); cout << char(186);
		gotoxy(80, i); cout << char(186);
		gotoxy(128, i); cout << char(186);
		gotoxy(140, i); cout << char(186);
		gotoxy(149, i); cout << char(186);
		gotoxy(157, i); cout << char(186);
		gotoxy(168, i); cout << char(186);
	}   
	
	// ve cac goc vuong
	gotoxy(180, 18); cout << char(187);
	gotoxy(180, 20); cout << char(185);
	gotoxy(180, 37); cout << char(188);
	
	gotoxy(52, 18); cout << char(201);
	gotoxy(52, 20); cout << char(204);
	gotoxy(52, 37); cout << char(200);
	
	gotoxy(58, 20); cout << char(206);
	gotoxy(68, 20); cout << char(206);
	gotoxy(80, 20); cout << char(206);
	gotoxy(128, 20); cout << char(206); 
	gotoxy(140, 20); cout << char(206); 
	gotoxy(149, 20); cout << char(206);
	gotoxy(157, 20); cout << char(206);
	gotoxy(168, 20); cout << char(186);
	
	gotoxy(58, 18); cout << char(203); gotoxy(58, 37); cout << char(202);
	gotoxy(68, 18); cout << char(203); gotoxy(68, 37); cout << char(202);
	gotoxy(80, 18); cout << char(203); gotoxy(80, 37); cout << char(202);
	gotoxy(128, 18); cout << char(203); gotoxy(128, 37); cout << char(202);
	gotoxy(140, 18); cout << char(203); gotoxy(140, 37); cout << char(202);
	gotoxy(149, 18); cout << char(203);	gotoxy(149, 37); cout << char(202);
	gotoxy(157, 18); cout << char(203);	gotoxy(157, 37); cout << char(202);
	gotoxy(168, 18); cout << char(203); gotoxy(168, 37); cout << char(202);
	
	gotoxy(54, 19); cout << "STT";
	gotoxy(61, 19); cout << "MA LOP";
	gotoxy(72, 19); cout << "MA MH";
	gotoxy(99, 19); cout << "TEN MON HOC";
	gotoxy(130, 19); cout << "NIEN KHOA";
	gotoxy(143, 19); cout << "NHOM";
	gotoxy(150, 19); cout << "HOC KY";
	gotoxy(158, 19); cout << "SV DA DK";
	gotoxy(169, 19); cout << "SLOT TRONG";
}

// khung xuat lop tin chi khong thoa dieu kien
void KhungXuatLTC_KTDK() {
	TextColor(241);
	gotoxy(85, 9); cout << "                                                      ";
	gotoxy(85, 10); cout << "      DANH SACH LOP TIN CHI KHONG THOA DIEU KIEN      ";
	gotoxy(85, 11); cout << "                                                      ";
	TextColor(7);
	
	// ve cac duong ngang
	for(int i = 52; i <= 160; i++) {
		gotoxy(i, 13); cout << char(205);
		gotoxy(i, 15); cout << char(205);
		gotoxy(i, 32); cout << char(205);
	}
	
	for(int i = 13; i <= 32; i++) {
		 
		// ve duong doc ben trai va phai
		gotoxy(52, i); cout << char(186);
		gotoxy(160, i); cout << char(186);
		 
		// ve doc xuong phan chia giua cac cot
		gotoxy(59, i); cout << char(186);
		gotoxy(72, i); cout << char(186);
		gotoxy(92, i); cout << char(186);
		gotoxy(108, i); cout << char(186);
		gotoxy(119, i); cout << char(186);
		gotoxy(129, i); cout << char(186);
		gotoxy(139, i); cout << char(186);
		gotoxy(148, i); cout << char(186);
	}   
	
	// ve cac goc vuong
	gotoxy(160, 13); cout << char(187);
	gotoxy(160, 15); cout << char(185);
	gotoxy(160, 32); cout << char(188);
	
	gotoxy(52, 13); cout << char(201);
	gotoxy(52, 15); cout << char(204);
	gotoxy(52, 32); cout << char(200);
	
	gotoxy(59, 15); cout << char(206);
	gotoxy(72, 15); cout << char(206);
	gotoxy(92, 15); cout << char(206);
	gotoxy(108, 15); cout << char(206); 
	gotoxy(119, 15); cout << char(206); 
	gotoxy(129, 15); cout << char(206);
	gotoxy(139, 15); cout << char(206);
	gotoxy(148, 15); cout << char(206);
	
	gotoxy(59, 13); cout << char(203); gotoxy(59, 32); cout << char(202);
	gotoxy(72, 13); cout << char(203); gotoxy(72, 32); cout << char(202);
	gotoxy(92, 13); cout << char(203); gotoxy(92, 32); cout << char(202);
	gotoxy(108, 13); cout << char(203); gotoxy(108, 32); cout << char(202);
	gotoxy(119, 13); cout << char(203); gotoxy(119, 32); cout << char(202);
	gotoxy(129, 13); cout << char(203);	gotoxy(129, 32); cout << char(202);
	gotoxy(139, 13); cout << char(203);	gotoxy(139, 32); cout << char(202);
	gotoxy(148, 13); cout << char(203); gotoxy(148, 32); cout << char(202);
	
	gotoxy(54, 14); cout << "STT";
	gotoxy(63, 14); cout << "MA LOP";
	gotoxy(80, 14); cout << "MA MH";
	gotoxy(96, 14); cout << "NIEN KHOA";
	gotoxy(112, 14); cout << "NHOM";
	gotoxy(122, 14); cout << "HOC KY";
	gotoxy(132, 14); cout << "SV MAX";
	gotoxy(141, 14); cout << "SV MIN";
	gotoxy(150, 14); cout << "SV DA DK";
	
	TextColor(116);
	gotoxy(53, 38); cout << "  BAN CO THAT SU MUON HUY CAC LOP KHONG DU DIEU KIEN?  ";
	gotoxy(53, 39); cout << "              Co: (Bam y), Khong: (Bam n)              ";
	TextColor(7);
	
	gotoxy(163, 21); TextColor(116); cout << "UP   :"; TextColor(12); cout << " LEN";
	gotoxy(163, 22); TextColor(116); cout << "LEFT :"; TextColor(12); cout << " TRAI";
	gotoxy(163, 23); TextColor(116); cout << "RIGHT:"; TextColor(12); cout << " PHAI";
	gotoxy(163, 24); TextColor(116); cout << "DOWN :"; TextColor(12); cout << " XUONG";
	
	gotoxy(57, 34); TextColor(116); cout << "Bam C/c: "; 
	gotoxy(65, 34); TextColor(12); cout << "Tiep tuc viec xoa"; TextColor(7);
	gotoxy(57, 35); TextColor(116); cout << "ESC    : "; 
	gotoxy(65, 35); TextColor(12); cout << "Ket thuc viec xoa"; TextColor(7);
	
	gotoxy(168, 17); cout << char(30);
	gotoxy(166, 18); cout << char(17);
	gotoxy(170, 18); cout << char(16);
	gotoxy(168, 19); cout << char(31);
}

void KhungHuongDan() {
	TextColor(116);
 
	gotoxy(93, 9);  cout << "           ";
	gotoxy(93, 10); cout << "           ";
	gotoxy(93, 11); cout << "           ";
	gotoxy(93, 12); cout << "           ";
	gotoxy(93, 13); cout << "           ";
 
	gotoxy(98, 10); cout << char(30);
	gotoxy(96, 11); cout << char(17);
	gotoxy(100, 11); cout << char(16);
	gotoxy(98, 12); cout << char(31);
 
 	gotoxy(79, 16); cout << "                                         ";
	gotoxy(79, 17); cout << "  DUNG 4 PHIM MUI TEN DE DI CHUYEN MENU  ";
	gotoxy(79, 18); cout << "           BAM ENTER DE CHON             ";
	gotoxy(79, 19); cout << "                                         ";
	TextColor(7);
	
	TextColor(225); gotoxy(93, 21); cout << "ENTER:"; TextColor(7); gotoxy(100, 21); cout << "CHON ";
	
	TextColor(225); gotoxy(93, 22); cout << "UP   :"; TextColor(7); gotoxy(100, 22); cout << "LEN  ";
	TextColor(225); gotoxy(93, 23); cout << "LEFT :"; TextColor(7); gotoxy(100, 23); cout << "TRAI ";
	TextColor(225); gotoxy(93, 24); cout << "RIGHT:"; TextColor(7); gotoxy(100, 24); cout << "PHAI ";
	TextColor(225); gotoxy(93, 25); cout << "DOWN :"; TextColor(7); gotoxy(100, 25); cout << "XUONG";
}

void XoaKhungHuongDan() {
	gotoxy(93, 9);  cout << "                                                                  ";
	gotoxy(93, 10); cout << "                                                                  ";
	gotoxy(93, 11); cout << "                                                                  ";
	gotoxy(93, 12); cout << "                                                                  ";
	gotoxy(93, 13); cout << "                                                                  ";
 
	gotoxy(98, 10); cout << "                                                                  ";
	gotoxy(96, 11); cout << "                                                                  ";
	gotoxy(100, 11); cout << "                                                                  ";
	gotoxy(98, 12); cout << "                                                                  ";
 
 	gotoxy(79, 16); cout << "                                                                  ";
	gotoxy(79, 17); cout << "                                                                  ";
	gotoxy(79, 18); cout << "                                                                  ";
	gotoxy(79, 19); cout << "                                                                  ";
	
	gotoxy(93, 21); cout << "                                                                  ";
	
	gotoxy(93, 22); cout << "                                                                  ";
	gotoxy(93, 23); cout << "                                                                  "; 
	gotoxy(93, 24); cout << "                                                                  "; 
	gotoxy(93, 25); cout << "                                                                  ";
}

void XoaKhungXuatLTC() {
	for(int i = 4; i <= 26; i++) {
		gotoxy(52, i); cout << "                                                                                                                        ";
	} 
}

void XoaKhungDSL() {
	for(int i = 4; i <= 28; i++) {
		gotoxy(52, i); cout << "                                                                                                                         ";
	}
}

void XoaKhungDSSV() {
	for(int i = 4; i <= 29; i++) {
		gotoxy(52, i); cout << "                                                                                                                         ";
	} 
}

void XoaKhungNhapDiem() {
	for(int i = 7; i <= 34; i++) {
		gotoxy(60, i); cout << "                                                                                                                         ";
	} 
}

void XoaKhungXuatLTC_KTDK() {
	for(int i = 9; i <= 34; i++) {
		gotoxy(52, i); cout << "                                                                                                                              ";
	} 
}
