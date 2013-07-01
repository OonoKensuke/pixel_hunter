#ifndef  _MODAL_LAYER_H_
#define  _MODAL_LAYER_H_


#include "cocos2d.h"

class ModalLayer : public cocos2d::CCLayer
{
public:
	virtual bool init();
	void menuCloseCallback(CCObject* pSender);
	virtual bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
	CREATE_FUNC(ModalLayer);
};
#endif
