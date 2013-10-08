#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GUI/CCScrollView/CCTableView.h"
#include "MyPageView.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CAdvanceScene : public cocos2d::CCLayer, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();

    // implement the "static node()" method manually
    CREATE_FUNC(CAdvanceScene);

	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);

	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);

	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) ;
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);

	void onBtnHomeClick(CCObject* pSrcObj);

	void onBtnHelpClick(CCObject* pSrcObj);

	void onBtnLeftClick(CCObject* pSrcObj);

	void onBtnRightClick(CCObject* pSrcObj);

	virtual void onEnter();
	virtual void onExit();

	/*virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);*/

protected:
	//根据手势滑动的距离和方向滚动图层
	//void adjustScrollView(float offset);
	//现实具体关卡
	void showStageLayer(int idx);

	CMyPageView *m_pScrollView;
	CCPoint m_touchPoint;
	int m_nCurPage;
};

#endif  // __HELLOWORLD_SCENE_H__