//
//  ModalLayer.m
//  pixel_hunter
//
//  Created by 大野 謙介 on 13/07/02.
//  Copyright 2013年 __MyCompanyName__. All rights reserved.
//


//#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ModalLayer.h"

using namespace cocos2d;
using namespace CocosDenshion;




//モーダルレイヤの優先順位
#define kModalLayerPriority kCCMenuHandlerPriority-1
//モーダルレイヤ上のCCMenuの優先順位
#define kModalLayerMenuPriority kCCMenuHandlerPriority-2

bool ModalLayer::init()
{
	if( !CCLayer::init() )
	{
		return  false;
	}
    
	this->setTouchPriority(kModalLayerPriority);
	this->setTouchEnabled(true);
	this->setTouchMode(kCCTouchesOneByOne);
    
	CCSize size = CCDirector::sharedDirector()->getVisibleSize();
    
	CCSprite* frame = CCSprite::create("frame.png");
	frame->setPosition(
                       ccp(size.width/2,size.height/2));
                       this->addChild(frame);
                       
                       CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                                             "tg_close_1.png",
                                                                             "tg_close_2.png",
                                                                             this,
                                                                             menu_selector(ModalLayer::menuCloseCallback) );
                       
                       CCSize frameSize = frame->getContentSize();
                       CCSize buttonSize = pCloseItem->getContentSize();
                       
                       pCloseItem->setPosition(ccp(
                                                   size.width/2 + frameSize.width/2 - buttonSize.width/2 -10,
                                                   size.height/2 + frameSize.height/2 - buttonSize.height/2 -10));
                       
                       
                       CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
                       pMenu->setTouchPriority(kModalLayerMenuPriority);
                       pMenu->setPosition(CCPointZero);
                       this->addChild(pMenu);
                       
                       return true;
                       }
                       
                       bool ModalLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
    {
        //モーダルレイヤで全てのタッチイベントを拾う
        return true;
    }
                       
                       void ModalLayer::menuCloseCallback(CCObject* pSender)
    {
        this->removeFromParentAndCleanup(true);
    }