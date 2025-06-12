#include "lerp.h"
#include "Time.h"
#include <algorithm>
#include <cmath>
lerp::lerp() : type_(BezierType::Linear),autoUpdate_(true),duration_(1.0f),timer_(0.0f),t_(0.0f)
{
	controlPoints_.resize(2);
	controlPoints_[0] = PointF(0, 0);
	controlPoints_[1] = PointF(0, 0);
}
lerp::lerp(PointF start, PointF end, float duration) : type_(BezierType::Linear),autoUpdate_(true),duration_(duration), timer_(0.0f), t_(0.0f)
{
	controlPoints_.resize(2);
	controlPoints_[0] = start;
	controlPoints_[1] = end;
}
lerp::lerp(PointF start, PointF control, PointF end, float duration) : type_(BezierType::Quadratic), autoUpdate_(true), duration_(duration), timer_(0.0f), t_(0.0f)
{
	controlPoints_.resize(3);
	controlPoints_[0] = start;
	controlPoints_[1] = control;
	controlPoints_[2] = end;
}
lerp::lerp(PointF start, PointF control1, PointF control2, PointF end, float duration) : type_(BezierType::Cubic), autoUpdate_(true), duration_(duration), timer_(0.0f), t_(0.0f)
{
	controlPoints_.resize(4);
	controlPoints_[0] = start;
	controlPoints_[1] = control1;
	controlPoints_[2] = control2;
	controlPoints_[3] = end;
}
lerp::~lerp()
{
}
void lerp::SetLinear(PointF start, PointF end)
{
	type_ = BezierType::Linear;
	controlPoints_.resize(2);
	controlPoints_[0] = start;
	controlPoints_[1] = end;
}
void lerp::SetQuadratic(PointF start, PointF control, PointF end)
{
	type_ = BezierType::Quadratic;
	controlPoints_.resize(3);
	controlPoints_[0] = start;
	controlPoints_[1] = control;
	controlPoints_[2] = end;
}
void lerp::SetCubic(PointF start, PointF control1, PointF control2, PointF end)
{
	type_ = BezierType::Cubic;
	controlPoints_.resize(4);
	controlPoints_[0] = start;
	controlPoints_[1] = control1;
	controlPoints_[2] = control2;
	controlPoints_[3] = end;
}
void lerp::SetAutoUpdate(bool autoUpdate)
{
	autoUpdate_ = autoUpdate;
}
void lerp::operator+=(const float& rhs)
{
	timer_ += rhs;
	if (timer_ > duration_)
	{
		timer_ = duration_;
	}
	if (autoUpdate_)
	{
		t_ = timer_ / duration_;
		if (t_ > 1.0f)
		{
			t_ = 1.0f;
		}
	}
}
void lerp::UpdateTime()
{
	*this += Time::DeltaTime();
}
float lerp::GetT() const
{
	return t_;
}
float lerp::SetT(float t)
{
	t_ = std::clamp(t, 0.0f, 1.0f);
	if (!autoUpdate_)
	{
		timer_ = t_ * duration_;
	}
}
PointF lerp::GetLerpPos()
{
	GetLerpPos(t_);
}

PointF lerp::GetLerpPos(float t)
{
	t = std::clamp(t, 0.0f, 1.0f);

	switch (type_)
	{
	case BezierType::Linear:
		return PointF(controlPoints_[0] + (controlPoints_[1] - controlPoints_[0]) * t);
	case BezierType::Quadratic:
		return CalculateQuadratic(t);
	case BezierType::Cubic:
		return CalculateCubic(t);
	default:
		return PointF(0, 0);
	}
}

PointF lerp::CalculateQuadratic(float t)
{
	//P = (1-t)^2*P1 + 2(1-t)t*P2 + t^2*P3
	//p1が始点、p2が制御点、p3が終点

	float oneMinusT = 1.0f - t;
	float oneMinusT2 = std::pow(oneMinusT, 2.0f);

	PointF result;
	result = ( oneMinusT2 * controlPoints_[0] ) + ( 2.0f * oneMinusT * t * controlPoints_[1] ) + ( t * t * controlPoints_[2] );
	return result;
}

PointF lerp::CalculateCubic(float t)
{
	//P = (1?t)^3*P1 + 3(1?t)^2*t*P2 +3(1?t)t^2*P3 + t^3*P4

	float oneMinusT = 1.0f - t;

	PointF result;
	result = (std::pow(oneMinusT, 3.0f) * controlPoints_[0]) 
		+ ( 3.0f * std::pow(oneMinusT, 2.0f)  * t * controlPoints_[1] ) 
		+ ( 3 * oneMinusT * std::pow(t, 2.0f) * controlPoints_[2] ) 
		+ std::pow(t, 3.0f) * controlPoints_[3];

	return result;
}
