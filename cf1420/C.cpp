#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;

struct node_t{
    long long even_low;
    long long even_high;
    long long odd_low;
    long long odd_high;

    node_t operator + (const node_t &other)const{
        node_t ans;
        ans.even_low = min(min(this->even_low,other.even_low),min(this->even_low + other.even_low,this->odd_low - other.odd_high));
        ans.even_high = max(max(this->even_high,other.even_high),max(this->even_high + other.even_high,this->odd_high - other.odd_low));
        ans.odd_low = min(min(this->odd_low,other.odd_low),min(this->even_low + other.odd_low,this->odd_low - other.even_high));
        ans.odd_high = max(max(this->odd_high,other.odd_high),max(this->even_high + other.odd_high,this->odd_high - other.even_low));
        return ans;
    }
};

int t,n,q;
node_t aint[4 * NMAX + 5];
int v[NMAX + 5];

void build(int nod,int st,int dr){
    if(st == dr){
        aint[nod] = {0,0,v[st],v[st]};
        return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

void update(int nod,int st,int dr,int pos,int val){
    if(dr < pos || st > pos){
        return ;
    }

    if(st == dr){
        aint[nod] = {0,0,val,val};
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,pos,val);
    update(nod * 2 + 1,mid + 1,dr,pos,val);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d %d",&n,&q);
        for(int i = 1;i <= n;i++){
            scanf("%d",&v[i]);
        }
        build(1,1,n);
        printf("%lld\n",max(max(aint[1].even_low,aint[1].even_high),max(aint[1].odd_low,aint[1].odd_high)));
        while(q--){
            int l,r;
            scanf("%d %d",&l,&r);
            swap(v[l],v[r]);
            update(1,1,n,l,v[l]);
            update(1,1,n,r,v[r]);
            printf("%lld\n",max(max(aint[1].even_low,aint[1].even_high),max(aint[1].odd_low,aint[1].odd_high)));
        }
    }

    return 0;
}
