#include <cstdio>
#include <vector>
#include <algorithm>
#include <deque>
#include <map>

using namespace std;

const int NMAX = 4e5;
const int LGMAX = 18;
const int QMAX = 4e5;

int n;
int q;
int v[NMAX + 5];
pair<long long,int> pref[NMAX + 5];
int nxt[NMAX + 5];
int ant[NMAX + 5];

int skip[NMAX + 5];

struct query_t{
    int l,r;
    int ans;
}queries[QMAX + 5];

///i cant belive that i have to reuse arrays to not get MLE.
///congrats. awesome problem.

void compute_skiplist_at(int h){
    for(int i = 1;i <= n;i++){
        nxt[i] = skip[i];
    } 

    for(int j = 1;j <= h;j++){
        for(int i = 1;i <= n;i++){
            ant[i] = nxt[i];
        }
        for(int i = 1;i <= n;i++){
            nxt[i] = ant[ant[i]];
        }
    }
}

int main(){

    freopen("sumzero.in","r",stdin);
    freopen("sumzero.out","w",stdout);

    scanf("%d",&n);

    ant[0] = -1;
    pref[0].first = 0;
    pref[0].second = 0;
    for(int i = 1;i <= n;i++){
        ant[i] = -1;
        scanf("%d",&v[i]);
        pref[i].first = v[i] + pref[i - 1].first;
        pref[i].second = i;
    }

    sort(pref,pref + 1 + n);
    for(int i = 1;i <= n;i++){
        if(pref[i - 1].first == pref[i].first){
            int x = pref[i - 1].second;
            int y = pref[i].second;
            nxt[x] = y;
            ant[y] = x;
        }
    }


    deque<int> dq;

    for(int i = 0;i <= n;i++){
        if(ant[i] != -1){
            while(dq.empty() == false && dq.front() < ant[i]){
                dq.pop_front();
            }
            if(dq.empty() == false && dq.front() == ant[i]){
                skip[ant[i] + 1] = i + 1;
                dq.pop_front();
            }
        }
        if(nxt[i]){
            dq.push_back(i);
        }
    }

    for(int i = n - 1;i;i--){
        if(skip[i] == 0){
            skip[i] = skip[i + 1];
        }
    }

    scanf("%d",&q);

    for(int i = 1;i <= q;i++){
        scanf("%d %d",&queries[i].l,&queries[i].r);
        queries[i].ans = 0;
    }

    ant[0] = 0;
    for(int h = LGMAX;h >= 0;h--){
        compute_skiplist_at(h);
        for(auto &it:queries){
            if(nxt[it.l] <= it.r + 1 && nxt[it.l] != 0){
                it.ans |= (1 << h);
                it.l = nxt[it.l];
            }
        }
    }

    for(int i = 1;i <= q;i++){
        printf("%d\n",queries[i].ans);
    }


    return 0;
}
