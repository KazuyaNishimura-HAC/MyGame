#ifndef PLAYER_H_
#define PLAYER_H_

#include <vector>
#include "../Actor.h"
#include "../../AssetID/Model.h"
#include "../../State/StateMachine.h"

class GUI;

class Player : public Actor
{
public:
    //コンストラクタ
    Player(IWorld* world = nullptr, GSuint mesh = Model::Player);
    Player(IWorld* world, GSuint mesh,const GSvector3& position);
    //デストラクタ
    ~Player()override;

    //更新
    virtual void Update(float deltaTime)override;
    virtual void LateUpdate(float deltaTime)override;
    //描画
    void Draw()const override;
    //接触判定
    void React(Actor& other)override;

    void Debug(float deltaTime)override;
private:
    StateMachine states_;
};
#endif
