#include "TowerListLayer.h"
#include "GameDefine.h"
#include "BattleScene.h"



using namespace cocos2d;
using namespace std;



// on "init" you need to initialize your instance
bool CTowerListLayer::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());


        bRet = true;
    } while (0);

    return bRet;
}

void CTowerListLayer::start( CCPoint ptStartCell, int idMap )
{

}

















