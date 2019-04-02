#include <stdio.h>
#include "artclass.h"

static int DIM[2];
static int R[500][500];
static int G[500][500];
static int B[500][500];

int main() {
    FILE *in = fopen("artclass.txt", "r");
    if(in == NULL) {
        puts("Failed to open input file (artclass.txt).");
        return 0;
    }
    
    if(fscanf(in, "%d%d", DIM, DIM+1) != 2) {
        printf("Line 1: H, W must be integers\n");
        return 0;
    }
    if(DIM[0] < 100 || 500 < DIM[0]) {
        printf("Line 1: 100 <= H <= 500\n");
        return 0;
    }
    if(DIM[1] < 100 || 500 < DIM[1]) {
        printf("Line 1: 100 <= W <= 500\n");
        return 0;
    }
    for(int i = 0; i< DIM[0]; i++) {
       for(int j = 0; j < DIM[1]; j++) {
           if(fscanf(in, "%d%d%d", &R[i][j], &G[i][j], &B[i][j]) != 3) {
               printf("Line %d: R[i][j], G[i][j], B[i][j] must be integers", i*DIM[1]+j+2, i, j);
               return 0;
           }
           if(R[i][j] < 0 || 255 < R[i][j]) {
               printf("Line %d: 0 <= R[%d][%d] <= 255", i*DIM[1]+j+2, i, j);
               return 0;
           }
           if(G[i][j] < 0 || 255 < G[i][j]) {
               printf("Line %d: 0 <= G[%d][%d] <= 255", i*DIM[1]+j+2, i, j);
               return 0;
           }
           if(B[i][j] < 0 || 255 < B[i][j]) {
               printf("Line %d: 0 <= B[%d][%d] <= 255", i*DIM[1]+j+2, i, j);
               return 0;
           }
       }
    }
    
    printf("%d\n", style(DIM[0], DIM[1], R, G, B));
    return 0;
}
