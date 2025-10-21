#include "TimeLine.h"
#include <iostream>
#include <fstream>
#include <string>
//#include <filesystem>
#include "../../../Actor/Actor.h"
#include "../../../World/IWorld.h"

TimeLine::TimeLine()
{
}

TimeLine::~TimeLine()
{
}

void TimeLine::Update(float deltaTime)
{
    if (runningEvent_ == nullptr) return;
    //�^�C�}�[�X�V
    if (endTime_ <= eventTimer_) {
        EndTimeLine();
        return;
    }

    //�����_�؂�̂�
    int frame = std::trunc(eventTimer_ * 60.0f);
    //���݂̃t���[���ɃC�x���g�����݂��Ă�����
    auto ev = runningEvent_->frameEvent.find(frame);
    if (ev != runningEvent_->frameEvent.end()) {
        std::vector<IKeyData*>& keys = ev->second;
        for (auto key : keys) {
            if (key == nullptr) continue;
            switch (key->type) {
            case IKeyData::Camera: {
                CameraKey* camKey = static_cast<CameraKey*>(key);
                
                SetView(camKey);
            } break;

            case IKeyData::Effect: {
                EffectKey* effKey = static_cast<EffectKey*>(key);
                // effKey->effect �ȂǂɃA�N�Z�X
                SetEffect(effKey);
            } break;

            default:
                break;
            }
        }
    }
    //�^�C�}�[�X�V
    eventTimer_ += deltaTime / 60.0f;
}

void TimeLine::StartTimeLine(std::string name)
{
    if (data_.find(name) == data_.end() || runningEvent_) return;
    runningEvent_ = data_.at(name);
    endTime_ = runningEvent_->playTime;
    eventTimer_ = 0.0f;
    camera_->SetPriority(CameraController::Event,true);
}

void TimeLine::EndTimeLine()
{
    runningEvent_ = nullptr;
    camera_->SetPriority(CameraController::Disable);
}

void TimeLine::LoadFile()
{
    //Preview�������X�V
    runningEvent_ = nullptr;
    //�O�̂��߈��N���A����
    KeyDataClear();
    std::ifstream ifs("Src/TimeLineData/test.json");
    if (ifs.is_open() && ifs.good())
    {
        ifs >> loadFile_;
        //�C�x���g��
        std::string eventName = loadFile_.value("EventName", "NONE");
        //�t���[���L�[����
        data_[eventName] = new TimeLineData();
        data_[eventName]->playTime = loadFile_.value("EventTime", 0.0f);
        //�L�[�����擾
        int keyCount = loadFile_.value("KeyCount", 0);
        
        for (int keyNum = 0; keyNum < keyCount; ++keyNum) {
            //key�ԍ�(string�^)
            std::string CurrentKey = "key" + std::to_string(keyNum);
            //�t���[���擾
            int frame = loadFile_[CurrentKey].value("frame",0);
            //�w��L�[�����݂�����Load
            if (loadFile_[CurrentKey].contains("Camera")) LoadView(data_[eventName]->frameEvent[frame], CurrentKey);
            if (loadFile_[CurrentKey].contains("Effect")) LoadEffect(data_[eventName]->frameEvent[frame], CurrentKey);
        }
    }

    ifs.close();
}

int TimeLine::TimeLineCount() const
{
    return data_.size();
}

float TimeLine::EventTimer()
{
    return eventTimer_;
}

bool TimeLine::IsRunning()
{
    return runningEvent_;
}

int TimeLine::FrameKeyCount(std::string name) const
{
    if (data_.find(name) == data_.end()) return -1;
    return data_.at(name)->frameEvent.size();
}

float TimeLine::EventTime(std::string name) const
{
    if (data_.find(name) == data_.end()) return -1;
    return data_.at(name)->playTime;
}

void TimeLine::SetEventTime(std::string name,float time)
{
    if (data_.find(name) == data_.end()) return;
    data_.at(name)->playTime = time;
}

TimeLineData* TimeLine::KeyDatas(std::string name) const
{
    if (data_.find(name) == data_.end()) return nullptr;
    return data_.at(name);
}

void TimeLine::AddKey(std::string name, int frame, IKeyData* data)
{
    TimeLineData* datas = KeyDatas(name);
    if (!datas) return;
    //�V�����t���[���̐���
    datas->frameEvent[frame].push_back(data);
}

