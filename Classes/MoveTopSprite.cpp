//
//  MoveTopSprite.cpp
//  MoveSprite
//
//  Created by MAEDAHAJIME on 2015/02/10.
//
//

#include "MoveTopSprite.h"

USING_NS_CC;

// _/_/_/ コンストラクタ プロパティー _/_/_/
MoveTopSprite::MoveTopSprite()
: _player(NULL) // 初期化
{
    
}

// MainScene デストラクタで解放 メモリーリークを防ぐ
// Objective-C deallocと同じ様なもの
MoveTopSprite::~MoveTopSprite()
{
    CC_SAFE_RELEASE_NULL(_player); // _spriteをreleaseしてメモリーリークを防ぎます
}

// createSceneはLayerをSceneに貼り付けて返すクラスメソッドです。
// 自分自身(MoveTopSprite)を生成し、空のSceneに貼り付けて返す簡単な処理を行っているだけです。
// これでほかのシーンからの遷移が楽に行えます。
Scene* MoveTopSprite::createScene()
{
    auto scene = Scene::create();
    auto layer = MoveTopSprite::create();
    scene->addChild(layer);
    return scene;
}

bool MoveTopSprite::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    // 初期化処理
    
    // Directorを取り出す
    auto director = Director::getInstance();
    
    //画面サイズを取得
    auto size = Director::getInstance()->getVisibleSize();
    // バックグランドカラー（ブルー）
    auto background = LayerColor::create(Color4B::BLUE,
                                         size.width,
                                         size.height);
    // Layerにバックグランドを追加
    this->addChild(background);
    
    //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
    
    // Playerをスプライトとして生成し、setPlayer()を使いメンバー変数にしています
    this->setPlayer(Sprite::create("Icon-304.png"));
    
    //位置を設定
    _player->setPosition(Vec2(680,400));
    
    //画面に追加をしています。
    this->addChild(_player);
    
    //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
    
    // シングルタッチモード
    auto listener = EventListenerTouchOneByOne::create();
    
    // ラムダ式
    // onTouchBeganは必須
    // 画面がタッチされたときに呼び出されます
    listener->onTouchBegan = [](Touch* touch, Event* event){
        
        // タッチされた時の処理
        
        // タッチ位置のログ出力
        log("Touch at (%f, %f)", touch->getLocation().x, touch->getLocation().y);
        
        return true; //　イベントを実行する　falseが返されたときは以後のイベントは実行されません。
    };
    
    
    // タッチされた点が移動したときに毎フレームが呼び出されます
    // []にthisが追加されています。ラムダキャプチャ ラムダの中で_player変数を利用している
    listener->onTouchMoved = [this](Touch* touch, Event* event){
        
        /* ラムダキャプチャ
         [=] : 全てのオブジェクトのコピーがラムダ式に渡されます。
         [&] : 全てのオブジェクトの参照がラムダ式に渡されます。
         [obj] :objのコピーがラムダ式に渡されます。
         [&obj]:objの参照がラムダ式に渡されます。
        */
        
        // タッチ中に動いた時の処理
        
        // タッチ位置が動いた時
        // 前回とのタッチ位置との差をベクトルで取得する
        Vec2 delta = touch->getDelta();
        
        // 現在のかわずたんの座標を取得する
        Vec2 position = _player->getPosition();
        
        // 現在座標　+ 移動量を新たな座標にする
        Vec2 newPosition = position + delta;
        
        /////////////////////////////////////////
        // キャラクターが画面から飛び出してしまうのを防ぐ
        // 画面サイズを取り出す
        auto winsiz = Director::getInstance()->getWinSize();
        

        if (newPosition.x < 0) { //もし、新しい位置が左端より左だったら

            newPosition.x = 0;   //x座標を0にする

        } else if(newPosition.x > winsiz.width){ //もし、右端より右だったら

            newPosition.x = winsiz.width;   //x座標を画面の横幅にする
        }

        if (newPosition.y < 0) { //もし、新しい位置が左端より左だったら
            
            newPosition.y = 0;   //y座標を0にする
            
        } else if(newPosition.y > winsiz.height){ //もし、右端より右だったら
            
            newPosition.y = winsiz.height;   //x座標を画面の縦幅にする
        }
        
        // "player.png"
        _player->setPosition(newPosition);
        
    };
    
    // EventListenerをEventDispatcherに登録してイベントの処理は完了
    // directorからEventDispatcherを取り出し、EventListenerを登録しています。
    // addEventListenerWithSceneGraphPriorityは、イベントの実行の優先順位を
    // ノードの重なり順に依存させる登録方法です。
    // 複数のEventListenerが登録されているとき、ノードの重なり順が上の方から優先的
    // に実行されていきます。
    // 今回はLayer全体でタッチを受け付けているため、thisを指定しています。
    director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}
