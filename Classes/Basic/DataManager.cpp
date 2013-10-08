#include "DataManager.h"
#include "cocos2d.h"
#include "GameDefine.h"
#include "Converter.h"

USING_NS_CC;

#define DB_FILE_NAME  "Conf\\Carrot.db"

// singleton stuff
static CDataManager *s_SharedDataManger = NULL;

CDataManager::CDataManager(void)
{
	
}


CDataManager::~CDataManager(void)
{
}

CDataManager* CDataManager::sharedDataManager( void )
{
	if (!s_SharedDataManger)
	{
		s_SharedDataManger = new CDataManager();
		s_SharedDataManger->init();
	}

	return s_SharedDataManger;
}

void CDataManager::init()
{
	std::string path=CCFileUtils::sharedFileUtils()->fullPathForFilename(DB_FILE_NAME);

	m_db.open(path.c_str());  
	if (!m_db.isOpen())
	{
		return;
	}

	//初始化时间随机函数
	static bool bRandCreated=false;
	if(!bRandCreated)
	{
		srand(unsigned(time(0)));
		bRandCreated = true;
	}

	initChapter();
	initStage();
	initMap();
	initMapObj();
}

void CDataManager::initChapter()
{
	m_mapChapter.clear();

	CppSQLite3Query q = m_db.execQuery("select * from tpl_chapter;");
	TPL_CHAPTER temp;
	while(!q.eof())
	{
		temp.idChapter = q.getIntField("idChapter");
		temp.bgAni = q.getStringField("bgAni");
		temp.name = CConverter::U2G(q.getStringField("name"));
		temp.nameAni = q.getIntField("nameAni");
		temp.nStageCnt = q.getIntField("nStageCnt");
		
		m_mapChapter[temp.idChapter] = temp;

		q.nextRow();
	}
	
}

void CDataManager::initStage()
{
	m_mapStage.clear();

	CppSQLite3Query q = m_db.execQuery("select * from tpl_stage;");
	TPL_STAGE temp;
	while(!q.eof())
	{
		temp.idChapter = q.getIntField("idChapter");
		temp.idMap = q.getIntField("idMap");
		temp.idStage = q.getIntField("idStage");
		temp.ani = q.getStringField("ani");
		temp.name = CConverter::U2G(q.getStringField("name"));
		temp.nStageNum = q.getIntField("nStageNum");
		temp.nWave = q.getIntField("nWave");
		temp.nWeaponSetId = q.getIntField("nWeaponSetId");

		m_mapStage[temp.idStage] = temp;

		q.nextRow();
	}
}

const map<int, TPL_CHAPTER>* CDataManager::getChapterList()
{
	return &m_mapChapter;
}

void CDataManager::findStageByChapterId( int nId, map<int, TPL_STAGE>& mapReturn )
{
	map<int, TPL_STAGE>::iterator iterTemp;
}

void CDataManager::ReadMapInfo( CCArray* pArray )
{
	m_Path.clear();
	m_mapCell.clear();

	if (pArray && pArray->count() > 0)    
	{    
		CCObject* pObj = NULL;    
		CCARRAY_FOREACH(pArray, pObj)    
		{    
			CCDictionary* spawnPoint = (CCDictionary*)pObj;
			const CCString* name = spawnPoint->valueForKey("name");
			int x = spawnPoint->valueForKey("x")->intValue();
			int y = spawnPoint->valueForKey("y")->intValue();

			string strValue = name->getCString();
			int iFind = strValue.find("PT");
			if (iFind != -1)
			{
				//即怪物可行走路径
				PATH_POINT temp;
				temp.name = strValue;
				temp.x = x + MAP_TILE_WIDHT/2;//居中
				temp.y = y - MAP_TILE_HEIGHT/2;
				string strIdx = strValue.substr(2);
				temp.idx = atoi(strIdx.c_str());
				m_Path[temp.idx] = temp;
			}
			else
			{
				MAP_CELL temp;
				temp.name = strValue;
				temp.x = x;
				temp.y = y;
				temp.width = spawnPoint->valueForKey("width")->intValue();
				temp.height = spawnPoint->valueForKey("height")->intValue();
				m_mapCell[temp.name] = temp;
			}
		}
	}
}

