#include "CameraManager.h"
#include "Camera.h"
#include "CameraController.h"
#include <imgui/imgui.h>

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
}

void CameraManager::Update(float deltaTime)
{
    ControllerUpdate(deltaTime);
	for (auto& camera : cameras_) {
		camera->Update(deltaTime);
	}
    Remove();
}

void CameraManager::ControllerUpdate(float deltaTime)
{
    CameraController* activeController = GetActiveController();

    activeController->Update(deltaTime);

    for (auto& camera : cameras_) {
        camera->SetController(activeController);
    }
}

void CameraManager::Draw(int id) const
{
	cameras_[id]->Draw();
}

void CameraManager::Remove()
{
    for (auto i = cameras_.begin(); i != cameras_.end();)
    {
        if ((*i)->IsDead())
        {
            delete* i;
            i = cameras_.erase(i);
        }
        else ++i;
    }

    for (auto i = controller_.begin(); i != controller_.end();)
    {
        if ((*i)->IsDead())
        {
            delete* i;
            i = controller_.erase(i);
        }
        else ++i;
    }
}

void CameraManager::Clear()
{

    for (auto& camera : cameras_)
    {
        delete camera;
    }
    cameras_.clear();

    for (auto& ctrl : controller_)
    {
        delete ctrl;
    }
    controller_.clear();
}

void CameraManager::Debug()
{
    for (auto& camera : cameras_) {
        camera->Debug();
    }
}

int CameraManager::CameraCount()
{
	return (int)cameras_.size();
}

void CameraManager::AddCamera(Camera* camera)
{
	cameras_.push_back(camera);
}

Camera* CameraManager::GetCamera(int id)
{
	return cameras_[id];
}

std::vector<Camera*> CameraManager::GetCameras() const
{
	return cameras_;
}

void CameraManager::AddController(CameraController* controller)
{
    controller_.push_back(controller);
}

CameraController* CameraManager::GetActiveController()
{
    CameraController* activeController = nullptr;

    for (auto& ctrl : controller_) {
        //一番最初に設定したコントローラを有効化
        if (!activeController) {
            activeController = ctrl;
            continue;
        }
        //優先順位の高い物を有効化
        if (activeController->GetPriority() < ctrl->GetPriority()) {
            //変更前のカメラ位置に移動するか？
            if (ctrl->IsMovePrevious()) {
                View preView = activeController->GetView();
                ctrl->SetView(preView.pos, preView.tar);
                ctrl->SetFov(preView.fov);
                ctrl->SetSmooth(preView.isSmooth);
                ctrl->SetMovePrevious(false);
            }
            activeController = ctrl;
        }
    }
    
    return activeController;
}

