#include "CountDownLayer.h"
#include "GameDefine.h"
#include "BattleScene.h"



using namespace cocos2d;
using namespace std;

#define		kTagCountDownLight	1000
#define		kTagCountDownNum	1001

// on "init" you need to initialize your instance
bool CCountDownLayer::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());


		CCSize size = CCDirector::sharedDirector()->getWinSize();


        bRet = true;
    } while (0);

    return bRet;
}

void CCountDownLayer::start()
{
	ShowCountDownLayer();
}


void CCountDownLayer::ShowCountDownLayer()
{
	CCSpriteFrameCache *pCache =  CCSpriteFrameCache::sharedSpriteFrameCache();
	pCache->addSpriteFrame(CCSpriteFrame::create("countdown_01.png",CCRectMake(0, 0, 98, 116)),"countdown_01.png");
	pCache->addSpriteFrame(CCSpriteFrame::create("countdown_02.png",CCRectMake(0, 0, 96, 116)),"countdown_02.png");
	pCache->addSpriteFrame(CCSpriteFrame::create("countdown_03.png",CCRectMake(0, 0, 74, 116)),"countdown_03.png");
	pCache->addSpriteFrame(CCSpriteFrame::create("countdown_11.png",CCRectMake(0, 0, 198, 194)),"countdown_11.png");
	pCache->addSpriteFrame(CCSpriteFrame::create("countdown_12.png",CCRectMake(0, 0, 116, 174)),"countdown_12.png");
	pCache->addSpriteFrame(CCSpriteFrame::create("countdown_13.png",CCRectMake(0, 0, 200, 200)),"countdown_13.png");

	CCSize size = getContentSize();

	//显示倒计时背景
	CCSprite* pBg = CCSprite::createWithSpriteFrameName("countdown_11.png");
	pBg->setPosition(ccp(size.width/2, size.height/2));
	addChild(pBg);

	CCSprite* pRotateLight = CCSprite::createWithSpriteFrameName("countdown_12.png");
	pRotateLight->setPosition(ccp(size.width/2, size.height/2));
	pRotateLight->setAnchorPoint(ccp(0.8, 0.55));
	addChild(pRotateLight, 1, kTagCountDownLight);

	CCActionInterval* pRotation = CCRotateBy::create(1.0f, -360.0f);
	CCActionInterval* pRep3 = CCRepeat::create(pRotation, 3);
	pRotateLight->runAction(pRep3);


	CCSprite* pCountDownNum = CCSprite::createWithSpriteFrameName("countdown_01.png");
	pCountDownNum->setPosition(ccp(size.width/2, size.height/2));
	addChild(pCountDownNum, 2, kTagCountDownNum);
	pCountDownNum->setScale(0.1f);
	
	m_nCountDownNum = 3;
	m_nCountDownNum --;
	CCActionInterval* pScaleAction = CCScaleTo::create(0.1f, 1.0f);
	CCCallFuncND* pCall = CCCallFuncND::create(this, callfuncND_selector(CCountDownLayer::OnCountDownActionOver), (void*)m_nCountDownNum);
	CCActionInterval* pDeleyCountDown = CCDelayTime::create(0.9f);
	CCActionInterval* pSeqCountDown = CCSequence::create(pScaleAction, pDeleyCountDown, pCall, NULL);
	pCountDownNum->runAction(pSeqCountDown);
}

void CCountDownLayer::OnCountDownActionOver( CCNode* pSprite, void* params )
{
	
	CCSprite* pCountDownNum = dynamic_cast<CCSprite*>(pSprite);
	if (pCountDownNum)
	{
		if (m_nCountDownNum > 0 && m_nCountDownNum <= 3)
		{
			CCString str;
			float fDeleyTime = 0.9f;
			switch (m_nCountDownNum)
			{
			case 1:
				str = CCString("countdown_03.png");
				fDeleyTime = 0.4f;
				break;
			case 2:
				str = CCString("countdown_02.png");
				break;
			case 3:
				str = CCString("countdown_01.png");
				break;
			}
			pCountDownNum->initWithSpriteFrameName(str.getCString());
			pCountDownNum->setScale(0.1f);
			CCActionInterval* pScaleAction = CCScaleTo::create(0.1f, 1.0f);
			CCCallFuncND* pCall = CCCallFuncND::create(this, callfuncND_selector(CCountDownLayer::OnCountDownActionOver), (void*)m_nCountDownNum);
			CCActionInterval* pDeleyCountDown = CCDelayTime::create(fDeleyTime);
			CCActionInterval* pSeqCountDown = CCSequence::create(pScaleAction, pDeleyCountDown, pCall, NULL);
			pCountDownNum->runAction(pSeqCountDown);
			
			m_nCountDownNum --;
		}
		else if(!m_nCountDownNum)
		{
			pCountDownNum->initWithSpriteFrameName("countdown_13.png");
			pCountDownNum->setScale(2.0f);
			pCountDownNum->setRotation(180.0f);
			CCActionInterval* pScaleAction = CCScaleTo::create(0.1f, 1.0f);
			CCActionInterval* pRotateAction = CCRotateTo::create(0.1f, 360.0f);
			CCActionInterval* pOverAction = CCSpawn::createWithTwoActions(pScaleAction, pRotateAction);
			CCActionInterval* pDeleyOver = CCDelayTime::create(0.3f);
			CCCallFunc* pCall = CCCallFunc::create(this, callfunc_selector(CCountDownLayer::CountDownLayerScale));
			CCActionInterval* pSeqGo = CCSequence::create(pOverAction, pDeleyOver, pCall, NULL);
			pCountDownNum->runAction(pSeqGo);

			CCNode* pNode = getChildByTag(kTagCountDownLight);
			if (pNode)
			{
				pNode->setVisible(false);
			}
		}
	}
}

void CCountDownLayer::CountDownLayerScale()
{
	CCActionInterval* pScaleAction = CCScaleTo::create(0.1f, 0.1f);
	CCCallFunc* pCall = CCCallFunc::create(this, callfunc_selector(CCountDownLayer::OnShowCountDownLayerOver));
	CCActionInterval* pSeqAction = CCSequence::createWithTwoActions(pScaleAction, pCall);
	runAction(pSeqAction);
}

void CCountDownLayer::OnShowCountDownLayerOver()
{
	//setVisible(false);
	//setScale(1.0f);

	//并且发送消息给场景倒计时结束
	CBattleScene* pBattle = dynamic_cast<CBattleScene*>(getParent());
	if (pBattle)
	{
		pBattle->Start();
	}
	removeAllChildrenWithCleanup(true);
	removeFromParentAndCleanup(true);
	
}

















