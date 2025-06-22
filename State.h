#pragma once
#include <string>
#include <functional>
class State
{
public:
	//デバッグで表示するための文字列
	std::string name_;
	//識別子
	unsigned int id_;

	//
	std::function<void(void)> initialize_;
	//振る舞い
	std::function<void(void)> behavior_;
	//終了条件
	std::function<bool()> exitCondition;
public:
	State();
	State(std::string name, unsigned int id, std::function<void(void)> func);
	~State();

	bool operator==(const State& rhs) const
	{
		return id_ == rhs.id_;
	}
	bool operator<(const State& rhs) const
	{
		return id_ < rhs.id_;
	}

	void SetName(std::string name)
	{
		name_ = name;
	}
	void SetInitialize(const std::function<void(void)>& func);
	void SetBehavior(const std::function<void(void)>& func);
	void SetExitCondition(const std::function<bool()>& func);
	const std::function<void(void)>& Initialize();
	const std::function<void(void)>& GetBehavior();
	const std::function<bool()>& GetExitCondition();
	int ID() { return id_; }

};

