//
// Created by georgerapeanu on 27.11.2022.
//

#ifndef CONTEST_ABSTRACTROUTEFACTORY_H
#define CONTEST_ABSTRACTROUTEFACTORY_H

#include "model/states/routes/Route.h"

class AbstractRouteFactory{
public:
    virtual ~AbstractRouteFactory() = 0;
    virtual Route generate() = 0;
    virtual Route crossover(Route &other) = 0;
    virtual Route mutate(Route &other) = 0;
};

#endif //CONTEST_ABSTRACTROUTEFACTORY_H
