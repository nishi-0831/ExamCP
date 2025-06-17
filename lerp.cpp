#include "lerp.h"
#include "Time.h"
#include <algorithm>
#include <cmath>

Lerp::Lerp() : type_(BezierType::Linear),autoUpdate_(true),duration_(1.0f),timer_(0.0f),t_(0.0f)
{
	SetLinear(PointF(0, 0), PointF(0, 0));
	/*controlPoints_.resize(2);
	controlPoints_[0] = PointF(0, 0);
	controlPoints_[1] = PointF(0, 0);*/
}
Lerp::Lerp(PointF start, PointF end, float duration) : type_(BezierType::Linear),autoUpdate_(true),duration_(duration), timer_(0.0f), t_(0.0f)
{
	SetLinear(start, end);
	/*controlPoints_.resize(2);
	controlPoints_[0] = start;
	controlPoints_[1] = end;*/
}
Lerp::Lerp(PointF start, PointF control, PointF end, float duration) : type_(BezierType::Quadratic), autoUpdate_(true), duration_(duration), timer_(0.0f), t_(0.0f)
{
	SetQuadratic(start, control, end);
	/*controlPoints_.resize(3);
	controlPoints_[0] = start;
	controlPoints_[1] = control;
	controlPoints_[2] = end;*/
}
Lerp::Lerp(PointF start, PointF control1, PointF control2, PointF end, float duration) : type_(BezierType::Cubic), autoUpdate_(true), duration_(duration), timer_(0.0f), t_(0.0f)
{
	SetCubic(start, control1, control2, end);
	/*controlPoints_.resize(4);
	controlPoints_[0] = start;
	controlPoints_[1] = control1;
	controlPoints_[2] = control2;
	controlPoints_[3] = end;*/
}
Lerp::~Lerp()
{
}
void Lerp::Init()
{
	loopMode_ = LoopMode::Once;
	dir_ = 1;
}

void Lerp::SetLinear(PointF start, PointF end)
{
	//Init();
	type_ = BezierType::Linear;
	controlPoints_.resize(2);
	controlPoints_[0] = start;
	controlPoints_[1] = end;
}
void Lerp::SetQuadratic(PointF start, PointF control, PointF end)
{
	//Init();
	type_ = BezierType::Quadratic;
	controlPoints_.resize(3);
	controlPoints_[0] = start;
	controlPoints_[1] = control;
	controlPoints_[2] = end;
}
void Lerp::SetCubic(PointF start, PointF control1, PointF control2, PointF end)
{
	//Init();
	type_ = BezierType::Cubic;
	controlPoints_.resize(4);
	controlPoints_[0] = start;
	controlPoints_[1] = control1;
	controlPoints_[2] = control2;
	controlPoints_[3] = end;
}
void Lerp::SetDuration(float duration)
{
	duration_ = duration;
}
void Lerp::SetAutoUpdate(bool autoUpdate)
{
	autoUpdate_ = autoUpdate;
}
void Lerp::SetLoopMode(LoopMode mode)
{
	loopMode_ = mode;
}
void Lerp::SetStart(PointF start)
{
	if (controlPoints_.size() > 0)
	{
		controlPoints_[0] = start;
	}
}
void Lerp::SetEnd(PointF end)
{
	int typeSize = (int)type_;
	controlPoints_[typeSize + 1] = end; 
	
}
void Lerp::SetControl1(PointF control1)
{
	if (type_ != BezierType::Linear)
	{
		controlPoints_[1] = control1;
	}
}
void Lerp::SetControl2(PointF control2)
{
	if (type_ != BezierType::Cubic)
	{
		controlPoints_[2] = control2;
	}
}
void Lerp::operator+=(const float& rhs)
{
	timer_ += rhs;	
}
void Lerp::UpdateTime()
{
	if (timer_ > duration_)
	{
		OnSurpassDuration();
	}
	else if (timer_ < 0.0f)
	{
		OnSurpassZero();
	}
	t_ = timer_ / duration_;
	*this += ( Time::DeltaTime() * (float)dir_ );
}

void Lerp::OnSurpassDuration()
{
	switch (loopMode_)
	{
		case LoopMode::Once:
			timer_ = duration_;
			break;
		case LoopMode::Loop:
			timer_ = 0;
			break;
		case LoopMode::PingPong:
			timer_ = duration_;
			dir_ = -1;
			break;
	}
}
void Lerp::OnSurpassZero()
{
	switch (loopMode_)
	{
	case LoopMode::Once:
		timer_ = 0;
		break;
	case LoopMode::Loop:
		timer_ = duration_;
		break;
	case LoopMode::PingPong:
		timer_ = 0;
		dir_ = 1;
		break;
	}
}

float Lerp::GetT() const
{
	return t_;
}
float Lerp::GetTimer() const
{
	return timer_;
}
int Lerp::GetDir() const
{
	return dir_;
}
void Lerp::SetT(float t)
{
	t_ = std::clamp(t, 0.0f, 1.0f);
	if (!autoUpdate_)
	{
		timer_ = t_ * duration_;
	}
}


PointF Lerp::GetLerpPos()
{
	return GetLerpPos(t_);
}

PointF Lerp::GetLerpPos(float t)
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

PointF Lerp::CalculateQuadratic(float t)
{
	//P = (1-t)^2*P1 + 2(1-t)t*P2 + t^2*P3
	//p1が始点、p2が制御点、p3が終点

	float oneMinusT = 1.0f - t;
	float oneMinusT2 = std::pow(oneMinusT, 2.0f);

	PointF result;
	result = ( oneMinusT2 * controlPoints_[0] ) + ( 2.0f * oneMinusT * t * controlPoints_[1] ) + ( t * t * controlPoints_[2] );
	return result;
}

PointF Lerp::CalculateCubic(float t)
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
