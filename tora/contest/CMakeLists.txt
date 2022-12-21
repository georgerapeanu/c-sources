cmake_minimum_required(VERSION 3.23)
project(contest)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(include/models)
include_directories(include/models/states)
include_directories(include/models/states/ships)
include_directories(include/models/factories)
include_directories(include/models/game_rules)
include_directories(include/models/states/game)
include_directories(include/models/states/routes)
include_directories(include/models/states/planets)
include_directories(include/models/states/solutions)

add_executable(contest
            main.cpp
        include/model/game_rules/GameRules.h include/model/states/game/AbstractGame.h include/model/states/game/Level1Game.h include/model/states/ships/Ship.h include/model/states/routes/Route.h include/model/states/moves/Move.h include/model/states/solutions/Solution.h include/model/states/game/Level2Game.h include/model/states/game/Level3Game.h include/model/states/planets/Planet.h include/model/factories/routes/AbstractRouteFactory.h)
