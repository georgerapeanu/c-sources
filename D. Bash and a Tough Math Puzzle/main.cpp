#include <cstdio>
#include <algorithm>
using namespace std;
int N,Q;
int AINT[4 * 500000 + 5];
int gcd(int a,int b){
    if(!b)return a;
    return gcd(b,a % b);
}
void build(int nod,int st,int dr){
    if(st == dr){
        scanf("%d",&AINT[nod]);
        return ;
    }
    int mid = (st + dr) / 2;
    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);
    AINT[nod] = gcd(AINT[2 * nod],AINT[2 * nod + 1]);
}
void u(int nod,int st,int dr,int pos,int val){
    if(pos > dr || pos < st){
        return ;
    }
    if(st == dr){
        AINT[nod] = val;
        return ;
    }
    int mid = (st + dr) / 2;
    u(nod * 2,st,mid,pos,val);
    u(nod * 2 + 1,mid + 1,dr,pos,val);
    AINT[nod] = gcd(AINT[2 * nod],AINT[2 * nod + 1]);
}
vector<pair<int,pair<int,int> > > V;
void q(int nod,int st,int dr,int S,int D,int X){
    if(dr < S || D < st){
        return ;
    }
    if(S <= st && dr <= D){
        if(AINT[nod] % X != 0){
            V.push_back({nod,{st,dr}});
        }
        return ;
    }
    int mid = (st + dr) / 2;
    q(nod * 2,st,mid,S,D,X);
    q(nod * 2 + 1,mid + 1,dr,S,D,X);
}
bool check(int nod,int st,int dr,int X){
    if(st == dr){
        return 1;
    }
    int mid = (st + dr) / 2;
    if(AINT[2 * nod] % X != 0 && AINT[2 * nod + 1] % X != 0){
        return 0;
    }
    if(AINT[2 * nod] % X != 0){
        return check(nod * 2,st,mid,X);
    }
    return check(nod * 2 + 1,mid + 1,dr,X);
}
int main()
{
    scanf("%d",&N);
    build(1,1,N);
    scanf("%d",&Q);
    while(Q--){
        int op,l,r,x;
        scanf("%d",&op);
        if(op == 2){
            scanf("%d %d",&l,&x);
            u(1,1,N,l,x);
        }
        else{
            scanf("%d %d %d",&l,&r,&x);
            V.clear();
            q(1,1,N,l,r,x);
            if(V.empty()){
                printf("YES\n");
            }
            else if((int)V.size() > 1){
                printf("NO\n");
            }
            else{
                bool ok = check(V[0].first,V[0].second.first,V[0].second.second,x);
                if(ok){
                    printf("YES\n");
                }
                else{
                    printf("NO\n");
                }
            }
        }
    }
    return 0;
}
