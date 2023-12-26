#ifndef __TEST_SCENE_4_H__
#define __TEST_SCENE_4_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Test_Scene_4 : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void loginButtonCallback(cocos2d::Ref* sender, cocos2d::ui::TextField* accountInput, cocos2d::ui::TextField* passwordInput);
    void registerButtonCallback(cocos2d::Ref* sender, cocos2d::ui::TextField* accountInput, cocos2d::ui::TextField* passwordInput);
    CREATE_FUNC(Test_Scene_4);
};

#endif // __TEST_SCENE_4_H__
