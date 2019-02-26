#ifndef __HOMECOMING_H
#define __HOMECOMING_H
#include <cstdio>
#include <cassert>
#include <algorithm>

using namespace std;

const int NMAX = 2e6;
const int KMAX = 2e6;

int n;
long long dp[NMAX + 5][2];
long long prefA[NMAX + 5];
long long prefB[NMAX + 5];
long long prefdelta[NMAX + 5];

int A[NMAX + 5];
int B[NMAX + 5];

long long sum(int l,int r,long long pref[]) {
    if(l <= r) {
        return pref[r] - pref[l - 1];
    }
    return pref[n] - pref[l - 1] + pref[r];
}

long long solve(int N, int K, int *AA, int *BB) {

    for(int i = 1; i <= N; i++) {
        A[i] = AA[i - 1];
        B[i] = BB[i - 1];
    }

    n = N;
    for(int i = 1; i <= N; i++) {
        prefA[i] = prefA[i - 1] + A[i];
        prefB[i] = prefB[i - 1] + B[i];
        prefdelta[i] = A[i] - B[i] + prefdelta[i - 1];
    }

    dp[1][1] = A[1]  - sum(1,K,prefB);

    long long mi = prefdelta[1] - dp[1][0],pos = 1;

    for(int i = 2; i <= N; i++) {
        dp[i][0] = max(dp[i - 1][0], A[i] + (-sum(i,(i + K - 2) % N + 1,prefB)) + (prefdelta[i - 1] - mi));
        if(prefdelta[i] - dp[i][0] < mi) {
            mi = prefdelta[i] - dp[i][0];
            pos = i;
        }
    }

    for(int i = 1; i <= K; i++) {
        B[i] = 0;
    }

    for(int i = 1; i <= N; i++) {
        prefA[i] = prefA[i - 1] + A[i];
        prefB[i] = prefB[i - 1] + B[i];
        prefdelta[i] = A[i] - B[i] + prefdelta[i - 1];
    }

    mi = prefdelta[1] - dp[1][1];
    pos = 1;

    for(int i = 2; i <= N; i++) {
        dp[i][1] = max(dp[i - 1][1], A[i] + (-sum(i,(i + K - 2) % N + 1,prefB)) + (prefdelta[i - 1] - mi));
        if(prefdelta[i] - dp[i][1] < mi) {
            mi = prefdelta[i] - dp[i][1];
            pos = i;
        }
    }

    return max(dp[N][1],dp[N][0]);
}
/*
int main() {
  int T; assert(scanf("%d", &T) == 1);
  for(int t = 0; t < T; t++) {
    int N, K; assert(scanf("%d%d", &N, &K) == 2);
    int *A = new int[N];
    int *B = new int[N];
    for(int i = 0; i < N; i++) assert(scanf("%d", &A[i]) == 1);
    for(int i = 0; i < N; i++) assert(scanf("%d", &B[i]) == 1);
    printf("%lld\n", solve(N, K, A, B));
    delete[] A;
    delete[] B;
  }
  return 0;
}*/
#endif
