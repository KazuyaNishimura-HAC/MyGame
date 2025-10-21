#ifndef TIME_LINE_EDITOR_H_
#define TIME_LINE_EDITOR_H_
#include <vector>
#include <imgui/imgui.h>
#include <GStransform.h>
#include "TimeLine.h"
class IWorld;
class TimeLineEditor
{
public:
	TimeLineEditor(IWorld* world,TimeLine& timeLine);
	~TimeLineEditor();
	void Update(float deltaTime);
	void DrawEditUI();
private:
	//フレームキーUIの移動
	struct EditKeyData {
		bool selected{ false };
		int frame{ 0 };
		GSvector2 pos{ 0.0f,0.0f };
		IKeyData* data{ nullptr };
	};
	void Clear();
	
	void AddTimeLine();
	void AddKey();
	void DeleteKey();
	void Edit();
	void KeyEdit();
	void PreView();
	void LoadKeyData(std::string name = "");
	void Save();
	void DrawUI();
	void UpdateKeyFrame(EditKeyData* key);
	GSvector2 ImVecToGSVec(ImVec2 vec);
	ImVec2 GSVecToImVec(GSvector2 vec);
	int KeyCount(int type);
	void ClearSelectedKey();
	EditKeyData* GetSelectedKey();
	bool IsInsideRect(const ImVec2& rectMin,const ImVec2& rectMax,const ImVec2& pos);

	std::unordered_map<int, std::vector<EditKeyData>> editKeyData_;
	const float circleSize_{ 5.0f };
	// 1フレーム幅
	float timeFillScale_ = 2.5f;
	float timeFillOffset_ = 0.0f;
	//タイムライン最大時間
	float eventTime_{ 5.0f };
	//ImGui描画領域
	ImVec2 canvasPos;
	ImVec2 canvasSize;
	std::vector<ImVec2> truckFillSize_;
	ImVec2 fillSize;
	ImVec2 fillSize2;
	ImVec2 mousePos;
	GSvector2 mouseClickPos_{ 0.0f,0.0f };
	GSvector2 mousePosInCanvas_{ 0.0f,0.0f };
	//選択中キー
	EditKeyData* selectedKey_{ nullptr };
	std::string selectedEventName_{""};
	TimeLine& timeLine_;
	IWorld* world_{ nullptr };
};

#endif