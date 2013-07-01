#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
//********************************
//ゲームが開始されると呼び出される関数
//********************************
bool HelloWorld::init()
{
    //緑グラデーション
    //if(CCLayerGradient::initWithColor(ccc4(70,145,15,255), ccc4(170,220,120,255),ccp(0.0f,1.0f)))
    //白黒グラデーション
    if(CCLayerGradient::initWithColor(ccc4(70,70,70,255), ccc4(220,220,220,255),ccp(0.0f,1.0f)))
            
    {
        
        //********************************
        //プレイヤーの実装
        //********************************
        //画面の幅取得
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        //画像ファイルとrectを指定してスプライトを作成
        CCSprite *player = CCSprite::create("dj.png",CCRectMake(0,0,100,100) );
        //スプライトの位置を設定
        player->setPosition(ccp(player->getContentSize().width*3/2,winSize.height/2));
        //表示サイズ指定
        player->setScale(0.5);
        //後で識別できるようにtagを設定
        player->setTag(1);
        //スプライトをレイヤに追加
        this->addChild(player);
        //________________________________

    }
    
    //********************************
    //タッチモードの実装
    //********************************
    //シングルタッチモード
    //this->setTouchMode(kCCTouchesOneByOne);
    //this->setTouchEnabled(true);
    //マルチタッチモード
    this->setTouchMode(kCCTouchesAllAtOnce);
    this->setTouchEnabled(true);
    //__________________________________
    
    

    
    
    
    
    //********************************
    //３秒ごとのスケジュールでgameLogicを実行
    //********************************
    this->schedule(schedule_selector(HelloWorld::gameLogic),3.0);
    
    
    
        return true;
}


//********************************
//画像を表示する関数
//********************************
void HelloWorld::addPixelArt()
{
    
    //pixelArtのスプライトを作成してレイヤへ追加
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite *pixelArt = CCSprite::create("1.png", CCRectMake(0, 0,80,80));
    
    int height = rand() % (int)winSize.height;
    int width = rand() % (int)winSize.width;

    //登場する場所
    //pixelArt->setPosition(ccp(winSize.width + pixelArt->getContentSize().width/2, height));
    pixelArt->setPosition(ccp(width, height));

    pixelArt->setTag(2);
    this->addChild(pixelArt);
    
    //アクションの継続時間
    float duration = 2.0f;
    
    //動いた後の位置
    int height_goal = rand() % (int)winSize.height;
    int width_goal = rand() % (int)winSize.width;
    //アクションの作成
    //CCMoveTo* actionMove = CCMoveTo::create(duration, ccp(pixelArt->getContentSize().width*3/2, pixelArt->getPositionY()));
    CCMoveTo* actionMove = CCMoveTo::create(duration, ccp(width_goal,height_goal));
    //アクションの実行
    pixelArt->runAction(actionMove);
}
//********************************


//********************************
//タップに反応させる
//********************************
void HelloWorld::ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event)
{
 //タッチされた座標を取得
    CCTouch *touch = (CCTouch *)touches->anyObject();
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    //playerを取得(tag=1で識別)
    CCSprite *player = (CCSprite *)this->getChildByTag(1);
    
    //playerをタッチされた座標まで移動させる
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    //継続時間は移動距離に比例させる
    float length = sqrtf(powf(location.x - player->getPositionX(), 2.0f) + powf(location.y - player->getPositionY(), 2.0f));
    float duration = length / winSize.width * 1.5f;
    CCMoveTo* actionMove = CCMoveTo::create(duration, location);
    player->runAction(actionMove);
}
//********************************



//********************************
//ゲームロジックを起動すると行われる関数群
//********************************
void HelloWorld::gameLogic()
{
    this->addPixelArt();
}
//********************************


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


//********************************
//コメント
//********************************

//________________________________
