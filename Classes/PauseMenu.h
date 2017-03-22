/*
* Samuel MacSweeney
* K00200955
*/

#ifndef _PauseMenu_H_
#define _PauseMenu_H_

#include "cocos2d.h"

class PauseMenu : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	// a selector callback
	void PauseGame(cocos2d::Ref *pSender);
	void goBack(cocos2d::Ref *pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(PauseMenu);
};
#endif
