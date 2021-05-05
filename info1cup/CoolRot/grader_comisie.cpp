#include <cstdio>
#include <bitset>
#include <cstdlib>
#include <cassert>
#include "coolrot.h"

// This grader will read the data from stdin and print to stdout.
// the number of positions the array will be rotated with.
// If at some point, the user does an illegal move, the grader will return -1 and stop.
// This checks if the input is valid.

/*

test format:

n q
a[0] a[1] ... a[n - 1]
m[0] ds[0] ds[1] ... ds[m[0] - 1]
m[1] ds[0] ds[1] ... ds[m[1] - 1]
...
m[q - 1] ds[0] ds[1] ... ds[m[q - 1] - 1]

*/

// Original problem constraints
static const int MAX_N = 100000;
static const int MAX_Q = 100000;
static const int MAX_M = 400;
static const int MAX_SUM = 2000000;

// n from the original problem
static int n;

// The number of rotations at the end of a query
static int rot;

// The initial array
static int a[MAX_N];

// The query operations
static int ds[MAX_M];

// legal[i] = Moves with d = i are legal
static std::bitset<1+MAX_N> legal;

// Used for checking if the initial array is a permutation aka check
// if the array contains duplicates
static std::bitset<MAX_N> marked;

// Rotate the array with d * x positions
void update(int d, int x) {
    // Check if the move's d is legal
    if(!legal[d]) {
        fprintf(stderr, "This move is illegal: %d\n", d);
        printf("-1\n");
        exit(0);
    }
    // Check if the move's x is legal
    if(!(0 < x && x < n / d)) {
        fprintf(stderr, "This move is out of bounds: %d\n", x);
        printf("-1\n");
        exit(0);
    }

    rot = (rot + d * x) % n;
}

int main() {
    int q;
    scanf("%d%d", &n, &q);
    
    // Check problem constraints
    assert(1 <= n && n <= MAX_N);
    assert(1 <= q && q <= MAX_Q);

    for(int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);

        // Check if the array is a permutation
        assert(0 <= a[i] && a[i] < MAX_N);
        assert(!marked[a[i]]);
        marked[a[i]] = true;
    }

    // Initialize the solution
    init(n, a, q);

    int summ = 0;
    for(int i = 0; i < q; ++i) {
        int m;
        scanf("%d", &m);
        summ += m;
        rot = 0;

        // Check if the sum of m's respect the problem's restrictions
        assert(summ <= MAX_SUM);
        
        // Read a query's set of moves
        for(int i = 0; i < m; ++i) {
            scanf("%d", &ds[i]);

            // Check if the moves are divisors of n
            assert(ds[i] != 0 && ds[i] < n && n % ds[i] == 0);
            legal[ds[i]] = true;
        }

        // Send the query to the participant
        query(m, ds);

        // Illegalise all moves from this query
        for(int i = 0; i < m; ++i)
            legal[ds[i]] = false;
    
        // Display the number of rotations
        printf("%d\n", rot);
    }
    return 0;
}


