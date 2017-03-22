/*
* Samuel MacSweeney
* K00200955
*/

#ifndef _SinglePlayerMenu_H_
#define _SinglePlayerMenu_H_

#include "cocos2d.h"

class SinglePlayerMenu : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	// a selector callback
	void NewGame(cocos2d::Ref *pSender);
	void goBack(cocos2d::Ref *pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(SinglePlayerMenu);
};
#endif
