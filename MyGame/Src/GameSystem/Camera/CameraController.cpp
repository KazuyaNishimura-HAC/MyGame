#include "CameraController.h"
#include "../../NameTag.h"

CameraController::CameraController(Priority priority, int id, const GSvector3& position, const GSvector3& target)
{
	priority_ = priority;
	id_ = id;
	view_.pos = position;
	view_.tar = target;
}

void CameraController::Update(float deltaTime)
{
	if (!IsShake()) return;
	shake_.Update(deltaTime);
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

void CameraController::SetPriority(Priority p, bool preMove)
{
	priority_ = p;
	SetMovePrevious(preMove);
}

CameraController::Priority CameraController::GetPriority() const
{
	return priority_;
}

std::string CameraController::GetPriorityName() const
{
	std::string Name;
	switch (priority_) {
	case Disable: Name = PriorityName::Disable;
		break;
	case Player: Name = PriorityName::Player;
		break;
	case Event: Name = PriorityName::Event;
		break;
	case Debug: Name = PriorityName::Debug;
		break;
	default: Name = PriorityName::Disable;
		break;
	}
	return Name;
}

void CameraController::SetView(const GSvector3& pos, const GSvector3& tar)
{
	SetPosition(pos);
	SetViewTarget(tar);
}

View& CameraController::GetView()
{
	return view_;
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

bool CameraController::IsSmooth() const
{
	return view_.isSmooth;
}

void CameraController::SetMovePrevious(bool preMove)
{
	preMove_ = preMove;
}

bool CameraController::IsMovePrevious() const
{
	return preMove_;
}



void CameraController::Die()
{
	isDead_ = true;
}

bool CameraController::IsDead() const
{
	return isDead_;
}

View CameraController::GetAffectedView()
{
	return shake_.ShakeView(view_);
}

void CameraController::SetShakeValues(float timer, float strength, float decayTime, float decaySpeed, float hz, GSvector2 vectorAffect, float fovAffect)
{
	shake_ = {timer,strength,decayTime,decaySpeed,hz,vectorAffect,fovAffect};
}

void CameraController::SetShake(const CameraShake& shake)
{
	shake_ = shake;
}

CameraShake& CameraController::GetShake()
{
	return shake_;
}

bool CameraController::IsShake()
{
	return shake_.timer != 0.0f;
}
