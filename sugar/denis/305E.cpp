#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int NMAX = 5e3;

int n;
char c[NMAX + 5];

int sg[NMAX + 5];
int fr[NMAX + 5];

vector<pair<int,int> > lengths;

int main() {

    sg[1] = 1;

    for(int i = 2; i <= NMAX; i++) {
        memset(fr,0,sizeof(fr));
        fr[sg[i - 2]] = 1;

        for(int x = 2; x < i; x++) {
            fr[sg[x - 2] ^ sg[i - x - 1]] = 1;
        }

        while(fr[sg[i]] == 1) {
            sg[i]++;
        }
    }

    fgets(c + 1,NMAX + 5,stdin);

    n = strlen(c + 1);
    n -= (c[n] == '\n');

    int xo = 0;

    int len = 0;

    for(int i = 2; i < n; i++) {
        if(c[i - 1] == c[i + 1]) {
            len++;
        }
        else {
            xo ^= sg[len];
            if(len) {
                lengths.push_back({len,i - len});
            }
            len = 0;
        }
    }

    xo ^= sg[len];

    if(len) {
        lengths.push_back({len,n - len});
    }

    printf((xo == 0 ? "Second\n":"First\n"));

    if(xo != 0) {
        for(auto it:lengths) {
            int target_xo = xo ^ sg[it.first];
            if(it.first == 1 && target_xo == 0) {
                printf("%d\n",it.second);
                return 0;
            }
            if(sg[it.first - 2] == target_xo) {
                printf("%d\n",it.second);
                return 0;
            }

            for(int x = 2; x < it.first; x++) {
                if((sg[x - 2] ^ sg[it.first - x - 1]) == target_xo) {
                    printf("%d\n",it.second + x - 1);
                    return 0;
                }
            }
        }
    }

    return 0;
}
