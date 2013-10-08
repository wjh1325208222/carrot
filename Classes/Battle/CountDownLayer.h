#ifndef __COUNT_DOWN_LAYER_H__
#define __COUNT_DOWN_LAYER_H__

#include "cocos2d.h"
#include "GameDataType.h"

USING_NS_CC;


class CCountDownLayer : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // implement the "static node()" method manually
    CREATE_FUNC(CCountDownLayer);

	void start();

protected:
	void ShowCountDownLayer();
	void OnCountDownActionOver(CCNode* pSprite, void* params);
	void CountDownLayerScale();
	void OnShowCountDownLayerOver();

	int m_nCountDownNum;
};

#endif  // __HELLOWORLD_SCENE_H__