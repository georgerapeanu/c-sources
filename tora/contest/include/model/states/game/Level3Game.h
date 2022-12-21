//
// Created by georgerapeanu on 27.11.2022.
//

#ifndef CONTEST_LEVEL3GAME_H
#define CONTEST_LEVEL3GAME_H

#include "AbstractGame.h"

class Level3Game: public AbstractGame{
    Level3Game();
    virtual ~Level3Game();
    virtual long long evaluate(const Solution &solution);
};

#endif //CONTEST_LEVEL3GAME_H
