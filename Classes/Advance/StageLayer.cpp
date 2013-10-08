#include "StageLayer.h"
#include "GameDefine.h"
#include "AdvanceScene.h"
#include "BattleScene.h"

using namespace cocos2d;
USING_NS_CC_EXT;


// on "init" you need to initialize your instance
bool CStageLayer::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());

        //////////////////////////////////////////////////////////////////////////
        // add your codes below...
        //////////////////////////////////////////////////////////////////////////
		CCFileUtils::sharedFileUtils()->addSearchPath("data/advance/stage1");

		CCSpriteFrameCache *pCache =  CCSpriteFrameCache::sharedSpriteFrameCache();

		pCache->addSpriteFrame(CCSpriteFrame::create("theme_pos_normal.png",CCRectMake(0, 0, 15, 13)),"theme_pos_normal.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("theme_pos_active.png",CCRectMake(0, 0, 15, 13)),"theme_pos_active.png");

		pCache->addSpriteFrame(CCSpriteFrame::create("ss_map01.png",CCRectMake(0, 0, 506, 334)),"ss_map01.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("ss_map02.png",CCRectMake(0, 0, 506, 334)),"ss_map02.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("ss_map03.png",CCRectMake(0, 0, 506, 334)),"ss_map03.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("ss_map04.png",CCRectMake(0, 0, 506, 334)),"ss_map04.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("ss_map05.png",CCRectMake(0, 0, 506, 334)),"ss_map05.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("ss_map06.png",CCRectMake(0, 0, 506, 334)),"ss_map06.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("ss_map07.png",CCRectMake(0, 0, 506, 334)),"ss_map07.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("ss_map08.png",CCRectMake(0, 0, 506, 334)),"ss_map08.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("ss_map09.png",CCRectMake(0, 0, 506, 334)),"ss_map09.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("ss_map10.png",CCRectMake(0, 0, 506, 334)),"ss_map10.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("ss_map11.png",CCRectMake(0, 0, 506, 334)),"ss_map11.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("ss_map12.png",CCRectMake(0, 0, 506, 334)),"ss_map12.png");
		
		pCache->addSpriteFrame(CCSpriteFrame::create("ss_cloud.png",CCRectMake(0, 0, 960, 152)),"ss_cloud.png");

		pCache->addSpriteFrame(CCSpriteFrame::create("ss_back_norma.png",CCRectMake(0, 0, 38, 32)),"ss_back_norma.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("ss_back_pressed.png",CCRectMake(0, 0, 66, 58)),"ss_back_pressed.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("choice.png",CCRectMake(0, 0, 120, 32)),"choice.png");

		pCache->addSpriteFrame(CCSpriteFrame::create("ss_play_normal_CN.png",CCRectMake(0, 0, 226, 72)),"ss_play_normal_CN.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("ss_play_pressed_CN.png",CCRectMake(0, 0, 226, 72)),"ss_play_pressed_CN.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("ss_waves_1.png",CCRectMake(0, 0, 203, 23)),"ss_waves_1.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("ss_waves_10.png",CCRectMake(0, 0, 219, 23)),"ss_waves_10.png");

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		CCSprite* spBg = CCSprite::create("themescene3-hd.png");
		spBg->setPosition(ccp(size.width/2 , size.height/2));
		this->addChild(spBg,0);

		//返回主页按钮
		CCMenuItemImage* pHome = CCMenuItemImage::create("ss_back_normal.png", "ss_back_pressed.png", this, menu_selector(CStageLayer::onBtnHomeClick));
		CCSize sNormal = pHome->getNormalImage()->getContentSize();
		CCSize sSel = pHome->getSelectedImage()->getContentSize();
		CCPoint posAnchor((sSel.width-sNormal.width)/2/sSel.width, (sSel.height-sNormal.height)/2/sSel.height);
		pHome->getSelectedImage()->setAnchorPoint(posAnchor);
		CCMenu* menuHome = CCMenu::create(pHome, NULL);

		//menuHome->alignItemsHorizontally();
		menuHome->setPosition(40, size.height - 30);
		addChild(menuHome,3);

		//帮助按钮
		CCMenuItemImage* pHelp = CCMenuItemImage::create("ss_help_normal.png", "ss_help_pressed.png", this, menu_selector(CStageLayer::onBtnHelpClick));
		sNormal = pHelp->getNormalImage()->getContentSize();
		sSel = pHelp->getSelectedImage()->getContentSize();
		posAnchor = ccp((sSel.width-sNormal.width)/2/sSel.width, (sSel.height-sNormal.height)/2/sSel.height);
		pHelp->getSelectedImage()->setAnchorPoint(posAnchor);
		CCMenu* menuHelp = CCMenu::create(pHelp, NULL);

		menuHelp->alignItemsHorizontally();
		menuHelp->setPosition(size.width - 40, size.height - 30);
		addChild(menuHelp,3);

		//选择关卡
		CCSprite* pChoice = CCSprite::createWithSpriteFrameName("choice.png");
		pChoice->setPosition(ccp(size.width/2, size.height - 30));
		addChild(pChoice);

		//关卡选择前景
		CCSprite* pForground = CCSprite::createWithSpriteFrameName("ss_cloud.png");
		pForground->setAnchorPoint(ccp(0,0));
		pForground->setPosition(ccp(0, 0));
		addChild(pForground, 2);

		//关卡翻页
		m_pScrollView = NULL;
		m_pScrollView = CMyPageView::create(this, CCSizeMake(960, 340), NULL);
		m_pScrollView->setDelegate(this);
		m_pScrollView->setDirection(kCCScrollViewDirectionHorizontal);
		m_pScrollView->setContentOffset(CCPointZero);
		m_pScrollView->setPageCnt(12);
		m_pScrollView->setPageSize(CCSizeMake(560, 340));
		m_pScrollView->setPosition(0, size.height/2 - 170);
		m_pScrollView->setViewOffsetSize(CCSizeMake(200, 0));
		m_pScrollView->setPageDelegate(this);
		//pLayer->setContentSize(CCSizeMake(size.width*5, 600));
		this->addChild(m_pScrollView, 1);
		m_pScrollView->reloadData();
		m_pScrollView->setCurPage(1);
		
		//开始按钮
		CCMenuItemImage* pPlay = CCMenuItemImage::create("ss_play_normal_CN.png", "ss_play_pressed_CN.png", this, menu_selector(CStageLayer::onBtnPlayClick));
		CCMenu* menuPlay = CCMenu::create(pPlay, NULL);

		menuPlay->alignItemsHorizontally();
		menuPlay->setPosition(size.width/2, 60);
		addChild(menuPlay,3);

		//当前关卡波数
		CCSprite* pWaves = CCSprite::create();
		pWaves->initWithSpriteFrameName("ss_waves_10.png");
		pWaves->setAnchorPoint(CCPointZero);
		pWaves->setPosition(ccp(size.width/2, size.height - 150));
		addChild(pWaves, 2);

        bRet = true;
    } while (0);

    return bRet;
}

cocos2d::CCSize CStageLayer::cellSizeForTable( CCTableView *table )
{
	 return CCSizeMake(560, 340);
}

CCTableViewCell* CStageLayer::tableCellAtIndex( CCTableView *table, unsigned int idx )
{
	CCString *string = CCString::createWithFormat("%d", idx);
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		CCString *fileName = CCString::createWithFormat("ss_map%02d.png", idx+1);
		CCSprite* sprite = CCSprite::create(fileName->getCString());
		CCSize sizeCell = cellSizeForTable(table);
		sprite->setPosition(ccp(sizeCell.width/2,sizeCell.height/2));
		sprite->setColor(ccGRAY);
		cell->addChild(sprite, 0, 123);
	}
	else
	{
		CCSprite* sprite = dynamic_cast<CCSprite*>(cell->getChildByTag(123));
		if (sprite)
		{
			CCString *fileName = CCString::createWithFormat("ss_map%02d.png", idx+1);
			sprite->initWithSpriteFrameName(fileName->getCString());
			CCSize sizeCell = cellSizeForTable(table);
			sprite->setColor(ccGRAY);
			sprite->setPosition(ccp(sizeCell.width/2,sizeCell.height/2));
		}
		
	}

	return cell;
}

