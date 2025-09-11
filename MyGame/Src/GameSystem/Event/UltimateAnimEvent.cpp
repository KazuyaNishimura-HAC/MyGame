#include "UltimateAnimEvent.h"
#include "../../GameSystem/Camera/CameraController.h"
#include "../../Actor/Player/Player.h"
#include "../../Graphics/Effect/PostEffect.h"

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
	PostEffect::Instance().SetIntensity(intensity);
	intensity -= deltaTime / 120.0f;
	intensity = CLAMP(intensity,0.0f,1.0f);
	if (timer_ < 30) {
		distanceBack = 1.0f;
		distanceSide = -2.0f;
		height = 0.3f;
	}
	else if (timer_ < 60) {
		distanceBack = 3.0f;
		distanceSide = -1.0f;
		height = 1.5f;
		intensity = 0.8f;
	}
	else if (timer_ < 80) {
		distanceBack = 3.0f;
		distanceSide = 1.0f;
		height = 1.5f;
	}
	else if (timer_ < 100) {
		distanceBack = 3.0f;
		distanceSide = -1.0f;
		height = 1.5f;
	}
	else if (timer_ < 120) {
		distanceBack = 3.0f;
		distanceSide = 1.0f;
		height = 1.5f;
		intensity = 0.8f;
	}
	else if (timer_ < 170) {
		distanceBack = 3.0f;
		distanceSide = -1.0f;
		height = 1.5f;
	}
	else if (timer_ < 180) {
		distanceBack = 4.5f;
		distanceSide = 0.0f;
		height = 1.5f;
		intensity = 0.8f;
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
	maxTime_ = player_->GetMesh()->MotionEndTime();
}

void UltimateAnimEvent::EndEvent()
{
	camera_->SetPriority(CameraController::Disable);
	IsInvoke(false);
	timer_ = 0.0f;
	PostEffect::Instance().SetIntensity(0.35f);
}
