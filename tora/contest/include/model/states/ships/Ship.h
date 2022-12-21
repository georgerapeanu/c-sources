//
// Created by georgerapeanu on 27.11.2022.
//

#ifndef CONTEST_SHIP_H
#define CONTEST_SHIP_H
#include <vector>

class Ship{
    std::vector<int> spending;
public:
    Ship();
    ~Ship();
    long double getSpeed();
    int getStrength();
    int getCargoCapacity();
    long double getDrillingSpeed();
};

#endif //CONTEST_SHIP_H
