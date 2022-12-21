//
// Created by georgerapeanu on 27.11.2022.
//

#ifndef CONTEST_LEVEL2GAME_H
#define CONTEST_LEVEL2GAME_H

#include "AbstractGame.h"

class Level2Game: public AbstractGame{
    Level2Game();
    virtual ~Level2Game();
    virtual long long evaluate(Solution &solution);
};

#endif //CONTEST_LEVEL2GAME_H
