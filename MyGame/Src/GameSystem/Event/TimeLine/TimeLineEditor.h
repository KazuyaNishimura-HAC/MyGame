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
    std::string truckArray_[3]{
        "Camera",
        "Effect",
        "CameraShake"
    };
	void Clear();
	
	void AddTimeLine();
	void AddKey();
	void DeleteKey();
    void AddTruck();
	void Edit();
	void KeyEdit();
	void PreView();
	void LoadKeyData(std::string name = "");
	void Save();
    void SaveFileDialog();
    void SaveKey(const IKeyData& key);
	void DrawUI();
	void UpdateKeyFrame(EditKeyData* key);
	GSvector2 ImVecToGSVec(ImVec2 vec);
	ImVec2 GSVecToImVec(GSvector2 vec);
	int KeyCount(int type);
	void ClearSelectedKey();
	EditKeyData* GetSelectedKey();
	bool IsInsideRect(const ImVec2& rectMin,const ImVec2& rectMax,const ImVec2& pos);
    //番号に応じたトラック名を返却
    std::string GetTruckName(int type);
    //トラックリストに要素が入っているか
    bool IsRowPresent(int type);
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
    ImVec2 fillTruckSize;
    //タイムラインFillのオフセット
    ImVec2 fillOffset{ 100,0 };
    ImVec2 fillStartPos;
	ImVec2 maxFillPos;
	ImVec2 fillSize2;
    //画面全体基準のマウス座標
	ImVec2 mousePos;
    //canvas内の座標
    GSvector2 mousePosInCanvas_{ 0.0f,0.0f };
	GSvector2 mouseClickPos_{ 0.0f,0.0f };
    //トラックの挿入順
    std::vector<int> rowIndex_;
    int selectedTruck_{ -1 };
    //追加トラック用番号
    int truckListNum_{ 0 };
	//選択中キー
	EditKeyData* selectedKey_{ nullptr };
	std::string selectedEventName_{"TEST1"};
    bool openSaveWindow_{ false };
    char saveEventName[256] = "";
	TimeLine& timeLine_;
	IWorld* world_{ nullptr };
};

#endif
