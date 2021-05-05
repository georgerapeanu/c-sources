g++ -std=c++11 -O0 -o $1 -Wall -Wextra -Wpedantic -g -fsanitize=address,undefined,signed-integer-overflow $1.cpp grader.cpp
