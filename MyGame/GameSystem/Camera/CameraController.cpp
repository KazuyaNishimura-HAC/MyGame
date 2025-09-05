#include "CameraController.h"

CameraController::CameraController(Priority priority, int id, const GSvector3& position, const GSvector3& target)
{
	priority_ = priority;
	id_ = id;
	view_.pos = position;
	view_.tar = target;
}

void CameraController::SetPosition(const GSvector3& pos)
{
	view_.pos = pos;
}

GSvector3 CameraController::GetPosition() const
{
	return view_.pos;
}

void CameraController::SetViewTarget(const GSvector3& tar)
{
	view_.tar = tar;
}

GSvector3 CameraController::GetViewTarget() const
{
	return view_.tar;
}

void CameraController::SetPriority(Priority p)
{
	priority_ = p;
}

void CameraController::SetView(const GSvector3& pos, const GSvector3& tar)
{
	SetPosition(pos);
	SetViewTarget(tar);
}

CameraController::Priority CameraController::GetPriority() const
{
	return priority_;
}

std::string CameraController::GetPriorityName() const
{
	std::string Name;
	switch (priority_) {
	case Disable: Name = "Disable";
		break;
	case Player: Name = "Player";
		break;
	case Event: Name = "Event";
		break;
	case Debug: Name = "Debug";
		break;
	default: Name = "Disable";
		break;
	}
	return Name;
}

void CameraController::SetID(int id)
{
	id_ = id;
}

int CameraController::GetID() const
{
	return id_;
}

void CameraController::SetFov(float fov)
{
	view_.fov = fov;
}

float CameraController::GetFov() const
{
	return view_.fov;
}

void CameraController::SetSmooth(bool smooth)
{
	view_.isSmooth = smooth;
}

bool CameraController::GetSmooth()
{
	return view_.isSmooth;
}

View& CameraController::GetView()
{
	return view_;
}

void CameraController::Die()
{
	isDead_ = true;
}

bool CameraController::IsDead() const
{
	return isDead_;
}