unsigned int CStageLayer::numberOfCellsInTableView( CCTableView *table )
{
	return 12;
}

void CStageLayer::tableCellTouched( cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell )
{
	CCLOG("cell touched at index: %i", cell->getIdx());
	showBattle(cell->getIdx());
}

void CStageLayer::onBtnHomeClick( CCObject* pSrcObj )
{
	/*CCScene* pScene = CStartScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);*/

	CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();

	CCNode* pNode = pScene->getChildByTag(ADVANCE_LAYER);
	if (!pNode)
	{
		CAdvanceScene* pLayer = CAdvanceScene::create();
		pScene->addChild(pLayer, 0, ADVANCE_LAYER);
	}

	pScene->removeChildByTag(STAGE_LAYER);
}

void CStageLayer::onBtnHelpClick( CCObject* pSrcObj )
{

}

void CStageLayer::scrollViewDidScroll( cocos2d::extension::CCScrollView* view )
{
	
}




void CStageLayer::onEnter()
{
	CCLayer::onEnter();
//	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, false);
}

void CStageLayer::onExit()
{
	CCLayer::onExit();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

void CStageLayer::onPageChange( CMyPageView *table, int oldPage, int newPage )
{
	if (m_pScrollView)
	{
		CCTableViewCell* pCell = m_pScrollView->cellAtIndex(oldPage - 1);
		if (pCell)
		{
			CCSprite* sprite = dynamic_cast<CCSprite*>(pCell->getChildByTag(123));
			if (sprite)
			{
				sprite->setColor(ccGRAY);
			}
		}

		pCell = m_pScrollView->cellAtIndex(newPage - 1);
		if (pCell)
		{
			CCSprite* sprite = dynamic_cast<CCSprite*>(pCell->getChildByTag(123));
			if (sprite)
			{
				sprite->setColor(ccWHITE);
			}
		}
	}
}

void CStageLayer::onBtnPlayClick( CCObject* pSrcObj )
{
	showBattle(m_pScrollView->getCurPage());
}

void CStageLayer::showBattle( int nSel )
{
	CCScene* pScene = CBattleScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
	CBattleScene* pLayer = dynamic_cast<CBattleScene*>(pScene->getChildByTag(BATTLE_LAYER));
	if (pLayer)
	{
		pLayer->EnterStage(1001);
	}
}













