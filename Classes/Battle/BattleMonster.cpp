#include "BattleMonster.h"
#include "Controller.h"
#include "DataManager.h"

USING_NS_CC;


bool CBattleMonster::init( void )
{
	bool bRet = CCSprite::init();
	m_pProHp = NULL;

	return bRet;
}

void CBattleMonster::MoveToNext(int idxCur)
{
	CCPoint posStart = getPosition();

	const PATH_POINT* pNextPoint = CDataManager::sharedDataManager()->GetNextStep(idxCur);
	if (pNextPoint)
	{
		CCPoint posEnd(pNextPoint->x, pNextPoint->y);
		float fDis = ccpDistance(posStart, posEnd);
		float fDur = fDis/100;
		CCActionInterval* pMove2 = CCMoveTo::create(fDur, posEnd);
		CCCallFuncND* pCall = CCCallFuncND::create(this, callfuncND_selector(CBattleMonster::OnMoveStepOver), (void*)pNextPoint->idx);
		CCActionInterval* pSeq = CCSequence::createWithTwoActions(pMove2, pCall);
		runAction(pSeq);
	}
	else
	{
		OnMoveOver();
	}
	
}

void CBattleMonster::OnMoveStepOver( CCNode* pObj, void* pParam )
{
	int idx = (int)pParam;
	MoveToNext(idx);
}

void CBattleMonster::OnMoveOver()
{
	setVisible(false);
}

CBattleMonster* CBattleMonster::create()
{
	CBattleMonster *pSprite = new CBattleMonster();
	if (pSprite && pSprite->init())
	{
		pSprite->autorelease();
		return pSprite;
	}
	CC_SAFE_DELETE(pSprite);
	return NULL;
}

bool CBattleMonster::initWithSpriteFrame( CCSpriteFrame *pSpriteFrame )
{
	bool bRet = CCSprite::initWithSpriteFrame(pSpriteFrame);

	return bRet;
}

bool CBattleMonster::initWithSpriteFrameName( const char *pszSpriteFrameName )
{
	bool bRet = CCSprite::initWithSpriteFrameName(pszSpriteFrameName);

	//ShowHp(10);

	return bRet;
}

void CBattleMonster::ShowHp( float nHp )
{
	if (!m_pProHp)
	{
		m_pProHpBg = CCSprite::create();
		m_pProHpBg->initWithSpriteFrameName("MonsterHP02.png");
		m_pProHpBg->setAnchorPoint(ccp(0.5, 0.5));
		m_pProHpBg->setPosition(ccp(getContentSize().width/2, getContentSize().height));
		addChild(m_pProHpBg, 1);

		CCSprite* pSprite = CCSprite::create();
		pSprite->initWithSpriteFrameName("MonsterHP01.png");
		m_pProHp = CCProgressTimer::create(pSprite);
		m_pProHp->setType(CCProgressTimerType::kCCProgressTimerTypeBar);
		m_pProHp->setAnchorPoint(ccp(0, 0.5));
		m_pProHp->setPosition(ccp((getContentSize().width - pSprite->getContentSize().width)/2, getContentSize().height));
		m_pProHp->setMidpoint(ccp(0, 0));
		m_pProHp->setBarChangeRate(ccp(1, 0));
		m_pProHp->setPercentage(100);
		addChild(m_pProHp, 2);
		
	}

	CCActionInterval* pActionFrom = CCProgressFromTo::create(3.0f, 100, nHp);
	m_pProHp->runAction(pActionFrom);

	/*CCActionInterval* pActionFrom2 = CCProgressTo::create(0.5, nHp);
	m_pProHpBg->runAction(pActionFrom2);*/
}
