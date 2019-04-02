#include <stdio.h>
#include "artclass.h"

static int DIM[2];
static int R[500][500];
static int G[500][500];
static int B[500][500];

#ifdef __cplusplus
extern "C" {
#endif

void __grader_init(int dim[2],
        int r[500][500], int g[500][500], int b[500][500]);

#ifdef __cplusplus
}
#endif

int main() {
    __grader_init(DIM, R, G, B);
    printf("%d\n", style(DIM[0], DIM[1], R, G, B));
    return 0;
}
