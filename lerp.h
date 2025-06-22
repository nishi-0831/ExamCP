#pragma once
#include "global.h"
#include <vector>

//ベジェ曲線の種類
enum class BezierType
{
	Linear,//2点の線形補間
	Quadratic,//3点の2次ベジェ曲線
	Cubic//4点の3次ベジェ曲線
};
enum class LoopMode
{
	Once,		//一度きり。ループしない
	Loop,		//1を超えたら0になる
	PingPong,	//もう一方の点へ進む
};
class Lerp
{
private:
	std::vector<PointF> controlPoints_; //制御点のリスト
	BezierType type_;					//ベジェ曲線タイプ
	bool autoUpdate_;					//自動更新のフラグ
	int dir_;							//移動方向
	float duration_;					//補間時間
	float t_;							//割合t
	float timer_;						//経過時間
	LoopMode loopMode_;					//ループの設定
	void OnSurpassDuration();			//timer_がduration_を超えたときに
	void OnSurpassZero();				//timer_が0未満になったときに呼ばれる
public:
	Lerp();

	//線形補間
	Lerp(PointF start, PointF end, float duration = 1.0f);

	//2次ベジェ曲線
	Lerp(PointF start,PointF control, PointF end, float duration = 1.0f);

	//3次ベジェ曲線
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

	//時間更新用
	void operator+=(const float& rhs);

	//時間の更新
	void UpdateTime();

	//tの取得
	float GetT() const;

	float GetTimer() const;

	int GetDir() const;

	//tの設定
	void SetT(float t);

	//端に到達したか
	//bool OnSurpass();

	//現在のt値での補間位置
	PointF GetLerpPos();

	//指定したt値での補間位置
	PointF GetLerpPos(float t);

	//2次ベジェ曲線の計算
	PointF CalculateQuadratic(float t);

	//3次ベジェ曲線の計算
	PointF CalculateCubic(float t);

	void Reset();
};

