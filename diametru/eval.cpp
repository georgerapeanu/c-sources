#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <cstring>

using namespace std;

FILE *f = fopen("diametru.out","r");

int n,m;
vector<int> graph[505];
int viz[505];

int find_best(int nod,set<pair<int,int> > &stuff) {
    vector<int> qu = {nod};
    viz[nod] = 1;

    int ans = 0;

    for(int i = 0; i < (int)qu.size(); i++) {
        for(auto it:graph[qu[i]]) {
            if(viz[it] == 0) {
                viz[it] = 1 + viz[qu[i]];
                qu.push_back(it);
            }
        }
    }

    for(int i = 1; i <= n; i++) {
        if(stuff.count({nod,i}) == 0 && viz[i] > viz[ans]) {
            ans = i;
        }
    }

    return ans;
}

int main() {

    int target;

    scanf("%d",&target);

    fscanf(f,"%d %d",&n,&m);

    for(int i = 1; i <= m; i++) {
        int a,b;
        fscanf(f,"%d %d",&a,&b);
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    set<pair<int,int> > stuff;
    int curr = 1;
    int ans = -1;
    int cnt = 0;

    while(ans != target) {
        printf("doing %d %d %d\n",cnt,curr,ans);
        memset(viz,0,sizeof(viz));
        int tmp = find_best(curr,stuff);
        ans = viz[tmp] - 1;
        stuff.insert({curr,tmp});
        stuff.insert({tmp,curr});
        curr = tmp;
        cnt++;
    }

    printf("doing %d %d %d\n",cnt,curr,ans);
    printf("ans is %d",cnt);

    fclose(f);

    return 0;
}
