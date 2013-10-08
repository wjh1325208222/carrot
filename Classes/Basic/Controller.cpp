#include "Controller.h"
#include "BattleScene.h"
#include "GameDefine.h"

USING_NS_CC;


// const PATH_POINT* CController::getNextStep( int idx )
// {
// 	CCScene* pRunScene = CCDirector::sharedDirector()->getRunningScene();
// 	int nSceneId = pRunScene->getTag();
// 	if (nSceneId == BATTLE_SCENE)
// 	{
// 		CBattleScene* pBattleScene = dynamic_cast<CBattleScene*>(pRunScene->getChildByTag(BATTLE_LAYER));
// 		if (pBattleScene)
// 		{
// 			return pBattleScene->GetNextStep(idx);
// 		}
// 	}
// 	return NULL;
// }
