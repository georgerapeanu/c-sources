//
// Created by georgerapeanu on 27.11.2022.
//

#ifndef CONTEST_ABSTRACTGAME_H
#define CONTEST_ABSTRACTGAME_H

#include "model/states/solutions/Solution.h"

class AbstractGame{
public:
    virtual ~AbstractGame();
    virtual long long evaluate(Solution &solution);
};
#endif //CONTEST_ABSTRACTGAME_H
