#ifndef STATE_NULL_H_
#define STATE_NULL_H_

#include "IState.h"

//��Ԃ����݂��Ȃ��ꍇ�̋󏈗�
class StateNull :public IState
{
public:
	void Update(float deltaTime)override {};
	void Enter()override {};
	void Exit()override {};
	void SetID(int id = 0)override { stateID = 0; };
	int GetID()override { return 0; }
};

#endif