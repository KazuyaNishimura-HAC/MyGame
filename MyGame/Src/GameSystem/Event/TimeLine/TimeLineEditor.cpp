#include "TimeLineEditor.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <imgui/imgui.h>
#include "../../InputSystem/InputSystem.h"
#include "../../../World/IWorld.h"
#include "../../../Actor/Actor.h"
#include "../../../NameTag.h"
TimeLineEditor::TimeLineEditor(IWorld* world,TimeLine& timeLine):
    world_{ world },timeLine_ { timeLine }
{
}

TimeLineEditor::~TimeLineEditor()
{
    Clear();
}

void TimeLineEditor::Update(float deltaTime)
{
}

void TimeLineEditor::DrawEditUI()
{
    ImGui::Begin("TimeLineTest");
    //マウス位置を取得
    mousePos = ImGui::GetIO().MousePos;
    //TimeLineEditorのCanvas内座標
    mousePosInCanvas_ = GSvector2{ mousePos.x - canvasPos.x, mousePos.y - canvasPos.y };
    if (ImGui::Button("LoadData")) LoadKeyData();
    PreView();
    DrawUI();
    Edit();
    if (ImGui::Button("SaveFile")) Save();
    ImGui::End();
}

void TimeLineEditor::Clear()
{
    ClearSelectedKey();
    //参照元はTimeLineでdelete
    editKeyData_.clear();
}

void TimeLineEditor::AddTimeLine()
{
}

void TimeLineEditor::AddKey()
{
    ImVec2 clickPos = { mouseClickPos_ .x,mouseClickPos_ .y};
    ImVec2 clickPosInCanvas_ = { clickPos.x - canvasPos.x, clickPos.y - canvasPos.y };
    EditKeyData keyData;
    if (IsInsideRect(canvasPos, fillSize2, clickPos)) {
        keyData.frame = clickPosInCanvas_.x / timeFillScale_;
        keyData.pos = { clickPosInCanvas_.x ,30};
        keyData.data = new CameraKey();
        keyData.selected = false;
        editKeyData_[IKeyData::Camera].push_back(keyData);
    }
    //選択中のキーをクリアしてから生成キーを選択
    ClearSelectedKey();
    timeLine_.AddKey(selectedEventName_, keyData.frame,keyData.data);
}

void TimeLineEditor::DeleteKey()
{
    if (!selectedKey_) return;
    int frame = selectedKey_->frame;
    IKeyData::KeyType type = selectedKey_->data->type;
    //選択キー解除
    selectedKey_ = nullptr;
    //editKeyData内の選択キー削除
    for (int index = 0; index < IKeyData::TypeCount; ++index) {
        auto eventIndex = editKeyData_.find(index);
        //存在しなければスキップ
        if (eventIndex == editKeyData_.end()) continue;
        auto& keyDatas = eventIndex->second;
        for (auto key = keyDatas.begin(); key != keyDatas.end(); ) {
            if (key->selected) {
                key->data = nullptr;
                key = keyDatas.erase(key);
            }
            else {
                ++key;
            }
        }
    }
    //完全に削除
    timeLine_.DeleteKey(selectedEventName_, frame, type);
}

