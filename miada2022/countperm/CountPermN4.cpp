#include<fstream>
#include <iostream>
using namespace std;
ifstream in ("countperm.in");
ofstream out ("countperm.out");
long long v[10000],n,nr;
const int modulo = 1e9 + 7;
int main (void) {
    in >> n;
    for (int i = 1; i <= n; i ++) {
        in >> v[i];
    }
    for (int a = 1; a <= n; a ++) {
        for (int b = a+1; b <= n; b ++) {
            for (int c = b+1; c <= n; c ++) {
                for (int d = c+1; d <= n; d ++) {
                    if (v[c] < v[a]  &&  v[d] < v[b] && v[a] < v[d]) {
                        nr = (nr + 1) % modulo;
                    }
                }
            }
        }
    }
    out << nr << "\n";
    return 0;
}
