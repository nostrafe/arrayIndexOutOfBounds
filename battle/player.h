#ifndef PLAYER_H
#define PLAYER_H

#include <QString>
#include <list>
#include "ship.h"
using namespace std;

class Player
{
public:
    Player();
    ~Player();

    bool addShip(int row, int col, ShipType type, ShipDirect direct);

    bool _canAddShip(list<QPoint> newPoss);

    list<QPoint> _getShipPositons();

public:
    QString _name;

    list<Ship*> _ships;

    int _steps = 0;
};

#endif // PLAYER_H
