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
    //TimeLineEditorのCanvas内座標取得
    mousePosInCanvas_ = GSvector2{ mousePos.x - canvasPos.x, mousePos.y - canvasPos.y };
    if (ImGui::Button("LoadData")) LoadKeyData();
    PreView();
    DrawUI();
    Edit();
    if (ImGui::Button("SaveFile")) {
        openSaveWindow_ = true;
        //開いているイベント名を初期値に設定
        strcpy_s(saveEventName, selectedEventName_.c_str());
        ImGui::OpenPopup("SaveFileDialog");
    }
    SaveFileDialog();
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
    //キー選択中ならreturn
    if (selectedKey_) return;
    ImVec2 clickPosInFill = { mouseClickPos_.x - fillStartPos.x, mouseClickPos_.y - fillStartPos.y };
    EditKeyData keyData;
    keyData.frame = clickPosInFill.x / timeFillScale_;
    keyData.pos = { clickPosInFill.x ,(selectedTruck_ * 60.0f) + 30.0f};
    keyData.selected = true;
    int keyType = rowIndex_[selectedTruck_];
    switch (keyType) {
        case IKeyData::Camera:
            keyData.data = new CameraKey();
            break;
        case IKeyData::Effect:
            keyData.data = new EffectKey();
            break;
        case IKeyData::Shake:
            keyData.data = new CameraShakeKey();
            break;
        //万が一登録していないキーが入ったらreturn;
        default : return;
    }
    
    editKeyData_[keyType].push_back(keyData);
    //念のため保持しているキーを解除
    ClearSelectedKey();
    //selectedがtrueのキーをselectedKey_に割り当て
    selectedKey_ = GetSelectedKey();
    //ゲーム内に反映させる
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

void TimeLineEditor::AddTruck()
{
    if (IsRowPresent(truckListNum_)) return;
    rowIndex_.push_back(truckListNum_);
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
            ImGui::Checkbox("IsSmooth", &camKey->view.isSmooth);
            if (camKey->view.isSmooth) {
                ImGui::SameLine();
                ImGui::InputFloat("Time", &camKey->view.smoothTime);
            }
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
        case IKeyData::Shake:
        {
            CameraShakeKey* shakeKey = SAs<CameraShakeKey>(selectedKey_->data);
            ImGui::InputFloat("Timer", &shakeKey->shake.timer);
            ImGui::InputFloat("strength", &shakeKey->shake.strength);
            ImGui::InputFloat("decayTime", &shakeKey->shake.decayTime);
            ImGui::InputFloat("decaySpeed", &shakeKey->shake.decaySpeed);
            ImGui::InputFloat("HZ", &shakeKey->shake.hz);
            ImGui::InputFloat2("AffectVector", shakeKey->shake.affectVector);
            ImGui::InputFloat("AffectFov", &shakeKey->shake.affectFov);
            break;
        }
        default: break;
    }
}

