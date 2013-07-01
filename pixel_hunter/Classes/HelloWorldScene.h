#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

//通常の背景
//class HelloWorld : public cocos2d::CCLayer
//画面背景をグラデーションにする
class HelloWorld : public cocos2d::CCLayerGradient

{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    //追加宣言
    void addPixelArt();
    void gameLogic();
    void ccTouchesBegan();
    void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HelloWorld);
    
};

#endif // __HELLOWORLD_SCENE_H__
