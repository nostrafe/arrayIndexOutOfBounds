#include "ship.h"

Ship::Ship()
{

}

std::list<QPoint> Ship::sGetShipPostions(QPoint lefttop, ShipType type, ShipDirect direct)
{
    list<QPoint> lRet;
    lRet.push_back(lefttop);
    for (auto i = 0; i < type; ++i)
    {
        switch (direct)
        {
        case Vertical:
        {
            lefttop.setY(lefttop.y() + 1);
        }break;
        case Horizontal:
        {
            lefttop.setX(lefttop.x() + 1);
        }break;
        default:
            break;
        }
        lRet.push_back(lefttop);
    }
    return lRet;
}