void TimeLineEditor::Edit()
{
    KeyEdit();
    if (ImGui::Button("DeleteKey")) DeleteKey();
    eventTime_ = timeLine_.EventTime(selectedEventName_);
    int keyCount = 0;
    for (size_t index = 0; index < editKeyData_.size(); ++index) {
        keyCount += KeyCount(index);
    }
    
    ImGui::Value("KeyCount", keyCount);
    ImGui::InputFloat("EventTime", &eventTime_);
    timeLine_.SetEventTime(selectedEventName_, eventTime_);
    
    //キー選択がされてないならreturn;
    if (!selectedKey_) return;
    int displayFrame = selectedKey_->pos.x / timeFillScale_;
    ImGui::Value("Frame", displayFrame);
    switch (selectedKey_->data->type) {
        case IKeyData::Camera:
        {
            //dataをCameraKeyで扱う
            CameraKey* camKey = SAs<CameraKey>(selectedKey_->data);
            ImGui::Checkbox("TargetActor", &camKey->isTargetActor);
            ImGui::InputFloat3("Position", camKey->view.pos);
            ImGui::InputFloat3("Target", camKey->view.tar);
            ImGui::InputFloat("Fov", &camKey->view.fov);
            ImGui::Checkbox("Smooth", &camKey->view.isSmooth);
            if (camKey->isTargetActor) {
                //プレイヤーの情報を渡す
                camKey->targetActor = world_->GetAllActor(ActorName::Player);
                std::string targetName;
                if (camKey->targetActor) targetName = camKey->targetActor->GetName();
                else targetName = "NotFound";
                ImGui::Text(targetName.c_str());
            }
            else {
                camKey->targetActor = nullptr;
            }
            break;
        }
        case IKeyData::Effect:
        {
            //dataをEffectKey型で扱う
            EffectKey* effKey = SAs<EffectKey>(selectedKey_->data);
            ImGui::Checkbox("TargetActor", &effKey->isTargetActor);
            ImGui::Value("Affected", effKey->effect.affected);
            break;
        }
        default: break;
    }
}

//キー編集
void TimeLineEditor::KeyEdit()
{
    
    bool isMouseInside = IsInsideRect(canvasPos, fillSize, mousePos);
    //編集可能な場所かつクリック時
    if (gsGetMouseButtonTrigger(GMOUSE_BUTTON_1) && isMouseInside) {
        for (int index = 0; index < IKeyData::TypeCount; ++index) {
            //キー選択を解除
            ClearSelectedKey();
            //map要素がないなら引き返し
            if (editKeyData_.find(index) == editKeyData_.end()) continue;
            for (auto& key : editKeyData_[index]) {
                float dist = gsVector2Distance(&key.pos, &mousePosInCanvas_);
                //クリック地点にキーが存在したらキー取得
                if (dist < circleSize_) {
                    selectedKey_ = &key;
                    selectedKey_->selected = true;
                    break;
                }
            }
            //キー選択が出来たらbreak
            if (selectedKey_) break;
        }
        mouseClickPos_ = ImVecToGSVec(mousePos);
    }
    //選択中のキーの横軸移動
    if (gsGetMouseButtonState(GMOUSE_BUTTON_1) &&  selectedKey_ && isMouseInside) {
        selectedKey_->pos = { mousePosInCanvas_.x,selectedKey_->pos.y };
        //最大フレーム空でないようにクランプ
        selectedKey_->pos.x = CLAMP(selectedKey_->pos.x,0,eventTime_ * 60.0f * timeFillScale_);
    }
    //キー選択解除
    if (gsGetMouseButtonDetach(GMOUSE_BUTTON_1) && selectedKey_) {
        //キーの更新
        UpdateKeyFrame(selectedKey_);
    }

    //キー追加
    if (gsGetMouseButtonTrigger(GMOUSE_BUTTON_2)) {
        ClearSelectedKey();
        AddKey();
    }
    //if (ImGui::Button("Delete Key")) {
    //    ImGui::OpenPopup("ConfirmDelete"); // モーダルを開く
    //}

    //if (ImGui::BeginPopupModal("ConfirmDelete")) {
    //    ImGui::Text("Reary?");
    //    if (ImGui::Button("Yes")) ImGui::CloseCurrentPopup();
    //    if (ImGui::Button("No"))  ImGui::CloseCurrentPopup();
    //    ImGui::EndPopup();
    //}
}

void TimeLineEditor::PreView()
{
    //指定のイベントを実行
    if (ImGui::Button("PreView")) {
        timeLine_.StartTimeLine(selectedEventName_);
    }
    ImGui::SameLine();
    std::string text = "Name:" + selectedEventName_;
    ImGui::Text(text.c_str());
}

