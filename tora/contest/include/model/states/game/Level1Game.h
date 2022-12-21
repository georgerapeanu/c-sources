//
// Created by georgerapeanu on 27.11.2022.
//

#ifndef CONTEST_LEVEL1GAME_H
#define CONTEST_LEVEL1GAME_H
#include <vector>
#include "model/states/solutions/Solution.h"
#include "AbstractGame.h"

class Level1Game : public AbstractGame{
    Level1Game();
    virtual ~Level1Game();
    virtual long long evaluate(Solution &solution);
};
#endif //CONTEST_LEVEL1GAME_H
