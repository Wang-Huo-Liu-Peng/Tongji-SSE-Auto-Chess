#ifndef __ACCOUNT_SCENE_H__
#define __ACCOUNT_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class AccountScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void loginButtonCallback(cocos2d::Ref* sender, cocos2d::ui::TextField* accountInput, cocos2d::ui::TextField* passwordInput);
    void registerButtonCallback(cocos2d::Ref* sender, cocos2d::ui::TextField* accountInput, cocos2d::ui::TextField* passwordInput);
    CREATE_FUNC(AccountScene);
};

#endif // __ACCOUNT_SCENE_H__
