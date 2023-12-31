#include "goldenshovel_hero_design.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "SettingScene.h"
#include "AccountScene.h"
#include "PrepareScene.h"
#include <Show_Chinese.h>

//#include<vector>
//#include "NetworkConnection.h"
#include"Client.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    

    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    /********************网络连接函数*********************/
    // 使用 NetworkManager 检查网络连接
   // NetworkManager::getInstance()->checkNetworkConnection();
    /*****************************************************/


    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("gyz.mp3", true);
    bool sound = UserDefault::getInstance()->getBoolForKey("SOUND"); //声音变量
    LabelTTF* isSoundBtn; //声音切换按钮
    if (sound)
        isSoundBtn = LabelTTF::create("Sound On", "Arial", 40);
    else
        isSoundBtn = LabelTTF::create("Sound Off", "Arial", 40);
    isSoundBtn->setColor(Color3B(204, 255, 253));
    float x = origin.x + visibleSize.width - isSoundBtn->getContentSize().width;
    float y = origin.y + visibleSize.height-isSoundBtn->getContentSize().height;
    isSoundBtn ->setPosition(Vec2(x, y));

    //isSoundBtn->setPosition(Point(visibleSize.width / 2, 50));
    this->addChild(isSoundBtn,2);
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width;
        float y = origin.y + closeItem->getContentSize().height;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    auto Show_Designer = Label::createWithTTF("Designed By L1KEAB0T&Ethebest777&Rock1ey&CoArrayLiu", "fonts/AaJiuZhongXiao-2.ttf", 24);
    if (Show_Designer == nullptr)
    {
        problemLoading("'fonts/AaJiuZhongXiao-2.ttf'");
    }
    else
    {
        Show_Designer->setColor(Color3B(249, 194, 111));
        // position the label on the center of the screen
        Show_Designer->setPosition(Vec2(origin.x + Show_Designer->getContentSize().width/2,
                                origin.y + visibleSize.height - Show_Designer->getContentSize().height/2));

        // add the label as a child to this layer
        this->addChild(Show_Designer, 1);
    }

    // add "HelloWorld" splash screen"
    auto Start_Screen = Sprite::create("Start_Screen.png");
    if (Start_Screen == nullptr)
    {
        problemLoading("'Start_Screen.png'");
    }
    else
    {
        // position the sprite on the center of the screen
        Start_Screen->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(Start_Screen, 0);
    }

    //创建菜单(用标签创建)
    //创建一个TTFConfig对象来设置标签的共同属性
    TTFConfig labelConfig;
    labelConfig.fontFilePath = "fonts/Marker Felt.ttf";
    labelConfig.fontSize = 60;
    labelConfig.glyphs = GlyphCollection::DYNAMIC;
    labelConfig.outlineSize = 0;
    labelConfig.customGlyphs = nullptr;
    labelConfig.distanceFieldEnabled = false;

    //菜单所需要的标签
    auto TestLabel_2 = Label::createWithTTF(labelConfig, "Setting");
    auto TestLabel_3 = Label::createWithTTF(labelConfig, "Practice");
    auto TestLabel_4 = Label::createWithTTF(labelConfig, "Account");

    // creating a Menu from a Vector of items
    Vector<MenuItem*> MenuItems;
    auto TestItem_2 = MenuItemLabel::create(TestLabel_2,
        [&](Ref* sender) {
            Director::getInstance()->pushScene(SettingScene::createScene());
        });
    auto TestItem_4 = MenuItemLabel::create(TestLabel_4,
        [&](Ref* sender) {
            Director::getInstance()->pushScene(AccountScene::createScene());
        });
    auto TestItem_3 = MenuItemLabel::create(TestLabel_3,
        [&](Ref* sender) {
            Player[1].RecoverData();
            Player[2].RecoverData();
            Player[1].Operator = HUMAN;
            Player[2].Operator = AI;
            Player[1].refresh_shop_free();
            Player[2].refresh_shop_free();
            PrepareScene* prepare1 = PrepareScene::create(1);
            Director::getInstance()->pushScene(prepare1);
        });


    //设置各个标签的间距
    const int height = TestItem_2->getContentSize().height;
    TestItem_2->setPosition(Vec2(origin.x ,origin.y -height * 3));
    TestItem_3->setPosition(Vec2(origin.x, origin.y - height * 2));
    TestItem_4->setPosition(Vec2(origin.x, origin.y - height * 1));
    MenuItems.pushBack(TestItem_2);
    MenuItems.pushBack(TestItem_4);
    MenuItems.pushBack(TestItem_3);

    auto GameMenu = Menu::createWithArray(MenuItems);
    GameMenu->setPosition(Vec2(origin.x + visibleSize.width / 2,
        origin.y + visibleSize.height / 2 - height * 2));
    this->addChild(GameMenu, 1);//将整个菜单加入场景中


    connectionFuture = connectionPromise.get_future();
    std::thread([&]() {
        bool result = Client::getInstance()->connect_to_server();
        connectionPromise.set_value(result);
    }).detach();



    Client::getInstance()->begin_send_and_listen();
    if (Client::getInstance()->csocket.isConnected)
        CCLOG("connected");
    else
        CCLOG("not connected");

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Client::getInstance()->write_event(Exit);
    Client::getInstance()->send_msg();
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
    CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void HelloWorld::update(float delta) {
    if (connectionFuture.valid() && connectionFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
        // 连接操作已经完成
        bool connectionResult = connectionFuture.get();

        if (connectionResult) {
            // 连接成功的处理代码
            CCLOG("Connected to server!");
        }
        else {
            // 连接不成功的处理代码
            CCLOG("Failed to connect to server.");
        }

        // 清除 future 对象，避免再次访问
        connectionFuture = std::future<bool>();
    }

    // ... 其他 update 逻辑
}