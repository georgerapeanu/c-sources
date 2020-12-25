#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "mex2d.h"

int** allocMatrix(int n1, int n2) {
    int** a = (int**)malloc(sizeof(int*) * n1 + sizeof(int) * n1 * n2);
    int* ptr = (int*)(a + n1);
    for (int i1 = 0; i1 < n1; ++i1) {
        a[i1] = ptr;
        ptr += n2;
    }
    return a;
}

int main() {
    FILE* f = fopen("input.txt", "r");
    int n1, n2;
    assert(fscanf(f, "%d%d", &n1, &n2) == 2);

    int** a = allocMatrix(n1, n2);
    for (int i1 = 0; i1 < n1; ++i1) {
        for (int i2 = 0; i2 < n2; ++i2) {
            assert(fscanf(f, "%d", a[i1] + i2) == 1);
        }
    }
    fclose(f);

    int** b = allocMatrix(n1, n2);
    solve(n1, n2, a, b);
    free(a);

    f = fopen("output.txt", "w");
    for (int i1 = 0; i1 < n1; ++i1) {
        for (int i2 = 0; i2 < n2; ++i2) {
            fprintf(f, "%d%c", b[i1][i2], " \n"[i2 == n2 - 1]);
        }
    }
    free(b);
    fclose(f);
    return 0;
}
