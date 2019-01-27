#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 3e5;

int n,a;

long long max_cost[NMAX + 5];
int left[NMAX + 5];
int right[NMAX + 5];
int st[NMAX + 5],len;

int profit[NMAX + 5];

struct node_t{
    long long pref_sum;
    long long suf_sum;
    long long best_sum;
    long long wholesum;
};

node_t aint[4 * NMAX + 5];

node_t join(node_t left,node_t right){
    node_t ans;
    ans.wholesum = left.wholesum + right.wholesum;
    ans.pref_sum = max(left.pref_sum,right.pref_sum + left.wholesum);
    ans.suf_sum = max(right.suf_sum,left.suf_sum + right.wholesum);
    ans.best_sum = max(left.suf_sum + right.pref_sum,max(left.best_sum,right.best_sum));
    return ans;
}

void build(int nod,int st,int dr){
    if(st == dr){
        aint[nod] = {profit[st],profit[st],profit[st],profit[st]};
        return ;
    }

    int mid = (st + dr) / 2;
    build(2 * nod,st,mid);
    build(2 * nod + 1,mid + 1,dr);

    aint[nod] = join(aint[2 * nod],aint[2 * nod + 1]);
}

node_t query(int nod,int st,int dr,int S,int D){
    if(dr < S || st > D){
        return {0,0,0,0};
    }
    if(S <= st && dr <= D){
        return aint[nod];
    }
    int mid = (st + dr) / 2;
    return join(query(2 * nod,st,mid,S,D),query(2 * nod + 1,mid + 1,dr,S,D));
}

long long best_sum(int l,int r){
    return query(1,1,n,l,r).best_sum;
}

int main(){

    scanf("%d %d",&n,&a);

    for(int i = 1;i <= n;i++){
        scanf("%lld %d",&max_cost[i],&profit[i]);
        profit[i] = a - profit[i];
    }

    long long ans = 0;

    for(int i = 1;i <= n;i++){
        ans = max(ans,1LL * profit[i]);
    }

    for(int i = 1;i < n;i++){
        max_cost[i] -= max_cost[i + 1];
        max_cost[i] = 1LL * max_cost[i] * max_cost[i];
    }

    for(int i = 1;i < n;i++){
        while(len && max_cost[st[len]] <= max_cost[i]){
            len--;
        }
        left[i] = st[len];
        st[++len] = i;
    }

    st[0] = n;
    len = 0;

    for(int i = n - 1;i;i--){
        while(len && max_cost[st[len]] < max_cost[i]){
            len--;
        }
        right[i] = st[len];
        st[++len] = i;
    }

    build(1,1,n);

    for(int i = 1;i < n;i++){
        int l = left[i] + 1;
        int r = right[i];
        ans = max(ans,best_sum(l,r) - max_cost[i]);
    }

    printf("%lld",ans);

    return 0;
}
