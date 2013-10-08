#include "MyPageView.h"

using namespace cocos2d;
USING_NS_CC_EXT;


CMyPageView* CMyPageView::create( CCTableViewDataSource* dataSource, CCSize size, CCNode *container )
{
	/*CMyPageView* pRet = new CMyPageView();
	pRet->init();
	if (pRet && pRet->initWithViewSize(size, container))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}
	return pRet;*/
	CMyPageView *table = new CMyPageView();
	table->init();
	table->initWithViewSize(size, container);
	table->autorelease();
	table->setDataSource(dataSource);
	table->_updateContentSize();
	return table;
}

bool CMyPageView::init()
{
	m_nCurPage = 1;
	m_nPageCnt = 1;
	m_nPageOffset = 150;
	m_viewOffsetSize = CCSizeMake(0, 0);
	m_pageDelegate = NULL;
	return CCScrollView::init();
}

void CMyPageView::setPageSize( CCSize& size )
{
	m_pageSize = size;
}

void CMyPageView::setPageCnt( int nPageCnt )
{
	m_nPageCnt = nPageCnt;
}

void CMyPageView::setCurPage( int nCurPage )
{
	int nOldPage = m_nCurPage;

	if (nCurPage > m_nPageCnt || nCurPage < 1)
	{
		return;
	}
	
	
	m_nCurPage = nCurPage;

	CCPoint  adjustPos = ccp(- m_pageSize.width * (m_nCurPage-1) + m_viewOffsetSize.width, 0);
	setContentOffset(adjustPos, true);

	if (m_pageDelegate)
	{
		m_pageDelegate->onPageChange(this, nOldPage, nCurPage);
	}
	
}

int CMyPageView::getCurPage()
{
	return m_nCurPage;
}

void CMyPageView::setTurnPageOffset( int offset )
{
	m_nPageOffset = offset;
}

bool CMyPageView::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	m_touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	return CCTableView::ccTouchBegan(pTouch, pEvent);
}

void CMyPageView::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	CCTableView::ccTouchMoved(pTouch, pEvent);

	CCLOG("move\n");

	/*CCPoint endPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	float distance = endPoint.x - m_touchPoint.x;
	if(fabs(distance) > m_nPageOffset)
	{
	CCLOG("TouchMove End(%f,%f) Start(%f,%f)\n",endPoint.x, endPoint.y, m_touchPoint.x, m_touchPoint.y);
	adjustScrollView(distance);
	m_touchPoint = endPoint;

	CCPoint offset = getContentOffset();
	CCLOG("TouchMove offset(%f,%f) \n",offset.x, offset.y);
	} */
}

void CMyPageView::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCTableView::ccTouchEnded(pTouch, pEvent);
	m_bDragging = true;

	CCPoint endPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	float distance = endPoint.x - m_touchPoint.x;
	if(fabs(distance) > m_nPageOffset)
	{
		adjustScrollView(distance);

		CCLOG("End\n");
	}
	else
	{
		CCPoint  adjustPos = ccp(- m_pageSize.width * (m_nCurPage-1) + m_viewOffsetSize.width, 0);
		setContentOffset(adjustPos, true);

		
	}
	
}

void CMyPageView::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	CCTableView::ccTouchCancelled(pTouch, pEvent);

	CCPoint endPoint = CCDirector::sharedDirector()->convertToGL(pTouch->getLocationInView());
	float distance = endPoint.x - m_touchPoint.x;
	if(fabs(distance) > m_nPageOffset)
	{
		adjustScrollView(distance);
	}
	else
	{
		CCPoint  adjustPos = ccp(- m_pageSize.width * (m_nCurPage-1) + m_viewOffsetSize.width, 0);
		setContentOffset(adjustPos, true);
	} 

	CCLOG("Cancelled\n");
}

void CMyPageView::adjustScrollView( int offset )
{
	int nOldPage = m_nCurPage;
	if (offset<0)
	{
		m_nCurPage ++;
	}else
	{
		m_nCurPage --;
	}

	if (m_nCurPage <1)
	{
		m_nCurPage = 1;
	}
	
	if (m_nCurPage > m_nPageCnt)
	{
		m_nCurPage = m_nPageCnt;
	}

	CCPoint  adjustPos = ccp(- m_pageSize.width * (m_nCurPage-1) + m_viewOffsetSize.width, 0);
	setContentOffset(adjustPos, true);

	m_bDragging = true;

	if (nOldPage != m_nCurPage)
	{
		if(m_pageDelegate)
		{
			m_pageDelegate->onPageChange(this, nOldPage, m_nCurPage);
		}
	}
	
}

cocos2d::CCSize CMyPageView::getPageSize()
{
	return m_pageSize;
}

void CMyPageView::setViewOffsetSize(const CCSize& size)
{
	m_viewOffsetSize = size;
}

int CMyPageView::getPageCnt()
{
	return m_nPageCnt;
}

void CMyPageView::setPageDelegate( CMyPageViewDelegate* pDelegate )
{
	m_pageDelegate = pDelegate;
}








