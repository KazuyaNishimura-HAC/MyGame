#include "GameEndEvent.h"
#include "../../Sound/SoundManager.h"
#include "../../GameSystem/InputSystem/InputSystem.h"
#include "../../UI/BlinkingImage.h"
const GSvector3 cameraOffset{ 0,6,15 };
const GSvector3 cameraBuckOffset{ 0,6,-15 };
const GSvector3 playerOffset{ 0,6,0 };
GameEndEvent::GameEndEvent(IWorld* world, const GSvector3& position, GSvector2 size)
    :Event::Event(world, position, size)
{
}

void GameEndEvent::Update(float deltaTime)
{
    for (int i = 0; i < cameras_.size();i++) {
        CameraMove(cameras_[i],i,deltaTime);
        //初期地点移動から地面に着いたらフリップ可能
        if (onceEvents_[i]) continue;
        if (sequence_ >= 2) {
            //フリップ中は初期地点に戻らない
            if (!(charactors_[i]->IsFlip())) {
                charactors_[i]->Transform().position({ 0,10,0 });
                charactors_[i]->PathReset();
                onceEvents_[i] = true;
            }
        }
    }
    
    if (sequence_ >= 2 && InputSystem::ButtonTrigger(InputSystem::Button::A))
    {
        EndEvent();
        return;
    }
    //time_が0になったら以下を実行
    if (!EventWait(deltaTime))return;
    sequence_++;
    if (sequence_ == 1) {
        for (auto camera : cameras_) {
            camera->SetPriority(Camera::Event);
            camera->SetFov(50.0f);
        }
        for(int i = 0;i < cameras_.size();i++) cameraAzimuths_[i] = cameras_[i]->Transform().eulerAngles().y - 180;

        // BGM処理
        if (!isPlayBGM_) {
            isPlayBGM_ = true;
            // CPU戦で負けた時は敗北BGM
            if (charactors_[1]->GetName() == "Enemy" && charactors_[0]->Winner() == false) {
                SoundManager::PlayBGM(Sound::BGM::ResultLoseBGM);
            }
            // それ以外の場合は勝利BGM
            else {
                SoundManager::PlayBGM(Sound::BGM::ResultWinBGM);
            }
        }
    }
    if (sequence_ == 2) {
        
        world_->AddGUI(new BlinkingImage({ Screen::HalfWidth,Screen::ScreenHeight - 100 }, Texture::PushToA, GSvector2(0.25f, 0.25f)));
    }
    timer_ = countDownTime;
}

void GameEndEvent::Draw() const
{
}

void GameEndEvent::BeginEvent()
{
    SoundManager::StopAll();

    SoundManager::PlaySE(Sound::SE::GameFinish);
    //イベント開始時のタイマ設定
    timer_ = countDownTime;
    //タイム処理を停止
    world_->Timer(false);
    //勝敗を決定(先に触れたキャラが勝利)
    reactCharactor_->Winner(true);
    reactCharactor_->GetEnemy()->Winner(false);
    //情報登録（カメラ、キャラクター）
    for (int i = 0; i < world_->GetCameraCount(); i++) {
        cameras_.push_back(world_->GetCameras(i));
    }
    charactors_.push_back(world_->GetCharactor(0));
    charactors_.push_back(world_->GetCharactor(1));

    //コースパスを取得
    cosePath_ = charactors_[0]->GetPathCose();

    //パスコースを設定
    for (auto charactor : charactors_) {
        SetCosePath(charactor);
    }

}

void GameEndEvent::EndEvent()
{
    
    world_->IsEnd(true);
    isEnd_ = true;
    //vector内を空に（メモリ未開放）
    cameras_.clear();
    charactors_.clear();
}

void GameEndEvent::CameraMove(Camera* camera,int id, float deltaTime)
{
    if (sequence_ == 0 && charactors_[id]->Winner()) {
        GSvector3 rotate = charactors_[id]->Transform().eulerAngles();
        //if (camera->GetPriority() == Camera::Event) return;
        camera->SetPriority(Camera::Event);
        camera->SetEulerAngle(rotate);
        camera->SetPosition(transform_.position() + k_GoalCamera_);
        camera->View(transform_.position() + k_GoalCamera_ + transform_.forward());  
    }
    if (sequence_ == 1) {
        
        if (camera->IsInversion()) cameraAzimuths_[id] += cameraSpeed_* deltaTime;
        else cameraAzimuths_[id] -= cameraSpeed_ * deltaTime;
        if (cameraAzimuths_[id] >= 360.0f) cameraAzimuths_[id] -= 360.0f;
    }
    if (sequence_ >= 1) {
        camera->SetEulerAngle(charactors_[id]->Transform().eulerAngles());
        camera->CalculatePosition(
            playerOffset * charactors_[id]->Transform().localToWorldMatrix(),
            15,
            cameraAzimuths_[id],
            0
        );
        camera->View(charactors_[id]->Transform().position());
    }
}

void GameEndEvent::SetCosePath(Charactor* charactor)
{
    //距離の初期値
    float minDist = 80.0f;
    int pathIndex = 0;
    GSvector3 charPos = charactor->Transform().position();

    for (int i = 0; i < cosePath_.size(); ++i) {
        GSvector3 dXZ = { cosePath_[i].x - charPos.x, 0.0f, cosePath_[i].z - charPos.z };
        const float dist = gsVector3Length(&dXZ);
        if (dist < minDist) {
            minDist = dist;
            //パス階層を取得
            pathIndex = i;
        }
    }
    //一番距離が近いパスを設定
    charactor->SetPathIndex(pathIndex);

}
