#include "BattleScene.h"
#include "GameDefine.h"
#include "GameDataType.h"
#include "BattleMonster.h"
#include "DataManager.h"
#include "CountDownLayer.h"
#include "BattleMenu.h"

using namespace cocos2d;
using namespace std;

#define		kTagTileMap			1000
#define		kTagMonster			1001
#define		kTagCarrot			1002
#define		kTagCountDownLight	1003
#define		kTagCountDownNum	1004
#define		kTagCarrotLife		1005

#define		kTagMapObjStart		10000

enum{
	DIRECTION_DOWN = 1,
	DIRECTION_LEFT,
	DIRECTION_UP,
	DIRECTION_RIGHT,
}DIRECTION;

CCScene* CBattleScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

		scene->setTag(BATTLE_SCENE);

        // 'layer' is an autorelease object
        CBattleScene *layer = CBattleScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer, 0, BATTLE_LAYER);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CBattleScene::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

		CCFileUtils::sharedFileUtils()->addSearchPath("data/battle/theme1");
		CCFileUtils::sharedFileUtils()->addSearchPath("data/battle/theme1/bg0");
		CCFileUtils::sharedFileUtils()->addSearchPath("data/battle/Items");

		CCSpriteFrameCache *pCache =  CCSpriteFrameCache::sharedSpriteFrameCache();

		pCache->addSpriteFrame(CCSpriteFrame::create("BG1-hd.png",CCRectMake(0, 0, 960, 640)),"BG1-hd.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("BG-hd.png",CCRectMake(0, 0, 960, 480)),"BG-hd.png");

		pCache->addSpriteFrame(CCSpriteFrame::create("fat_boss_green01.png",CCRectMake(0, 0, 98, 128)),"fat_boss_green01.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("fat_boss_green02.png",CCRectMake(0, 0, 102, 120)),"fat_boss_green02.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("MonsterHP01.png",CCRectMake(0, 0, 52, 12)),"MonsterHP01.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("MonsterHP02.png",CCRectMake(0, 0, 48, 8)),"MonsterHP02.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("start01.png",CCRectMake(0, 0, 93, 73)),"start01.png");

		//萝卜资源
		pCache->addSpriteFrame(CCSpriteFrame::create("hlb21.png",CCRectMake(0, 0, 75, 106)),"hlb21.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("hlb22.png",CCRectMake(0, 0, 75, 106)),"hlb22.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("hlb23.png",CCRectMake(0, 0, 75, 106)),"hlb23.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("hlb0.png",CCRectMake(0, 0, 45, 17)),"hlb0.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("hlb1.png",CCRectMake(0, 0, 75, 46)),"hlb1.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("hlb2.png",CCRectMake(0, 0, 79, 66)),"hlb2.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("hlb3.png",CCRectMake(0, 0, 75, 66)),"hlb3.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("hlb4.png",CCRectMake(0, 0, 77, 106)),"hlb4.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("hlb6.png",CCRectMake(0, 0, 77, 106)),"hlb6.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("hlb8.png",CCRectMake(0, 0, 77, 106)),"hlb8.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("hlb9.png",CCRectMake(0, 0, 77, 106)),"hlb9.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("hlb10.png",CCRectMake(0, 0, 75, 106)),"hlb10.png");

		pCache->addSpriteFrame(CCSpriteFrame::create("hlb11.png",CCRectMake(0, 0, 107, 104)),"hlb11.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("hlb12.png",CCRectMake(0, 0, 115, 106)),"hlb12.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("hlb13.png",CCRectMake(0, 0, 105, 110)),"hlb13.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("hlb14.png",CCRectMake(0, 0, 111, 110)),"hlb14.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("hlb15.png",CCRectMake(0, 0, 115, 112)),"hlb15.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("hlb16.png",CCRectMake(0, 0, 109, 112)),"hlb16.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("hlb17.png",CCRectMake(0, 0, 111, 112)),"hlb17.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("hlb18.png",CCRectMake(0, 0, 117, 112)),"hlb18.png");

		pCache->addSpriteFrame(CCSpriteFrame::create("BossHP01.png",CCRectMake(0, 0, 74, 38)),"BossHP01.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("BossHP02.png",CCRectMake(0, 0, 74, 38)),"BossHP02.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("BossHP03.png",CCRectMake(0, 0, 74, 38)),"BossHP03.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("BossHP04.png",CCRectMake(0, 0, 74, 38)),"BossHP04.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("BossHP05.png",CCRectMake(0, 0, 74, 38)),"BossHP05.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("BossHP06.png",CCRectMake(0, 0, 74, 38)),"BossHP06.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("BossHP07.png",CCRectMake(0, 0, 74, 38)),"BossHP07.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("BossHP08.png",CCRectMake(0, 0, 74, 38)),"BossHP08.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("BossHP09.png",CCRectMake(0, 0, 74, 38)),"BossHP09.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("BossHP10.png",CCRectMake(0, 0, 74, 38)),"BossHP10.png");

		
		
		CBattleMenu* pMenu = CBattleMenu::create();
		addChild(pMenu);

        bRet = true;
    } while (0);

    return bRet;
}

void CBattleScene::EnterStage(int idStage)
{
	const TPL_STAGE* pStage = CDataManager::sharedDataManager()->findStage(idStage);
	if (!pStage)
	{
		return ;
	}
	const TPL_MAP* pMap = CDataManager::sharedDataManager()->findMap(pStage->idMap);
	if (!pMap)
	{
		return;
	}

	CCSpriteFrameCache *pCache =  CCSpriteFrameCache::sharedSpriteFrameCache();
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//地图背景
	CCSprite* pSpriteBg = CCSprite::createWithSpriteFrameName(pMap->mapBg.c_str());
	pSpriteBg->setPosition(ccp(size.width/2, size.height/2));
	pSpriteBg->setScale(CCDirector::sharedDirector()->getContentScaleFactor());

	this->addChild(pSpriteBg, -1);

	//地图前景
	CCSprite* pSpriteMap = CCSprite::create(pMap->mapFore.c_str());
	pSpriteMap->setPosition(ccp(size.width/2, pSpriteMap->getContentSize().height/2));
	pSpriteMap->setScale(CCDirector::sharedDirector()->getContentScaleFactor());
	this->addChild(pSpriteMap, 0);

	//加载地图
	m_pMap = NULL;
	m_pMap = CCTMXTiledMap::create(pMap->map.c_str());
	addChild(m_pMap, 1, kTagTileMap);
	m_pMap->setPosition(ccp(0, 0));
	ReadTmxMap();

	//怪物
	CBattleMonster* pMon = CBattleMonster::create();
	pMon->initWithSpriteFrameName("fat_boss_green01.png");
	CCAnimation* pAni = CCAnimation::create();
	CCSpriteFrame* pFrame = pCache->sharedSpriteFrameCache()->spriteFrameByName("fat_boss_green01.png");
	pAni->addSpriteFrame(pFrame);
	pFrame = pCache->sharedSpriteFrameCache()->spriteFrameByName("fat_boss_green02.png");
	pAni->addSpriteFrame(pFrame);
	pAni->setDelayPerUnit(0.2f);
	CCActionInterval* pAnimate = CCAnimate::create(pAni);
	CCActionInterval* pRepForver = CCRepeatForever::create(pAnimate);
	pMon->runAction(pRepForver);
	addChild(pMon, 3, kTagMonster);

	CCPoint ptStart;
	const PATH_POINT* pPoint = CDataManager::sharedDataManager()->GetPointByName(pMap->startPos.c_str());
	if (pPoint)
	{
		ptStart = ccp(pPoint->x, pPoint->y);
		pMon->setPosition(ccp(size.width/2, size.height/2));
	}

	//地图开始点
	CCSprite* pSpriteStart = CCSprite::createWithSpriteFrameName("start01.png");
	pSpriteStart->setAnchorPoint(ccp(0.5, 0));
	pSpriteStart->setPosition(ptStart);
	addChild(pSpriteStart, 3);

	//萝卜
	CCSprite* pSpriteCarrot = CCSprite::createWithSpriteFrameName("hlb10.png");
	pSpriteCarrot->setAnchorPoint(ccp(0.25, 0));
	CCPoint ptStand;

	//暂时配置为路径结束点的前一个点
	pPoint = CDataManager::sharedDataManager()->GetPointByName(pMap->endPos.c_str());
	if (pPoint)
	{
		ptStand = ccp(pPoint->x, pPoint->y);
	}
	
	pSpriteCarrot->setPosition(ptStand);
	addChild(pSpriteCarrot, 3, kTagCarrot);
	ShowCarrotFunction();


	//萝卜背景
	CCSprite* pSpriteCarrotBg = CCSprite::createWithSpriteFrameName("hlb0.png");
	pSpriteCarrotBg->setAnchorPoint(ccp(0.5, 0.5));
	//暂时配置为路径结束点的前一个点
	pSpriteCarrotBg->setPosition(ptStand);
	addChild(pSpriteCarrotBg, 2);

	CCFileUtils::sharedFileUtils()->addSearchPath("data/battle/theme1/clound");

	pCache->addSpriteFrame(CCSpriteFrame::create("cloud01.png",CCRectMake(0, 0, 80, 60)),"cloud01.png");
	pCache->addSpriteFrame(CCSpriteFrame::create("cloud03.png",CCRectMake(0, 0, 80, 64)),"cloud03.png");
	pCache->addSpriteFrame(CCSpriteFrame::create("cloud04.png",CCRectMake(0, 0, 146, 80)),"cloud04.png");
	pCache->addSpriteFrame(CCSpriteFrame::create("cloud05.png",CCRectMake(0, 0, 160, 116)),"cloud05.png");
	pCache->addSpriteFrame(CCSpriteFrame::create("cloud07.png",CCRectMake(0, 0, 152, 160)),"cloud07.png");

	CDataManager::sharedDataManager()->findMapObj(pMap->idMap, m_vecMapObj);
	CCPoint ptObj(0, 0);
	vector<TPL_MAP_OBJ>::iterator iterTemp;
	for (iterTemp = m_vecMapObj.begin(); iterTemp != m_vecMapObj.end(); iterTemp++)
	{
		CBattleMonster* pMapObj = CBattleMonster::create();
		pMapObj->initWithSpriteFrameName(iterTemp->objAni.c_str());
		const MAP_CELL* pCell = CDataManager::sharedDataManager()->findMapCell(iterTemp->pos.c_str());
		if (pCell)
		{
			ptObj = ccp(pCell->x, pCell->y);
		}
		pMapObj->setPosition(ptObj);
		ptObj = ccp(0, 0);
		pMapObj->setAnchorPoint(ptObj);
		addChild(pMapObj, 3, kTagMapObjStart + iterTemp->idObj);

		if (iterTemp->action != 0)
		{
			CCActionInterval* pAction = NULL;
			switch(iterTemp->action)
			{
			case 1://上下移动
				{
					CCPoint pos = pMapObj->getPosition();
					CCPoint posMove2 = pos;
					posMove2.y += iterTemp->data1;
					CCActionInterval* pMove2 = CCMoveTo::create(2.0f, posMove2);
					CCActionInterval* pMoveReverse = CCMoveTo::create(2.0f, pos);
					CCActionInterval* pDeley = CCDelayTime::create(5.0f);
					pAction = CCRepeatForever::create(CCSequence::create(pMove2, pMoveReverse, pDeley, NULL));
				}
				break;
			case 2://左右移动
				{
					CCPoint pos = pMapObj->getPosition();
					CCPoint posMove2 = pos;
					posMove2.x += iterTemp->data1;
					CCActionInterval* pMove2 = CCMoveTo::create(2.0f, posMove2);
					CCActionInterval* pMoveReverse = CCMoveTo::create(2.0f, pos);
					CCActionInterval* pDeley = CCDelayTime::create(5.0f);
					pAction = CCRepeatForever::create(CCSequence::create(pMove2, pMoveReverse, pDeley, NULL));
				}
				break;
			}
			if (pAction)
			{
				pMapObj->runAction(pAction);
			}
		}
		
	}
	ShowArrow(pMap->idMap);

}

void CBattleScene::ReadTmxMap()
{
	CCTMXObjectGroup* pObjGrp = m_pMap->objectGroupNamed("PATH");  
	if (pObjGrp)  
	{
		CCArray* objArray = pObjGrp->getObjects();  

		CDataManager::sharedDataManager()->ReadMapInfo(objArray);
	}
}

void CBattleScene::onEnter()
{
	CCLayer::onEnter();

	ShowCountDownLayer();
	
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 10, true);
}

void CBattleScene::onExit()
{
	CCLayer::onExit();
}

void CBattleScene::ShowCarrotFunction()
{
	CCNode* pSprite = getChildByTag(kTagCarrot);

	CCActionInterval* pCarrotAction;

	int nRand = rand()%3;
	switch(nRand)
	{
	case 0:
		{
			CCSpriteFrameCache *pCache =  CCSpriteFrameCache::sharedSpriteFrameCache();
			CCArray* ary = CCArray::create();
			for (int nIndex = 0; nIndex <= 8;nIndex++)
			{
				CCString* pStr = CCString::createWithFormat("hlb1%d.png", nIndex);
				ary->addObject(pCache->sharedSpriteFrameCache()->spriteFrameByName(pStr->getCString()));
			}
			CCAnimation* pAnimation = CCAnimation::createWithSpriteFrames(ary, 0.1f);
			pAnimation->setRestoreOriginalFrame(true);
			CCActionInterval* pAni = CCAnimate::create(pAnimation);
			CCActionInterval* pAniRevese = pAni->reverse();
			pCarrotAction = CCSequence::createWithTwoActions(pAni, pAniRevese);
			pSprite->setAnchorPoint(ccp(0.5, 0));
		}
		break;
	case 1:
		{
			CCActionInterval* pRotate = CCRotateTo::create(0.3f, -30.0f);
			CCActionInterval* pRotateReverse = CCRotateTo::create(0.3f, 0.0f);
			CCActionInterval* pRotate2 = CCRotateTo::create(0.1f, 10.0f);
			CCActionInterval* pRotateReverse2 = CCRotateTo::create(0.1f, 0.0f);
			CCActionInterval* pSequeAction = CCSequence::create(pRotate, pRotateReverse, pRotate2, pRotateReverse2, NULL);
			CCActionInterval* pRep3 = CCRepeat::create(pSequeAction, 3);
			pCarrotAction = CCSequence::create(pRep3, pRotate, pRotateReverse, NULL);
		}
		break;
	case 2:
		{
			CCSpriteFrameCache *pCache =  CCSpriteFrameCache::sharedSpriteFrameCache();
			CCAnimation* pAni = CCAnimation::create();
			CCSpriteFrame* pFrame = pCache->sharedSpriteFrameCache()->spriteFrameByName("hlb21.png");
			pAni->addSpriteFrame(pFrame);
			pFrame = pCache->sharedSpriteFrameCache()->spriteFrameByName("hlb22.png");
			pAni->addSpriteFrame(pFrame);
			pFrame = pCache->sharedSpriteFrameCache()->spriteFrameByName("hlb23.png");
			pAni->addSpriteFrame(pFrame);
			pAni->setDelayPerUnit(0.05f);
			CCActionInterval* pAnimate = CCAnimate::create(pAni);
			CCActionInterval* pAnimateReverse = pAnimate->reverse();
			pCarrotAction = CCSequence::createWithTwoActions(pAnimate, pAnimateReverse);
		}
		break;
	}

	CCActionInterval* pCarrotDeley = CCDelayTime::create(5.0f);
	CCCallFunc* pCarrotCall = CCCallFunc::create(this, callfunc_selector(CBattleScene::ShowCarrotFunction));
	CCCallFuncND* pCarrotActionOver = CCCallFuncND::create(this, callfuncND_selector(CBattleScene::ShowCarrotActionOver), (void*)nRand);
	CCActionInterval* pCarrotSeq = CCSequence::create(pCarrotAction, pCarrotActionOver, pCarrotDeley, pCarrotCall, NULL);
	pSprite->runAction(pCarrotSeq);
}

void CBattleScene::ShowCarrotActionOver( CCNode* pSprite, void* params )
{
	pSprite->setAnchorPoint(ccp(0.25, 0));
}

void CBattleScene::ShowCountDownLayer()
{
	CCountDownLayer* pCountDownLayer = CCountDownLayer::create();
	pCountDownLayer->init();
	addChild(pCountDownLayer, 10, COUNTDOWN_LAYER);
	pCountDownLayer->start();
}

void CBattleScene::Start()
{
	//removeChildByTag(COUNTDOWN_LAYER);
}

bool CBattleScene::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void CBattleScene::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{

}

void CBattleScene::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void CBattleScene::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{

}

void CBattleScene::ShowArrow(int idMap)
{
	const TPL_MAP* pMap = CDataManager::sharedDataManager()->findMap(idMap);
	if (!pMap)
	{
		return;
	}
	CCPoint ptStart;
	CCPoint ptNext;
	const PATH_POINT* pPoint = CDataManager::sharedDataManager()->GetPointByName(pMap->startPos.c_str());
	if (pPoint)
	{
		ptStart = ccp(pPoint->x, pPoint->y);

		pPoint = CDataManager::sharedDataManager()->GetNextStep(pPoint->idx);
		if (pPoint)
		{
			ptNext = ccp(pPoint->x, pPoint->y);
		}
	}

	float fRotation = 270.0f;
	int nDirector = DIRECTION_DOWN;//方向
	int offsetX = ptNext.x - ptStart.x;
	int offsetY = ptNext.y - ptStart.y;
	if (offsetX)
	{
		if (offsetX < 0)
		{
			nDirector = DIRECTION_LEFT;
			fRotation = 0.0f;
		}
		else
		{
			nDirector = DIRECTION_RIGHT;
			fRotation = 180.0f;
		}
	}
	else if (offsetY)
	{
		if (offsetY < 0)
		{
			nDirector = DIRECTION_UP;
			fRotation = 90.0f;
		}
	}
	
	
	CCPoint ptSprite = ptStart;
	CCSpriteFrameCache *pCache =  CCSpriteFrameCache::sharedSpriteFrameCache();
	pCache->addSpriteFrame(CCSpriteFrame::create("arrow.png",CCRectMake(0, 0, 38, 52)),"arrow.png");
	for (int nIndex = 0; nIndex < 3; nIndex++)
	{
		m_arySp[nIndex] = CCSprite::createWithSpriteFrameName("arrow.png");
		m_arySp[nIndex]->setRotation(fRotation);
		if (offsetX)
		{
			ptSprite.x = ptStart.x + nIndex * 30 * (offsetX/abs(offsetX));
		}
		if (offsetY)
		{
			ptSprite.y = ptStart.y + nIndex * 30 * (offsetY/abs(offsetY));
		}
		m_arySp[nIndex]->setPosition(ptSprite);
		addChild(m_arySp[nIndex], 4);
		m_arySp[nIndex]->setScale(0.1f);
		m_arySp[nIndex]->setOpacity(0);

		CCActionInterval* scaleSmallAction = CCScaleTo::create(0.0f, 0.1f);
		CCActionInterval* pBeforeFadeAction = CCDelayTime::create(nIndex * 0.15f);
		CCActionInterval* fadeOutAction = CCFadeOut::create(0.15f);
		CCActionInterval* pAfterFadeAction = CCDelayTime::create( (3 - nIndex) * 0.15f);
		CCActionInterval* pSeqFadeOut = CCSequence::create(pBeforeFadeAction, fadeOutAction, scaleSmallAction, pAfterFadeAction, NULL);

		CCActionInterval* scaleAction = CCScaleTo::create(0.15f, 1.0f);
		CCActionInterval* fadeAction = CCFadeIn::create(0.15f);
		CCActionInterval* pBeforeDeleyAction = CCDelayTime::create(nIndex * 0.15f);
		CCActionInterval* pSpawnAction = CCSpawn::create(scaleAction, fadeAction, NULL);
		CCActionInterval* pDeleyAction = CCDelayTime::create( (3 - nIndex) * 0.15f);
		CCActionInterval* pSeqAction = CCSequence::create(pBeforeDeleyAction, pSpawnAction, pDeleyAction, pSeqFadeOut, NULL);
		CCActionInterval* pRepAction = CCRepeat::create(pSeqAction, 99);
		m_arySp[nIndex]->runAction(pRepAction);
	}
	
	

}

























