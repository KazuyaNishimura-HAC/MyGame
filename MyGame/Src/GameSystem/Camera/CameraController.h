#ifndef CAMERA_CONTROLLER_H_
#define CAMERA_CONTROLLER_H_
#include <GStransform.h>
#include <string>

struct View {
	GSvector3 pos;
	GSvector3 tar;
	float fov{ 45.0f };
	bool isSmooth{ false };
};

struct CameraShake {
	float timer;
	float strength;
	//減衰時間
	float decayTime;
	//減衰速度
	float decaySpeed;
	//周波数（何回揺れるか）
	float hz;
	//揺れの影響度
	GSvector2 affectVector;
	float affectFov;
	
	CameraShake(float time, float strength, float decayTime, float decaySpeed, float hz, GSvector2 vectorAffect, float fovAffect)
		:timer{ time }, strength{ strength }, decayTime{ decayTime }, decaySpeed{ decaySpeed }, hz{ hz }, affectVector{ vectorAffect }, affectFov{ fovAffect }
	{};
	//生成時、初期値設定
	CameraShake() :CameraShake(0.0f, 2.0f, 30.0f, 1.0f, 20.0f, { 1.0f,1.0f }, 5.0f) {};

	void Update(float deltaTime) {
		float t = timer / 60.0f;
		float r = t * affectRand;
		randValue += { gsRandf(-r, r), gsRandf(-r, r), gsRandf(-r, r) };
		timer = MAX(timer - deltaTime * decaySpeed, 0);
	}
	//シェイク後の値を返却
	View ShakeView(View view) {
		if (timer <= 0.0f || strength <= 0.0f) return view;
		float pow = sinf(strength * timer * hz * 3.141f / 60 + randValue.z) * MIN(timer / decayTime, 1);
		view.fov += affectFov * pow;
		GSvector3 dir = (view.tar - view.pos).normalized();
		GSvector3 right = dir.cross(GSvector3::up()).normalized();
		GSvector3 up = dir.cross(right).normalized();
		GSvector2 randV{ sinf(view.tar.x + randValue.x),sinf(view.tar.z + randValue.y) };
		up *= affectVector.y * pow * randV.y;
		right *= affectVector.x * pow * randV.x;
		view.tar += up + right;
		view.pos -= up + right;
		return view;
	};
private:
	//揺れのランダム値
	GSvector3 randValue{ 0.0f,0.0f,0.0f };
	//ランダム揺れの影響度
	float affectRand{ 5.0f };
};

class CameraController
{
public:
	enum Priority {
		Disable,  //無効
		Player,   //プレイヤー
		Event,    //イベント
		Debug     //デバック用
	};
	CameraController(Priority p = Priority::Disable,int id = 0,const GSvector3& position = { 0,0,0 }, const GSvector3& target = { 0,0,0 });
	void Update(float deltaTime);
	//座標設定・取得
	void SetPosition(const GSvector3& pos);
	GSvector3 GetPosition() const;
	//注視点設定・取得
	void SetViewTarget(const GSvector3& tar);
	GSvector3 GetViewTarget() const;
	//優先度設定・取得
	void SetPriority(Priority p);
	Priority GetPriority() const;
	//優先度名を取得
	std::string GetPriorityName() const;
	//座標・注視点設定
	void SetView(const GSvector3& pos,const GSvector3& tar);
	//View構造体取得
	View& GetView();
	//カメラIDの取得・設定
	void SetID(int id);
	int GetID() const;
	//視野角設定・取得
	void SetFov(float fov);
	float GetFov() const;
	//Lerp設定・取得
	void SetSmooth(bool smooth);
	bool IsSmooth() const;

	void Die();
	bool IsDead()const;

	//======シェイク処理=======

	//シェイク後ビュー
	View GetAffectedView();
	//シェイク値を設定
	void SetShakeValues(float timer = 0, float strength = 2, float decayTime = 30, float decaySpeed = 1, float hz = 20, GSvector2 vectorAffect = { 1,1 }, float fovAffect = 5);
	void SetShake(const CameraShake& shake);

	CameraShake& GetShake();

	bool IsShake();
	
private:
	View view_{};
	Priority priority_;
	CameraShake shake_{};
	int id_{ 0 };
	bool isDead_{ false };
};

#endif