#include "AdvanceScene.h"
#include "StartScene.h"
#include "StageLayer.h"
#include "GameDefine.h"

using namespace cocos2d;
USING_NS_CC_EXT;

CCScene* CAdvanceScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

		scene->setTag(ADVANCE_SCENE);

        // 'layer' is an autorelease object
        CAdvanceScene *layer = CAdvanceScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer, 0, ADVANCE_LAYER);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CAdvanceScene::init()
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
		CCFileUtils::sharedFileUtils()->addSearchPath("data/advance");
		CCFileUtils::sharedFileUtils()->addSearchPath("data/advance/book");

		CCSpriteFrameCache *pCache =  CCSpriteFrameCache::sharedSpriteFrameCache();

		pCache->addSpriteFrame(CCSpriteFrame::create("theme_pos_normal.png",CCRectMake(0, 0, 15, 13)),"theme_pos_normal.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("theme_pos_active.png",CCRectMake(0, 0, 15, 13)),"theme_pos_active.png");

		pCache->addSpriteFrame(CCSpriteFrame::create("theme_pack01.png",CCRectMake(0, 0, 650, 512)),"theme_pack01.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("theme_pack02.png",CCRectMake(0, 0, 666, 514)),"theme_pack02.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("theme_pack03.png",CCRectMake(0, 0, 668, 512)),"theme_pack03.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("theme_pack04.png",CCRectMake(0, 0, 660, 514)),"theme_pack04.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("theme_pack05.png",CCRectMake(0, 0, 628, 512)),"theme_pack05.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("theme_pack06.png",CCRectMake(0, 0, 668, 526)),"theme_pack06.png");
		
		

		CCSize size = CCDirector::sharedDirector()->getWinSize();

		CCSprite* spBg = CCSprite::create("themescene3-hd.png");
		spBg->setPosition(ccp(size.width/2 , size.height/2));
		this->addChild(spBg);

		//返回主页按钮
		CCMenuItemImage* pHome = CCMenuItemImage::create("theme_home_normal.png", "theme_home_pressed.png", this, menu_selector(CAdvanceScene::onBtnHomeClick));
		CCSize sNormal = pHome->getNormalImage()->getContentSize();
		CCSize sSel = pHome->getSelectedImage()->getContentSize();
		CCPoint posAnchor((sSel.width-sNormal.width)/2/sSel.width, (sSel.height-sNormal.height)/2/sSel.height);
		pHome->getSelectedImage()->setAnchorPoint(posAnchor);
		CCMenu* menuHome = CCMenu::create(pHome, NULL);

		menuHome->alignItemsHorizontally();
		menuHome->setPosition(40, size.height - 30);
		addChild(menuHome);

		//帮助按钮
		CCMenuItemImage* pHelp = CCMenuItemImage::create("ss_help_normal.png", "ss_help_pressed.png", this, menu_selector(CAdvanceScene::onBtnHelpClick));
		sNormal = pHelp->getNormalImage()->getContentSize();
		sSel = pHelp->getSelectedImage()->getContentSize();
		posAnchor = ccp((sSel.width-sNormal.width)/2/sSel.width, (sSel.height-sNormal.height)/2/sSel.height);
		pHelp->getSelectedImage()->setAnchorPoint(posAnchor);
		CCMenu* menuHelp = CCMenu::create(pHelp, NULL);

		menuHelp->alignItemsHorizontally();
		menuHelp->setPosition(size.width - 40, size.height - 30);
		addChild(menuHelp);

		//table
		/*CCTableView* pTableView = CCTableView::create(this, CCSizeMake(size.width, size.height - 140));
		pTableView->setDirection(kCCScrollViewDirectionHorizontal);
		pTableView->setPosition(ccp(0 , 30));
		pTableView->setDelegate(this);
		this->addChild(pTableView);
		pTableView->reloadData();*/

		//选择关卡
		CCSprite* pChoice = CCSprite::create("choice.png");
		pChoice->setPosition(ccp(size.width/2, size.height - 30));
		addChild(pChoice);

		//关卡翻页
		
		/*CCLayer* pLayer = CCLayer::create();
		for (int nIndex = 0; nIndex < 5; nIndex++)
		{
			CCString *string = CCString::createWithFormat("theme_pack0%d.png", nIndex+1);
			CCSprite* pSprite = CCSprite::create(string->getCString());
			pSprite->setPosition(ccp(size.width * (nIndex + 0.5f), size.height/2-20));
			pLayer->addChild(pSprite);
		}*/
		m_pScrollView = CMyPageView::create(this, CCSizeMake(size.width, 600), NULL);
		m_pScrollView->setDelegate(this);
		m_pScrollView->setDirection(kCCScrollViewDirectionHorizontal);
		m_pScrollView->setContentOffset(CCPointZero);
		m_pScrollView->setPageCnt(5);
		m_pScrollView->setPageSize(CCSizeMake(size.width, 600));
		//pLayer->setContentSize(CCSizeMake(size.width*5, 600));
		this->addChild(m_pScrollView);
		m_pScrollView->reloadData();

		//向左与向右按钮
		CCMenuItemImage* pBtnLeft = CCMenuItemImage::create("theme_pointleft_normal.png", "theme_pointleft_pressed.png", this, menu_selector(CAdvanceScene::onBtnLeftClick));
		CCMenu* menuBtnLeft = CCMenu::create(pBtnLeft, NULL);
		menuBtnLeft->setPosition(ccp(60, size.height/2));
		addChild(menuBtnLeft);

		CCMenuItemImage* pBtnRight = CCMenuItemImage::create("theme_pointright_normal.png", "theme_pointright_pressed.png", this, menu_selector(CAdvanceScene::onBtnRightClick));
		CCMenu* menuBtnRight = CCMenu::create(pBtnRight, NULL);
		menuBtnRight->setPosition(ccp(size.width - 60, size.height/2));
		addChild(menuBtnRight);

		
		//页数
		for (int nIndex = 0;nIndex < 5; nIndex++)
		{
			CCSprite *pPoint = CCSprite::createWithSpriteFrameName("theme_pos_normal.png");
			pPoint->setTag(nIndex);
			int nPointWidth = pPoint->getContentSize().width + 10;
			pPoint->setPosition(ccp((size.width - 5 * nPointWidth)/2 + nPointWidth * (nIndex-1), 30));
			this->addChild(pPoint);
		}
		CCSprite *pPoint = (CCSprite *)this->getChildByTag(0);
		pPoint->setDisplayFrame(pCache->spriteFrameByName("theme_pos_active.png"));

        bRet = true;
    } while (0);

    return bRet;
}

