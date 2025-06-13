#pragma once
#include "GameObject.h"
#include "global.h"
#include "Lerp.h"
class DrawBezier :
    public GameObject
{
public:
    Lerp lerp;
    DrawBezier();
    void Update() override;
    void Draw() override;

    void MoveControlPos();
};

