#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "player.h"
#include "bullet.h"

typedef enum
{
    NotStarted,
    P1Place,
    P2Place,
    WaitP1Attack,
    P1Attack,
    P1AttackFinish,
    WaitP2Attack,
    P2Attack,
    P2AttachFinish,
    Overed,
}GameStatus;

class GameManager
{
public:
    GameManager();

public:
    Player _p1;
    Player _p2;

    Bullet _curFlyBullet;

    GameStatus _status = NotStarted;

    int shipCount = 5;

};

#endif // GAMEMANAGER_H
