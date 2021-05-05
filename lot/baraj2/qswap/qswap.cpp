#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e6;

int n;
int p[NMAX + 5];
int aib[NMAX + 5];

int min_suff[NMAX + 5];
int max_pref[NMAX + 5];


void update(int pos,int val){
    for(;pos;pos -= (-pos) & pos){
        aib[pos] += val;
    }
}

int query(int pos){
    int ans = 0;

    for(;pos <= n;pos += (-pos) & pos){
        ans += aib[pos];
    }

    return ans;
}

void reset_aib(){
    for(int i = 1;i <= n;i++){
        aib[i] = 0;
    }
}

class SegmentTree{
    int n;
    vector<int> aint;
    vector<int> lazy;

    void propag(int nod,int st,int dr){
        if(lazy[nod] == 0 || st == dr){
            return ;
        }

        lazy[nod * 2] += lazy[nod];
        aint[nod * 2] += lazy[nod];
        lazy[nod * 2 + 1] += lazy[nod];
        aint[nod * 2 + 1] += lazy[nod];
        
        lazy[nod] = 0;
    }

    void update_add(int nod,int st,int dr,int l,int r,int value){
        propag(nod,st,dr);
        if(dr < l || st > r){
            return ;
        }

        if(l <= st && dr <= r){
            aint[nod] += value;
            lazy[nod] += value;
            return ;
        }

        int mid = (st + dr) / 2;

        update_add(nod * 2,st,mid,l,r,value);
        update_add(nod * 2 + 1,mid + 1,dr,l,r,value);

        aint[nod] = max(aint[nod * 2],aint[nod * 2 + 1]);
    }

    void update_set(int nod,int st,int dr,int pos,int value){
        propag(nod,st,dr);

        if(dr < pos || st > pos){
            return ;
        }

        if(st == dr){
            aint[nod] = value;
            return ;
        }

        int mid = (st + dr) / 2;

        update_set(nod * 2,st,mid,pos,value);
        update_set(nod * 2 + 1,mid + 1,dr,pos,value);

        aint[nod] = max(aint[nod * 2],aint[nod * 2 + 1]);
    }

    int query(int nod,int st,int dr,int l,int r){
        propag(nod,st,dr);

        if(r < st || l > dr){
            return -1e9;
        }

        if(l <= st && dr <= r){
            return aint[nod];
        }

        int mid = (st + dr) / 2;

        return max(query(nod * 2,st,mid,l,r),query(nod * 2 + 1,mid + 1,dr,l,r));
    }


public:

    SegmentTree(int n){
        this->n = n;
        this->aint = vector<int>(4 * n + 5,-1e9);
        this->lazy = vector<int>(4 * n + 5,0);
    }

    void update(int pos){
        printf("update %d\n",pos);
        if(pos < 1){
            return ;
        }
        update_add(1,1,n,1,pos,1);
    }

    void activate(int pos){
        printf("activate %d\n",pos);
        update_set(1,1,n,pos,0);
    }

    int query(int l,int r){
        int tmp = query(1,1,n,l,r);
        printf("query %d %d is %d\n",l,r,tmp);
        return tmp;
    }
};

int main(){

    scanf("%d",&n);

    long long cnt_inv = 0;

    for(int i = 1;i <= n;i++){
        scanf("%d",&p[i]);
        cnt_inv += query(p[i]);
        update(p[i],1);
    }


    min_suff[n] = p[n];
    max_pref[1] = p[1];

    for(int i = n - 1;i >= 1;i--){
        min_suff[i] = min(p[i],min_suff[i + 1]);
    }
    for(int i = 2;i <= n;i++){
        max_pref[i] = max(p[i],max_pref[i - 1]);
    }

    long long ans = cnt_inv;
    int best_reduction = 0;

    SegmentTree aint(n);


    
    ans -= 2 * best_reduction;

    printf("%lld\n",ans);

    return 0;
}
