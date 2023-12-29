#include "Test_Scene_4.h"
#include"Client.h"

USING_NS_CC;

Scene* Test_Scene_4::createScene()
{
    return Test_Scene_4::create();
}

bool Test_Scene_4::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto layout = cocos2d::ui::Layout::create();
    layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    layout->setBackGroundColor(cocos2d::Color3B(100, 149, 237));

    auto accountInput = cocos2d::ui::TextField::create("请输入账号", "Arial", 30);
    accountInput->setPosition(Vec2(240, 400));
    accountInput->setPlaceHolderColor(cocos2d::Color4B::GRAY);
    accountInput->setPlaceHolder("Enter your account");
    accountInput->setCursorEnabled(true);  // 启用光标
    layout->addChild(accountInput);

    auto passwordInput = cocos2d::ui::TextField::create("请输入密码", "Arial", 30);
    passwordInput->setPosition(Vec2(240, 320));
    passwordInput->setPasswordEnabled(true);
    passwordInput->setPasswordStyleText("*");
    passwordInput->setCursorEnabled(true);  // 启用光标
    layout->addChild(passwordInput);

    auto registerButton = cocos2d::ui::Button::create("join.png");
    registerButton->setPosition(Vec2(240, 100));
    registerButton->addClickEventListener(CC_CALLBACK_1(Test_Scene_4::registerButtonCallback, this, accountInput, passwordInput));
    layout->addChild(registerButton);

    auto loginButton = cocos2d::ui::Button::create("login.png");
    loginButton->setPosition(Vec2(240, 160));
    loginButton->addClickEventListener(CC_CALLBACK_1(Test_Scene_4::loginButtonCallback, this, accountInput, passwordInput));
    layout->addChild(loginButton);

    addChild(layout);

    //退出当前场景的按钮
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        [&](Ref* sender) {
            Director::getInstance()->popScene();//释放当前场景，再从场景栈中弹出栈顶的场景，并将其设置为当前运行场景。
        });
    float x = origin.x + visibleSize.width - closeItem->getContentSize().width;
    float y = origin.y + closeItem->getContentSize().height;
    closeItem->setPosition(Vec2(x, y));

    auto exitMenu = Menu::create(closeItem, NULL);
    exitMenu->setPosition(Vec2::ZERO);
    this->addChild(exitMenu, 1);

    return true;
}

void Test_Scene_4::loginButtonCallback(cocos2d::Ref* sender, cocos2d::ui::TextField* accountInput, cocos2d::ui::TextField* passwordInput)
{
    std::string account = accountInput->getString();
    std::string password = passwordInput->getString();

    char str_ac[max_ac_num] = { 0 };
    str_ac[max_ac_num] = '\0';
    copy(account.begin(), account.end(), str_ac);
    char str_pw[max_ac_pw] = { 0 };
    str_ac[max_ac_pw] = '\0';
    copy(account.begin(), account.end(), str_pw);
    // 在这里处理登录逻辑，可以与后端通信验证账号密码
    Client::getInstance()->write_event(Login);
    Client::getInstance()->write_account(str_ac);
    Client::getInstance()->write_password(str_pw);
    Client::getInstance()->send_msg();
    Sleep(0.5);
    if(Client::getInstance() ->csocket._passInfo->_result==1)
        CCLOG("success login");
    else
        CCLOG("fail to login");
    // 示例：简单打印输入的账号和密码
   // CCLOG("Account: %s, Password: %s", account.c_str(), password.c_str());
}


void Test_Scene_4::registerButtonCallback(cocos2d::Ref* sender, cocos2d::ui::TextField* accountInput, cocos2d::ui::TextField* passwordInput)
{
    std::string account = accountInput->getString();
    std::string password = passwordInput->getString();

    // 在这里处理注册逻辑，可以与后端通信保存新账号密码

    // 示例：简单打印输入的账号和密码
    CCLOG("Register: Account: %s, Password: %s", account.c_str(), password.c_str());
}