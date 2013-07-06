#ifndef __Modal__ModalScene__
#define __Modal__ModalScene__

#include "cocos2d.h"

class ModalLayer : public cocos2d::CCLayer
{
public:
    virtual bool init();
    void menuCloseCallback(CCObject* pSender);
    virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    CREATE_FUNC(ModalLayer);
};

#endif /* defined(__Modal__ModalScene__) */