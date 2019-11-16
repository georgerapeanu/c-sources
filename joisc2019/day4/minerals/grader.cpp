#include "minerals.h"
#include <cstdio>
#include <cstdlib>
#include <algorithm>

constexpr int MAX_N = 43000;
constexpr int MAX_CALLS = 1000000;

namespace {

void WrongAnswer(int code) {
    printf("Wrong Answer [%d]\n", code);
    exit(0);
}

int N;
int counterpart[2 * MAX_N + 1];

int num_queries;
int num_kinds;
int on[2 * MAX_N + 1];
int count[2 * MAX_N + 1];

int num_answers;
int answer[2 * MAX_N + 1];

}  // namespace

int Query(int x) {
    if (!(1 <= x && x <= 2 * N)) {
        WrongAnswer(1);
    }
    if (++num_queries > MAX_CALLS) {
        WrongAnswer(2);
    }
    const int type = std::min(x, counterpart[x]);
    if (on[x]) {
        --on[x];
        --count[type];
        if (count[type] == 0) {
            --num_kinds;
        }
    } else {
        ++on[x];
        ++count[type];
        if (count[type] == 1) {
            ++num_kinds;
        }
    }
    return num_kinds;
}

void Answer(int a, int b) {
    if (++num_answers > N) {
        WrongAnswer(6);
    }
    if (!(1 <= a && a <= 2 * N && 1 <= b && b <= 2 * N)) {
        WrongAnswer(3);
    }
    if (answer[a] != 0) {
        WrongAnswer(4);
    }
    answer[a] = b;
    if (answer[b] != 0) {
        WrongAnswer(4);
    }
    answer[b] = a;
    if (!(counterpart[a] == b && counterpart[b] == a)) {
        WrongAnswer(5);
    }
}

int main() {
    if (scanf("%d", &N) != 1) {
        fprintf(stderr, "Error while reading input\n");
        exit(1);
    }
    for (int i = 1; i <= N; ++i) {
        int x, y;
        if (scanf("%d%d", &x, &y) != 2) {
            fprintf(stderr, "Error while reading input\n");
            exit(1);
        }
        counterpart[x] = y;
        counterpart[y] = x;
    }
    Solve(N);
    if (num_answers != N) {
        WrongAnswer(6);
    }
    printf("Accepted: %d\n", num_queries);
    return 0;
}
