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
	//��������
	float decayTime;
	//�������x
	float decaySpeed;
	//���g���i����h��邩�j
	float hz;
	//�h��̉e���x
	GSvector2 affectVector;
	float affectFov;
	
	CameraShake(float time, float strength, float decayTime, float decaySpeed, float hz, GSvector2 vectorAffect, float fovAffect)
		:timer{ time }, strength{ strength }, decayTime{ decayTime }, decaySpeed{ decaySpeed }, hz{ hz }, affectVector{ vectorAffect }, affectFov{ fovAffect }
	{};
	//�������A�����l�ݒ�
	CameraShake() :CameraShake(0.0f, 2.0f, 30.0f, 1.0f, 20.0f, { 1.0f,1.0f }, 5.0f) {};

	void Update(float deltaTime) {
		float t = timer / 60.0f;
		float r = t * affectRand;
		randValue += { gsRandf(-r, r), gsRandf(-r, r), gsRandf(-r, r) };
		timer = MAX(timer - deltaTime * decaySpeed, 0);
	}
	//�V�F�C�N��̒l��ԋp
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
	//�h��̃����_���l
	GSvector3 randValue{ 0.0f,0.0f,0.0f };
	//�����_���h��̉e���x
	float affectRand{ 5.0f };
};

class CameraController
{
public:
	enum Priority {
		Disable,  //����
		Player,   //�v���C���[
		Event,    //�C�x���g
		Debug     //�f�o�b�N�p
	};
	CameraController(Priority p = Priority::Disable,int id = 0,const GSvector3& position = { 0,0,0 }, const GSvector3& target = { 0,0,0 });
	void Update(float deltaTime);
	//���W�ݒ�E�擾
	void SetPosition(const GSvector3& pos);
	GSvector3 GetPosition() const;
	//�����_�ݒ�E�擾
	void SetViewTarget(const GSvector3& tar);
	GSvector3 GetViewTarget() const;
	//�D��x�ݒ�E�擾
	void SetPriority(Priority p,bool preMove = false);
	Priority GetPriority() const;
	//�D��x�����擾
	std::string GetPriorityName() const;
	//���W�E�����_�ݒ�
	void SetView(const GSvector3& pos,const GSvector3& tar);
	//View�\���̎擾
	View& GetView();
	//�J����ID�̎擾�E�ݒ�
	void SetID(int id);
	int GetID() const;
	//����p�ݒ�E�擾
	void SetFov(float fov);
	float GetFov() const;
	//Lerp�ݒ�E�擾
	void SetSmooth(bool smooth);
	bool IsSmooth() const;

	void SetMovePrevious(bool preMove);
	bool IsMovePrevious() const;

	void Die();
	bool IsDead()const;

	//======�V�F�C�N����=======

	//�V�F�C�N��r���[
	View GetAffectedView();
	//�V�F�C�N�l��ݒ�
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
	//�֑ؑO�̃J��������ړ����邩
	bool preMove_{ false };
};

#endif