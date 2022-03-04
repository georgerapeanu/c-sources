g++ $1.cpp stub-comisie.cpp -O0 -g -fsanitize=address,undefined,signed-integer-overflow -o _$1
