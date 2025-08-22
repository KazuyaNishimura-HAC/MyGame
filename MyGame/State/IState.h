#ifndef ISTATE_H_
#define ISTATE_H_

class IState {
public:
	virtual ~IState() = default;
	virtual void Update(float deltaTime) = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual void SetID(int id) = 0;
	virtual int GetID() = 0;
protected:
	int stateID{ 0 };
};

#endif