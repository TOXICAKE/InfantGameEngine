#include"XzyGraphics.h"
#include"InfantGameEngine.h"
SCENERY Scenery(21, 8);
void Collision(int _GroupId,SettingOption _option) {
	int O_Color, O_Key;
	char O_Char;
	for (int i = 1; i <= Scenery.Gr_TotalEn(_GroupId); i += 1) {
		O_Color = Scenery.GETint(Scenery.Gr_GETpENTITY(_GroupId, i), En_color);
		if (O_Color >= 10) {
			O_Color -= 10;
		}
		else {
			O_Color += 10;
		}
		O_Key = Scenery.GETint(Scenery.Gr_GETpENTITY(_GroupId, i), En_color);
		O_Char = Scenery.GETchar(Scenery.Gr_GETpENTITY(_GroupId, i));
		Scenery.En_Fresh(Scenery.Gr_GETpENTITY(_GroupId, i), O_Color, O_Char, _option, O_Key);
	}
}
void Paint(int PenId,int _GroupId,int &_SpinEn) {
	int Entity = PenId;
	int _color = Scenery.GETint(PenId,En_color);
	while (1) {
		if (_kbhit()) {
			switch (_getch()) {
			case's':
				Scenery.En_Move(PenId,_down, 1);
				break;
			case 'w':
				Scenery.En_Move(PenId, _up, 1);
				break;
			case'a':
				Scenery.En_Move(PenId, _left, 1);
				break;
			case 'd':
				Scenery.En_Move(PenId, _right, 1);
				break;
			case 'i':
				if (_SpinEn == 0) {
					SAY(11, 105, 10, "没有设定中心");
				}
				else {
					Scenery.En_Fresh(PenId, _color, ' ', off, 200);
					return;
				}
				break;
			case ' ':
				Entity = Scenery.GETentity(Scenery.GETint(PenId, En_x), Scenery.GETint(PenId, En_y) - 1);
				if ( Entity!= -1) {
					if(Scenery.GETint(Entity,En_GroupId)==_GroupId){
						if (_SpinEn != 0) {
							Scenery.En_Fresh(_SpinEn, _color, '*', on, 20);
						}
						_SpinEn = Entity;
						Scenery.En_Fresh(Entity, 10, '+', on, 20);
						SAY(11, 105, 10, "            ");
					}
				}
				break;
			case 9:
				_color += 1;
				if (_color > 16) {
					_color = 10;
				}
				Scenery.En_Fresh(PenId, _color, '^', off, 200);
				break;
			case 13://enter
				if (Scenery.GETentity(Scenery.GETint(PenId, En_x), Scenery.GETint(PenId, En_y) - 1) == -1) {
					Entity = Scenery.CreateEntity(Scenery.GETint(PenId, En_x), Scenery.GETint(PenId, En_y) - 1, _color, '*', on, 20);
					Scenery.AddEnToGroup(_GroupId, Entity);
				}
				break;
			}
		}
	}
}
int PackUp(int StartId, int EndId) {
	int NewGroupId = Scenery.CreateGroup();
	for (int i = StartId; i <= EndId; i += 1) {
		Scenery.AddEnToGroup(NewGroupId, i);
	}
	return NewGroupId;
}
int CreateGe(int id, int _x, int _y,int _color,int &_SpinEn,char _char,int var1=8) {
	int StartNum = Scenery.TotalEn()+1;
	switch (id) {
	case 0:
		_SpinEn=Scenery.CreateEntity(_x+var1/4, _y+(var1/2)-1 , _color, ' ', on, id + 2);
		for (int i = 0; i < var1-1; i += 1) {
			Scenery.CreateEntity(_x , _y + i, _color, _char, on, id + 2);
		}
		for (int i = 0; i < (var1/2)-1; i += 1) {
			Scenery.CreateEntity(_x+1, _y+1, _color,_char, on, id + 2);
			_x += 1;
			_y += 1;
		}
		for (int i = 0; i<(var1/2)-2; i += 1) {
			Scenery.CreateEntity(_x -1, _y + 1, _color, _char, on, id + 2);
			_x -= 1;
			_y += 1;
		}
		
		break;
	case 1:
		_SpinEn = Scenery.CreateEntity(_x + 1, _y + 2, _color,' ', on, id + 2);
		Scenery.CreateEntity(_x, _y, _color, _char, on, id + 2);
		Scenery.CreateEntity(_x , _y + 1, _color, _char, on, id + 2);
		Scenery.CreateEntity(_x, _y + 2, _color, _char, on, id + 2);
		Scenery.CreateEntity(_x, _y+3, _color, _char, on, id + 2);
		Scenery.CreateEntity(_x, _y + 4, _color, _char, on, id + 2);
		Scenery.CreateEntity(_x+1, _y+1, _color, _char, on, id + 2);
		Scenery.CreateEntity(_x+2, _y+2, _color, _char, on, id + 2);
		Scenery.CreateEntity(_x+1, _y+3, _color, _char, on, id + 2);
		break;
	case 2://squre
		_SpinEn= Scenery.CreateEntity(_x + var1/2, _y + var1/2, 10, '+', on, id + 2);
		for (int i = 0; i < var1; i += 1) {//横
			Scenery.CreateEntity(_x + i, _y, _color, _char, on, id + 2);
			Scenery.CreateEntity(_x + i+1, _y+var1, _color, _char, on, id + 2);
		}
		for (int i = 0; i < var1; i += 1) {//竖
			Scenery.CreateEntity(_x , _y+1+i, _color, _char, on, id + 2);
			Scenery.CreateEntity(_x + var1, _y +i, _color, _char, on, id + 2);
		}
		break;
	case 3:

		break;
	}
	return PackUp(StartNum, Scenery.TotalEn());
}
int main() {
	int Pen,MaxGe=6;
	int SpinEn[100]={ 0 };
	int NowSelection = CreateGe(0, 1, 1, 12,SpinEn[1], '*',10);//1
	CreateGe(1, 1, 14, 15, SpinEn[2], '*', 0);//2
	CreateGe(0, 10, 1, 11, SpinEn[3], '*', 10);//3
	CreateGe(1, 5, 14, 14, SpinEn[4], '*', 0);//4
	CreateGe(0, 20, 1, 16, SpinEn[5], '*', 8);//5
	NowSelection = CreateGe(2, 30, 1, 13, SpinEn[6], '*', 5);//6
	GUANGBIAO(0);
	Scenery.DRAW(10, 'H');
	Scenery.CreateEntity(75, 17, 16, 'T', off);
	Scenery.CreateEntity(76, 17, 16, '0', off);
	Scenery.CreateEntity(77, 17, 16, 'K', off);
	Scenery.CreateEntity(78, 17, 16, 'I', off);
	Pen=Scenery.CreateEntity(30, 16, 13, ' ', off, 200);//画笔
	SAY(14, 95, 24, "N0P3");
	SAY(15, 3, 5, "[拼图模式]");
	GOTOXY(10, 2);
	cout << MaxGe;
	cout << "巧板";
	SAY(10, 20, 2, "wasd 移动");
	SAY(15, 30, 2, "q 逆时针旋转，e 顺时针旋转");
	SAY(12, 20, 3, "g 关闭碰撞 i 创建自定义图案");
	SAY(13, 20, 4, "TAB 切换积木");
	while (1) {
		if (_kbhit()) {
			switch (_getch()) {
			case'q':
				Scenery.Gr_Spin(NowSelection, Scenery.GETint(SpinEn[NowSelection],En_x), Scenery.GETint(SpinEn[NowSelection], En_y), anti_cw);
				break;
			case'e':
				Scenery.Gr_Spin(NowSelection, Scenery.GETint(SpinEn[NowSelection], En_x), Scenery.GETint(SpinEn[NowSelection], En_y), _cw);
				break;
			case's':
				Scenery.Gr_Move(NowSelection, _down, 1);
				break;
			case 'w':
				Scenery.Gr_Move(NowSelection, _up, 1);
				break;
			case'a':
				Scenery.Gr_Move(NowSelection, _left, 1);
				break;
			case 'd':
				Scenery.Gr_Move(NowSelection, _right, 1);
				break;
			case 'g':
				if (Scenery.GETint(SpinEn[NowSelection], En_collision) == on) {
					Collision(NowSelection, off);
				}
				else {
					Collision(NowSelection, on);
				}
				break;
			case 'i':
				SAY(12, 3, 5, "[画笔模式]");
				SAY(10, 20, 2, "wasd 移动画笔,ENTER键画画            ");
				SAY(12, 20, 3, "空格键设定中心 i 保存并退出画图       ");
				SAY(13, 20, 4, "TAB 切换颜画笔色       ");
				Scenery.En_Fresh(SpinEn[NowSelection], 10, '\0', Scenery.GETint(SpinEn[NowSelection], En_collision), NowSelection + 2);
				Scenery.En_Fresh(Pen, 14, '^', off, 200);
				NowSelection = Scenery.CreateGroup();
				Paint(Pen,NowSelection,SpinEn[NowSelection]);
				MaxGe += 1;
				SAY(15, 3, 5, "[拼图模式]");
				GOTOXY(10, 2);
				cout << MaxGe;
				cout << "巧板";
				SAY(10, 20, 2, "wasd 移动 ");
				SAY(15, 30, 2, "q 逆时针旋转，e 顺时针旋转");
				SAY(12, 20, 3, "g 关闭碰撞 i 创建自定义图案       ");
				SAY(13, 20, 4, "TAB 切换积木       ");
				break;
			case 9://[TAB]
				Scenery.En_Fresh(SpinEn[NowSelection], 10, '\0', Scenery.GETint(SpinEn[NowSelection],En_collision), NowSelection + 2);
				NowSelection += 1;
				if (NowSelection >= MaxGe+1) {
					NowSelection = 1;
				}
				Scenery.En_Fresh(SpinEn[NowSelection], 10, '+', Scenery.GETint(SpinEn[NowSelection], En_collision), NowSelection + 2);
				break;
			}
		}
	}
}