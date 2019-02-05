#ifndef __GRADER_CPP__
#define __GRADER_CPP__

#include "graderlib.cpp"
#include "icc.h"

int main() {
    using namespace ceoi_2016;
    InitGrader();

    run(NumVertices());

    GraderExitFail();
    return 0;
}

#endif // __GRADER_CPP__
