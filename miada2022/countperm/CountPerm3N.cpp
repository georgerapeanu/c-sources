#include<fstream>
using namespace std;
ifstream in ("countperm.in");
ofstream out ("countperm.out");
long long n,sum,mat[4005][4005], v[4005];
const int modulo = 1e9 +7;
int main (void) {
    in >> n;
    for (int i = 1; i <= n; i ++) {
        in >> v[i];
        mat[i][v[i]] = 1;
    }

    for (int i = 1; i <= n; i ++) {
        for (int j = 1; j <= n; j ++) {
            mat[i][j] += mat[i-1][j] + mat[i][j-1] - mat[i-1][j-1];
        }
    }

    for (int a = 1; a <= n; a ++) {
        for (int b = a+1; b <= n; b ++) {
            for (int c = b+1; c <= n; c ++) {
                if (v[c] < v[a] && v[a] < v[b]) {
                    sum = (sum + mat[n][v[b]-1] - mat[n][v[a]] - mat[c][v[b]-1] + mat[c][v[a]]) % modulo;
                }
            }
        }
    }

    out << sum;
    return 0;
}

