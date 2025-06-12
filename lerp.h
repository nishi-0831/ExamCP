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
class lerp
{
private:
	std::vector<PointF> controlPoints_; //����_�̃��X�g
	BezierType type_;					//�x�W�F�Ȑ��^�C�v
	bool autoUpdate_;					//�����X�V�̃t���O
	float duration_;					//��Ԏ���
	float t_;							//����t
	float timer_;						//�o�ߎ���
public:
	lerp();

	//���`���
	lerp(PointF start, PointF end, float duration = 1.0f);

	//2���x�W�F�Ȑ�
	lerp(PointF start,PointF control, PointF end, float duration = 1.0f);

	//3���x�W�F�Ȑ�
	lerp(PointF start,PointF control1, PointF control2, PointF end, float duration = 1.0f);

	
	~lerp();

	
	void SetLinear(PointF start, PointF end);
	void SetQuadratic(PointF start, PointF control, PointF end);
	void SetCubic(PointF start, PointF control1, PointF control2, PointF end);

	void SetAutoUpdate(bool autoUpdate);
	
	

	//���ԍX�V�p
	void operator+=(const float& rhs);

	//���Ԃ̍X�V
	void UpdateTime();

	//t�̎擾
	float GetT() const;

	//t�̐ݒ�
	float SetT(float t);

	//���݂�t�l�ł̕�Ԉʒu
	PointF GetLerpPos();

	//�w�肵��t�l�ł̕�Ԉʒu
	PointF GetLerpPos(float t);

	//2���x�W�F�Ȑ��̌v�Z
	PointF CalculateQuadratic(float t);

	//3���x�W�F�Ȑ��̌v�Z
	PointF CalculateCubic(float t);

};

