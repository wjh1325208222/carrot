#ifndef __TOWER_LIST_LAYER_H__
#define __TOWER_LIST_LAYER_H__

#include "cocos2d.h"
#include "GameDataType.h"

USING_NS_CC;


class CTowerListLayer : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // implement the "static node()" method manually
    CREATE_FUNC(CTowerListLayer);

	void start(CCPoint ptStartCell, int idMap);
};

#endif  // __HELLOWORLD_SCENE_H__