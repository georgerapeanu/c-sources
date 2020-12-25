#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "nice_lines.h"

namespace {
    const int __MAX_N = 100;

    int __subtask_id;
    int __n, __qmax, __qmin;
    int __queries;
    int __a[__MAX_N];
    int __b[__MAX_N];

    // Print score to stdout and exit.
    void score_and_exit(const double pts, const char *verdict) {
        fprintf(stderr, "Verdict = %s\n", verdict);
        fprintf(stdout, "Score = %lf\n", pts);
        exit(0);
    }

    long double compute_query(long double x, long double y) {
        long double dist = 0;
        for(int i = 0;i < __n;i++){
            dist += fabs(__a[i] * x - y + __b[i]) / sqrt(1LL * __a[i] * __a[i] + 1);
        }
        return dist; // You can compute the distance...
        // or read it from the input...
        printf("query(%Lf, %Lf) = ", x, y);
        fflush(stdout);
        long double answer;
        assert(scanf("%Lf", &answer) == 1);
        return answer;
    }
    
    double score(int q) {
        if (q > __qmax) {
            return 0;
        } else if (q <= __qmin) {
            return 1;
        } else {
            return 1.0 - 0.7 * double(q - __qmin) / double(__qmax - __qmin);
        }
    }

    void wrongQueryFormat() {
        score_and_exit(0, "Invalid parameters supplied as query!");
    }

    void accepted(double pts) {
        score_and_exit(pts, "Is it OK?");
    }

    void readTest() {
        assert(scanf("%d", &__subtask_id) == 1);
        assert(scanf("%d%d%d", &__n, &__qmax, &__qmin) == 3);
        for (int i = 0; i < __n; i++) {
            assert(scanf("%d%d", &__a[i], &__b[i]) == 2);
        }
    }
}

long double query(long double x, long double y) {
    __queries++;
    if (__queries > __qmax) {
        score_and_exit(0, "Too many queries!");
    }
    if (!isfinite(x) || !isfinite(y)
            || fabs(x) > 1e12 || fabs(y) > 1e12) {
        fprintf(stderr, "x = %Lf, y = %Lf, ", x, y);
        wrongQueryFormat();
    }
    return compute_query(x, y);
}

void the_lines_are(std::vector<int> a, std::vector<int> b) {
    assert(__n == (int)a.size() && a.size() == b.size());
    printf("Your answer is:\n");
    for (int i = 0; i < __n; i++) {
        printf("a[%d] = %d, b[%d] = %d\n", i, a[i], i, b[i]);
    }
    printf("Number of queries is: %d\n", __queries);
    accepted(score(__queries));
}

int main() {
    readTest();
    solve(__subtask_id, __n);
    return 0;
}
