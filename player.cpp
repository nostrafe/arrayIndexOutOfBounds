#include "player.h"

#include "ship.h"

Player::Player()
{
    
}


Player::~Player()
{
    for(auto it = _ships.begin();it!=_ships.end();++it)
    {
        delete *it;
    }
    _ships.clear();
}

bool Player::addShip(int col, int row, ShipType type, ShipDirect direct)
{
    
    for (auto it = _ships.begin(); it != _ships.end(); ++it)
    {
        if ((*it)->_position.x() == row && (*it)->_position.y() == col)
        {
            return false;
        }
    }

    auto t = new Ship();
    t->_type = type;
    t->_direct = direct;
    t->_position = QPoint(row, col);
    _ships.push_back(t);
    return true;
}

bool Player::_canAddShip(list<QPoint> newPoss)
{
    for (auto it = _ships.begin(); it != _ships.end(); ++it)
    {
        auto t2 = Ship::sGetShipPostions((*it)->_position, (*it)->_type, (*it)->_direct);
        for (auto it2 = t2.begin(); it2 != t2.end(); ++it2)
        {
            for (auto it3 = newPoss.begin(); it3 != newPoss.end(); ++it3)
            {
                if (it3->x() == it2->x() && it3->y() == it2->y())
                {
                    return false;
                }
            }
        }
    }
    return true;
}

std::list<QPoint> Player::_getShipPositons()
{
    list<QPoint> lRet;
    for (auto it = _ships.begin(); it != _ships.end(); ++it)
    {
        auto s = *it;
        auto cc = Ship::sGetShipPostions(s->_position, s->_type, s->_direct);
        for (auto it2 = cc.begin(); it2 != cc.end(); ++it2)
        {
            lRet.push_back(*it2);
        }
    }
    return lRet;
}
