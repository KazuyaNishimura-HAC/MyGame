#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include "IState.h"
#include <unordered_map>

class StateMachine
{
public:
	StateMachine();
	~StateMachine();
	void Update(float deltaTime);
	void AddState(int stateName,IState* state);
	void ChangeState(int nextStateName);
	//�X�e�[�g�̎擾
	int CurrentState();
	int PrevState();
	//�����Ɠ����X�e�[�g���H
	bool IsCurrentState(int stateName);
	bool IsPrevState(int stateName);

	int StateCount();
	void Debug();
private:
	std::unordered_map<int, IState*> states_;
	IState* currentState_;
	IState* prevState_;
};

#endif