void TimeLineEditor::LoadKeyData(std::string name)
{
    if (name == "")selectedEventName_ = "TEST1";

    ClearSelectedKey();
    editKeyData_.clear();
    //キー種類追加(空箱を作る)
    for (int keyType = 0; keyType < IKeyData::TypeCount; ++keyType) {
        editKeyData_[keyType];
    }
    //TimeLine全てのキーを取得
    TimeLineData* timeLineData = timeLine_.KeyDatas(selectedEventName_);
    //フレームごとに存在イベントの追加
    for (auto data : timeLineData->frameEvent) {
        //一つのフレームに存在するKeyを取得
        for (auto key : data.second) {
            //キーごとの情報を格納
            EditKeyData keyData;
            keyData.frame = data.first;
            keyData.pos = { timeFillScale_ * keyData.frame , ((int)key->type * 60) + 30.0f };
            keyData.data = key;
            editKeyData_[key->type].push_back(keyData);
        }
    }
    //追加後空のイベント配列を削除
    for (int keyType = 0; keyType < IKeyData::TypeCount; ++keyType) {
        if (editKeyData_[keyType].empty()) editKeyData_.erase(keyType);
    }
    if (ImGui::IsItemActive()) {
        // （押されてドラッグ中など）のとき
    }

    if (ImGui::IsItemHovered()) {
        // 直前の "Key" ボタンにマウスが乗っている
    }

    //値取得（カメラキーのみ）
    /*for (const auto& key : editKeyData_[IKeyData::Camera]) {
        CameraKey* camKey = SAs<CameraKey>(key.data);
        View a = camKey->view;
    }*/
    
}

void TimeLineEditor::Save()
{
    nlohmann::ordered_json saveFile{};
    std::string eventName = selectedEventName_;
    int frameKeyCount = timeLine_.FrameKeyCount(selectedEventName_);
    TimeLineData* data = timeLine_.KeyDatas(eventName);
    saveFile["EventName"] = eventName;
    saveFile["KeyCount"] = frameKeyCount;
    saveFile["EventTime"] = data->playTime;
    int frameCount = 0;
    for (const auto& frameData : data->frameEvent) {
        std::string keyNum = "key" + std::to_string(frameCount);
        int frame = frameData.first;
        saveFile[keyNum]["frame"] = frame;
        //IKey情報を入力
        for (const auto& key : frameData.second) {
            if (auto cam = DAs<CameraKey>(key)) {
                std::string targetType = cam->isTargetActor ? "Actor" : "World";
                saveFile[keyNum]["Camera"]["targetType"] = targetType;
                if (cam->targetActor) {
                    saveFile[keyNum]["Camera"]["targetName"] = cam->targetActor->GetName();
                }
                saveFile[keyNum]["Camera"]["position"] = { cam->view.pos.x,cam->view.pos.y,cam->view.pos.z };
                saveFile[keyNum]["Camera"]["target"] = { cam->view.tar.x,cam->view.tar.y,cam->view.tar.z };
                saveFile[keyNum]["Camera"]["fov"] = cam->view.fov;
                saveFile[keyNum]["Camera"]["smooth"] = cam->view.isSmooth; 
            }
            if (auto eff = DAs<EffectKey>(key)) {
                saveFile[keyNum]["Effect"]["affected"] = eff->effect.affected;
            }
        }
        frameCount++;
    }
    // ファイルにJSONデータを書き込む
    std::ofstream of("Src/TimeLineData/test.json");
    of << saveFile.dump(4);
    of.close();
    //更新後データ読み込み
    timeLine_.LoadFile();
    //Edit用配列を更新
    LoadKeyData();
}

