/*
* Samuel MacSweeney
* K00200955
*/

#ifndef _MainMenu_H_
#define _MainMenu_H_

#include "cocos2d.h"

class MainMenu : public cocos2d::Layer
{
	public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);
	void singlePlayer(cocos2d::Ref *pSender);
	void multiPlayer(cocos2d::Ref *pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MainMenu);
};

#endif