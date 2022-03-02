
#include <iostream>

#include "Plane.h"
#include "MyTools.h"

using namespace std;
using namespace MyTools;

void Plane::Draw() const
{
    logger->SetColor(CC_LightBlue);
    logger->GotoXY(x, y);
    cout << "=========>";
    logger->GotoXY(x - 2, y - 1);
    cout << "===";
    logger->GotoXY(x + 3, y - 1);
    cout << "\\\\\\\\";
    logger->GotoXY(x + 3, y + 1);
    cout << "////";
}
