//InfantGameEngine strat``2020.02.16
//Developed by N0P3
//如果你觉得有趣，就给它一颗星吧~
#include"XzyGraphics.h"
const int SCENERY_hight = 20;//max 31
const int SCENERY_width = 80;//max 120
enum SettingOption
{
	off = 0,
	on
};
enum DirectionOfRotation
{
	_cw=0,
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
	void En_Fresh(int EntityId, int _color, char __char, int _Collision, int _Key);
	void En_Fresh(ENTITY* pEntity, int _color, char __char, int _Collision, int _Key);
	ENTITY* GETdownENTITY(ENTITY* pEntity);
	ENTITY* GETpENTITY(int _x, int _y);
	ENTITY* Gr_GETpENTITY(int _GroupId, int Gr_EntityId);
	int Gr_Spin(int _GroupId, int _x, int _y, DirectionOfRotation _RotationDirection);
	void DRAW(int color,char _chr);
	int TotalEn();
	int TotalGr();
};
ENTITY* SCENERY::En_GoTo(int entity_id, int _x, int _y) {
	ENTITY* pEntity = GETpENTITY(entity_id);
	return En_GoTo(pEntity, _x, _y);
}
ENTITY* SCENERY::En_GoTo(ENTITY* pEntity, int _x, int _y) {
	string str = "";
	ENTITY entity = *pEntity;
	if (pEntity->OEntity != NULL) {
		str += pEntity->OEntity->_char;
		scenery_pEntity[pEntity->x][pEntity->y] = pEntity->OEntity;
		SAY(pEntity->OEntity->color, x + pEntity->OEntity->x - 1, y + pEntity->OEntity->y - 1, str);//复原原始位置
	}
	else {
		scenery_pEntity[pEntity->x][pEntity->y] = pEntity->OEntity;
		SAY(0, x + pEntity->x - 1, y + pEntity->y - 1, " ");
	}
	str = "";
	str += pEntity->_char;
	pEntity->x = _x;
	pEntity->y = _y;
	pEntity->OEntity = scenery_pEntity[pEntity->x][pEntity->y];
	scenery_pEntity[pEntity->x][pEntity->y] = pEntity;
	SAY(pEntity->color, x + pEntity->x - 1, y + pEntity->y - 1, str);
	return pEntity->OEntity;
}
int SCENERY::En_MaxMoveDistance(int entity_id, Direction _direction) {

	ENTITY* pEntity = GETpENTITY(entity_id);
	return En_MaxMoveDistance(pEntity, _direction);
}
int SCENERY::En_MaxMoveDistance(ENTITY* pEntity, Direction _direction) {
	int Actual_x = 0, Actual_y = 0;
	switch (_direction) {
	case _up:
		if (pEntity->collision == on) {//考虑碰撞
			for (int i = 1; i < pEntity->y; i += 1) {
				if (pEntity->y - i > 0 && (scenery_pEntity[pEntity->x][pEntity->y - i] == NULL || (scenery_pEntity[pEntity->x][pEntity->y - i]->collision == off || scenery_pEntity[pEntity->x][pEntity->y - i]->GroupId == pEntity->GroupId))) {//在布景内且检测碰撞层为无碰撞(可移动)

					Actual_y -= 1;//实际纵向可移动距离+1

				}
				else {
					break;
				}
			}
			
			return 0 - Actual_y;
		}
		else {
			if (pEntity->y > 1) {
				return pEntity->y;
			}
			else {
				return 0;
			}
			
		}
		break;
	case _down:
		if (pEntity->collision == on) {//考虑碰撞
			for (int i = 1; i <=SCENERY_hight - pEntity->y; i += 1) {
				if (pEntity->y + i <= SCENERY_hight && (scenery_pEntity[pEntity->x][pEntity->y + i] == NULL || (scenery_pEntity[pEntity->x][pEntity->y + i]->collision == off || scenery_pEntity[pEntity->x][pEntity->y + i]->GroupId == pEntity->GroupId))) {//在布景内且检测碰撞层为无碰撞(可移动)

					Actual_y += 1;//实际纵向可移动距离+1

				}
				else {
					break;
				}
			}
			return Actual_y;
		}
		else {
			if (SCENERY_hight - pEntity->y > 0) {
				return SCENERY_hight - pEntity->y;
			}
			else {
				return 0;
			}
		}
		break;
	case Direction::_left:
		if (pEntity->collision == on) {//考虑碰撞
			for (int i = 1; i < pEntity->x; i += 1) {
				if (pEntity->x - i > 0 && (scenery_pEntity[pEntity->x - i][pEntity->y] == NULL || (scenery_pEntity[pEntity->x - i][pEntity->y]->collision == off || scenery_pEntity[pEntity->x - i][pEntity->y]->GroupId == pEntity->GroupId))) {//在布景内且检测碰撞层为无碰撞(可移动)
					Actual_x -= 1;//实际横向可移动距离+1

				}
				else {
					break;
				}
			}
			return 0 - Actual_x;
		}
		else {
			if (pEntity->x > 1) {
				return pEntity->x;
			}
			else {
				return 0;
			}
		}
		break;
	case Direction::_right:
		if (pEntity->collision == on) {//考虑碰撞
			for (int i = 1; i <= SCENERY_width - pEntity->x; i += 1) {
				if (pEntity->x + i <= SCENERY_width && (scenery_pEntity[pEntity->x + i][pEntity->y] == NULL || (scenery_pEntity[pEntity->x + i][pEntity->y]->collision == off || scenery_pEntity[pEntity->x + i][pEntity->y]->GroupId == pEntity->GroupId))) {//在布景内且检测碰撞层为无碰撞(可移动)
					Actual_x += 1;//实际横向可移动距离+1
				}
				else {
					break;
				}
			}
			return Actual_x;
		}
		else {
			if (SCENERY_width - pEntity->x > 0) {
				return SCENERY_width - pEntity->x;
			}
			else {
				return 0;
			}
		}
		break;
	}
}
ENTITY* SCENERY::En_Move(int entity_id, Direction _direction, int _distance)
{
	ENTITY* pEntity = GETpENTITY(entity_id);
	return En_Move(pEntity, _direction, _distance);
}
ENTITY* SCENERY::En_Move(ENTITY* pEntity, Direction _direction, int _distance) {
	int Actual_x = 0, Actual_y = 0;
	switch (_direction) {
	case _up:
		if (pEntity->collision == on) {//考虑碰撞
			for (int i = 1; i <= _distance; i += 1) {
				if (pEntity->y - i > 0 && (scenery_pEntity[pEntity->x][pEntity->y - i] == NULL || (scenery_pEntity[pEntity->x][pEntity->y - i]->collision == off || scenery_pEntity[pEntity->x][pEntity->y - i]->GroupId == pEntity->GroupId))) {//在布景内且检测碰撞层为无碰撞(可移动)

					Actual_y -= 1;//实际纵向可移动距离+1

				}
				else {
					break;
				}
			}

		}
		else {
			if (_distance < pEntity->y) {
				Actual_y = 0 - _distance;
			}
			else {
				Actual_y = 0-(pEntity->y-1);
			}
			
		}
		break;
	case _down:
		if (pEntity->collision == on) {//考虑碰撞
			for (int i = 1; i <= _distance; i += 1) {
				if (pEntity->y + i <= SCENERY_hight && (scenery_pEntity[pEntity->x][pEntity->y + i] == NULL || (scenery_pEntity[pEntity->x][pEntity->y + i]->collision == off || scenery_pEntity[pEntity->x][pEntity->y + i]->GroupId == pEntity->GroupId))) {//在布景内且检测碰撞层为无碰撞(可移动)

					Actual_y += 1;//实际纵向可移动距离+1

				}
				else {
					break;
				}
			}

		}
		else {
			if ((SCENERY_hight - pEntity->y) >_distance ) {
				Actual_y = _distance;
			}
			else {
				Actual_y = SCENERY_hight - pEntity->y;
			}
			
		}
		break;
	case Direction::_left:
		if (pEntity->collision == on) {//考虑碰撞
			for (int i = 1; i <= _distance; i += 1) {
				if (pEntity->x - i > 0 && (scenery_pEntity[pEntity->x - i][pEntity->y] == NULL || (scenery_pEntity[pEntity->x - i][pEntity->y]->collision == off || scenery_pEntity[pEntity->x - i][pEntity->y]->GroupId == pEntity->GroupId))) {//在布景内且检测碰撞层为无碰撞(可移动)

					Actual_x -= 1;//实际横向可移动距离+1

				}
				else {
					break;
				}
			}

		}
		else {
			if(_distance<pEntity->x){
				Actual_x = 0 - _distance;
			}
			else {
				Actual_x = 0 - (pEntity->x-1);
			}
			
		}
		break;
	case Direction::_right:
		if (pEntity->collision == on) {//考虑碰撞
			for (int i = 1; i <= _distance; i += 1) {
				if (pEntity->x + i <= SCENERY_width && (scenery_pEntity[pEntity->x + i][pEntity->y] == NULL || (scenery_pEntity[pEntity->x + i][pEntity->y]->collision == off || scenery_pEntity[pEntity->x + i][pEntity->y]->GroupId == pEntity->GroupId))) {//在布景内且检测碰撞层为无碰撞(可移动)

					Actual_x += 1;//实际横向可移动距离+1

				}
				else {
					break;
				}
			}

		}
		else {
			if (SCENERY_width - pEntity->x > _distance) {
				Actual_x = _distance;
			}
			else {
				Actual_x = SCENERY_width - pEntity->x;
			}
			
		}
		break;
	}
	string str = "";
	if (pEntity->OEntity != NULL) {
		str += pEntity->OEntity->_char;
		scenery_pEntity[pEntity->x][pEntity->y] = pEntity->OEntity;
		SAY(pEntity->OEntity->color, x + pEntity->OEntity->x - 1, y + pEntity->OEntity->y - 1, str);//复原原始位置
	}
	else {
		scenery_pEntity[pEntity->x][pEntity->y] = NULL;
		SAY(0, x + pEntity->x - 1, y + pEntity->y - 1, " ");
	}
	str = "";
	str += pEntity->_char;
	pEntity->x += Actual_x;
	pEntity->y += Actual_y;
	pEntity->OEntity = scenery_pEntity[pEntity->x][pEntity->y];
	scenery_pEntity[pEntity->x][pEntity->y] = pEntity;
	SAY(pEntity->color, x + pEntity->x - 1, y + pEntity->y - 1, str);
	return pEntity->OEntity;
}
ENTITY* SCENERY::GETpENTITY(int entity_id)
{
	ENTITY* p = HeadEntity;
	for (int i = 1; i <= TotalEntity; i += 1) {
		p = p->next;
		if (i == entity_id) {
			break;
		}
	}
	return p;
}
GROUP* SCENERY::GETpGROUP(int group_id) {
	GROUP* p = HeadGroup;
	for (int i = 1; i <= TotalGroup; i += 1) {
		p = p->next;
		if (i == group_id) {
			break;
		}
	}
	return p;
}
SCENERY::SCENERY(int _x, int _y) {
	x = _x;
	y = _y;
}
int SCENERY::CreateEntity(int _x, int _y, int _color, char __char, SettingOption _colliction, int _Key) {
	string str = "";
	str += __char;
	TotalEntity += 1;
	if (scenery_pEntity[_x][_y] != NULL) {
		pLastEntity->next = new ENTITY(TotalEntity, _x, _y, _color, __char, _colliction, _Key, scenery_pEntity[_x][_y]);
	}
	else {
		pLastEntity->next = new ENTITY(TotalEntity, _x, _y, _color, __char, _colliction, _Key);
	}
	pLastEntity = pLastEntity->next;
	scenery_pEntity[_x][_y] = pLastEntity;
	SAY(_color, x + _x - 1, y + _y - 1, str);
	return TotalEntity;
}
int SCENERY::CreateGroup() {
	pLastGroup->next = new GROUP;
	pLastGroup = pLastGroup->next;
	TotalGroup += 1;
	return TotalGroup;
}
void SCENERY::AddEnToGroup(int GroupId, int EntityId) {
	GROUP* p = GETpGROUP(GroupId);
	p->pLastGroupData->next = new GROUPDATA(EntityId, GETpENTITY(EntityId));
	p->pLastGroupData = p->pLastGroupData->next;
	p->DataSize += 1;
	GETpENTITY(EntityId)->GroupId = GroupId;
}
void SCENERY::DelEnToGroup(int EntityId) {
	ENTITY* p = GETpENTITY(EntityId);
	p->GroupId = 0;
}
int SCENERY::Gr_Move(int group_id, Direction _direction, int _distance) {
	string str = "";
	int MinDistance = 0;
	GROUP* pGroup = GETpGROUP(group_id);
	int* MaxDistanceArray = new int[pGroup->DataSize];
	int* pInt = MaxDistanceArray;
	GROUPDATA* p = pGroup->pHeadGroupData;
	for (int i = 1; i <= pGroup->DataSize; i += 1) {
		p = p->next;
		if ((p->pEntity)->GroupId != group_id) {
			pInt[i - 1] = 9999;
			continue;
		}
		pInt[i - 1] = En_MaxMoveDistance(p->pEntity, _direction);//计算出实体的最远移动距离
		if (pInt[i - 1] >= _distance) {
			pInt[i - 1] = _distance;
		}
	}
	MinDistance = pInt[0];
	for (int i = 0; i < pGroup->DataSize; i += 1) {//计算最短距离
		if (pInt[i] < MinDistance) {
			MinDistance = pInt[i];
		}
	}
	p = pGroup->pHeadGroupData;
	for (int i = 1; i <= pGroup->DataSize; i += 1) {
		p = p->next;
		if ((p->pEntity)->GroupId != group_id) {
			continue;
		}
		str = "";
		if (p->pEntity->OEntity != NULL) {
			str += (p->pEntity)->OEntity->_char;
			SAY((p->pEntity)->OEntity->color, x + (p->pEntity)->OEntity->x - 1, y + (p->pEntity)->OEntity->y - 1, str);//打印被遮挡字符
			scenery_pEntity[(p->pEntity)->OEntity->x][(p->pEntity)->OEntity->y] = (p->pEntity)->OEntity;
		}
		else {
			SAY(0, x + (p->pEntity)->x - 1, y + (p->pEntity)->y - 1, " ");//打印被遮挡字符
			scenery_pEntity[(p->pEntity)->x][(p->pEntity)->y] = NULL;
		}

	}
	p = pGroup->pHeadGroupData;
	for (int i = 1; i <= pGroup->DataSize; i += 1) {
		p = p->next;
		if ((p->pEntity)->GroupId != group_id) {
			continue;
		}
		switch (_direction) {
		case _up:
			p->pEntity->OEntity = scenery_pEntity[(p->pEntity)->x][(p->pEntity)->y - MinDistance];//保留新位置实体地址
			scenery_pEntity[(p->pEntity)->x][(p->pEntity)->y - MinDistance] = p->pEntity;
			p->pEntity->y -= MinDistance;
			break;
		case _down:
			p->pEntity->OEntity = scenery_pEntity[(p->pEntity)->x][(p->pEntity)->y + MinDistance];//保留新位置实体地址
			scenery_pEntity[(p->pEntity)->x][(p->pEntity)->y + MinDistance] = p->pEntity;
			p->pEntity->y += MinDistance;
			break;
		case _left:
			p->pEntity->OEntity = scenery_pEntity[(p->pEntity)->x - MinDistance][(p->pEntity)->y];//保留新位置实体地址
			scenery_pEntity[(p->pEntity)->x - MinDistance][(p->pEntity)->y] = p->pEntity;
			p->pEntity->x -= MinDistance;
			break;
		case _right:
			p->pEntity->OEntity = scenery_pEntity[(p->pEntity)->x + MinDistance][(p->pEntity)->y];//保留新位置实体地址
			scenery_pEntity[(p->pEntity)->x + MinDistance][(p->pEntity)->y] = p->pEntity;//在新位置放置实体地址
			p->pEntity->x += MinDistance;
			break;
		default:
			break;
		}
		str = "";
		str += (p->pEntity)->_char;
		SAY((p->pEntity)->color, x + (p->pEntity)->x - 1, y + (p->pEntity)->y - 1, str);//打印字符

	}
	return MinDistance;
}
int SCENERY::GETint(int EntityId, GetintOption _selection) {
	ENTITY* p = GETpENTITY(EntityId);
	return GETint(p, _selection);
}
char SCENERY::GETchar(int EntityId) {
	ENTITY* p = GETpENTITY(EntityId);
	return GETchar(p);
}
ENTITY* SCENERY::GETdownENTITY(int EntityId) {
	ENTITY* p = GETpENTITY(EntityId);
	return p->OEntity;
}
int SCENERY::GETint(ENTITY* pEntity, GetintOption _selection) {
	if (pEntity != NULL)
	{
		switch (_selection) {
		case En_id:
			return pEntity->id;
		case En_x:
			return pEntity->x;
		case En_y:
			return pEntity->y;
		case En_color:
			return pEntity->color;
		case En_collision:
			return pEntity->collision;
		case En_GroupId:
			return pEntity->GroupId;
		case En_Key:
			return pEntity->Key;
		default:
			return  0;
			break;
		}
	}
	else {
		return 0;
	}
}
char SCENERY::GETchar(ENTITY* pEntity) {
	return pEntity->_char;
}
void SCENERY::En_Fresh(ENTITY* pEntity, int _color, char __char, int _Collision, int _Key) {
	string str = "";
	pEntity->color = _color;
	pEntity->_char = __char;
	pEntity->collision = _Collision;
	pEntity->Key = _Key;
	str += __char;
	SAY(_color, x + pEntity->x - 1, y + pEntity->y - 1, str);
}
void SCENERY::En_Fresh(int EntityId, int _color, char __char, int _Collision, int _Key) {
	ENTITY* p = GETpENTITY(EntityId);
	En_Fresh(p,_color,__char,_Collision,_Key);
}
ENTITY* SCENERY::GETdownENTITY(ENTITY* pEntity) {

	return pEntity->OEntity;
}
ENTITY* SCENERY::GETpENTITY(int _x, int _y) {
	return scenery_pEntity[_x][_y];
}
GROUPDATA::GROUPDATA(int _EntityId, ENTITY* _pEntity) {
	EntityId = _EntityId;
	pEntity = _pEntity;
}
ENTITY* SCENERY::Gr_GETpENTITY(int _GroupId, int Gr_EntityId) {
	GROUP* Gr_Point = GETpGROUP(_GroupId);
	GROUPDATA* Gd_Point = Gr_Point->pHeadGroupData;
	for (int i = 0; i < Gr_EntityId; i += 1) {
		Gd_Point = Gd_Point->next;
	}
	return Gd_Point->pEntity;
}
ENTITY::ENTITY(int _id, int _X, int _Y, int _color, char __char, int _Collision, int _Key, ENTITY* _OEntity) {
	id = _id;
	x = _X;
	y = _Y;
	color = _color;
	_char = __char;
	collision = _Collision;
	OEntity = _OEntity;
	Key = _Key;
}
int _abs(int _num) {
	if (_num > 0) {
		return _num;
	}
	else {
		return (0-_num);
	}
}
int SCENERY::TotalEn() {
	return TotalEntity;
}
int SCENERY::TotalGr() {
	return TotalGroup;
}
int SCENERY::Gr_Spin(int _GroupId, int _x, int _y, DirectionOfRotation _RotationDirection) {
	GROUP* Gr_Point = GETpGROUP(_GroupId);
	GROUPDATA* Gd_Point = Gr_Point->pHeadGroupData;
	ENTITY* En_Point = NULL, * TempEn_Point = new ENTITY(-1, 0, 0, 0, ' ', on);
	TempEn_Point->GroupId = _GroupId;
	string str = "";
	int D_x = 0, D_y = 0,index=0,T_x,T_y;
	int* TargetArray = new int[(Gr_Point->DataSize) * 2];
	int _distance = 0;
	for (int i = 1; i <= Gr_Point->DataSize; i += 1) {
		Gd_Point = Gd_Point->next;
		En_Point = Gd_Point->pEntity;
		TempEn_Point->collision = En_Point->collision;
		if (En_Point->GroupId != _GroupId) {
			continue;
		}
		else {
			if (_RotationDirection == _cw) {
				//顺时针
				D_x = En_Point->x - _x;//<0为左
				D_y = En_Point->y - _y;//<0为上
				if (D_y != 0 || D_x != 0) {
					if (D_x < 0) {
						if (D_y < 0) {
							//第一象限
							T_x= _x - D_y;
							T_y= _y + D_x;
							if (En_Point->x < _x + D_y) {
								_distance = T_y - En_Point->y;
								if (En_MaxMoveDistance(En_Point, _up) >= _abs(_distance)) {
									TempEn_Point->y = T_y;//构造临时实体
									TempEn_Point->x = En_Point->x;
									_distance = T_x - En_Point->x;
									if (En_MaxMoveDistance(TempEn_Point, _right) < _abs(_distance)) {
										return -1;//不可移动
									}
								}
								else {
									return -1;//不可移动
								}
							}
							else {
								_distance = T_x - En_Point->x;
								if (En_MaxMoveDistance(En_Point, _right) >= _abs(_distance)) {
									TempEn_Point->x = T_x;//构造临时实体
									TempEn_Point->y = En_Point->y;
									_distance = T_y - En_Point->y;
									if (En_MaxMoveDistance(TempEn_Point, _down) < _abs(_distance)&& En_Point->x != _x + D_y) {
										return -1;//不可移动
									}
								}
								else {
									return -1;//不可移动
								}
							}
						}
						else {
							//第四象限
							T_x = _x - D_y;
							T_y = _y + D_x;
							if (En_Point->y >= _y + D_x) {
								//VIII
								_distance = T_y - En_Point->y;
								if (En_MaxMoveDistance(En_Point, _up) >= _abs(_distance)) {
									TempEn_Point->y = T_y;//构造临时实体
									TempEn_Point->x = En_Point->x;
									_distance = T_x - En_Point->x;
									if (En_MaxMoveDistance(TempEn_Point, _right) < _abs(_distance)&&En_Point->y != _y + D_x) {
										return -1;//不可移动
									}
								}
								else {
									return -1;//不可移动
								}
							}
							else {
								_distance = T_x - En_Point->x;
								if (En_MaxMoveDistance(En_Point, _left) >= _abs(_distance)) {
									TempEn_Point->x = T_x;//构造临时实体
									TempEn_Point->y = En_Point->y;
									_distance = T_y - En_Point->y;
									if (En_MaxMoveDistance(TempEn_Point, _up) < _abs(_distance)) {
										return -1;//不可移动
									}
								}
								else {
									return -1;//不可移动
								}
							}
						}
					}
					else {
						if (D_y <= 0) {
							//第二象限
							T_x = _x - D_y;
							T_y = _y + D_x;
							if (En_Point->y < _y - D_x) {
								//III
								_distance = T_x - En_Point->x;
								if (En_MaxMoveDistance(En_Point, _right) >= _abs(_distance)) {
									TempEn_Point->x = T_x;//构造临时实体
									TempEn_Point->y = En_Point->y;
									_distance = T_y - En_Point->y;
									if (En_MaxMoveDistance(TempEn_Point, _down) < _abs(_distance)) {
										return -1;//不可移动
									}
								}
								else {
									return -1;//不可移动
								}
							}
							else {
								//IV
								_distance = T_y - En_Point->y;
								if (En_MaxMoveDistance(En_Point, _down) >= _abs(_distance)) {
									TempEn_Point->y = T_y;//构造临时实体
									TempEn_Point->x = En_Point->x;
									_distance = T_x - En_Point->x;
									if (En_MaxMoveDistance(TempEn_Point, _left) < _abs(_distance)&& En_Point->y != _y - D_x) {
										return -1;//不可移动
									}
								}
								else {
									return -1;//不可移动
								}
							}
						}
						else {
							//第三象限
							T_x = _x - D_y;
							T_y = _y + D_x;
							if (En_Point->x >= _x - D_y) {
								//VI
								_distance = T_x - En_Point->x;
								if (En_MaxMoveDistance(En_Point, _left) >= _abs(_distance)) {
									TempEn_Point->x = T_x;//构造临时实体
									TempEn_Point->y = En_Point->y;
									_distance = T_y - En_Point->y;
									if (En_MaxMoveDistance(TempEn_Point, _up) < _abs(_distance)&& En_Point->x != _x - D_y) {
										return -1;//不可移动
									}
								}
								else {
									return -1;//不可移动
								}
							}
							else {
								//V
								_distance = T_y - En_Point->y;
								if (En_MaxMoveDistance(En_Point, _down) >= _abs(_distance)) {
									TempEn_Point->y = T_y;//构造临时实体
									TempEn_Point->x = En_Point->x;
									_distance = T_x - En_Point->x;
									if (En_MaxMoveDistance(TempEn_Point, _left) < _abs(_distance)) {
										return -1;//不可移动
									}
								}
								else {
									return -1;//不可移动
								}
							}
						}
					}

				}
				else {
					T_x = _x;
					T_y = _y;
				}
			}
			else{
				D_x = En_Point->x - _x;//<0为左
				D_y = En_Point->y - _y;//<0为上
				if (D_y != 0 || D_x != 0) {
					if (D_x < 0) {
						if (D_y <= 0) {
							//第一象限
							
							T_x = _x + D_y;
							T_y = _y - D_x;
							if (En_Point->x <= _x + D_y) {
								//I区
								_distance = T_y - En_Point->y;
								if (En_MaxMoveDistance(En_Point, _down) >= _abs(_distance)) {
									TempEn_Point->y = T_y;//构造临时实体
									TempEn_Point->x = En_Point->x;
									_distance = T_x - En_Point->x;
									if (En_MaxMoveDistance(TempEn_Point, _right) < _abs(_distance) && En_Point->x != _x + D_y) {
										return -1;//不可移动
									}
								}
								else {
									return -1;//不可移动
								}
							}
							else {
								//II区
								_distance = T_x - En_Point->x;
								if (En_MaxMoveDistance(En_Point, _left) >= _abs(_distance)) {
									TempEn_Point->x = T_x;//构造临时实体
									TempEn_Point->y = En_Point->y;
									_distance = T_y - En_Point->y;
									if (En_MaxMoveDistance(TempEn_Point, _down) < _abs(_distance)) {
										return -1;//不可移动
									}
								}
								else {
									return -1;//不可移动
								}
							}
						}
						else {
							//第四象限
							
							T_x = _x + D_y;
							T_y = _y - D_x;
							if (En_Point->y < _y + D_x) {
								//VIII
								_distance = T_y - En_Point->y;
								if (En_MaxMoveDistance(En_Point, _down) >= _abs(_distance)) {
									TempEn_Point->y = T_y;//构造临时实体
									TempEn_Point->x = En_Point->x;
									_distance = T_x - En_Point->x;
									if (En_MaxMoveDistance(TempEn_Point, _right) < _abs(_distance)) {
										return -1;//不可移动
									}
								}
								else {
									return -1;//不可移动
								}
							}
							else {
								//VII
								_distance = T_x - En_Point->x;
								if (En_MaxMoveDistance(En_Point, _right) >= _abs(_distance)) {
									TempEn_Point->x = T_x;//构造临时实体
									TempEn_Point->y = En_Point->y;
									_distance = T_y - En_Point->y;
									if (En_MaxMoveDistance(TempEn_Point, _up) < _abs(_distance) && En_Point->y != _y + D_x) {
										return -1;//不可移动
									}
								}
								else {
									return -1;//不可移动
								}
							}
						}
					}
					else{
						if (D_y < 0) {
							//第二象限
							
							T_x = _x + D_y;
							T_y = _y - D_x;
							if (En_Point->y > _y - D_x) {
								//IV
								_distance = T_y - En_Point->y;
								if (En_MaxMoveDistance(En_Point, _up) >= _abs(_distance)) {
									TempEn_Point->y = T_y;//构造临时实体
									TempEn_Point->x = En_Point->x;
									_distance = T_x - En_Point->x;
									if (En_MaxMoveDistance(TempEn_Point, _left) < _abs(_distance)) {
										return -1;//不可移动
									}
								}
								else {
									return -1;//不可移动
								}
							}
							else {
								//III
								_distance = T_x - En_Point->x;
								if (En_MaxMoveDistance(En_Point, _left) >= _abs(_distance)) {
									TempEn_Point->x = T_x;//构造临时实体
									TempEn_Point->y = En_Point->y;
									_distance = T_y - En_Point->y;
									if (En_MaxMoveDistance(TempEn_Point, _down) < _abs(_distance) && En_Point->y != _y - D_x) {
										return -1;//不可移动
									}
								}
								else {
									return -1;//不可移动
								}
							}
						}
						else {
							//第三象限
							
							T_x = _x + D_y;
							T_y = _y - D_x;
							if (En_Point->x > _x - D_y) {
								//VI
								_distance = T_x - En_Point->x;
								if (En_MaxMoveDistance(En_Point, _right) >= _abs(_distance)) {
									TempEn_Point->x = T_x;//构造临时实体
									TempEn_Point->y = En_Point->y;
									_distance = T_y - En_Point->y;
									if (En_MaxMoveDistance(TempEn_Point, _up) < _abs(_distance)) {
										return -1;//不可移动
									}
								}
								else {
									return -1;//不可移动
								}
							}
							else {
								//V
								_distance = T_y - En_Point->y;
								if (En_MaxMoveDistance(En_Point, _up) >= _abs(_distance)) {
									TempEn_Point->y = T_y;//构造临时实体
									TempEn_Point->x = En_Point->x;
									_distance = T_x - En_Point->x;
									if (En_MaxMoveDistance(TempEn_Point, _left) < _abs(_distance) && En_Point->x != _x - D_y) {
										return -1;//不可移动
									}
								}
								else {
									return -1;//不可移动
								}
							}
							
						}
					}

				}
				else {
					T_x = _x;
					T_y = _y;
				}
			}
		}
		TargetArray[index] = T_x;
		TargetArray[index + 1] = T_y;
		index += 2;
	}
	Gd_Point = Gr_Point->pHeadGroupData;
	for (int i = 1; i <= Gr_Point->DataSize; i += 1) {
		Gd_Point = Gd_Point->next;
		En_Point = Gd_Point->pEntity;
		if (En_Point->GroupId != _GroupId) {
			continue;
		}
		str = "";
		if (En_Point->OEntity != NULL) {
			str += En_Point->OEntity->_char;
			SAY(En_Point->OEntity->color, x + En_Point->OEntity->x - 1, y + En_Point->OEntity->y - 1, str);//打印被遮挡字符
			scenery_pEntity[En_Point->OEntity->x][En_Point->OEntity->y] = En_Point->OEntity;
		}
		else {
			SAY(0, x + En_Point->x - 1, y + En_Point->y - 1, " ");//打印被遮挡字符
			scenery_pEntity[En_Point->x][En_Point->y] = NULL;
		}
	}
	index = 0;
	Gd_Point = Gr_Point->pHeadGroupData;
	for (int i = 1; i <= Gr_Point->DataSize; i += 1) {
		Gd_Point = Gd_Point->next;
		En_Point = Gd_Point->pEntity;
		En_Point->OEntity = scenery_pEntity[TargetArray[index]][TargetArray[index+1]];//保留新位置实体地址
		scenery_pEntity[TargetArray[index]][TargetArray[index + 1]] = En_Point;//在新位置放置实体地址
		En_Point->x = TargetArray[index];
		En_Point->y = TargetArray[index + 1];
		str = "";
		str += En_Point->_char;
		SAY(En_Point->color, x + En_Point->x - 1, y + En_Point->y - 1, str);//打印字符
		index += 2;
	}
	return 0;//旋转结束
}
void SCENERY::DRAW(int color,char _chr) {
	string _str = "";
	_str += _chr;
	DRAW_SQURE(x-1, y-1, x + SCENERY_width, y + SCENERY_hight, 0, _str, 1);
}
int main() {
//这部分测试代码是我12岁的刚学c++一星期的弟弟写的。
//实体的管理很糟糕（完全没有管理）
	GUANGBIAO(0);
	SCENERY MainScenery(30, 5);//创建一个场景
	MainScenery.DRAW(_Gray, 'H');//画出场景的边框
	//------------------------------------------------------------------------
	MainScenery.CreateGroup();//组1 构成主角的实体被放进这个组中
	MainScenery.CreateEntity(3, 1, 12, 'O', on);//1
	MainScenery.AddEnToGroup(1, 1);
	MainScenery.CreateEntity(2, 2, 14, 'O', on, 1);//2
	MainScenery.CreateEntity(3, 2, 14, 'O', on, 1);//3
	MainScenery.CreateEntity(4, 2, 14, 'O', on, 1);//4
	MainScenery.CreateEntity(3, 3, 14, 'O', on, 1);//5
	MainScenery.CreateEntity(2, 4, 14, 'O', on, 1);//6
	MainScenery.CreateEntity(4, 4, 14, 'O', on, 1);//7
	MainScenery.CreateEntity(50, 5, H_Green, '0', off, 2);//8
	MainScenery.CreateEntity(3, 17, _Gray, '0', off, 3);//9 button
	MainScenery.CreateEntity(50, 19, H_Blue, '|', on, 2);//10 door1
	MainScenery.CreateEntity(50, 18, H_Blue, '|', on, 2);//11 door2
	MainScenery.CreateEntity(50, 17, H_Blue, '|', on, 2);//12 door3
	MainScenery.CreateEntity(50, 16, H_Blue, '|', on, 2);//13 door4
	MainScenery.CreateEntity(50, 15, H_Blue, '|', on, 2);//14 door5
	MainScenery.CreateEntity(50, 20, H_Blue, '|', on, 2);//15 door5
	MainScenery.CreateEntity(50, 14, H_Gray, 'I', on, 1);//16 wall1 
	for (int i = 1; i <= 30; i += 1) {
		MainScenery.CreateEntity(50 + i, 14, H_Gray, '-', on, 1);//16 wall2
	}
	MainScenery.CreateEntity(52, 17, _Gray, '0', off, 3);//17 button
	MainScenery.AddEnToGroup(1, 2);
	MainScenery.AddEnToGroup(1, 3);
	MainScenery.AddEnToGroup(1, 4);
	MainScenery.AddEnToGroup(1, 5);
	MainScenery.AddEnToGroup(1, 6);
	MainScenery.AddEnToGroup(1, 7);
	while (1) {
		if (_kbhit()) {
			switch (_getch()) {
			case'q':
				MainScenery.Gr_Spin(1, MainScenery.GETint(1, En_x), MainScenery.GETint(1, En_y), anti_cw);
				break;
			case'e':
				MainScenery.Gr_Spin(1, MainScenery.GETint(1, En_x), MainScenery.GETint(1, En_y), _cw);
				break;
			case's':
				MainScenery.Gr_Move(1, _down, 1);
				break;
			case 'w':
				MainScenery.Gr_Move(1, _up, 1);
				break;
			case'a':
				MainScenery.Gr_Move(1, _left, 1);
				break;
			case 'd':
				MainScenery.Gr_Move(1, _right, 1);
				break;
			case 'j'://小人的左手放在按钮上，按下j键就可以使用按钮
				if (MainScenery.GETint(MainScenery.GETdownENTITY(2), En_Key) == 3) {
					if (MainScenery.GETint(MainScenery.GETdownENTITY(2), En_color) == H_Gray) {
						MainScenery.En_Fresh(MainScenery.GETdownENTITY(2), _Gray, '0', off, 3);
						MainScenery.En_Fresh(MainScenery.GETpENTITY(8), H_Green, '0', off, 1);
						for (int i = 1; i <= MainScenery.TotalEn(); i += 1) {
							if (MainScenery.GETint(i, En_Key) == 2) {
								MainScenery.En_Fresh(MainScenery.GETpENTITY(i), H_Blue, '|', on, 2);
							}
						}
					}
					else {
						MainScenery.En_Fresh(MainScenery.GETpENTITY(8), H_Red, '0', on, 1);
						MainScenery.En_Fresh(MainScenery.GETdownENTITY(2), H_Gray, '0', off, 3);
						for (int i = 1; i <= MainScenery.TotalEn(); i += 1) {
							if (MainScenery.GETint(i, En_Key) == 2) {
								MainScenery.En_Fresh(MainScenery.GETpENTITY(i), H_Yellow, '|', off, 2);
							}
						}
					}

				}
				break;
			}
		}

	}


	GOTOXY(1, 2);
	std::system("pause");
}
