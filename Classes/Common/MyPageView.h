#ifndef __MY_PAGE_VIEW_H__
#define __MY_PAGE_VIEW_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class CMyPageView;

class CMyPageViewDelegate
{
public:
    virtual ~CMyPageViewDelegate() {}
   
    virtual void onPageChange(CMyPageView *table, int oldPage, int newPage) = 0;

};

class CMyPageView : public CCTableView
{
public:
	static CMyPageView* create(CCTableViewDataSource* dataSource, CCSize size, CCNode *container);

	 bool init();

	//设置每页页数大小
    void setPageSize(CCSize& size);

	CCSize getPageSize();

	//设置页数
	void setPageCnt(int nPageCnt);

	int getPageCnt();

	//设置当前页数
	void setCurPage(int nCurPage);

	//获取当前页数
	int getCurPage();

	//设置翻页滑动距离
	void setTurnPageOffset(int offset);

	//设置第一项距离左边偏移量
	void setViewOffsetSize(const CCSize& size);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	void setPageDelegate(CMyPageViewDelegate* pDelegate);

protected:
	void adjustScrollView(int offset);

	CCSize m_pageSize;

	int m_nPageCnt;

	int m_nCurPage;

	CCPoint m_touchPoint;

	int m_nPageOffset;

	//设置初始便宜量
	CCSize m_viewOffsetSize;

	CMyPageViewDelegate* m_pageDelegate;
};

#endif  // __HELLOWORLD_SCENE_H__