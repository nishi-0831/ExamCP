#include "State.h"

static unsigned int stateCount = 0;

State::State():id_(stateCount++)
{
	//name_ = "state:" + std::to_string(id_);
}

State::State(std::string name, unsigned int id, std::function<void(void)> func)
	:name_{name},id_{id},behavior_{func}
{
}

State::~State()
{
}

void State::SetInitialize(const std::function<void(void)>& func)
{
	initialize_ = func;
}
void State::SetBehavior(const std::function<void(void)>& func)
{
	behavior_ = func;
}
void State::SetExitCondition(const std::function<bool()>& func)
{
	exitCondition = func;
}
const std::function<void(void)>& State::Initialize() { return initialize_; }
const std::function<void(void)>& State::GetBehavior() { return  behavior_; }
const std::function<bool()>& State::GetExitCondition() { return exitCondition; }