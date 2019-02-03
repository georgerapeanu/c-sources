#include <cstdio>
#include <vector>

using namespace std;

const int NMAX = 2.5e5;

int n,m,k;
vector<int> graph[NMAX + 5];
int lvl[NMAX + 5];
int father[NMAX + 5];
bool leaf[NMAX + 5];
int viz[NMAX + 5];

void dfs(int nod,int tata) {
    lvl[nod] = 1 + lvl[tata];
    father[nod] = tata;
    viz[nod] = true;

    leaf[nod] = true;

    for(auto it:graph[nod]) {
        if(it == tata || viz[it] == true) {
            continue;
        }
        dfs(it,nod);
        leaf[nod] = false;
    }
}

int main() {

    scanf("%d %d %d",&n,&m,&k);

    for(int i = 1; i <= m; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    dfs(1,0);

    for(int i = 1; i <= n; i++) {
        if(1LL * lvl[i] * k >= n) {
            printf("PATH\n%d\n",lvl[i]);
            for(int nod = i; nod; nod = father[nod]) {
                printf("%d ",nod);
            }
            return 0;
        }
    }

    printf("CYCLES\n");

    for(int i = 1; i <= n; i++) {
        if(leaf[i] == true && k > 0) {
            k--;
            int x = graph[i][0];
            int y = graph[i][1];

            if(lvl[x] > lvl[y]) {
                swap(x,y);
            }

            for(int j = 2; j < (int)graph[i].size(); j++) {
                int it = graph[i][j];
                if(lvl[it] < lvl[x]) {
                    y = x;
                    x = it;
                }
                else if(lvl[it] < lvl[y]) {
                    y = it;
                }
            }

            if(lvl[i] - lvl[x] + 1 >= 3 && (lvl[i] - lvl[x] + 1) % 3 != 0) {
                printf("%d\n",lvl[i] - lvl[x] + 1);
                for(int nod = i; nod != father[x]; nod = father[nod]) {
                    printf("%d ",nod);
                }
                printf("\n");
            }
            else if(lvl[i] - lvl[y] + 1 >= 3 && (lvl[i] - lvl[y] + 1) % 3 != 0) {
                printf("%d\n",lvl[i] - lvl[y] + 1);
                for(int nod = i; nod != father[y]; nod = father[nod]) {
                    printf("%d ",nod);
                }
                printf("\n");
            }
            else {
                printf("%d\n",lvl[y] - lvl[x] + 2);
                for(int nod = y; nod != father[x]; nod = father[nod]) {
                    printf("%d ",nod);
                }
                printf("%d\n",i);
            }
        }
    }

    return 0;
}
