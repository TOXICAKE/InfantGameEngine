//内置HELP手册，调用函数_HELP_查看
#include<iostream> 
#include<fstream> 
#include<stdlib.h>
#include<random>
#include<ctime>
#include<Windows.h>
#include<string>
#include<conio.h>
#define TAB 101
#pragma  comment(lib,"XzyGraphics.lib")
using namespace std;
enum
{
	_Gray = 0,
	_Red,
	_Yellow,
	_Green,
	_GreenBlue,
	_Blue,
	_Violet,
	H_Gray = 10,
	H_Red,
	H_Yellow,
	H_Green,
	H_GreenBlue,
	H_Blue,
	H_Violet,
};
struct DATAOFFORM
{
	int value;
	string OptionName;
	DATAOFFORM* next = NULL;
};
struct RECORD {

	int PartI_Color = 0, PartII_Color = 0, PartIII_Color = 0;
	string PartI = "", PartII = "", PartIII = "",ExtraMessage="";
	RECORD* last = NULL, * next = NULL;

};
class FORM
{
private:
	DATAOFFORM* DataHead = NULL;
public:
	string title = "Here Is Title", FormStr = "+", OptionStr = "O", ClearStr = " ";
	int x1, y1, x2, y2, TitleColor = 0, FIX_x = 2, FIX_y = 1;
	int optionX, optionY;
	FORM(int Inx1, int Iny1, int Inx2, int Iny2, int InoptionX, int InoptionY);
	void CLEAR();
	void GETOPTIONXY(int id,int& RETURNX, int& RETURNY);
	string GETOPTIONNAME(int id);
	void SETOPTIONNAME(int id, string InName);
	void SETVALUE(int id, int InValue);
	int GETVALUE(int id);
	int SELECTION(int COLOR_form, int COLOR_option, int COLOR_str);
	void TEST();
	void DRAW(int COLOR_form, int COLOR_option, int COLOR_str);
};
class SCROLL_LIST {
private:
	int total = 0, StrLimit;
	RECORD FirstRecord;
public:
	int x, y, MaxNum;
	string title = "Here Is Title", str = "+", ClearStr = " ";
	int TitleColor = 0;
	SCROLL_LIST(int _x, int _y, int _StrLimit, int _MaxNum);
	void DRAW(int color);
	void DISPLAY(int _StartId, int _EndId);
	void CREATERECORD(int _ColorI, string _PartI, int _ColorII = 0, string _PartII = "", int _ColorIII = 0, string _PartIII = "");
	int ROLL(int SqureColor, int PointColor);
	RECORD GETRECORD(int id);
	void CLEAR();
};
inline void GOTOXY(int x, int y);
void WSIZE(int a);
void SETCOLOR(int color, int x, int y);
void ANYLINE(int color, int x, int y, int l, string str, int PianYi);
void VERTICALLINE(int color, int x, int y, int l, string str);
void DRAW_SQURE(int x1, int y1, int x2, int y2, int color, string str, int XPianYi);
void GUANGBIAO(int a);
void SAY(int color, int x, int y, string word);
string ENTER(int color, int x, int y, int lenth);
void _HELP_();
/*
 * Copyright (c) by XuZiyi/(N0P3). All rights reserved.
 * Consult your license regarding permissions and restrictions.
V2.2:20200202
*/
