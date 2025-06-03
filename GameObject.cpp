#include "GameObject.h"

GameObject::GameObject()
	:isAlive_{true},x_(0),y_(0),imageSize_({0,0})
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
	return { x_ - centerSizeX, y_ - centerSizeY, x_ + centerSizeX, y_ + imageSize_.y + centerSizeY };
}
