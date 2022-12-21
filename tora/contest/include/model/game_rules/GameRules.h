//
// Created by georgerapeanu on 27.11.2022.
//

#ifndef CONTEST_GAMERULES_H
#define CONTEST_GAMERULES_H
class GameRules{
public:
    static long double getDefaultMovementSpeed();
    static long double getIncrementMovementSpeed();
    static int getDefaultStrength();
    static int getIncrementStrength();
    static int getDefaultCargo();
    static int getIncrementCargo();
    static int getDefaultDrillingSpeed();
    static int getIncrementDrillingSpeed();
    static int getTimeLimit();
};
#endif //CONTEST_GAMERULES_H
