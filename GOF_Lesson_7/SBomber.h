#pragma once

#include <vector>
#include<memory>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include  "SBomberImpl.h"

class SBomber
{
public:
    SBomber();
    ~SBomber();
    
    inline bool GetExitFlag() const { return pSBomberImpl->exitFlag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();

private:
    std::unique_ptr<SBomberImpl> pSBomberImpl;

    
};