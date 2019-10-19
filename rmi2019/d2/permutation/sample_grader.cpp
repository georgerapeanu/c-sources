#include <bits/stdc++.h>
#include "permutation.h"

using namespace std;

namespace A {
  int N;
  const int MAX_N = 1000;
  int P[1 + MAX_N];
  int queries = 0;
  
  void readInput() {
    //printf("The permutation you have to guess is:\n");
    scanf("%d", &N);
    for (int i = 1; i <= N; i++) {
      scanf("%d", &P[i]);
      //printf("%d ", P[i]);
    }
    //printf("\n");
  }
  
  int query(int V[]) {
    queries++;
    printf("query(");
    for (int i = 0; i < N - 1; i++) {
      printf("%d, ", V[i]);
    }
    printf("%d) = ", V[N - 1]);
    int freq[1 + N];
    for (int i = 0; i <= N; i++) {
      freq[i] = 0;
    }
    for (int i = 0; i < N; i++) {
      freq[V[i]]++;
    }
    for (int i = 1; i <= N; i++) {
      assert(freq[i] == 1);
    }
		int answer = 0;
    for (int i = 0; i + 1 < N; i++) {
      answer += abs(P[V[i + 1]] - P[V[i]]);
    }
    printf("%d\n", answer);
    fflush(stdout);
		return answer;
	}

	void answer(int V[]) {
    bool ok = true;
    for (int i = 1; i <= N; i++) {
      ok &= (V[i - 1] == P[i]);
    }
    if (ok) {
      printf("Correct! with N = %d, Q = %d\n", N, queries);
    } else {
        bool ok = true;
        for(int i = 1;i <= N;i++){
            ok &= (V[i - 1] == N + 1 - P[i]);
        }
        if(ok){
            printf("Correct! with N = %d, Q = %d\n", N, queries);
        }
        else
          printf("Wrong answer!\n");
    }
		exit(0);
	}
}

int query(int p[]) {
	return A::query(p);
}

void answer(int ans[]) {
  A::answer(ans);
}

int query(std::vector<int> v) {
  int array[A::N];
  for (int i = 0; i < A::N; i++) {
    array[i] = v[i];
  }
  return query(array);
}

void answer(std::vector<int> v) {
  int array[A::N];
  for (int i = 0; i < A::N; i++) {
    array[i] = v[i];
  }
  answer(array);
}

int main(int argc, char **argv) {
  A::readInput();
  solve(A::N);
  return 0;
}
