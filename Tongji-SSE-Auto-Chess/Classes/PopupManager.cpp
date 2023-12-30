// PopupManager.cpp
#include "PopupManager.h"

void PopupManager::displayPopup(cocos2d::Layer* parentLayer, const std::string& displayText)
{
    // 创建一个精灵以显示背景图像
    auto background = cocos2d::Sprite::create("Blank_pop-up.png");
    background->setPosition(2560 / 2, 1600 / 2);  // 将位置设置为屏幕中央
    background->setTag(7);
    parentLayer->addChild(background);

    // 创建一个标签以显示文字
    auto label = cocos2d::Label::createWithTTF(displayText, "fonts/arial.ttf", 24);
    label->setPosition(2560 / 2, 1600 / 2);  // 将位置设置为屏幕中央
    label->setColor(cocos2d::Color3B::BLACK);  // 设置文字颜色为黑色
    parentLayer->addChild(label);

    // 设置一个点击事件，用于关闭弹窗
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        // 移除标签
        label->removeFromParent();
        // 移除背景图片
        background->removeFromParent();
        return true;
    };
    parentLayer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, background);
}

void PopupManager::displayPopup(cocos2d::Scene* parentScene, const std::string& displayText)
{
    // 创建一个精灵以显示背景图像
    auto background = cocos2d::Sprite::create("Blank_pop-up.png");
    background->setPosition(2560 / 2, 1600 / 2);  // 将位置设置为屏幕中央
    background->setTag(7);
    parentScene->addChild(background);

    // 创建一个标签以显示文字
    auto label = cocos2d::Label::createWithTTF(displayText, "fonts/arial.ttf", 24);
    label->setPosition(2560 / 2, 1600 / 2);  // 将位置设置为屏幕中央
    label->setColor(cocos2d::Color3B::BLACK);  // 设置文字颜色为黑色
    parentScene->addChild(label);

    // 设置一个点击事件，用于关闭弹窗
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event* event) {
        // 移除标签
        label->removeFromParent();
        // 移除背景图片
        background->removeFromParent();
        return true;
        };
    parentScene->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, background);
}
