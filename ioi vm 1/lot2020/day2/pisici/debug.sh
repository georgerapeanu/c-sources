time g++ -std=c++11 -g -DEVAL -pipe -fsanitize=undefined -fsanitize=address -fsanitize=signed-integer-overflow -lm -Wall -Wextra -Wpedantic -Wshadow -DXOX -O2 -o _pisici grader.cpp pisici.cpp
