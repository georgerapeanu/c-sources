#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#include "makebipartite.h"

int main() {

    int T;
    scanf("%d", &T);
    for(int t = 0; t < T; t++) {
        int N, M;
        scanf("%d%d", &N, &M);
        int* X = (int*)malloc(sizeof(int) * M);
        int* Y = (int*)malloc(sizeof(int) * M);
        char* S = (char*)malloc(sizeof(char) * (N + 1));
        S[N] = '\0';
        for(int i = 0; i < M; i++) {
            int x, y;
            scanf("%d%d", &x, &y);
            X[i] = x; Y[i] = y;
        }
        solve(N, M, X, Y, S);
        free(X); free(Y);
        printf("%s\n", S);
        free(S);
    }

    return 0;
}
