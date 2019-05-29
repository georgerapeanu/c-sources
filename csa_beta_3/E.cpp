#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;

int n;
vector<int> graph[NMAX + 5];
char c[NMAX + 5];
bool expected_color[NMAX + 5];
long long cost[NMAX + 5];
long long delta[NMAX + 5];

long long dfs(int nod,int tata) {
    expected_color[nod] = 1 ^ expected_color[tata];
    delta[nod] = 0;
    cost[nod] = 0;

    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        dfs(it,nod);
        cost[nod] += abs(delta[it]) + cost[it];
        delta[nod] += delta[it];
    }
    char tmp = (expected_color[nod] == 0 ? 'R':'B');
    if(tmp == c[nod]);
    else if(tmp == 'R')delta[nod]++;
    else delta[nod]--;

    return (delta[nod] == 0 ? cost[nod]:-1);
}

int main() {

    scanf("%d\n",&n);
    fgets(c + 1,NMAX + 5,stdin);

    for(int i = 1; i < n; i++) {
        int x,y;
        scanf("%d %d\n",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    expected_color[0] = false;
    long long a = dfs(1,0);

    expected_color[0] = true;
    long long b = dfs(1,0);

    if(a == -1 && b == -1)printf("-1");
    else if(a != -1 && b != -1)printf("%lld",min(a,b));
    else printf("%lld\n",max(a,b));

    return 0;
}
