#include "BattleMenu.h"
#include "GameDefine.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace std;
USING_NS_CC_EXT;

#define	kTagWaveBg	1000

// on "init" you need to initialize your instance
bool CBattleMenu::init()
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

		pCache->addSpriteFrame(CCSpriteFrame::create("MenuBG.png",CCRectMake(0, 0, 926, 78)),"MenuBG.png");
		pCache->addSpriteFrame(CCSpriteFrame::create("MenuCenter_01_CN.png",CCRectMake(0, 0, 236, 52)),"MenuCenter_01_CN.png");

		CCSize size = CCDirector::sharedDirector()->getWinSize();
		
		//菜单
		CCPoint ptAnchor = ccp(0.5, 1);
		CCPoint pos;
		CCSprite* pMenuBg = CCSprite::createWithSpriteFrameName("MenuBG.png");
		pMenuBg->setAnchorPoint(ptAnchor);
		pos = ccp(size.width/2, size.height);
		pMenuBg->setPosition(pos);
		addChild(pMenuBg, 10);

		////设置层的大小及位置
		//setContentSize(pMenuBg->getContentSize());
		//setAnchorPoint(ptAnchor);
		//setPosition(ccp(size.width/2, size.height));

		CCSize sizeLayer = pMenuBg->getContentSize();
		pos = ccp(sizeLayer.width/2, sizeLayer.height/2 + 6);

		//波数
		CCSprite* pWaveBg = CCSprite::createWithSpriteFrameName("MenuCenter_01_CN.png");
		pMenuBg->addChild(pWaveBg, 2, kTagWaveBg);
		pWaveBg->setPosition(pos);



        bRet = true;
    } while (0);

    return bRet;
}














