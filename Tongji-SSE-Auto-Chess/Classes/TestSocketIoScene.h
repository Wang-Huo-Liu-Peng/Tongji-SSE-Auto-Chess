#pragma once
#ifndef __TestSocketIo_SCENE_H__
#define __TestSocketIo_SCENE_H__
#include "cocos2d.h"
#include "network\SocketIO.h"
USING_NS_CC;
using namespace cocos2d::network;

//继承SocketIO::SIODelegate和实现四个虚函数
class TestSocketIo : public cocos2d::Layer, SocketIO::SIODelegate
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    //socket连接时调用
    void onConnect(SIOClient* client);
    //收到数据时调用
    void onMessage(SIOClient* client, const std::string& data);
    //连接错误或接收到错误信号时调用
    void onError(SIOClient* client, const std::string& data);
    //socket关闭时调用
    void onClose(SIOClient* client);

    // implement the "static create()" method manually
    CREATE_FUNC(TestSocketIo);

    SIOClient* client;

};

#endif // __TestSocketIo_SCENE_H__

