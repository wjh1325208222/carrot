#include "StartScene.h"
#include "AdvanceScene.h"
#include "GameDefine.h"

using namespace cocos2d;

CCScene* CStartScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

		scene->setTag(START_SCENE);

        // 'layer' is an autorelease object
        CStartScene *layer = CStartScene::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CStartScene::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());
		
		CCSize szWin = CCDirector::sharedDirector()->getWinSize();

		//开始界面背景图
		CCSprite* pSpriteBg = CCSprite::create("start.png");
		pSpriteBg->setPosition(ccp(szWin.width/2, szWin.height/2));
		this->addChild(pSpriteBg);
		
		//保卫萝卜标题
		CCSprite* pSpriteTitle = CCSprite::create("title.png");
		pSpriteTitle->setPosition(ccp(szWin.width/2, 280));
		this->addChild(pSpriteTitle,10);

		//冒险模式和BOSS模式按钮
		CCMenuItemImage* menuAdvance = CCMenuItemImage::create("btn1.png","btn2.png",this, menu_selector(CStartScene::onBtnAdvanceClick));
		CCMenuItemImage* menuBoss = CCMenuItemImage::create("btn3.png","btn4.png",this, menu_selector(CStartScene::onBtnBossClick));
		CCMenu* pMenu = CCMenu::create(menuAdvance, menuBoss, NULL);
		pMenu->alignItemsHorizontallyWithPadding(20.f);
		pMenu->setPosition(ccp(szWin.width/2, 100));
		addChild(pMenu);

		//萝卜
		CCSprite* spCarrot = CCSprite::create("carrot.png");
		spCarrot->setPosition(ccp(szWin.width/2, szWin.height/2 + 30));
		this->addChild(spCarrot, 9);

		//叶子1
		CCSprite* spLeaf1 = CCSprite::create("leaf-1.png");
		spLeaf1->setPosition(ccp(szWin.width/2 - 70, szWin.height/2 + 110));
		this->addChild(spLeaf1, 7);

		//叶子2
		CCSprite* spLeaf2 = CCSprite::create("leaf-2.png");
		spLeaf2->setPosition(ccp(szWin.width/2, szWin.height/2 + 130));
		this->addChild(spLeaf2, 8);
		CCActionInterval* rotaAction = CCRotateTo::create(0.15f, 30.f);
		CCActionInterval* rotaReverse = CCRotateTo::create(0.15f, 10.f);
		CCActionInterval* rotaAction2 = CCRotateTo::create(0.1f, 30.f);
		CCActionInterval* rotaReverse2 = CCRotateTo::create(0.1f, 0.f);
		CCActionInterval* pDelay = CCDelayTime::create(3.0f);
		CCSequence* pSeq = CCSequence::create(rotaAction, rotaReverse,rotaAction2,rotaReverse2, pDelay, NULL);
		CCRepeatForever* pRepForver = CCRepeatForever::create(pSeq);
		spLeaf2->runAction(pRepForver);

		//叶子3
		CCSprite* spLeaf3 = CCSprite::create("leaf-3.png");
		spLeaf3->setPosition(ccp(szWin.width/2 + 60, szWin.height/2 + 120));
		this->addChild(spLeaf3, 7);

		CCActionInterval* pDelay2 = CCDelayTime::create(2.0f);
		CCActionInterval* rota2Action = CCRotateTo::create(0.15f, 30.f);
		CCActionInterval* rota2Reverse = CCRotateTo::create(0.15f, 10.f);
		CCActionInterval* rota2Action2 = CCRotateTo::create(0.1f, 30.f);
		CCActionInterval* rota2Reverse2 = CCRotateTo::create(0.1f, 0.f);
		CCActionInterval* pDelay3 = CCDelayTime::create(1.0f);
		CCSequence* pSeq2 = CCSequence::create(pDelay2, rota2Action, rota2Reverse,rota2Action2,rota2Reverse2,pDelay3,NULL);
		CCRepeatForever* pRepForver2 = CCRepeatForever::create(pSeq2);
		spLeaf3->runAction(pRepForver2);

		//小鸟
		CCSprite* spBird = CCSprite::create("bird.png");
		spBird->setPosition(ccp(szWin.width/5, szWin.height*3/4));
		this->addChild(spBird,7);

		CCActionInterval* pMoveTo = CCMoveTo::create(1.0f, ccp(szWin.width/5, szWin.height*3/4-20));
		CCActionInterval* pMoveTo2 = CCMoveTo::create(1.0f, ccp(szWin.width/5, szWin.height*3/4+20));
		CCSequence* pSeqBird = CCSequence::create(pMoveTo, pMoveTo2,NULL);
		CCRepeatForever* pRepForverBird = CCRepeatForever::create(pSeqBird);
		spBird->runAction(pRepForverBird);

		//云朵1
		CCSprite* spCloud = CCSprite::create("cloud1.png");
		spCloud->setPosition(ccp(-200, szWin.height - 150));
		spCloud->setOpacity(50);
		this->addChild(spCloud, 6);

		CCActionInterval* pMoveCloudTo = CCMoveTo::create(20.0f, ccp(szWin.width + 200, szWin.height - 150));
		CCActionInterval* pMoveCloudBack = CCMoveTo::create(0.f, ccp(-200, szWin.height - 150));
		CCActionInterval* pDelayCloud = CCDelayTime::create(2.0f);
		CCSequence* pSeqCloud = CCSequence::create(pMoveCloudTo, pMoveCloudBack, pDelayCloud, NULL);
		CCRepeatForever* pRepForverCloud = CCRepeatForever::create(pSeqCloud);
		spCloud->runAction(pRepForverCloud);

		//云朵2
		CCSprite* spCloud2 = CCSprite::create("cloud2.png");
		spCloud2->setPosition(ccp(-400, szWin.height - 100));
		spCloud2->setOpacity(50);
		this->addChild(spCloud2, 6);

		CCActionInterval* pMoveCloudTo2 = CCMoveTo::create(30.0f, ccp(szWin.width + 400, szWin.height - 100));
		CCActionInterval* pMoveCloudBack2 = CCMoveTo::create(0.f, ccp(-200, szWin.height - 100));
		CCActionInterval* pDelayCloud2 = CCDelayTime::create(2.0f);
		CCSequence* pSeqCloud2 = CCSequence::create(pMoveCloudTo2, pMoveCloudBack2, pDelayCloud2, NULL);
		CCRepeatForever* pRepForverCloud2 = CCRepeatForever::create(pSeqCloud2);
		spCloud2->runAction(pRepForverCloud2);


        bRet = true;
    } while (0);

    return bRet;
}

void CStartScene::onBtnAdvanceClick(CCObject* pObj)
{
	CCScene* pScene = CAdvanceScene::scene();
	CCScene* pPageScene = CCTransitionPageTurn::create(1.0f, pScene, false);
	CCDirector::sharedDirector()->replaceScene(pPageScene);
}

void CStartScene::onBtnBossClick( CCObject* pObj )
{

}




