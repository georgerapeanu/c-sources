#include <cstdio>
#include <cstdlib>
#include "xylophone.h"

static const int N_MAX = 5000;
static const int Q_MAX = 10000;
static int N;
static int A[N_MAX];
static bool used[N_MAX];
static int query_c;
static int answer_c;

int query(int s, int t) {
    if(query_c >= Q_MAX) {
        printf("Wrong Answer\n");
        exit(0);
    }
    query_c++;
    if(!(1 <= s && s <= t && t <= N)) {
        printf("Wrong Answer\n");
        exit(0);
    }
    int mx = 0, mn = N + 1;
    for(int i = s - 1; i < t; i++) {
        if(mx < A[i]) {
            mx = A[i];
        }
        if(mn > A[i]) {
            mn = A[i];
        }
    }
    return mx - mn;
}

void answer(int i, int a) {
    answer_c++;
    if(!(1 <= i && i <= N)) {
        printf("Wrong Answer\n");
        exit(0);
    }
    if(!(1 <= a && a <= N)) {
        printf("Wrong Answer\n");
        exit(0);
    }
    if(used[i - 1]) {
        printf("Wrong Answer\n");
        exit(0);
    }
    if(a != A[i - 1]) {
        printf("Wrong Answer\n");
        exit(0);
    }
    used[i - 1] = true;
}

int main() {
    query_c = 0;
    answer_c = 0;
    if(scanf("%d", &N) != 1) {
        fprintf(stderr, "Error while reading input\n");
        exit(1);
    }
    for(int i = 0; i < N; i++) {
        if(scanf("%d", A + i) != 1) {
            fprintf(stderr, "Error while reading input\n");
            exit(1);
        }
        used[i] = false;
    }
    solve(N);
    if(!(answer_c == N)) {
        printf("Wrong Answer\n");
        exit(0);
    }
    printf("Accepted : %d\n", query_c);
}
