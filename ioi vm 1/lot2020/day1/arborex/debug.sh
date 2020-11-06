g++ -DEVAL -std=gnu++11 -O2 -pipe -static -s -o _arborex grader.cpp arborex.cpp
time g++ -std=c++11 -g -DEVAL -pipe -fsanitize=undefined -fsanitize=address -fsanitize=signed-integer-overflow -lm -Wall -Wextra -Wpedantic -Wshadow -DXOX -O2 -o _arborex grader.cpp arborex.cpp