const PATH_POINT* CDataManager::GetCurStepInfo( int curIdx )
{
	map<int, PATH_POINT>::iterator iterTemp;
	iterTemp = m_Path.find(curIdx);
	if (iterTemp != m_Path.end())
	{
		return &(iterTemp->second);
	}
	return NULL;
}

const PATH_POINT* CDataManager::GetNextStep( int curIdx /*= 0*/ )
{
	map<int, PATH_POINT>::iterator iterTemp;

	if (!curIdx)
	{
		iterTemp = m_Path.begin();
		if (iterTemp != m_Path.end())
		{
			return &(iterTemp->second);
		}
		return NULL;
	}
	
	iterTemp = m_Path.find(curIdx);
	if (iterTemp != m_Path.end())
	{
		iterTemp++;
		if (iterTemp != m_Path.end())
		{
			return &(iterTemp->second);
		}
	}
	return NULL;
}

const PATH_POINT* CDataManager::GetPointByName( const char* szName )
{
	map<int, PATH_POINT>::iterator iterTemp;
	for (iterTemp = m_Path.begin(); iterTemp != m_Path.end(); iterTemp++)
	{
		if (!iterTemp->second.name.compare(szName))
		{
			return &(iterTemp->second);
		}
	}
	return NULL;
}

const map<int, PATH_POINT>* CDataManager::getMapPath()
{
	return &m_Path;
}

void CDataManager::initMap()
{
	m_mapMap.clear();

	CppSQLite3Query q = m_db.execQuery("select * from tpl_map;");
	TPL_MAP temp;
	while(!q.eof())
	{
		temp.idMap= q.getIntField("idMap");
		temp.map = q.getStringField("map");
		temp.startPos = q.getStringField("startPos");
		temp.endPos = q.getStringField("endPos");
		temp.mapBg = q.getStringField("mapBg");
		temp.mapFore = q.getStringField("mapFore");
		
		m_mapMap[temp.idMap] = temp;

		q.nextRow();
	}
}

const TPL_MAP* CDataManager::findMap( int idMap )
{
	map<int, TPL_MAP>::iterator iterTemp;
	iterTemp = m_mapMap.find(idMap);
	if (iterTemp != m_mapMap.end())
	{
		return &(iterTemp->second);
	}
	return NULL;
}

void CDataManager::initMapObj()
{
	m_mapObj.clear();

	CppSQLite3Query q = m_db.execQuery("select * from tpl_map_obj;");
	TPL_MAP_OBJ temp;
	while(!q.eof())
	{
		temp.idMap= q.getIntField("idMap");
		temp.idObj = q.getIntField("idObj");
		temp.objAni = q.getStringField("objAni");
		temp.pos = q.getStringField("pos");
		temp.action = q.getIntField("action");
		temp.data1 = q.getIntField("data1");
		temp.height = q.getIntField("height");
		temp.width = q.getIntField("width");

		m_mapObj[temp.idObj] = temp;

		q.nextRow();
	}
}

void CDataManager::findMapObj( int idMap, vector<TPL_MAP_OBJ>& vecObj )
{
	vecObj.clear();
	map<int, TPL_MAP_OBJ>::iterator iterTemp;
	for (iterTemp = m_mapObj.begin(); iterTemp != m_mapObj.end(); iterTemp++)
	{
		if (iterTemp->second.idMap == idMap)
		{
			vecObj.push_back(iterTemp->second);
		}
	}
}

const TPL_STAGE* CDataManager::findStage( int idStage )
{
	map<int, TPL_STAGE>::iterator iterTemp;
	iterTemp = m_mapStage.find(idStage);
	if (iterTemp != m_mapStage.end())
	{
		return &(iterTemp->second);
	}
	return NULL;
}

const MAP_CELL* CDataManager::findMapCell( string cellName )
{
	map<string, MAP_CELL>::iterator iterTemp;
	iterTemp = m_mapCell.find(cellName);
	if (iterTemp != m_mapCell.end())
	{
		return &(iterTemp->second);
	}
	return NULL;
}


