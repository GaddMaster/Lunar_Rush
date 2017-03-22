#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_
//Testing me out
#include "cocos2d.h"
#include "MainMenu.h"
#include "FirstWorld.h"

class  AppDelegate : private cocos2d::Application
{
	public:
		AppDelegate();
		virtual ~AppDelegate();
		virtual void initGLContextAttrs();
		virtual bool applicationDidFinishLaunching();
		virtual void applicationDidEnterBackground();
		virtual void applicationWillEnterForeground();
};

#endif

