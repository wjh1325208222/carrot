#ifndef __GAMEDATATYPE_H__
#define __GAMEDATATYPE_H__

#include "CCStdC.h"
#include "string.h"
#include <string>
#include <vector>
#include <map>

using namespace std;

//关卡章节
typedef struct{
	int idChapter;		//章节id
	string name;		//章节名
	string nameAni;		//名字ani
	int nStageCnt;		//关卡数量
	string bgAni;		//章节图片
}TPL_CHAPTER;

//关卡
typedef struct{
	int idStage;		//关卡id
	string name;		//关卡名
	int idChapter;		//所属章节id
	int nStageNum;		//第几关
	string ani;			//关卡ani
	int	nWave;			//波数
	int nWeaponSetId;	//可用武器id
	int idMap;			//对应地图id
}TPL_STAGE;

//怪物行走的地图路径
typedef struct{
	string name;
	int x;
	int y;
	int idx;
}PATH_POINT;

//地图上可放置格子
typedef struct{
	string name;
	int x;
	int y;
	int width;
	int height;
	int idObj;
}MAP_CELL;

//地图相关
typedef struct{
	int idMap;			//地图id
	string map;			//地图文件
	string startPos;	//起始位置，对应tmx文件的路径名
	string mapBg;		//地图背景图
	string mapFore;		//地图前景图
	string endPos;		//结束坐标，即萝卜所在位置
}TPL_MAP;

//地图物件相关
typedef struct  
{
	int	idObj;			//地图物件id
	int idMap;			//所属物件id
	string pos;			//放置坐标
	string objAni;		//物件ani
	int width;			//物件宽度,几个格子大小
	int height;		//物件高度,格子大小
	int action;		//是否有动作，0无 1 上下移动 2左右移动
	int data1;		//移动偏移量
	int lifeMax;	//最大生命值

	//物件游戏过程中数据
	int life;		//物件生命，当为0时，消除该物件
}TPL_MAP_OBJ;

//用户相关数据
typedef struct
{
	int curStage;
}USER;
#endif

