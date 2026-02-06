#include "UltimateAnimEvent.h"
#include "../../World/IWorld.h"
#include "../../GameSystem/Camera/Camera.h"
#include "../../GameSystem/Camera/CameraController.h"
#include "../../Actor/Charactor/Player/Player.h"
UltimateAnimEvent::UltimateAnimEvent(IWorld* world, int invokeType, const GSvector3& position, GSvector2 size)
	:Event::Event(world, invokeType, position, size)
{
	camera_ = new CameraController(CameraController::Disable);
	camera_->SetSmooth(true);
	world_->AddCameraController(camera_);
}

void UltimateAnimEvent::Update(float deltaTime)
{
	GSvector3 playerPos = player_->Transform().position();
	GSvector3 forward = player_->Transform().forward();  // プレイヤーの正面方向ベクトル
	GSvector3 right = player_->Transform().right();
	GSvector3 up = GSvector3(0, 1, 0);    // 上方向ベクトル
	if (timer_ < 30) {
        //プレイヤーを敵に近づける
        player_->UpdateDirection();
        if (player_->IsEnemyNearby()) player_->MoveForward(player_->NearstEnemyDist() - 1.5f);
        else player_->MoveForward(2);

		distanceBack = 1.0f;
		distanceSide = -2.0f;
		height = 0.3f;
        camera_->SetShakeValues(50.0f, 5.0f, 160.0f, 1.0f, 20.0f, { 0.1f,0.1f }, 0.0f);
	}
    else {
        distanceBack = 5.0f;
        height = 3.0f;
        if (timer_ < 60) {
            camera_->SetShake(shakeValues);
        }
        else if (timer_ < 80) {
        }
        else if (timer_ < 100) {
            camera_->SetShake(shakeValues);
        }
        else if (timer_ < 120) {
        }
        else if (timer_ < 170) {
            camera_->SetShake(shakeValues);
        }
        else if (timer_ < 180) {
            
        }
    }
    

	// カメラ位置を計算
	GSvector3 cameraPos = playerPos + (forward * -distanceBack) + (up * height) + (right * -distanceSide);
	GSvector3 cameraTar = playerPos + GSvector3{ 0.0f,1.5f,0.0f };
	camera_->SetView(cameraPos, cameraTar);

	//timer_がmaxTimeになったら以下を実行
	if (!EventWait(deltaTime))return;

	EndEvent();
}

void UltimateAnimEvent::Draw() const
{
}

void UltimateAnimEvent::BeginEvent()
{
	player_ = world_->GetPlayer();
	camera_->SetPriority(CameraController::Event);
	GSvector3 cameraPos = world_->GetCamera()->Transform().position();
	GSvector3 cameraTar = cameraPos.forward();
	camera_->SetView(cameraPos, cameraTar);
	//モーション時間をイベントの時間と同期させる
	SetEventTime(player_->GetMesh()->MotionEndTime());
}

void UltimateAnimEvent::EndEvent()
{
	camera_->SetPriority(CameraController::Disable);
	SetInvoke(false);
	ResetTimer();
}
