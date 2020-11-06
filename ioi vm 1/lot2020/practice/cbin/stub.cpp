#include <cstdio>
#include <cstdlib>
#include "cbin.h"

bool query(const int &number) {
    printf("Query: %d\n", number);
    int x;
    scanf("%d", &x);
    if(x == -1) exit(0);
    return x;
}

void answer(const int &ans) {
    printf("Answer: %d\n", ans);
    exit(0);
}

int main() {
    int N;
    scanf("%d", &N);
    solve(N);
	return 0;
}