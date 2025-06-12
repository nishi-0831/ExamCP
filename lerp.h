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
class lerp
{
private:
	std::vector<PointF> controlPoints_; //制御点のリスト
	BezierType type_;					//ベジェ曲線タイプ
	bool autoUpdate_;					//自動更新のフラグ
	float duration_;					//補間時間
	float t_;							//割合t
	float timer_;						//経過時間
public:
	lerp();

	//線形補間
	lerp(PointF start, PointF end, float duration = 1.0f);

	//2次ベジェ曲線
	lerp(PointF start,PointF control, PointF end, float duration = 1.0f);

	//3次ベジェ曲線
	lerp(PointF start,PointF control1, PointF control2, PointF end, float duration = 1.0f);

	
	~lerp();

	
	void SetLinear(PointF start, PointF end);
	void SetQuadratic(PointF start, PointF control, PointF end);
	void SetCubic(PointF start, PointF control1, PointF control2, PointF end);

	void SetAutoUpdate(bool autoUpdate);
	
	

	//時間更新用
	void operator+=(const float& rhs);

	//時間の更新
	void UpdateTime();

	//tの取得
	float GetT() const;

	//tの設定
	float SetT(float t);

	//現在のt値での補間位置
	PointF GetLerpPos();

	//指定したt値での補間位置
	PointF GetLerpPos(float t);

	//2次ベジェ曲線の計算
	PointF CalculateQuadratic(float t);

	//3次ベジェ曲線の計算
	PointF CalculateCubic(float t);

};

