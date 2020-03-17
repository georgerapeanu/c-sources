#include <cstdio>

FILE *g = fopen("magic4.out","w");

int val[] = {65535, 21845, 13107, 4369, 3855, 1285, 771, 257, 255, 85, 51, 17, 15, 5, 3, 1};

int main() {

    fprintf(g,"0\n");

    for(int i = 1; i < (1 << 16); i++) {
        fprintf(g,"%d\n",val[__builtin_ctz(i)]);
    }

    fclose(g);

    return 0;
}
