
#include <iostream>
#include<memory>
#include "Bomb.h"
#include "MyTools.h"

using namespace MyTools;
using namespace std;


void Bomb::Draw() const
{
    logger->SetColor(CC_LightMagenta);
    logger->GotoXY(x, y);
    cout << "*";
}