void TimeLine::DeleteKey(std::string name, int frame, IKeyData::KeyType type)
{
    TimeLineData* datas = KeyDatas(name);
    if (!datas) return;

    // �t���[�������݂��Ȃ���Ή������Ȃ�
    auto it = datas->frameEvent.find(frame);
    if (it == datas->frameEvent.end()) return;
    auto& frameKeys = it->second;
    //�L�[���폜
    for (auto key = frameKeys.begin(); key != frameKeys.end(); ) {
        if ((*key)->type == type) {
            delete* key;
            key = frameKeys.erase(key);
        }
        else {
            ++key;
        }
    }
    //�t���[���ɃC�x���g���Ȃ��Ȃ�폜
    if (frameKeys.empty()) {
        datas->frameEvent.erase(frame);
    }
}

void TimeLine::MoveKey(std::string name, int oldFrame, int newFrame, IKeyData* data)
{
    TimeLineData* datas = KeyDatas(name);
    if (!datas) return;
    //�V�����t���[���L�[�̐���
    datas->frameEvent[newFrame].push_back(data);

    // �t���[�������݂��Ȃ���Ή������Ȃ�
    auto it = datas->frameEvent.find(oldFrame);
    if (it == datas->frameEvent.end()) return;
    auto& frameKeys = it->second;
    //�L�[���폜
    for (auto key = frameKeys.begin(); key != frameKeys.end(); ) {
        if ((*key)->type == data->type) {
            key = frameKeys.erase(key);
        }
        else {
            ++key;
        }
    }
    //�t���[���ɃC�x���g���Ȃ��Ȃ�폜
    if (frameKeys.empty()) {
        datas->frameEvent.erase(oldFrame);
    }
}

void TimeLine::SetIWorld(IWorld* world)
{
    if (world_ || camera_) return;
    world_ = world;
    camera_ = new CameraController(CameraController::Disable);
    world_->AddCameraController(camera_);
}

void TimeLine::KeyDataClear()
{
    runningEvent_ = nullptr;
    for (auto& pair : data_) {
        // --- �e�t���[�����Ƃ̃C�x���g���폜 ---
        for (auto& framePair : pair.second->frameEvent) {
            auto& keyEvents = framePair.second;
            for (auto* keyData : keyEvents) {
                delete keyData; // IKeyData�����
            }
            keyEvents.clear();
        }
        //IKeyData�z��
        pair.second->frameEvent.clear();
        //TimeLineData�z��폜
        delete pair.second;
    }
    data_.clear();
}

void TimeLine::AllClear()
{
    world_ = nullptr;
    camera_ = nullptr;
    KeyDataClear();
}

void TimeLine::LoadView(std::vector<IKeyData*>& data, std::string key)
{
    //Camera�ݒ��o�^���ǉ�
    CameraKey* camera = new CameraKey();
    std::vector<float> viewPos = loadFile_[key]["Camera"]["position"];
    std::vector<float> viewTar = loadFile_[key]["Camera"]["target"];
    camera->view.pos = { viewPos[0],viewPos[1],viewPos[2] };
    camera->view.tar = { viewTar[0],viewTar[1],viewTar[2] };
    camera->view.fov = loadFile_[key]["Camera"]["fov"];
    camera->view.isSmooth = loadFile_[key]["Camera"]["smooth"];
    
    if (loadFile_[key]["Camera"]["targetType"] == "Actor") {
        std::string actorName = loadFile_[key]["Camera"].value("targetName", "");
        camera->isTargetActor = true;
        camera->targetActor = world_->GetActor(actorName);
    }
    data.push_back(camera);
}

void TimeLine::LoadEffect(std::vector<IKeyData*>& data, std::string key)
{
    //Effect�ݒ��o�^���ǉ�
    EffectKey* testEffect = new EffectKey();
    testEffect->effect.affected = loadFile_[key]["Effect"]["affected"];
    data.push_back(testEffect);
}

void TimeLine::SetView(CameraKey* key)
{
    View view;
    if (key->isTargetActor) {
        //�^�[�Q�b�g�����Offset�l��ݒ�
        GStransform actorTransform = key->targetActor->Transform();
        view.tar = actorTransform.position() + key->view.tar;
        view.pos = view.tar + (actorTransform.forward() * key->view.pos.x)
            + (actorTransform.up() * key->view.pos.y)
            + (actorTransform.right() * key->view.pos.z);
        //fov,smooth�͂��̂܂�
        view.fov = key->view.fov;
        view.isSmooth = key->view.isSmooth;
    }
    else {
        view = key->view;
    }
    camera_->SetView(view.pos,view.tar);
    camera_->SetFov(view.fov);
    camera_->SetSmooth(view.isSmooth);
}

void TimeLine::SetEffect(EffectKey* key)
{

}

void TimeLine::SetShake(CameraShakeKey* key)
{
}
