#include "GameObject.h"
#include <DxLib.h>
GameObject::GameObject()
	:isAlive_{true},x_(0),y_(0),imageSize_({0,0}),hImage_(-1)
{
	//‹ó
}

GameObject::~GameObject()
{
	//‹ó
}

Rect GameObject::GetRect()
{
	int centerSizeX = imageSize_.x / 2;
	int centerSizeY = imageSize_.y / 2;
	return { x_ - centerSizeX, y_ - centerSizeY, x_ + centerSizeX, y_  + centerSizeY };
}

Point GameObject::GetImageCenter()
{
	return Point(imageSize_.x / 2, imageSize_.y / 2);
}

void GameObject::Draw()
{
	if (!isAlive_) return;

	Rect rect = GetRect();
	DrawExtendGraphF(rect.x,rect.y, rect.width, rect.height, hImage_, TRUE);
	DrawBox(rect.x, rect.y, rect.width, rect.height, GetColor(255, 0, 0), FALSE);
}