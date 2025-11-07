#ifndef TIME_LINE_H_
#define TIME_LINE_H_
#include <vector>
#include <nlohmann/json.hpp>
#include "TImeLineData.h"

class IWorld;
class Actor;
//実行用キー
struct TimeLineData {
	float playTime{ 0.0f };
	//intはフレーム数
	std::map<int,std::vector<IKeyData*>> frameEvent{};
};

//IKey内の種類を判別する
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
	//イベント開始
	void StartTimeLine(std::string name);
	void EndTimeLine();
	void LoadFile();
	int TimeLineCount() const;
	float EventTimer();
	bool IsRunning();
	//フレームごとのキーカウント
	int FrameKeyCount(std::string name) const;
    //イベント時間
	float EventTime(std::string name) const;
	void SetEventTime(std::string name,float time);
	//キーデータ全取得
	TimeLineData* KeyDatas(std::string name) const;
	//キーの追加・削除
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
	//ファイル読み込み
	nlohmann::ordered_json loadFile_;
	//フレームごとにあるイベントデータ（再生用）
	std::unordered_map<std::string, TimeLineData*> data_;
	//追加トラック込みの順番
	std::vector<int> addOrderData_;
	float eventTimer_{ 0.0f };
	float endTime_{ 0.0f };
	TimeLineData* runningEvent_{ nullptr };
	IWorld* world_{ nullptr };
	CameraController* camera_{ nullptr };
	Actor* actor_{ nullptr };
};
#endif
