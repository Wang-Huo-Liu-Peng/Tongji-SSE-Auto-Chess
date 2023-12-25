// PopupManager.h
#pragma once

#include "cocos2d.h"

class PopupManager {
public:
    static void displayPopup(cocos2d::Layer* parentLayer, const std::string& displayText);

private:
    static void errorWindowClose(cocos2d::Ref* sender);
};
