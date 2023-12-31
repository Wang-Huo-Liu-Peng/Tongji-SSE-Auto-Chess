//#include <goldenshovel_hero_design.h>
#include "HelloWorldScene.h"
#include "Test_Scene_2.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Test_Scene_2::createScene()
{
    return Test_Scene_2::create();
}

bool Test_Scene_2::init()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    ///////////////////////////////
    // 创建背景音乐音量滑动条控件
    auto bgmSlider = ui::Slider::create();
    bgmSlider->loadBarTexture("slider_progress.png");
    bgmSlider->loadSlidBallTextures("slider_ball.png", "slider_ball.png", "");
    bgmSlider->loadProgressBarTexture("slider_progress.png");
    bgmSlider->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.6));
    bgmSlider->addEventListener(CC_CALLBACK_2(Test_Scene_2::bgmSliderCallback, this));
    this->addChild(bgmSlider);

    // 创建音效音量滑动条控件
    auto sfxSlider = ui::Slider::create();
    sfxSlider->loadBarTexture("slider_progress.png");
    sfxSlider->loadSlidBallTextures("slider_ball.png", "slider_ball.png", "");
    sfxSlider->loadProgressBarTexture("slider_progress.png");
    sfxSlider->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.5));
    sfxSlider->addEventListener(CC_CALLBACK_2(Test_Scene_2::sfxSliderCallback, this));
    this->addChild(sfxSlider);

    // 设置滑动条的大小
    float desiredWidth = visibleSize.width - 100; // 设置滑动条的宽度
    float desiredHeight = bgmSlider->getContentSize().height; // 使用原始高度
    bgmSlider->setContentSize(Size(desiredWidth, desiredHeight));
    sfxSlider->setContentSize(Size(desiredWidth, desiredHeight));

    // 创建文字提示
    bgmLabel = Label::createWithSystemFont("", "Arial", 24);
    bgmLabel->setPosition(Vec2(bgmSlider->getPositionX() + bgmSlider->getContentSize().width / 2 + 50, bgmSlider->getPositionY()));
    this->addChild(bgmLabel);

    // 创建文字提示
    sfxLabel = Label::createWithSystemFont("", "Arial", 24);
    sfxLabel->setPosition(Vec2(sfxSlider->getPositionX() + sfxSlider->getContentSize().width / 2 + 50, sfxSlider->getPositionY()));
    this->addChild(sfxLabel);

    //文字显示
    auto BGMLabel = Label::createWithSystemFont("BGM", "Arial", 40);
    auto SFXLabel = Label::createWithSystemFont("SFX", "Arial", 40);
    BGMLabel->setPosition(Vec2(bgmSlider->getPositionX() - bgmSlider->getContentSize().width / 2-50 , bgmSlider->getPositionY()));
    SFXLabel->setPosition(Vec2(sfxSlider->getPositionX() - sfxSlider->getContentSize().width / 2-50 , sfxSlider->getPositionY()));
    this->addChild(BGMLabel);
    this->addChild(SFXLabel);
    ///////////////////////////////


    //退出当前场景的按钮
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

void Test_Scene_2::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}


void Test_Scene_2::bgmSliderCallback(Ref* sender, ui::Slider::EventType eventType)
{
    if (eventType == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        ui::Slider* slider = dynamic_cast<ui::Slider*>(sender);
        int volume = slider->getPercent();

        // 设置背景音乐音量
        CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(volume / 100.0f);

        // 更新文字提示
        std::string labelText = "" + std::to_string(volume) + "%";
        bgmLabel->setString(labelText);
    }
}

void Test_Scene_2::sfxSliderCallback(Ref* sender, ui::Slider::EventType eventType)
{
    if (eventType == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        ui::Slider* slider = dynamic_cast<ui::Slider*>(sender);
        int volume = slider->getPercent();

        // 设置音效音量
        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(volume / 100.0f);

        // 更新文字提示
        std::string labelText = "" + std::to_string(volume) + "%";
        sfxLabel->setString(labelText);
    }
}

