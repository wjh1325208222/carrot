#ifndef __DATAMANAGER_H__
#define __DATAMANAGER_H__

#include "CppSQLite3.h"
#include "GameDataType.h"
#include "CCStdC.h"
#include "cocos2d.h"
#include <map>
#include <vector>

USING_NS_CC;
using namespace std;

class CDataManager
{
public:
	static CDataManager* sharedDataManager(void);

	void init();

	//获得
	const map<int, TPL_CHAPTER>* getChapterList();
	//读取地图怪物行走路径当前格子信息
	const PATH_POINT* GetCurStepInfo(int curIdx);
	//读取下个个字信息
	const PATH_POINT* GetNextStep(int curIdx = 0);
	//获取地图上可行走的路径
	const map<int, PATH_POINT>* getMapPath();
	//通过路径名获取该路径详细信息
	const PATH_POINT* GetPointByName(const char* szName);


	//查找
	void findStageByChapterId(int nId, map<int, TPL_STAGE>& mapReturn);
	//查找章节
	const TPL_STAGE* findStage(int idStage);
	//查找地图
	const TPL_MAP* findMap(int idMap);
	//查找地图物件
	void findMapObj(int idMap, vector<TPL_MAP_OBJ>& vecObj);
	//查找地图可放置格子
	const MAP_CELL* findMapCell(string cellName);


	//读取地图数据
	void ReadMapInfo(CCArray* pArray);

	

	

protected:
	CDataManager(void);
	~CDataManager(void);

	CppSQLite3DB m_db;			//数据库

	//
	void initChapter();
	void initStage();
	void initMap();
	void initMapObj();

	//章节列表
	map<int, TPL_CHAPTER> m_mapChapter;

	//副本列表
	map<int, TPL_STAGE> m_mapStage;


	map<int, PATH_POINT> m_Path;

	map<string, MAP_CELL> m_mapCell;

	//地图
	map<int, TPL_MAP> m_mapMap;

	//地图物件
	map<int, TPL_MAP_OBJ> m_mapObj;
};


#endif

