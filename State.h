#pragma once
#include <string>
#include <functional>
class State
{
public:
	//�f�o�b�O�ŕ\�����邽�߂̕�����
	std::string name_;
	//���ʎq
	unsigned int id_;

	//
	std::function<void(void)> initialize_;
	//�U�镑��
	std::function<void(void)> behavior_;
	//�I������
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

