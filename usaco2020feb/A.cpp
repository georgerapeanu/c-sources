#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 2e5;
const int QMAX = 2e5;


int n,q;
int v[NMAX + 5];
int last[NMAX + 5];
vector<pair<int,int>> queries[NMAX + 5];
int ans[QMAX + 5];
int st[NMAX + 5];
int len;

int aib[NMAX + 5];

void update(int pos,int val){
    for(;pos <= n;pos += (-pos) & pos){
        aib[pos] += val;
    }
}

int query(int pos){
    int ans = 0;
    for(;pos;pos -= (-pos) & pos){
        ans += aib[pos];
    }
    return ans;
}

int main(){

    scanf("%d %d",&n,&q);

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);
    }

    for(int i = 1;i <= q;i++){
        int l,r;
        scanf("%d %d",&l,&r);

        queries[r].push_back({l,i});
    }

    len = 0;
    for(int i = 1;i <= n;i++){
        while(len > 0 && v[st[len]] > v[i]){
            len--;
        }
        if(len > 0 && st[len] <= last[v[i]]){
            update(last[v[i]],-1); 
        }
        st[++len] = i;
        last[v[i]] = i;
        update(i,1);

        for(auto it:queries[i]){
            ans[it.second] = query(i) - query(it.first - 1);
        }
    }

    for(int i = 1;i <= q;i++){
        printf("%d\n",ans[i]);
    }


    return 0;
}
