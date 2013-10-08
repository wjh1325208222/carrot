#ifndef __STAGE_LAYER_H__
#define __STAGE_LAYER_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "GUI/CCScrollView/CCTableView.h"
#include "MyPageView.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CStageLayer : public cocos2d::CCLayer, public cocos2d::extension::CCTableViewDataSource, public cocos2d::extension::CCTableViewDelegate,CMyPageViewDelegate
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // implement the "static node()" method manually
    CREATE_FUNC(CStageLayer);

	virtual cocos2d::CCSize cellSizeForTable(cocos2d::extension::CCTableView *table);

	virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(cocos2d::extension::CCTableView *table, unsigned int idx);

	virtual unsigned int numberOfCellsInTableView(cocos2d::extension::CCTableView *table);

	virtual void scrollViewDidScroll(cocos2d::extension::CCScrollView* view) ;
	virtual void scrollViewDidZoom(cocos2d::extension::CCScrollView* view) {}
	virtual void tableCellTouched(cocos2d::extension::CCTableView* table, cocos2d::extension::CCTableViewCell* cell);

	void onBtnHomeClick(CCObject* pSrcObj);

	void onBtnHelpClick(CCObject* pSrcObj);

	void onBtnPlayClick(CCObject* pSrcObj);

	virtual void onEnter();
	virtual void onExit();

	virtual void onPageChange(CMyPageView *table, int oldPage, int newPage);

	void showBattle(int nSel);

	/*virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);*/

protected:
	//根据手势滑动的距离和方向滚动图层
	//void adjustScrollView(float offset);

	CMyPageView *m_pScrollView;
	CCPoint m_touchPoint;
	int m_nCurPage;
};

#endif  // __HELLOWORLD_SCENE_H__