
#include <conio.h>
#include <windows.h>

#include "MyTools.h"
#include "SBomber.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "House.h"

using namespace std;
using namespace MyTools;

SBomber::SBomber() : pSBomberImpl(make_unique<SBomberImpl>())
{
    logger->WriteToLog(string(__FUNCTION__) + " was invoked");

    Plane* p = new Plane;
    p->SetDirection(1, 0.1);
    p->SetSpeed(4);
    p->SetPos(5, 10);
    pSBomberImpl->vecDynamicObj.push_back(p);

    LevelGUI* pGUI = new LevelGUI;
    pGUI->SetParam(pSBomberImpl->passedTime, pSBomberImpl->fps,
        pSBomberImpl->bombsNumber, pSBomberImpl->score);

    const uint16_t maxX = logger->GetMaxX();
    const uint16_t maxY = logger->GetMaxY(); 
    const uint16_t offset = 3;
    const uint16_t width = maxX - 7;
    pGUI->SetPos(offset, offset);
    pGUI->SetWidth(width);
    pGUI->SetHeight(maxY - 4);
    pGUI->SetFinishX(offset + width - 4);
    pSBomberImpl->vecStaticObj.push_back(pGUI);

    Ground* pGr = new Ground;
    const uint16_t groundY = maxY - 5;
    pGr->SetPos(offset + 1, groundY);
    pGr->SetWidth(width - 2);
    pSBomberImpl->vecStaticObj.push_back(pGr);

    Tank* pTank = new Tank;
    pTank->SetWidth(13);
    pTank->SetPos(30, groundY - 1);
    pSBomberImpl->vecStaticObj.push_back(pTank);

    pTank = new Tank;
    pTank->SetWidth(13);
    pTank->SetPos(50, groundY - 1);
    pSBomberImpl->vecStaticObj.push_back(pTank);

    House * pHouse = new House;
    pHouse->SetWidth(13);
    pHouse->SetPos(80, groundY - 1);
    pSBomberImpl->vecStaticObj.push_back(pHouse);

    /*
    Bomb* pBomb = new Bomb;
    pBomb->SetDirection(0.3, 1);
    pBomb->SetSpeed(2);
    pBomb->SetPos(51, 5);
    pBomb->SetSize(SMALL_CRATER_SIZE);
    vecDynamicObj.push_back(pBomb);
    */
}

SBomber::~SBomber()
{
    for (size_t i = 0; i < pSBomberImpl->vecDynamicObj.size(); i++)
    {
        if (pSBomberImpl->vecDynamicObj[i] != nullptr)
        {
            delete pSBomberImpl->vecDynamicObj[i];
        }
    }

    for (size_t i = 0; i < pSBomberImpl->vecStaticObj.size(); i++)
    {
        if (pSBomberImpl->vecStaticObj[i] != nullptr)
        {
            delete pSBomberImpl->vecStaticObj[i];
        }
    }
}

void SBomber::MoveObjects()
{
    logger->WriteToLog(string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < pSBomberImpl->vecDynamicObj.size(); i++)
    {
        if (pSBomberImpl->vecDynamicObj[i] != nullptr)
        {
            pSBomberImpl->vecDynamicObj[i]->Move(pSBomberImpl->deltaTime);
        }
    }
};

void SBomber::CheckObjects()
{
    logger->WriteToLog(string(__FUNCTION__) + " was invoked");

    pSBomberImpl->CheckPlaneAndLevelGUI();
    pSBomberImpl->CheckBombsAndGround();
};


void SBomber::ProcessKBHit()
{
    int c = _getch();

    if (c == 224)
    {
        c = _getch();
    }

    logger->WriteToLog(string(__FUNCTION__) + " was invoked. key = ", c);

    switch (c) {

    case 27: // esc
        pSBomberImpl->exitFlag = true;
        break;

    case 72: // up
        pSBomberImpl->FindPlane()->ChangePlaneY(-0.25);
        break;

    case 80: // down
        pSBomberImpl->FindPlane()->ChangePlaneY(0.25);
        break;

    case 'b':
        logger->WriteToLog(std::string("SBomberImpl::DropBomb was invoked"));
        pSBomberImpl->DropBomb();
        break;

    case 'B':
        logger->WriteToLog(std::string("SBomberImpl::DropBomb was invoked"));
        pSBomberImpl->DropBomb();
        break;

    default:
        break;
    }
}

void SBomber::DrawFrame()
{
    logger->WriteToLog(string(__FUNCTION__) + " was invoked");

    for (size_t i = 0; i < pSBomberImpl->vecDynamicObj.size(); i++)
    {
        if (pSBomberImpl->vecDynamicObj[i] != nullptr)
        {
            pSBomberImpl->vecDynamicObj[i]->Draw();
        }
    }

    for (size_t i = 0; i < pSBomberImpl->vecStaticObj.size(); i++)
    {
        if (pSBomberImpl->vecStaticObj[i] != nullptr)
        {
            pSBomberImpl->vecStaticObj[i]->Draw();
        }
    }

    logger->GotoXY(0, 0);
    pSBomberImpl->fps++;

    pSBomberImpl->FindLevelGUI()->SetParam(pSBomberImpl->passedTime, pSBomberImpl->fps, pSBomberImpl->bombsNumber, pSBomberImpl->score);
}

void SBomber::TimeStart()
{
    logger->WriteToLog(string(__FUNCTION__) + " was invoked");
    pSBomberImpl->startTime = GetTickCount64();
}

void SBomber::TimeFinish()
{
    pSBomberImpl->finishTime = GetTickCount64();
    pSBomberImpl->deltaTime = uint16_t(pSBomberImpl->finishTime - pSBomberImpl->startTime);
    pSBomberImpl->passedTime += pSBomberImpl->deltaTime;

    logger->WriteToLog(string(__FUNCTION__) + " deltaTime = ", (int)pSBomberImpl->deltaTime);
}

