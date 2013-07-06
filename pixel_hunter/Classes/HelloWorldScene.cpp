#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

//モーダルレイヤの実験
#include "ModalLayer.h"
//CCSpriteをタップ可能にする
#include "TapSprite.h"


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
    //EXP表示関数の実行
    //********************************
    this->EXPDisplay();
    //________________________________
    
    //********************************
    //コレクトモードボタン表示関数の実行
    //********************************
    this->collectModeButton();
    //________________________________
    

    

    
    
    //********************************
    //タッチモードの実装(※キャラ等の最後に実装)
    //********************************
    //シングルタッチモード
    //this->setTouchMode(kCCTouchesOneByOne);
    //this->setTouchEnabled(true);
    //マルチタッチモード
    this->setTouchMode(kCCTouchesAllAtOnce);
    this->setTouchEnabled(true);
    //__________________________________
    
    

    
    
    
    //********************************
    //プリロードの音源の関数を呼び出しBGMを再生
    //********************************
    this->preLoadSound();
    this->playBGM();
    //________________________________




    
    
    
    //********************************
    //３秒ごとのスケジュールでgameLogicを実行
    //********************************
    this->schedule(schedule_selector(HelloWorld::gameLogic),3.0);
    //________________________________

    
    //********************************
    //毎フレームごとに衝突判定メソッドを実行
    //********************************
    this->schedule(schedule_selector(HelloWorld::update));
    this->scheduleUpdate();
    //________________________________

    
    
    
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
    //直線移動
    //CCMoveTo* actionMove = CCMoveTo::create(duration, location);
    player->runAction(actionMove);
    
    //モーダルレイヤのコード
    //ModalLayer* layer = ModalLayer::create();
    //this->addChild(layer);
}
//********************************


//********************************
//音声のプリロード
//********************************
void HelloWorld::preLoadSound()
{
    //BGMのプリロード
    SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("BGM01.mp3");
    
    //効果音のプリロード
    SimpleAudioEngine::sharedEngine()->preloadEffect("config.wav");
    SimpleAudioEngine::sharedEngine()->preloadEffect("damage.wav");

    //BGMの音量の設定
    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);
    //効果音の音量設定
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
}
//________________________________



//********************************
//BGM再生
//********************************
void HelloWorld::playBGM()
{
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("BGM01.mp3", true);
}
//________________________________


//********************************
//効果音再生
//********************************
void HelloWorld::playSoundEffect()
{
    SimpleAudioEngine::sharedEngine()->playEffect("damage.wav");
    
}
//________________________________



//********************************
//衝突判定
//********************************
void HelloWorld::update(float dt)
{
    //playerのスプライトを取得(tag=1で識別)
    CCSprite* player = (CCSprite *)this->getChildByTag(1);
    //判定基準の領域
    CCRect playerRect = CCRectMake(
                                   player->getPosition().x -(player->getContentSize().width/4),
                                   player->getPosition().y -(player->getContentSize().height/4),
                                   player->getContentSize().width/2,
                                   player->getContentSize().height/2);
    
    //衝突対象のスプライトを取得(tag=2)で識別
    CCSprite* pixelArt = (CCSprite *)this->getChildByTag(2);
    if(pixelArt == NULL) return; //pixelArtが無ければ処理を抜ける
    CCRect pixelArtRect = CCRectMake(
                                     pixelArt->getPosition().x - (pixelArt->getContentSize().width/2),
                                     pixelArt->getPosition().y - (pixelArt->getContentSize().height/2),
                                     pixelArt->getContentSize().width,
                                     pixelArt->getContentSize().height
                                     );
    
    //衝突判定
    if(playerRect.intersectsRect(pixelArtRect))
    {
        //音声を再生
        this->playSoundEffect();
        
        //pixelArtを削除
        this->removeChild(pixelArt,true);

        //********************************
        //EXPロジック関数の実行
        //********************************
        this->EXPlogic();
        //________________________________

    }
}
//________________________________


//********************************
//コレクト機能の画像表示
//********************************
void HelloWorld::collectModeButton()
{
    
    //ボタン
    CCMenuItemImage *button = CCMenuItemImage::create("collect.png","black_collect.png",this,menu_selector(HelloWorld::collectMode));
    //表示位置
    
    //collectModeButtonのスプライトを作成してレイヤへ追加
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    int height = winSize.height*0.9;
    int width = winSize.width *0.9;
    
    //表示する場所
    button->setPosition(ccp(width, height));
    
    //タグで識別
    button->setTag(5);
    this->addChild(button);
}
//________________________________

//********************************
//コレクト機能のモーダルビュー起動
//********************************
void HelloWorld::collectMode(CCObject* pSender)
{
    //モーダルレイヤのコード
    ModalLayer* layer = ModalLayer::create();
    this->addChild(layer);
    
}
//********************************










//********************************
//EXPの表示
//********************************
void HelloWorld::EXPDisplay()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    if(CCLayer::init())
    {
        //EXP文字列
        CCLabelTTF* EXPLabel = CCLabelTTF::create("EXP","arial",48);
        EXPLabel->setPosition(ccp(winSize.width/2, winSize.height - EXPLabel->getContentSize().height/2));
        EXPLabel->setTag(3);
        this->addChild(EXPLabel);
        
        //EXPポイント
        CCLabelTTF* pointsLabel = CCLabelTTF::create("0","arial",48);
        pointsLabel->setPosition(ccp(EXPLabel->getPositionX() + EXPLabel->getContentSize().width,
                                     winSize.height - pointsLabel->getContentSize().height/2));
        pointsLabel->setTag(4);
        this->addChild(pointsLabel);
                              
    }
}
//________________________________


//********************************
//EXPのロジック
//********************************
void HelloWorld::EXPlogic()
{
    //EXPを加算
    this->EXP_Points += 3;
    //pointsLabelのラベルを取得
    CCLabelTTF* label = (CCLabelTTF *)this->getChildByTag(4);
    //intからCCStringにキャスト
    CCString* points = CCString::createWithFormat("%d",this->EXP_Points);
    //pointsLabelの表示を更新
    label->setString(points->getCString());
}
//________________________________








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
