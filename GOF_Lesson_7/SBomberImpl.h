#pragma once
#include<vector>
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "House.h"
#include"Plane.h"
#include"LevelGUI.h"


class SBomberImpl
{
public:
    SBomberImpl() : exitFlag(false), startTime(0), finishTime(0), deltaTime(0),
        passedTime(0), fps(0), bombsNumber(10), score(0) {}

protected:
    void CheckPlaneAndLevelGUI();
    void CheckBombsAndGround();
    void __fastcall CheckDestoyableObjects(Bomb* pBomb);

    void __fastcall DeleteDynamicObj(DynamicObject* pBomb);
    void __fastcall DeleteStaticObj(GameObject* pObj);

    Ground* FindGround() const;
    Plane* FindPlane() const;
    LevelGUI* FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;
    std::vector<Bomb*> FindAllBombs() const;

    void DropBomb();

    std::vector<DynamicObject*> vecDynamicObj;
    std::vector<GameObject*> vecStaticObj;

    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;

    friend class SBomber;
};