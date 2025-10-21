#ifndef TIME_LINE_H_
#define TIME_LINE_H_
#include <vector>
#include <nlohmann/json.hpp>
#include "TImeLineData.h"

class IWorld;
class Actor;
//���s�p�L�[
struct TimeLineData {
	float playTime{ 0.0f };
	//int�̓t���[����
	std::map<int,std::vector<IKeyData*>> frameEvent{};
};

//IKey���̎�ނ𔻕ʂ���
template<typename T>
T* DAs(IKeyData* data) {
	return dynamic_cast<T*>(data);
}
template<typename T>
T* SAs(IKeyData* data) {
	return static_cast<T*>(data);
}

class TimeLine
{
public:
	TimeLine();
	~TimeLine();
	void Update(float deltaTime);
	//�C�x���g�J�n
	void StartTimeLine(std::string name);
	void EndTimeLine();
	void LoadFile();
	int TimeLineCount() const;
	float EventTimer();
	bool IsRunning();
	//�t���[�����Ƃ̃L�[�J�E���g
	int FrameKeyCount(std::string name) const;
    //�C�x���g����
	float EventTime(std::string name) const;
	void SetEventTime(std::string name,float time);
	//�L�[�f�[�^�S�擾
	TimeLineData* KeyDatas(std::string name) const;
	//�L�[�̒ǉ��E�폜
	void AddKey(std::string name,int frame, IKeyData* data);
	void DeleteKey(std::string name, int frame, IKeyData::KeyType type);
	void MoveKey(std::string name, int oldFrame,int newFrame, IKeyData* data);
	void SetIWorld(IWorld* world);
	void KeyDataClear();
	void AllClear();
private:
	
	void LoadView(std::vector<IKeyData*>& data, std::string key);
	void LoadEffect(std::vector<IKeyData*>& data, std::string key);
	void SetView(CameraKey* key);
	void SetEffect(EffectKey* key);
	void SetShake(CameraShakeKey* key);
	//�t�@�C���ǂݍ���
	nlohmann::ordered_json loadFile_;
	//�t���[�����Ƃɂ���C�x���g�f�[�^�i�Đ��p�j
	std::unordered_map<std::string, TimeLineData*> data_;
	//�ǉ��g���b�N���݂̏���
	std::vector<int> addOrderData_;
	float eventTimer_{ 0.0f };
	float endTime_{ 0.0f };
	TimeLineData* runningEvent_{ nullptr };
	IWorld* world_{ nullptr };
	CameraController* camera_{ nullptr };
	Actor* actor_{ nullptr };
};
#endif