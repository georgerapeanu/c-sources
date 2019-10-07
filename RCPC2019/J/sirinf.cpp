#include <fstream>
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

ifstream f("sirinf.in");
ofstream g("sirinf.out");

const int NMAX = 1e6;

int t;
string s;
int z[2 * NMAX + 5];

int main() {

    f >> t;

    while(t--) {

        f >> s;

        int n = s.size();

        s = " " + s + s;

        z[1] = (int)s.size() - 1;
        z[2] = 0;
        for(int i = 2; i < (int)s.size(); i++) {
            z[i] = max(0,min(z[2],z[i - 1] - 1));
            while(i + z[i] < (int)s.size() && s[1 + z[i]] == s[i + z[i]]) {
                z[i]++;
            }
        }

        int ans = 1;

        for(int i = 2; i <= n; i++) {
            if(i + z[i] < (int)s.size() && s[i + z[i]] < s[1 + z[i]]) {
                ans++;
            }
        }

        g << ans << "\n";

    }

    f.close();
    g.close();

    return 0;
}