cocos2d::CCSize CAdvanceScene::cellSizeForTable( CCTableView *table )
{
	 return CCSizeMake(960, 600);
}

CCTableViewCell* CAdvanceScene::tableCellAtIndex( CCTableView *table, unsigned int idx )
{
	CCString *string = CCString::createWithFormat("%d", idx);
	CCTableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new CCTableViewCell();
		cell->autorelease();
		CCString *fileName = CCString::createWithFormat("theme_pack0%d.png", idx+1);
		CCSprite* sprite = CCSprite::create(fileName->getCString());
		sprite->setPosition(ccp(480,300));
		cell->addChild(sprite, 0, 123);
	}
	else
	{
		CCSprite* sprite = dynamic_cast<CCSprite*>(cell->getChildByTag(123));
		if (sprite)
		{
			CCString *fileName = CCString::createWithFormat("theme_pack0%d.png", idx+1);
			sprite->initWithSpriteFrameName(fileName->getCString());
			sprite->setPosition(ccp(480,300));
		}
		
	}

	return cell;
}

unsigned int CAdvanceScene::numberOfCellsInTableView( CCTableView *table )
{
	return 5;
}

void CAdvanceScene::tableCellTouched( cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell )
{
	CCLOG("cell touched at index: %i", cell->getIdx());
	showStageLayer(cell->getIdx());
}

void CAdvanceScene::onBtnHomeClick( CCObject* pSrcObj )
{
	CCScene* pScene = CStartScene::scene();
	CCDirector::sharedDirector()->replaceScene(pScene);
}

void CAdvanceScene::onBtnHelpClick( CCObject* pSrcObj )
{

}

void CAdvanceScene::onBtnLeftClick( CCObject* pSrcObj )
{
	int nPage = m_pScrollView->getCurPage();
	m_pScrollView->setCurPage(nPage-1);
}

void CAdvanceScene::onBtnRightClick( CCObject* pSrcObj )
{
	int nPage = m_pScrollView->getCurPage();
	m_pScrollView->setCurPage(nPage+1);
}

void CAdvanceScene::scrollViewDidScroll( cocos2d::extension::CCScrollView* view )
{
	CCSpriteFrameCache *pCache =  CCSpriteFrameCache::sharedSpriteFrameCache();
	for (int nIndex = 0; nIndex < 5; nIndex++)
	{
		CCSprite *pPoint = (CCSprite *)this->getChildByTag(nIndex);
		if (pPoint)
		{
			pPoint->setDisplayFrame(pCache->spriteFrameByName("theme_pos_normal.png"));
		}
	}
	

	
	CCSprite *pPoint = (CCSprite *)this->getChildByTag(m_pScrollView->getCurPage()-1);
	if (pPoint)
	{
		pPoint->setDisplayFrame(pCache->spriteFrameByName("theme_pos_active.png"));
	}
}




void CAdvanceScene::onEnter()
{
	CCLayer::onEnter();
//	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, false);
}

void CAdvanceScene::onExit()
{
	CCLayer::onExit();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}

void CAdvanceScene::showStageLayer(int idx)
{
	CCScene* pScene = CCDirector::sharedDirector()->getRunningScene();

	CCNode* pNode = pScene->getChildByTag(STAGE_LAYER);
	if (!pNode)
	{
		CStageLayer* pLayer = CStageLayer::create();
		pScene->addChild(pLayer, 0, STAGE_LAYER);
	}

	pScene->removeChildByTag(ADVANCE_LAYER);
	/*pNode = pScene->getChildByTag(ADVANCE_LAYER);
	if (pNode)
	{
		pNode->setVisible(false);
	}*/
}














