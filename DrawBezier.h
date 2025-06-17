#pragma once
#include "GameObject.h"
#include "global.h"
#include "Lerp.h"
class DrawBezier :
    public GameObject
{
public:
    Lerp lerp_;
    DrawBezier();
    void Update() override;
    void LerpUpdate();
    void LerpUpdate(Lerp* lerp, int index);
    void Draw() override;

    void MoveControlPos();
};

