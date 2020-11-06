#include "Anthony.h"
#include "Catherine.h"
#include <cstdio>
#include <cstdlib>
#include <random>
#include <utility>
#include <vector>

namespace {

using std::atoll;
using std::exit;
using std::fprintf;
using std::printf;
using std::scanf;
using std::vector;

void WrongAnswer(int code) {
  printf("Wrong Answer [%d]\n", code);
  exit(0);
}

}  // namespace

int main(int argc, char **argv) {
  long long seed = 0;
  if (argc >= 2) {
    seed = atoll(argv[1]);
  }
  std::mt19937 rng(seed);

  // input
  int N, M, A, B, S;
  if (scanf("%d%d%d%d%d", &N, &M, &A, &B, &S) != 5) {
    fprintf(stderr, "Error while reading input.\n");
    exit(1);
  }
  vector<int> U(M), V(M);
  for (int i = 0; i < M; ++i) {
    if (scanf("%d%d", &U[i], &V[i]) != 2) {
      fprintf(stderr, "Error while reading input.\n");
      exit(1);
    }
  }

  // Anthony
  const vector<int> x = Mark(N, M, A, B, U, V);
  if (x.size() != static_cast<size_t>(M)) {
    WrongAnswer(1);
  }
  for (int i = 0; i < M; ++i) {
    if (!(0 <= x[i] && x[i] <= A - 1)) {
      WrongAnswer(2);
    }
  }

  vector<vector<vector<int>>> adjacent_towns(N, vector<vector<int>>(A));
  for (int i = 0; i < M; ++i) {
    adjacent_towns[U[i]][x[i]].push_back(V[i]);
    adjacent_towns[V[i]][x[i]].push_back(U[i]);
  }

  // Catherine
  Init(A, B);
  int num_moves = 0;
  int last_town = -1, current_town = S;
  for (; current_town != 0; ) {
    if (num_moves >= N + B) {
      printf("Wrong Answer; Number of moves > N + B\n");
      exit(0);
    }
    vector<int> y(A, 0);
    vector<vector<int>> next_towns(A);
    for (int j = 0; j < A; ++j) {
      for (const int next_town : adjacent_towns[current_town][j]) {
        if (next_town != last_town) {
          ++y[j];
          next_towns[j].push_back(next_town);
        }
      }
    }
    const int z = Move(y);
    ++num_moves;
    if (!(-1 <= z && z <= A - 1)) {
      WrongAnswer(3);
    }
    if (last_town == -1 && z == -1) {
      WrongAnswer(4);
    }
    if (0 <= z && z <= A - 1 && y[z] == 0) {
      WrongAnswer(5);
    }
    if (z == -1) {
      std::swap(last_town, current_town);
    } else {
      last_town = current_town;
      current_town =
          next_towns[z][std::uniform_int_distribution<int>(0, y[z] - 1)(rng)];
    }
  }

  printf("Number of moves = %d\n", num_moves);
  return 0;
}
