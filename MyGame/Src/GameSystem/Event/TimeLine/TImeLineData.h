#ifndef TIMELINE_DATA_H_
#define TIMELINE_DATA_H_
#include "../../../GameSystem/Camera/CameraController.h"
class Actor;

struct TestEffect {
	float affected{ 0.0f };
};

//����ނ̃C�x���g���e���ꊇ�Ǘ�
struct IKeyData {
	virtual ~IKeyData() = default;
	//�L�[���
	enum KeyType {
		Camera,
		Effect,
		Shake,
		//enum�v�f��
		TypeCount
	};
	KeyType type;
	// Actor�Ǐ]�p
	bool isTargetActor = false;
	Actor* targetActor = nullptr;
};
//�L�[���Ƃ̏��(�����ɃL�[���ǉ�)
struct CameraKey : IKeyData {
	CameraKey() { type = Camera; }
	View view{};
};
struct EffectKey : IKeyData {
	EffectKey() { type = Effect; }
	TestEffect effect{};
};
struct CameraShakeKey : IKeyData {
	CameraShakeKey() { type = Shake; }
	CameraShake shake{};
};
#endif