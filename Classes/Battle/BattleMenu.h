#ifndef __BATTLE_MENU_H__
#define __BATTLE_MENU_H__

#include "cocos2d.h"
#include "GameDataType.h"

USING_NS_CC;


class CBattleMenu : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // implement the "static node()" method manually
    CREATE_FUNC(CBattleMenu);

protected:

	
};

#endif  // __HELLOWORLD_SCENE_H__