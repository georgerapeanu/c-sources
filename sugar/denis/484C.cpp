#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#include <deque>

using namespace std;

const int NMAX = 1e6;

char c[NMAX + 5];
char nc[NMAX + 5];

int perm[NMAX + 5];
int tmp[NMAX + 5];
int wut[NMAX + 5];

vector<int> graph[NMAX + 5];

bool on_path[NMAX + 5];

int main() {

    fgets(c + 1,NMAX + 5,stdin);

    int n = strlen(c + 1);
    n = n - (c[n] == '\n');

    int q;

    scanf("%d",&q);

    while(q--) {
        int k,d;
        scanf("%d %d",&k,&d);
        int last = 1;
        for(int i = 1; i <= k; i++) {
            graph[i].clear();
            tmp[i] = last;
            last += d;
            on_path[i] = false;
            if(last > k) {
                last = last % d + 1;
            }
        }
        for(int i = 0; i < k; i++) {
            perm[tmp[i + 1]] = i;
        }
        deque<int> path;
        for(int nod = k; nod; nod = perm[nod]) {
            path.push_front(nod);
            on_path[nod] = true;
        }
        vector<int> pos;
        deque<int> init_path = path;
        for(int i = 1; i <= n - k; i++) {
            pos.push_back(path.front());
            path.pop_front();
            path.push_back(i + k);
        }

        for(int i = 0; i < (int)path.size(); i++) {
            wut[init_path[i]] = path[i];
        }

        for(int i = 1; i <= k; i++) {
            if(on_path[i] == false) {
                vector<int> cycle;
                for(int nod = i; on_path[nod] == false; nod = perm[nod]) {
                    on_path[nod] = true;
                    cycle.push_back(nod);
                }
                for(int i = 0; i < (int)cycle.size(); i++) {
                    wut[cycle[(i + (n - k)) % (int)cycle.size()]] = cycle[i];
                }
            }
        }

        for(int i = 1; i <= k; i++) {
            pos.push_back(wut[i]);
        }

        for(int i = 1; i <= n; i++) {
            nc[i] = c[pos[i - 1]];
        }

        for(int i = 1; i <= n; i++) {
            c[i] = nc[i];
        }

        for(int i = 1; i <= n; i++) {
            c[i] = nc[i];
        }

        for(int i = 1; i <= k; i++) {
            perm[tmp[i]] = i;
        }

        for(int i = 1; i <= k; i++) {
            nc[n - k + perm[i]] = c[n - k + i];
        }

        for(int i = 1; i <= n; i++) {
            c[i] = nc[i];
        }

        fputs(c + 1,stdout);

    }

    return 0;
}
