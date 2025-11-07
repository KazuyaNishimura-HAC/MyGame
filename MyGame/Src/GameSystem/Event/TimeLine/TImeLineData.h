#ifndef TIMELINE_DATA_H_
#define TIMELINE_DATA_H_
#include "../../../GameSystem/Camera/CameraController.h"
class Actor;

struct TestEffect {
	float affected{ 0.0f };
};

//多種類のイベント内容を一括管理
struct IKeyData {
	virtual ~IKeyData() = default;
	//キー種類
	enum KeyType {
		Camera,
		Effect,
		Shake,
		//enum要素数
		TypeCount
	};
	KeyType type;
	// Actor追従用
	bool isTargetActor = false;
	Actor* targetActor = nullptr;
};
//キーごとの情報(ここにキー情報追加)
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
