#pragma once
#include "global.h"
#include <vector>

//�x�W�F�Ȑ��̎��
enum class BezierType
{
	Linear,//2�_�̐��`���
	Quadratic,//3�_��2���x�W�F�Ȑ�
	Cubic//4�_��3���x�W�F�Ȑ�
};
enum class LoopMode
{
	Once,		//��x����B���[�v���Ȃ�
	Loop,		//1�𒴂�����0�ɂȂ�
	PingPong,	//��������̓_�֐i��
};
class Lerp
{
private:
	std::vector<PointF> controlPoints_; //����_�̃��X�g
	BezierType type_;					//�x�W�F�Ȑ��^�C�v
	bool autoUpdate_;					//�����X�V�̃t���O
	int dir_;							//�ړ�����
	float duration_;					//��Ԏ���
	float t_;							//����t
	float timer_;						//�o�ߎ���
	LoopMode loopMode_;					//���[�v�̐ݒ�
	void OnSurpassDuration();			//timer_��duration_�𒴂����Ƃ���
	void OnSurpassZero();				//timer_��0�����ɂȂ����Ƃ��ɌĂ΂��
public:
	Lerp();

	//���`���
	Lerp(PointF start, PointF end, float duration = 1.0f);

	//2���x�W�F�Ȑ�
	Lerp(PointF start,PointF control, PointF end, float duration = 1.0f);

	//3���x�W�F�Ȑ�
	Lerp(PointF start,PointF control1, PointF control2, PointF end, float duration = 1.0f);

	
	~Lerp();

	void Init();

	void SetLinear(PointF start, PointF end);
	void SetQuadratic(PointF start, PointF control, PointF end);
	void SetCubic(PointF start, PointF control1, PointF control2, PointF end);
	void SetDuration(float duration);
	void SetAutoUpdate(bool autoUpdate);
	void SetLoopMode(LoopMode mode);
	void SetStart(PointF start);
	void SetEnd(PointF end);
	void SetControl1(PointF control1);
	void SetControl2(PointF control2);

	//���ԍX�V�p
	void operator+=(const float& rhs);

	//���Ԃ̍X�V
	void UpdateTime();

	//t�̎擾
	float GetT() const;

	float GetTimer() const;

	int GetDir() const;

	//t�̐ݒ�
	void SetT(float t);

	//�[�ɓ��B������
	//bool OnSurpass();

	//���݂�t�l�ł̕�Ԉʒu
	PointF GetLerpPos();

	//�w�肵��t�l�ł̕�Ԉʒu
	PointF GetLerpPos(float t);

	//2���x�W�F�Ȑ��̌v�Z
	PointF CalculateQuadratic(float t);

	//3���x�W�F�Ȑ��̌v�Z
	PointF CalculateCubic(float t);

	void Reset();
};

