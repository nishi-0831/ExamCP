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
class Lerp
{
private:
	std::vector<PointF> controlPoints_; //����_�̃��X�g
	BezierType type_;					//�x�W�F�Ȑ��^�C�v
	bool autoUpdate_;					//�����X�V�̃t���O
	bool playReverse_;					//�t�Đ����邩
	bool isReverse_;					//���݂͋t�Đ����ۂ�
	bool isLoop_;						//���[�v���邩
	float duration_;					//��Ԏ���
	float t_;							//����t
	float timer_;						//�o�ߎ���
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
	
	

	//���ԍX�V�p
	void operator+=(const float& rhs);
	void operator-=(const float& rhs);

	//���Ԃ̍X�V
	void UpdateTime();

	//t�̎擾
	float GetT() const;

	float GetTimer() const;

	//t�̐ݒ�
	void SetT(float t);

	//�t�Đ��̐ݒ�
	void SetReverse(bool flag);

	//���[�v�̐ݒ�
	void SetLoop(bool flag);

	//���݂�t�l�ł̕�Ԉʒu
	PointF GetLerpPos();

	//�w�肵��t�l�ł̕�Ԉʒu
	PointF GetLerpPos(float t);

	//2���x�W�F�Ȑ��̌v�Z
	PointF CalculateQuadratic(float t);

	//3���x�W�F�Ȑ��̌v�Z
	PointF CalculateCubic(float t);

};

