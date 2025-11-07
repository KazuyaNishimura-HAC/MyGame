#include "StateMachine.h"
#include "StateNull.h"
#include <imGui/imgui.h>

//ステートが無い時の空ステート
static StateNull nullState;

StateMachine::StateMachine()
	:currentState_{ &nullState }, prevState_{ &nullState }
{

}

StateMachine::~StateMachine()
{
	currentState_ = &nullState;
	prevState_ = &nullState;
	for (auto state : states_)
	{
		delete state.second;
	}
	states_.clear();
}

void StateMachine::Update(float deltaTime)
{
	currentState_->Update(deltaTime);
}

void StateMachine::AddState(int stateName, IState* state)
{
	auto success = states_.insert({stateName,state});
	//追加出来たらIDを登録
	if(success.second) state->SetID(stateName);
}

void StateMachine::ChangeState(int stateName)
{
	//遷移要素が無ければreturn
	if (states_.count(stateName) == 0) return;
	IState* nextState = states_[stateName];
	prevState_ = currentState_;
	currentState_->Exit();
	currentState_ = nextState;
	currentState_->Enter();
}

int StateMachine::CurrentState()
{
	return currentState_->GetID();
}

int StateMachine::PrevState()
{
	return prevState_->GetID();
}

bool StateMachine::IsCurrentState(int stateName)
{
	return currentState_->GetID() == stateName;
}

bool StateMachine::IsPrevState(int stateName)
{
	return prevState_->GetID() == stateName;
}

int StateMachine::StateCount()
{
	return (int)states_.size();
}

void StateMachine::Debug()
{
}
