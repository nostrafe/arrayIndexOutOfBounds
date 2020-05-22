#ifndef BULLET_H
#define BULLET_H

#include <QPoint>

class Player;

class Bullet
{
public:
    Bullet();

    QPoint _position;
    Player* _owner=nullptr;
};

#endif // BULLET_H
