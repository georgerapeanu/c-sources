#include "pswap.h"
#include <iostream>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector< vector<int> > p(n,vector<int>(m,0));
    for (int i = 0; i < n; i++)	{
        for (int j = 0; j < m; j++) {
            cin >> p[i][j];
        }
    }

    int result = solve(n, m, p);

    printf("%d\n", result);
    return 0;
}
