//
//  MoveTopSprite.h
//  MoveSprite
//
//  Created by MAEDAHAJIME on 2015/02/10.
//
//

#ifndef __MoveSprite__MoveTopSprite__
#define __MoveSprite__MoveTopSprite__

#include "cocos2d.h"

class MoveTopSprite :public cocos2d::Layer
{
protected:
    // コンストラクタ 初期化
    MoveTopSprite();
    // デストラクタ メモリーリークを解放
    virtual ~MoveTopSprite();
    // メソッド CREATE_FUNCとの連携
    bool init() override;
    
public:
    static cocos2d::Scene* createScene();
    
    CREATE_FUNC(MoveTopSprite);
    
    // _/_/_/ プロパティー _/_/_/
    // 頻繁に他の場所から参照するためメンバー変数としてシーンクラスに保持させる
    //　_Player変数と、getPlayer()メソッド、setPlayer(Sprite *)メソッドが自動的に実装される
    CC_SYNTHESIZE_RETAIN(cocos2d::Sprite*, _player, Player);
};


#endif /* defined(__MoveSprite__MoveTopSprite__) */
