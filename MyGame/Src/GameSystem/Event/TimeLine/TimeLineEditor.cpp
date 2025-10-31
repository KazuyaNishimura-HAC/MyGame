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
    //�}�E�X�ʒu���擾
    mousePos = ImGui::GetIO().MousePos;
    //TimeLineEditor��Canvas�����W
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
    //�Q�ƌ���TimeLine��delete
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
    //�I�𒆂̃L�[���N���A���Ă��琶���L�[��I��
    ClearSelectedKey();
    timeLine_.AddKey(selectedEventName_, keyData.frame,keyData.data);
}

void TimeLineEditor::DeleteKey()
{
    if (!selectedKey_) return;
    int frame = selectedKey_->frame;
    IKeyData::KeyType type = selectedKey_->data->type;
    //�I���L�[����
    selectedKey_ = nullptr;
    //editKeyData���̑I���L�[�폜
    for (int index = 0; index < IKeyData::TypeCount; ++index) {
        auto eventIndex = editKeyData_.find(index);
        //���݂��Ȃ���΃X�L�b�v
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
    //���S�ɍ폜
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
    
    //�L�[�I��������ĂȂ��Ȃ�return;
    if (!selectedKey_) return;
    int displayFrame = selectedKey_->pos.x / timeFillScale_;
    ImGui::Value("Frame", displayFrame);
    switch (selectedKey_->data->type) {
        case IKeyData::Camera:
        {
            //data��CameraKey�ň���
            CameraKey* camKey = SAs<CameraKey>(selectedKey_->data);
            ImGui::Checkbox("TargetActor", &camKey->isTargetActor);
            ImGui::InputFloat3("Position", camKey->view.pos);
            ImGui::InputFloat3("Target", camKey->view.tar);
            ImGui::InputFloat("Fov", &camKey->view.fov);
            ImGui::Checkbox("Smooth", &camKey->view.isSmooth);
            if (camKey->isTargetActor) {
                //�v���C���[�̏���n��
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
            //data��EffectKey�^�ň���
            EffectKey* effKey = SAs<EffectKey>(selectedKey_->data);
            ImGui::Checkbox("TargetActor", &effKey->isTargetActor);
            ImGui::Value("Affected", effKey->effect.affected);
            break;
        }
        default: break;
    }
}

//�L�[�ҏW
void TimeLineEditor::KeyEdit()
{
    
    bool isMouseInside = IsInsideRect(canvasPos, fillSize, mousePos);
    //�ҏW�\�ȏꏊ���N���b�N��
    if (gsGetMouseButtonTrigger(GMOUSE_BUTTON_1) && isMouseInside) {
        for (int index = 0; index < IKeyData::TypeCount; ++index) {
            //�L�[�I��������
            ClearSelectedKey();
            //map�v�f���Ȃ��Ȃ�����Ԃ�
            if (editKeyData_.find(index) == editKeyData_.end()) continue;
            for (auto& key : editKeyData_[index]) {
                float dist = gsVector2Distance(&key.pos, &mousePosInCanvas_);
                //�N���b�N�n�_�ɃL�[�����݂�����L�[�擾
                if (dist < circleSize_) {
                    selectedKey_ = &key;
                    selectedKey_->selected = true;
                    break;
                }
            }
            //�L�[�I�����o������break
            if (selectedKey_) break;
        }
        mouseClickPos_ = ImVecToGSVec(mousePos);
    }
    //�I�𒆂̃L�[�̉����ړ�
    if (gsGetMouseButtonState(GMOUSE_BUTTON_1) &&  selectedKey_ && isMouseInside) {
        selectedKey_->pos = { mousePosInCanvas_.x,selectedKey_->pos.y };
        //�ő�t���[����łȂ��悤�ɃN�����v
        selectedKey_->pos.x = CLAMP(selectedKey_->pos.x,0,eventTime_ * 60.0f * timeFillScale_);
    }
    //�L�[�I������
    if (gsGetMouseButtonDetach(GMOUSE_BUTTON_1) && selectedKey_) {
        //�L�[�̍X�V
        UpdateKeyFrame(selectedKey_);
    }

    //�L�[�ǉ�
    if (gsGetMouseButtonTrigger(GMOUSE_BUTTON_2)) {
        ClearSelectedKey();
        AddKey();
    }
    //if (ImGui::Button("Delete Key")) {
    //    ImGui::OpenPopup("ConfirmDelete"); // ���[�_�����J��
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
    //�w��̃C�x���g�����s
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
    //�L�[��ޒǉ�(�󔠂����)
    for (int keyType = 0; keyType < IKeyData::TypeCount; ++keyType) {
        editKeyData_[keyType];
    }
    //TimeLine�S�ẴL�[���擾
    TimeLineData* timeLineData = timeLine_.KeyDatas(selectedEventName_);
    //�t���[�����Ƃɑ��݃C�x���g�̒ǉ�
    for (auto data : timeLineData->frameEvent) {
        //��̃t���[���ɑ��݂���Key���擾
        for (auto key : data.second) {
            //�L�[���Ƃ̏����i�[
            EditKeyData keyData;
            keyData.frame = data.first;
            keyData.pos = { timeFillScale_ * keyData.frame , ((int)key->type * 60) + 30.0f };
            keyData.data = key;
            editKeyData_[key->type].push_back(keyData);
        }
    }
    //�ǉ����̃C�x���g�z����폜
    for (int keyType = 0; keyType < IKeyData::TypeCount; ++keyType) {
        if (editKeyData_[keyType].empty()) editKeyData_.erase(keyType);
    }
    if (ImGui::IsItemActive()) {
        // �i������ăh���b�O���Ȃǁj�̂Ƃ�
    }

    if (ImGui::IsItemHovered()) {
        // ���O�� "Key" �{�^���Ƀ}�E�X������Ă���
    }

    //�l�擾�i�J�����L�[�̂݁j
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
        //IKey�������
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
    // �t�@�C����JSON�f�[�^����������
    std::ofstream of("Src/TimeLineData/test.json");
    of << saveFile.dump(4);
    of.close();
    //�X�V��f�[�^�ǂݍ���
    timeLine_.LoadFile();
    //Edit�p�z����X�V
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
    // �w�i
    drawList->AddRectFilled(canvasPos, fillSize, IM_COL32(50, 50, 50, 255));

    drawList->AddRectFilled(canvasPos, fillSize2, IM_COL32(70, 70, 70, 100));

    //�J�[�\���ʒu�Ɂ��`��
    if (IsInsideRect(canvasPos, fillSize, mousePos))drawList->AddCircleFilled(mousePos, 5, IM_COL32(0, 100, 180, 90), 12);

    drawList->AddCircleFilled({mouseClickPos_.x,mouseClickPos_.y}, 5, IM_COL32(0, 100, 180, 90), 12);

    //�����jkeyPos����timelineScale�������ƃt���[�����������邼��(keyPos.x / timelineScale = frame)
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
    
    // ���Ԏ�
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
    //Preview�p���C���`��
    if (timeLine_.IsRunning()) {
        float x = canvasPos.x + (timeLine_.EventTimer() * 60.0f * timeFillScale_) - timeFillOffset_;
        drawList->AddLine(ImVec2(x, canvasPos.y), ImVec2(x, canvasPos.y + canvasSize.y), IM_COL32(200, 200, 200, 255));
    }
    //�L�[����p�̓����w�i(�^�C�����C����̓E�B���h�E���얳��)
    ImVec2 invisibleFill = { fillSize.x - canvasPos.x,fillSize.y - canvasPos.y };
    ImGui::InvisibleButton("my_rect_block", invisibleFill);
    // �e�L�X�g����`�̉��ɔz�u
    ImGui::SetCursorScreenPos(ImVec2(canvasPos.x, fillSize.y + 5));
    
}
void TimeLineEditor::UpdateKeyFrame(EditKeyData* key)
{
    int oldFrame = selectedKey_->frame;
    int newFrame = selectedKey_->pos.x / timeFillScale_;
    if (oldFrame == newFrame) return;
    //�L�[�X�V
    selectedKey_->frame = newFrame;

    timeLine_.MoveKey(selectedEventName_, oldFrame,newFrame, selectedKey_->data);
}
//ImVec��GSVec�^�ɕϊ�
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
        //map�v�f���Ȃ��Ȃ�����Ԃ�
        if (editKeyData_.find(index) == editKeyData_.end()) continue;
        for (auto& key : editKeyData_[index]) {
            //�I�𒆂̃L�[��ԋp
            if (key.selected) return &key;
        }
    }
    return nullptr;
}
//UI�͈́i�l�p�`�j����position�����݂��邩�H
bool TimeLineEditor::IsInsideRect(const ImVec2& rectMin, const ImVec2& rectMax, const ImVec2& pos)
{
    return (pos.x >= rectMin.x && pos.x <= rectMax.x &&
        pos.y >= rectMin.y && pos.y <= rectMax.y);
}