#include <cstdio>

using namespace std;

const int NMAX = 3000;

int n,m;
bool adj[NMAX + 5][NMAX + 5];
bool del[NMAX + 5];

int main() {

    scanf("%d %d",&n,&m);

    for(int i = 1; i <= m; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        adj[x][y] = true;
        adj[y][x] = true;;
    }

    for(int i = 1; i <= n; i++) {
        if(del[i] == true) {
            continue;
        }
        for(int j = i + 1; j <= n; j++) {
            if(del[j] == true) {
                continue;
            }
            if(adj[i][j] == false) {
                del[i] = del[j] = true;
                break;
            }
        }
    }

    for(int i = 1,cnt = 0; i <= n && cnt < n / 3; i++) {
        if(del[i] == false) {
            printf("%d ",i);
            cnt++;
        }
    }


    return 0;
}
