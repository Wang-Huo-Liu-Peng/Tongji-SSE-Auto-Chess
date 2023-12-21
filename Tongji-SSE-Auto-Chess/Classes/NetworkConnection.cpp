#include "cocos2d.h"
#include "network/HttpClient.h"

USING_NS_CC;
using namespace network;

class TimeSaveManager {
public:
    static TimeSaveManager* getInstance() {
        static TimeSaveManager instance;
        return &instance;
    }

    // 发送GET请求获取用户的时间存档数据
    void getTimeSave(const std::string& userId) {
        HttpRequest* request = new HttpRequest();
        request->setUrl(StringUtils::format("http://localhost:3000/get-time-save/%s", userId.c_str()));
        request->setRequestType(HttpRequest::Type::GET);
        request->setResponseCallback(CC_CALLBACK_2(TimeSaveManager::onGetTimeSaveResponse, this));
        HttpClient::getInstance()->send(request);
        request->release();
    }

    // 发送POST请求更新用户的时间存档数据
    void updateTimeSave(const std::string& userId, int newTimeSave) {
        HttpRequest* request = new HttpRequest();
        request->setUrl("http://localhost:3000/update-time-save");
        request->setRequestType(HttpRequest::Type::POST);
        request->setResponseCallback(CC_CALLBACK_2(TimeSaveManager::onUpdateTimeSaveResponse, this));

        // 设置请求参数
        std::string postData = StringUtils::format("userId=%s&timeSave=%d", userId.c_str(), newTimeSave);
        request->setRequestData(postData.c_str(), postData.size());

        // 发送请求
        HttpClient::getInstance()->send(request);
        request->release();
    }

private:
    // 处理GET请求的回调
    void onGetTimeSaveResponse(HttpClient* client, HttpResponse* response) {
        if (!response || !response->isSucceed()) {
            CCLOG("Get Time Save Request failed");
            return;
        }

        // 处理服务器响应的数据，这里可以解析JSON等格式
        std::vector<char>* buffer = response->getResponseData();
        std::string responseData(buffer->begin(), buffer->end());
        CCLOG("Get Time Save Response: %s", responseData.c_str());
        // 在这里处理服务器响应的数据
    }

    // 处理POST请求的回调
    void onUpdateTimeSaveResponse(HttpClient* client, HttpResponse* response) {
        if (!response || !response->isSucceed()) {
            CCLOG("Update Time Save Request failed");
            return;
        }

        // 处理服务器响应的数据，这里可以解析JSON等格式
        std::vector<char>* buffer = response->getResponseData();
        std::string responseData(buffer->begin(), buffer->end());
        CCLOG("Update Time Save Response: %s", responseData.c_str());
        // 在这里处理服务器响应的数据
    }
};
