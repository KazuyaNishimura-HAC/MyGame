#ifndef CAMERA_CONTROLLER_H_
#define CAMERA_CONTROLLER_H_
#include <GStransform.h>
#include <string>

struct View {
	GSvector3 pos;
	GSvector3 tar;
	GSvector3 rot;
	float fov{ 45.0f };
	bool isSmooth{ false };
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
	void SetPosition(const GSvector3& pos);
	GSvector3 GetPosition() const;
	void SetViewTarget(const GSvector3& tar);
	GSvector3 GetViewTarget() const;
	void SetPriority(Priority p);
	void SetView(const GSvector3& pos,const GSvector3& tar);
	Priority GetPriority() const;
	std::string GetPriorityName() const;
	void SetID(int id);
	int GetID() const;
	void SetFov(float fov);
	float GetFov() const;
	void SetSmooth(bool smooth);
	bool GetSmooth();


	View& GetView();
	
	void Die();
	bool IsDead()const;
private:
	View view_{};
	Priority priority_;
	int id_;
	bool isDead_{ false };
};

#endif