#ifndef __BATTLEMONSTER_H__
#define __BATTLEMONSTER_H__

#include "GameDataType.h"
#include "cocos2d.h"

USING_NS_CC;

class CBattleMonster: public CCSprite
{
public:
	static CBattleMonster* create();

	virtual bool initWithSpriteFrame(CCSpriteFrame *pSpriteFrame);

	virtual bool initWithSpriteFrameName(const char *pszSpriteFrameName);

	//设置怪物信息

	virtual bool init(void);

	void MoveToNext(int idxCur);

	//移动一步结束
	void OnMoveStepOver(CCNode* pObj, void* pParam);
	
	//移动完毕
	void OnMoveOver();

	void ShowHp(float nHp);

protected:
	CCProgressTimer* m_pProHp;
	CCSprite* m_pProHpBg;
};


#endif