//キー編集
void TimeLineEditor::KeyEdit()
{
    
    bool isMouseInside = IsInsideRect(fillStartPos, maxFillPos, mousePos);
    //編集可能な場所かつクリック時
    if (gsGetMouseButtonTrigger(GMOUSE_BUTTON_1) && isMouseInside) {
        for (int index = 0; index < IKeyData::TypeCount; ++index) {
            //キー選択を解除
            ClearSelectedKey();
            //map要素がないなら引き返し
            if (editKeyData_.find(index) == editKeyData_.end()) continue;
            for (auto& key : editKeyData_[index]) {
                GSvector2 canvasKeyPos = key.pos + ImVecToGSVec(fillOffset);
                float dist = gsVector2Distance(&canvasKeyPos, &mousePosInCanvas_);
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
        //Offset分減算した座標を反映実際のフレーム座標に割り当て
        selectedKey_->pos.x = mousePosInCanvas_.x - ImVecToGSVec(fillOffset).x;
        //最大フレーム空でないようにクランプ
        selectedKey_->pos.x = CLAMP(selectedKey_->pos.x,0,eventTime_ * 60.0f * timeFillScale_);
    }
    //キー選択解除
    if (gsGetMouseButtonDetach(GMOUSE_BUTTON_1) && selectedKey_) {
        //キーの更新
        UpdateKeyFrame(selectedKey_);
    }

    //キー追加
    if (gsGetMouseButtonTrigger(GMOUSE_BUTTON_2) && IsInsideRect(fillStartPos, maxFillPos, GSVecToImVec(mouseClickPos_))) {
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
    //イベントが存在しないならリターン
    if (!timeLine_.KeyDatas(selectedEventName_)) return;
    //各要素をクリア
    ClearSelectedKey();
    editKeyData_.clear();
    rowIndex_.clear();
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
            //トラックごとのキー情報を格納
            editKeyData_[key->type].push_back(keyData);
        }
    }
    //追加後空のイベント配列を削除
    for (int keyType = 0; keyType < IKeyData::TypeCount; ++keyType) {
        if (editKeyData_[keyType].empty()) {
            editKeyData_.erase(keyType);
            continue;
        }
        rowIndex_.push_back(keyType);
    }

    //編集キーのy座標だけ上に積める
    for (size_t i = 0; i < rowIndex_.size(); ++i) {
        int keyType = rowIndex_[i];
        for (auto& key : editKeyData_[keyType]) {
            key.pos.y = (i * 60) + 30.0f;
        }
    }
    
}

void TimeLineEditor::Save()
{
    nlohmann::ordered_json saveFile{};
    std::string eventName = selectedEventName_;
    
    int frameKeyCount = timeLine_.FrameKeyCount(eventName);
    TimeLineData* data = timeLine_.KeyDatas(eventName);
    std::string saveName = saveEventName;
    if (!data) return;
    saveFile["EventName"] = saveName;
    saveFile["KeyCount"] = frameKeyCount;
    saveFile["EventTime"] = data->playTime;
    int frameCount = 0;
    for (const auto& frameData : data->frameEvent) {
        std::string keyNum = "key" + std::to_string(frameCount);
        int frame = frameData.first;
        saveFile[keyNum]["frame"] = frame;
        //IKey情報を入力
        for (int type = 0; type < IKeyData::TypeCount;++type) {
            for (const auto& key : frameData.second) {
                //順番通りのキータイプじゃないなら見つかるまでcontinue
                if (key->type != type) continue;
                if (auto cam = DAs<CameraKey>(key)) {
                    std::string targetType = cam->isTargetActor ? "Actor" : "World";
                    saveFile[keyNum]["Camera"]["targetType"] = targetType;
                    if (cam->targetActor) {
                        saveFile[keyNum]["Camera"]["targetName"] = cam->targetActor->GetName();
                    }
                    saveFile[keyNum]["Camera"]["position"] = { cam->view.pos.x,cam->view.pos.y,cam->view.pos.z };
                    saveFile[keyNum]["Camera"]["target"] = { cam->view.tar.x,cam->view.tar.y,cam->view.tar.z };
                    saveFile[keyNum]["Camera"]["fov"] = cam->view.fov;
                    saveFile[keyNum]["Camera"]["IsSmooth"] = cam->view.isSmooth;
                    if(cam->view.isSmooth) saveFile[keyNum]["Camera"]["smoothTime"] = cam->view.smoothTime;
                }
                if (auto eff = DAs<EffectKey>(key)) {
                    saveFile[keyNum]["Effect"]["affected"] = eff->effect.affected;
                }
                if (auto shake = DAs<CameraShakeKey>(key)) {
                    saveFile[keyNum]["CameraShake"]["timer"] = shake->shake.timer;
                    saveFile[keyNum]["CameraShake"]["strength"] = shake->shake.strength;
                    saveFile[keyNum]["CameraShake"]["decayTime"] = shake->shake.decayTime;
                    saveFile[keyNum]["CameraShake"]["decaySpeed"] = shake->shake.decaySpeed;
                    saveFile[keyNum]["CameraShake"]["hz"] = shake->shake.hz;
                    //小数第三位まで四捨五入で整理
                    saveFile[keyNum]["CameraShake"]["affectVector"] = { shake->shake.affectVector.x,shake->shake.affectVector.y };
                    saveFile[keyNum]["CameraShake"]["affectFov"] = shake->shake.affectFov;

                }
            }
        }
        
        frameCount++;
    }
    //今保存したファイルを選択
    selectedEventName_ = saveName;
    // ファイルにJSONデータを書き込む
    std::ofstream of("Src/TimeLineData/" + saveName + ".json");
    of << saveFile.dump(4);
    of.close();
    //更新後データ読み込み
    timeLine_.LoadFile();
    //Edit用配列を更新
    LoadKeyData();
}

void TimeLineEditor::SaveFileDialog()
{
    if (!openSaveWindow_) return;
    
    if (ImGui::BeginPopupModal("SaveFileDialog", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("FileName");

        ImGui::InputText("##filename", saveEventName, IM_ARRAYSIZE(saveEventName));

        ImGui::Spacing();

        if (ImGui::Button("Save", ImVec2(120, 0))) {
            Save();
            ImGui::CloseCurrentPopup();
            openSaveWindow_ = false;
        }

        ImGui::SameLine();

        if (ImGui::Button("Cancel", ImVec2(120, 0))) {
            ImGui::CloseCurrentPopup();
            openSaveWindow_ = false;
        }

        ImGui::EndPopup();
    }
}

void TimeLineEditor::SaveKey(const IKeyData& key)
{
    //ここにType別ごとに保存
}

void TimeLineEditor::DrawUI()
{
    ImGui::BeginChild(ImGui::GetID((void*)0), ImVec2(100, 40), ImGuiWindowFlags_NoTitleBar);
    for (int i = 0; i < std::size(truckArray_); ++i)
    {
        bool press = ImGui::Button(GetTruckName(i).c_str());
        if (!press)continue;
        truckListNum_ = i;
    }
    ImGui::EndChild();
    ImGui::SameLine();
    if (ImGui::Button(("AddTruck : " + GetTruckName(truckListNum_)).c_str())) {
        AddTruck();
    }
    if (eventTime_ <= 0.0f) return;
    ImDrawList* drawList = ImGui::GetWindowDrawList();
    canvasPos = ImGui::GetCursorScreenPos();
    fillStartPos = { canvasPos.x + fillOffset.x,canvasPos.y + fillOffset.y };
    canvasSize = ImVec2(ImGui::GetContentRegionAvail().x, 300);
    maxFillPos = ImVec2(fillStartPos.x + (60.0f * eventTime_ * timeFillScale_), fillStartPos.y + rowIndex_.size() * 60.0f);
    //トラックの数だけ塗りつぶし描画
    for (size_t i = 0; i < rowIndex_.size();++i) {
        GSvector2 truckStartPos = ImVecToGSVec(fillStartPos);
        truckStartPos.y += 60 * i;
        drawList->AddText(ImVec2(canvasPos.x, canvasPos.y + 20 + (i * 60)),
            IM_COL32(255, 255, 255, 255),
            GetTruckName(rowIndex_[i]).c_str());
        ImVec2 invisibleFill = { 60.0f * eventTime_ * timeFillScale_ + fillOffset.x ,60.0f };
        if (ImGui::InvisibleButton("truck"+ i, invisibleFill)) selectedTruck_ = i;

        ImVec2 truckEndPos = { maxFillPos.x,truckStartPos.y + 60.0f };
        
        //トラック描画
        if (selectedTruck_ == i) {
            drawList->AddRectFilled(GSVecToImVec(truckStartPos), truckEndPos, IM_COL32(50, 50, 50, 255));
        }
        else {
            drawList->AddRectFilled(GSVecToImVec(truckStartPos), truckEndPos, IM_COL32(50, 50, 50, 150));
        }
        //境界線描画
        ImVec2 truckLineStarts = { canvasPos.x , canvasPos.y + 60 * i };
        drawList->AddLine(truckLineStarts, ImVec2(maxFillPos.x, truckLineStarts.y), IM_COL32(200, 200, 200, 255));
    }
    //カーソル位置に◯描画
    if (IsInsideRect(fillStartPos, maxFillPos, mousePos))drawList->AddCircleFilled(mousePos, 5, IM_COL32(0, 100, 180, 90), 12);

    //クリック地点に◯描画
    if (IsInsideRect(fillStartPos, maxFillPos, GSVecToImVec(mouseClickPos_))) {
        drawList->AddCircleFilled({ mouseClickPos_.x,mouseClickPos_.y }, 5, IM_COL32(0, 100, 180, 90), 12);
    }

    //メモ）keyPosからtimelineScaleを引くとフレーム数が書けるぞい(keyPos.x / timelineScale = frame)
    for (int index = 0; index < IKeyData::TypeCount;++index) {
        for (const auto& key : editKeyData_[index]) {
            ImVec2 keyPos = { fillStartPos.x + key.pos.x,fillStartPos.y + key.pos.y};
            //選択キーは赤色に描画
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
            x = fillStartPos.x + t * timeFillScale_ - timeFillOffset_;
            float lineAlpha;
            //60フレーム感覚で線を濃くする
            lineAlpha = t % 60 ? 40 : 100;
            drawList->AddLine(ImVec2(x, fillStartPos.y), ImVec2(x, maxFillPos.y), IM_COL32(200, 200, 200, lineAlpha));
        }
        if (t % 60 == 0) {
            drawList->AddText(ImVec2(x + 2, fillStartPos.y), IM_COL32_WHITE, std::to_string(t).c_str());
        }
    }
    //Preview用ライン描画
    if (timeLine_.IsRunning()) {
        float x = fillStartPos.x + (timeLine_.EventTimer() * 60.0f * timeFillScale_) - timeFillOffset_;
        drawList->AddLine(ImVec2(x, fillStartPos.y), ImVec2(x, maxFillPos.y), IM_COL32(255, 0, 0, 255));
    }
    // テキストを矩形の下に配置
    ImGui::SetCursorScreenPos(ImVec2(canvasPos.x, maxFillPos.y + 5));
    
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

std::string TimeLineEditor::GetTruckName(int type)
{
    return truckArray_[type];
}

bool TimeLineEditor::IsRowPresent(int type)
{
    return std::find(rowIndex_.begin(), rowIndex_.end(), type) != rowIndex_.end();
}