void TimeLineEditor::DrawUI()
{
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    canvasPos = ImGui::GetCursorScreenPos();
    canvasSize = ImVec2(ImGui::GetContentRegionAvail().x, 200);
    if (eventTime_ <= 0.0f) return;
    fillSize = ImVec2(canvasPos.x + (60.0f * eventTime_ * timeFillScale_), canvasPos.y + canvasSize.y);
    fillSize2 = ImVec2(canvasPos.x + (60.0f * eventTime_ * timeFillScale_), canvasPos.y + 60);
    // 背景
    drawList->AddRectFilled(canvasPos, fillSize, IM_COL32(50, 50, 50, 255));

    drawList->AddRectFilled(canvasPos, fillSize2, IM_COL32(70, 70, 70, 100));

    //カーソル位置に◯描画
    if (IsInsideRect(canvasPos, fillSize, mousePos))drawList->AddCircleFilled(mousePos, 5, IM_COL32(0, 100, 180, 90), 12);

    drawList->AddCircleFilled({mouseClickPos_.x,mouseClickPos_.y}, 5, IM_COL32(0, 100, 180, 90), 12);

    //メモ）keyPosからtimelineScaleを引くとフレーム数が書けるぞい(keyPos.x / timelineScale = frame)
    for (int index = 0; index < IKeyData::TypeCount;++index) {
        for (const auto& key : editKeyData_[index]) {
            ImVec2 keyPos = {canvasPos.x + key.pos.x,canvasPos.y + key.pos.y};

            if (key.selected) {
                drawList->AddCircleFilled(keyPos, circleSize_, IM_COL32(255, 0, 0, 255), 12);
                continue;
            }
            drawList->AddCircleFilled(keyPos, circleSize_, IM_COL32(255, 255, 0, 255), 12);
        }
    }
    
    // 時間軸
    for (int t = 0; t <= 60 * eventTime_; t++) {
        float x = 0;
        if (t % 10 == 0) {
            x = canvasPos.x + t * timeFillScale_ - timeFillOffset_;
            float lineAlpha;
            lineAlpha = t % 60 ? 40 : 100;
            drawList->AddLine(ImVec2(x, canvasPos.y), ImVec2(x, canvasPos.y + canvasSize.y), IM_COL32(200, 200, 200, lineAlpha));
        }
        if (t % 60 == 0) {
            drawList->AddText(ImVec2(x + 2, canvasPos.y), IM_COL32_WHITE, std::to_string(t).c_str());
        }
    }
    //Preview用ライン描画
    if (timeLine_.IsRunning()) {
        float x = canvasPos.x + (timeLine_.EventTimer() * 60.0f * timeFillScale_) - timeFillOffset_;
        drawList->AddLine(ImVec2(x, canvasPos.y), ImVec2(x, canvasPos.y + canvasSize.y), IM_COL32(200, 200, 200, 255));
    }
    //キー操作用の透明背景(タイムライン上はウィンドウ操作無効)
    ImVec2 invisibleFill = { fillSize.x - canvasPos.x,fillSize.y - canvasPos.y };
    ImGui::InvisibleButton("my_rect_block", invisibleFill);
    // テキストを矩形の下に配置
    ImGui::SetCursorScreenPos(ImVec2(canvasPos.x, fillSize.y + 5));
    
}
void TimeLineEditor::UpdateKeyFrame(EditKeyData* key)
{
    int oldFrame = selectedKey_->frame;
    int newFrame = selectedKey_->pos.x / timeFillScale_;
    if (oldFrame == newFrame) return;
    //キー更新
    selectedKey_->frame = newFrame;

    timeLine_.MoveKey(selectedEventName_, oldFrame,newFrame, selectedKey_->data);
}
//ImVecをGSVec型に変換
GSvector2 TimeLineEditor::ImVecToGSVec(ImVec2 vec)
{
    return GSvector2(vec.x,vec.y);
}
ImVec2 TimeLineEditor::GSVecToImVec(GSvector2 vec)
{
    return ImVec2(vec.x,vec.y);
}
int TimeLineEditor::KeyCount(int type)
{
    return editKeyData_[type].size();
}
void TimeLineEditor::ClearSelectedKey()
{
    if (!selectedKey_) return;
    selectedKey_->selected = false;
    selectedKey_ = nullptr;
}
TimeLineEditor::EditKeyData* TimeLineEditor::GetSelectedKey()
{
    for (int index = 0; index < IKeyData::TypeCount; ++index) {
        //map要素がないなら引き返し
        if (editKeyData_.find(index) == editKeyData_.end()) continue;
        for (auto& key : editKeyData_[index]) {
            //選択中のキーを返却
            if (key.selected) return &key;
        }
    }
    return nullptr;
}
//UI範囲（四角形）内にpositionが存在するか？
bool TimeLineEditor::IsInsideRect(const ImVec2& rectMin, const ImVec2& rectMax, const ImVec2& pos)
{
    return (pos.x >= rectMin.x && pos.x <= rectMax.x &&
        pos.y >= rectMin.y && pos.y <= rectMax.y);
}