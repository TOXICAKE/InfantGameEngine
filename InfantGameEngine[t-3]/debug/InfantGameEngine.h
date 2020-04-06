#include<iostream> 
#include<fstream> 
#include<stdlib.h>
#include<random>
#include<ctime>
#include<Windows.h>
#include<string>
#include<conio.h>
using namespace std;
#pragma  comment(lib,"InfantGameEngine.lib")
const int SCENERY_hight = 20;//max 31
const int SCENERY_width = 80;//max 120
enum SettingOption
{
	off = 0,
	on
};
enum DirectionOfRotation
{
	_cw = 0,
	anti_cw
};
enum GetintOption
{
	En_id = 0,
	En_x,
	En_y,
	En_color,
	En_GroupId,
	En_collision,
	En_Key
};
enum Direction
{
	_up = 1,
	_down,
	_left,
	_right,
	_left_up,
	_right_up,
	_right_down,
	_left_down,
	_NoDirection

};
class SCENERY;
class ENTITY;
class GROUPDATA {
public:
	int EntityId = 0;
	ENTITY* pEntity = NULL;
	GROUPDATA* next = NULL;
	GROUPDATA(int _EntityId, ENTITY* _pEntity);
};
class GROUP {
	friend class SCENERY;
private:
	GROUPDATA* pHeadGroupData = new GROUPDATA(0, NULL), * pLastGroupData = pHeadGroupData;
	GROUP* next = NULL;
	int DataSize = 0, id = 0;

};
class ENTITY {

private:
	int id, x = 1, y = 1, color = 0, collision = on, GroupId = 0, Key = 0;
	char _char = ' ';
	ENTITY* next = NULL, * OEntity = NULL;
	ENTITY(int _id, int _X, int _Y, int _color, char __char, int _Collision, int _Key = 0, ENTITY * _OEntity = NULL);

	friend class SCENERY;

};
class SCENERY {
private:
	int x = 1, y = 1;
	friend class ENTITY;
	ENTITY* scenery_pEntity[SCENERY_width+1][SCENERY_hight+1] = { 0 };//No Zero No 00000!!
	GROUP* HeadGroup = new GROUP;
	GROUP* pLastGroup = HeadGroup;
	ENTITY* HeadEntity = new ENTITY(0, 0, 0, 0, char(32), off);
	ENTITY* pLastEntity = HeadEntity;
	int TotalEntity = 0, TotalGroup = 0;

public:
	ENTITY* En_GoTo(int entity_id, int x, int y);
	ENTITY* En_GoTo(ENTITY* entity, int x, int y);
	int En_MaxMoveDistance(int entity_id, Direction _direction);
	int En_MaxMoveDistance(ENTITY* pEntity, Direction _direction);
	ENTITY* En_Move(int entity_id, Direction _direction, int _distance);
	ENTITY* En_Move(ENTITY* pEntity, Direction _direction, int _distance);
	ENTITY* GETpENTITY(int entity_id);
	GROUP* GETpGROUP(int group_id);
	SCENERY(int _x, int _y);
	int CreateEntity(int _x, int _y, int _color, char __char, SettingOption _colliction, int _Key = 0);
	int CreateGroup();
	void AddEnToGroup(int GroupId, int EntityId);
	void DelEnToGroup(int EntityId);
	int Gr_Move(int group_id, Direction _direction, int _distance);
	int GETint(int EntityId, GetintOption _selection);
	char GETchar(int EntityId);
	ENTITY* GETdownENTITY(int EntityId);
	int GETint(ENTITY* pEntity, GetintOption _selection);
	char GETchar(ENTITY* pEntity);
	void En_Fresh(ENTITY* pEntity, int _color, char __char, int _Collision, int _Key);
	void En_Fresh(int EntityId, int _color, char __char, int _Collision, int _Key);
	ENTITY* GETdownENTITY(ENTITY* pEntity);
	ENTITY* GETpENTITY(int _x, int _y);
	ENTITY* Gr_GETpENTITY(int _GroupId, int Gr_EntityId);
	int TotalEn();
	int TotalGr();
	void DRAW(int color, char _chr);
	int Gr_Spin(int _GroupId, int _x, int _y, DirectionOfRotation _RotationDirection);
	int Gr_TotalEn(int _GroupId);
	int GETentity(int _x, int _y);
};
int _abs(int _num);