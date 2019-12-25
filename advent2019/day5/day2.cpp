#include <cstdio>
#include <cassert>

using namespace std;

int v[int(1e6 + 5)];

int main(int argc,char **argv) {

    assert(argc == 3);

    int fst = (argv[1][0] - '0') * (argv[1][1] >= '0' && argv[1][1] <= '9' ? 10:1) + (argv[1][1] <= '9' && argv[1][1] >= '0') * (argv[1][1] - '0' );
    int snd = (argv[2][0] - '0') * (argv[2][1] >= '0' && argv[2][1] <= '9' ? 10:1) + (argv[2][1] <= '9' && argv[2][1] >= '0') * (argv[2][1] - '0' );

    int n = 0;

    while(scanf("%d,",&v[n]) == 1) {
        n++;
    }

    int start = 0;

    v[1] = fst;
    v[2] = snd;

    while(start <= n) {
        if(v[start] == 99) {
            break;
        }
        else if(v[start] == 1) {
            v[v[start + 3]] = v[v[start + 1]] + v[v[start + 2]];
            start += 4;
        }
        else if(v[start] == 2) {
            v[v[start + 3]] = v[v[start + 1]] * v[v[start + 2]];
            start += 4;
        }
        else {
            ///dunno
        }
    }

    printf("%d\n",v[0]);

    return 0;
}
