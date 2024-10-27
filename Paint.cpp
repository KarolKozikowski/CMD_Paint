#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <chrono>
#include <windows.h>
#include <thread>
#define usleep(usec) std::this_thread::sleep_for(std::chrono::microseconds(usec))
using namespace std;

int key_Erase = 0;
int key_Write = 0;
int index_Color = 7;
int symbol_Type = 0;
bool is_Boxed;
bool is_Running = true;

void gotoxy(int x, int y){
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void screensize(int& width, int& height) {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		width = (int)(csbi.srWindow.Right-csbi.srWindow.Left+1);
		height = (int)(csbi.srWindow.Bottom-csbi.srWindow.Top+1);
	}
void color (int c){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, c);
	index_Color = c;
}
int custom (int x, int y){
	int a;
	color (7);
	gotoxy (39, 0);
	cout << "   ";
	gotoxy (39, 0);
	cin >> a;
	gotoxy (x, y);
	return a;
}
char symbol (int a){
	char b;
	switch(a){
		case 0:
			b = '*';
			break;
		case 1:
			b = '#';
			break;
		case 2:
			b = '0';
			break;
		case 3:
			b = '-';
			break;
		case 4:
			b = '+';
			break;
		case 5:
			b = ' ';
			break;
	}
	return b;
}
void brush (int size, int x, int y){
	for (int i=1; i<=(size*2)+1; i++){
		gotoxy (x-size, y-(size+1)+i);
		for (int j=0; j<(size*2)+1; j++){
			key_Erase ? cout << symbol(5) : cout << symbol(symbol_Type);
		}
	}
}
void start_Menu(){
	color(11);
	gotoxy(1, 0);
	cout << "____   ___   _   _    ";
	gotoxy(1, 1);
	cout << "| _ | | _ | | | | \\  ||";
	gotoxy(1, 2);
	cout << "||_|| ||_|| | | ||\\\\ ||";
	gotoxy(1, 3);
	cout << "| __| | _ | | | || \\\\||";
	gotoxy(1, 4);
	cout << "||    || || |_| ||  \\_|";
	gotoxy(25, 0);
	color(3);
	cout << " ____";
	gotoxy(25, 1);
	cout << "|_  _|";
	gotoxy(25, 2);
	cout << "  ||";
	gotoxy(25, 3);
	cout << "  ||";
	gotoxy(25, 4);
	cout << "  ||";
	gotoxy(1, 5);
	color(8);
	cout << "v0.29";            //update 
	color (7);
	int width=0, height=0;
	screensize(width, height);
	int x = width/2, y = height/2;
	gotoxy(x-10, y-1);
	cout << "CHOOSE CANVAS TYPE:";
	gotoxy(x-10, y+1);
	cout << "BOXED [1]   FREE [2]";
	gotoxy(0, height-2);
	color(4);
	cout << "QUIT:[Q]";
	char number;
	while(number != '1' && number != '2' && number != 'q'){
		number = getch();
	}
	system("cls");
	if(number == 'q'){
		is_Running = false;
		return;
	}
	number == '1' ? is_Boxed = true : is_Boxed = false;
	if(!is_Boxed){
		gotoxy(x-17, y-1);
		color(15);
		cout << "Set your console size as you like.";
		gotoxy(x-12, y);
		color(9);
		cout << "Full screen recommended.";
		gotoxy(x-19, y+1);
		color(8);
		cout << "Press any key (except 'q') to continue.";
		gotoxy(0, height-2);
		color (4);
		cout << "Return:[Q]";
		color (7);
		gotoxy(x+12, y);
		int temp = 0;
		while (temp==0) temp = getch();
		system("cls");
		if(temp == 'q') start_Menu();
	}
}
void UI (int x, int y){
	gotoxy(0, 0);
	int temp_Color = index_Color;
	color (7);
	cout << "Draw:   | Erase:   | Symbol:  | Color: ";
	for (int i=0; i<51; i++){
		cout << " ";
	}
	if(is_Boxed){
		cout << "[-][ ][";
		color (4);
		cout << "X";
		color (7);
		cout << "]|" << endl;
		for (int j=0; j<99; j++){
			cout << "_";
		}
		cout << "|" << endl;
		for(int k=0; k<23; k++){
			for(int j=0; j<99; j++){
				cout << " ";
			}
			cout << "|" << endl;
		}
		for (int j=0; j<99; j++){
			cout << "_";
		}
		cout << "|" << endl;
	}
	else{
		int width=0, height=0;
		screensize(width, height);
		gotoxy(0, height-2);
	}
	cout << "Move:[W][A][S][D]  Draw:[R]  Erase:[E]  Clear:[C]  Color:[1-9]  Custom:[0]->[enter]  Symbol:[,][.]" << endl;
	color (4);
	cout << "Exit:[Q]";
	color (temp_Color);
	gotoxy(x, y);
}
void update_UI (int x, int y){
	bool is_Draw;
	bool is_Erase;
	int temp_Color = index_Color;
	key_Write ? is_Draw = true : is_Draw = false;
	gotoxy (5, 0);
	color(8);
	if (is_Draw){
		cout << "on ";
	}
	else{
		cout << "off";
	}
	key_Erase ? is_Erase = true : is_Erase = false;
	gotoxy (16, 0);
	if (is_Erase){
		cout << "on ";
	}
	else{
		cout << "off";
	}
	gotoxy (29, 0);
	cout << symbol (symbol_Type);
	gotoxy (39, 0);
	color(temp_Color);
	cout << index_Color;
	gotoxy (x, y);
}
void welcome (){
	gotoxy (42, 13);
	color (2);
	cout << "Welcome to Paint!";
	int temp = 0;
	while (temp==0) temp = getch();
	color (7);
	system ("cls");
	UI(4, 2);

}
void paint(){
	int width=0, height=0;
	screensize(width, height);
	int x, y;
	if(is_Boxed){
		x = 49, y = 13;
	}
	else{
		x = width/2, y = height/2-1;
	}
	int brush_Size = 0;
	UI(x, y);
	if(is_Boxed) welcome();
	update_UI (x, y);
	int wLim, sLim, aLim, dLim;
	is_Boxed ? wLim=2 : wLim=1;
	is_Boxed ? sLim=24 : sLim=height-3;
	aLim=0;
	is_Boxed ? dLim=98 : dLim=width-1;
	for (int key = 0; key != 'q'; key = kbhit() ? getch() : 0){
		switch (key) {
			case 'w':
				y > wLim ? y-- : 0;
				break;
			case 's':
				y < sLim ? y++ : 0;
				break;
			case 'a':
				x > aLim ? x-- : 0;
				break;
			case 'd':
				x < dLim ? x++ : 0;
				break;
			case 'r':
				key_Write == 0 ? key_Write++ : key_Write--;
				key_Erase = 0;
				update_UI (x, y);
				break;
			case 'e':
				key_Erase == 0 ? key_Erase++ : key_Erase--;
				key_Write = 0;
				update_UI (x, y);
				break;
			case 'c':
				system("cls");
				UI(x, y);
				update_UI (x, y);
				break;
			case '1':
				color (1);
				update_UI (x, y);
				break;
			case '2':
				color (2);
				update_UI (x, y);
				break;
			case '3':
				color (3);
				update_UI (x, y);
				break;
			case '4':
				color (4);
				update_UI (x, y);
				break;
			case '5':
				color (5);
				update_UI (x, y);
				break;
			case '6':
				color (6);
				update_UI (x, y);
				break;
			case '7':
				color (7);
				update_UI (x, y);
				break;
			case '8':
				color (8);
				update_UI (x, y);
				break;
			case '9':
				color (9);
				update_UI (x, y);
				break;
			case '0':
 				color (custom(x, y));
 				update_UI (x, y);
 				break;
 			case '.':
 				symbol_Type < 4 ? symbol_Type++ : symbol_Type = 0;
 				update_UI (x, y);
 				break;
 			case ',':
 				symbol_Type > 0 ? symbol_Type-- : symbol_Type = 4;
 				update_UI (x, y);
 				break;
 			case '[':
 				if(brush_Size > 0){
 					brush_Size--;
 					if(is_Boxed){
						aLim--;
 						wLim--;
 						dLim++;
 						sLim++;
 					}
				 }
 				break;
 			case ']':
 				if(is_Boxed ? brush_Size < 3 : brush_Size < 6 && y > wLim && y < sLim && x > aLim && x < dLim){
 					brush_Size++;
 					if(is_Boxed){
 						aLim++;
 						wLim++;
 						dLim--;
 						sLim--;
 					}
				 }
 				break;
		}
		if (key_Write || key_Erase){
			gotoxy (x, y);
			brush (brush_Size, x, y);
		}
		else{
			gotoxy(x, y);
			cout << "";
		}
		if(!is_Boxed){ //updates movement limits in case screensize changes
			width=0;
			height=0;
			wLim=1;
			sLim=0;
			dLim=0;
			aLim=0;
			screensize(width, height);
			dLim=width-1;
			sLim=height-3;
			wLim+=brush_Size;
			dLim-=brush_Size;
			sLim-=brush_Size;
			aLim+=brush_Size;
		}
	}
	return;
}
int main (){
	while(is_Running){
		system ("cls");
		start_Menu();
		if(is_Running) paint();
	}
}