#include "AccountScene.h"
#include "Client.h"
#include <PopupManager.h>
#include "SelectModeScene.h"

USING_NS_CC;

Scene* AccountScene::createScene()
{
    return AccountScene::create();
}

bool AccountScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto layout = cocos2d::ui::Layout::create();
    layout->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    layout->setBackGroundColor(cocos2d::Color3B(100, 149, 237));

    auto accountInput = cocos2d::ui::TextField::create("�������˺�", "Arial", 30);
    accountInput->setPosition(Vec2(1280, 800));
    accountInput->setPlaceHolderColor(cocos2d::Color4B::GRAY);
    accountInput->setPlaceHolder("Enter your account");
    accountInput->setCursorEnabled(true);  // ���ù��
    layout->addChild(accountInput);

    auto passwordInput = cocos2d::ui::TextField::create("����������", "Arial", 30);
    passwordInput->setPosition(Vec2(1280, 600));
    passwordInput->setPasswordEnabled(true);
    passwordInput->setPasswordStyleText("*");
    passwordInput->setCursorEnabled(true);  // ���ù��
    layout->addChild(passwordInput);

    auto registerButton = cocos2d::ui::Button::create("join.png");
    registerButton->setPosition(Vec2(1100, 400));
    registerButton->addClickEventListener(CC_CALLBACK_1(AccountScene::registerButtonCallback, this, accountInput, passwordInput));
    layout->addChild(registerButton);

    auto loginButton = cocos2d::ui::Button::create("login.png");
    loginButton->setPosition(Vec2(1500, 400));
    loginButton->addClickEventListener(CC_CALLBACK_1(AccountScene::loginButtonCallback, this, accountInput, passwordInput));
    layout->addChild(loginButton);

    addChild(layout);

    //�˳���ǰ�����İ�ť
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        [&](Ref* sender) {
            Director::getInstance()->popScene();//�ͷŵ�ǰ�������ٴӳ���ջ�е���ջ���ĳ���������������Ϊ��ǰ���г�����
        });
    float x = origin.x + visibleSize.width - closeItem->getContentSize().width;
    float y = origin.y + closeItem->getContentSize().height;
    closeItem->setPosition(Vec2(x, y));

    auto exitMenu = Menu::create(closeItem, NULL);
    exitMenu->setPosition(Vec2::ZERO);
    this->addChild(exitMenu, 1);

    return true;
}

void AccountScene::loginButtonCallback(cocos2d::Ref* sender, cocos2d::ui::TextField* accountInput, cocos2d::ui::TextField* passwordInput)
{
    std::string account = accountInput->getString();
    std::string password = passwordInput->getString();
    CCLOG("Account: %s, Password: %s", account.c_str(), password.c_str());

    char str_ac[max_ac_num] = { 0 };
    str_ac[max_ac_num-1] = '\0';

    copy(account.begin(), account.end(), str_ac);
    char str_pw[max_ac_pw] = { 0 };
    str_ac[max_ac_pw-1] = '\0';
    copy(password.begin(), password.end(), str_pw);
    // �����ﴦ����¼�߼�����������ͨ����֤�˺�����
    Client::getInstance()->write_event(Login);
    Client::getInstance()->write_account(str_ac);
    Client::getInstance()->write_password(str_pw);
    Client::getInstance()->send_msg(); 
        if (Client::getInstance()->csocket._passInfo->_result == 2) {
            //��ת��ѡ�񳡾�
            Director::getInstance()->pushScene(SelectModeScene::createScene());
        }
        else if (Client::getInstance()->csocket._passInfo->_result == 1)
            PopupManager::displayPopup(this, "fail to login: Password fault");
        else if (Client::getInstance()->csocket._passInfo->_result == 0)
            PopupManager::displayPopup(this, "fail to login: account not exist");
 
    // ʾ�����򵥴�ӡ������˺ź�����
    //CCLOG("Account: %s, Password: %s", account.c_str(), password.c_str());
}


void AccountScene::registerButtonCallback(cocos2d::Ref* sender, cocos2d::ui::TextField* accountInput, cocos2d::ui::TextField* passwordInput)
{
    std::string account = accountInput->getString();
    std::string password = passwordInput->getString();

    CCLOG("Account: %s, Password: %s", account.c_str(), password.c_str());

    char str_ac[max_ac_num] = { 0 };
    str_ac[max_ac_num - 1] = '\0';

    copy(account.begin(), account.end(), str_ac);
    char str_pw[max_ac_pw] = { 0 };
    str_ac[max_ac_pw - 1] = '\0';
    copy(password.begin(), password.end(), str_pw);
    // �����ﴦ����¼�߼�����������ͨ����֤�˺�����
    Client::getInstance()->write_event(Register);
    Client::getInstance()->write_account(str_ac);
    Client::getInstance()->write_password(str_pw);
    Client::getInstance()->send_msg();
    Sleep(1);
    if (Client::getInstance()->csocket._passInfo->_result == 1)
        PopupManager::displayPopup(this, "succed to register");
    else if (Client::getInstance()->csocket._passInfo->_result == 0)
        PopupManager::displayPopup(this, "fail to register: account have existed");

    // �����ﴦ��ע���߼�����������ͨ�ű������˺�����

    // ʾ�����򵥴�ӡ������˺ź�����
    //CCLOG("Register: Account: %s, Password: %s", account.c_str(), password.c_str());
}