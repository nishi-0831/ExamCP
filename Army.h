#pragma once
#include "GameObject.h"
#include "global.h"
#include <vector>

class Enemy;


class Army :
    public GameObject
{
public:
    Army();
    ~Army();
    void Update() override;
    void Draw() override;
    std::vector<Enemy*> enemy_;
    bool InterSectEnemy(const Rect& bullet);
    bool IsLeftEnd();
    bool IsRightEnd();
};

