#ifndef __BATTLE_SCENE_H__
#define __BATTLE_SCENE_H__

#include "cocos2d.h"
#include "GameDataType.h"

USING_NS_CC;


class CBattleScene : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    // implement the "static node()" method manually
    CREATE_FUNC(CBattleScene);

	virtual void onEnter();
	virtual void onExit();

	void EnterStage(int idStage);

	void Start();

protected:
	void ReadTmxMap();

	void ShowCarrotFunction();
	void ShowCarrotActionOver(CCNode* pSprite, void* params);

	void ShowCountDownLayer();

	void ShowArrow(int idMap);

	//弹出点击区域不可放置错误
	void ShowTouchPlaceErr(CCPoint ptTouch);

	//显示炮塔菜单
	void ShowTowerMenu(CCPoint ptTouch);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	void OnTouchClick(CCPoint pos);

	CCTMXTiledMap* m_pMap;

	int m_nCountDownNum;

	//当前地图的物件
	vector<TPL_MAP_OBJ> m_vecMapObj;

	//箭头
	CCSprite* m_arySp[3];
};

#endif  // __HELLOWORLD_SCENE_H__