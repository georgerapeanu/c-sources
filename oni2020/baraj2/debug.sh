g++ -DEVAL -std=gnu++11 -O0 -pipe -g -fsanitize=address,undefined,signed-integer-overflow -s -o pswap grader.cpp pswap.cpp
