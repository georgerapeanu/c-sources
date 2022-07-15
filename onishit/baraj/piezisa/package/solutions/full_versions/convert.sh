(echo "//"$1;cat $1 grader_concurent.cpp) | grep -v "piezisa.h" > $1.full_neparsat.cpp
(echo "//"$1;cat $1 grader_comisie.cpp) | grep -v "piezisa.h" > $1.full_parsat.cpp

