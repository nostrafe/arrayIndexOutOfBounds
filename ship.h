#ifndef SHIP_H
#define SHIP_H

#include <QPoint>
#include <list>

typedef enum 
{
    Ship1=1,
    Ship2,
    Ship3,
    Ship4,
    Ship5,
}ShipType;

typedef enum 
{
    Horizontal,
    Vertical,
}ShipDirect;

using namespace std;

class Ship
{
public:
    

public:
    Ship();
    static list<QPoint> sGetShipPostions(QPoint lefttop, ShipType type, ShipDirect direct);

public:
    QPoint _position = QPoint(0,0);
    int _width;
    int _height;
    ShipType _type =Ship1;
    ShipDirect _direct= Vertical;
    //list<QPoint> _destroiedParts;
};

#endif // SHIP_H
