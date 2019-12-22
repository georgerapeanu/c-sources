#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const int NMAX = 1e6;

int n;

vector<int> graph[NMAX + 5];
int coef[NMAX + 5];

int main() {

    scanf("%d",&n);

    for(int i = 0; i < n; i++) {
        int fa;
        scanf("%d",&fa);
        if(fa > -1) {
            graph[fa].push_back(i);
        }
    }

    for(int i = 0; i < n; i++) {
        scanf("%d",&coef[i]);
    }

    priority_queue<pair<int,int> > pq;

    pq.push({coef[0],0});

    while(!pq.empty()) {
        pair<int,int> tmp = pq.top();
        pq.pop();
        printf("%d ",tmp.second);

        for(auto it:graph[tmp.second]) {
            pq.push({coef[it],it});
        }
    }

    return 0;
}
