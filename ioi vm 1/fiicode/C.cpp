#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

const int MMAX = 1e5;
const int inf = 1e9;

struct train_t{
    int l,r,t;

    bool operator < (const train_t &other)const{
        if(t - l != other.t - other.l){
            return t - l < other.t - other.l;
        }
        if(l != other.l){
            return l < other.l;
        }
        if(r != other.r){
            return r < other.r;
        }
        return t < other.t;
    }
};

int n,m,t;
vector<train_t> trains;

map<int,int> to_norm;

int aint[4 * 2 * MMAX + 5];

void build(int nod,int st,int dr){
    aint[nod] = inf;
    if(st == dr){
        return;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);
}

void update(int nod,int st,int dr,int pos,int val){
    if(dr < pos || st > pos){
        return ;
    }

    if(st == dr){
        aint[nod] = min(aint[nod],val);
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,pos,val);
    update(nod * 2 + 1,mid + 1,dr,pos,val);

    aint[nod] = min(aint[nod * 2],aint[nod * 2 + 1]);
}

int query(int nod,int st,int dr,int l,int r){
    if(r < st || l > dr){
        return inf;
    }

    if(l <= st && dr <= r){
        return aint[nod];
    }

    int mid = (st + dr) / 2;

    return min(query(nod * 2,st,mid,l,r),query(nod * 2 + 1,mid + 1,dr,l,r));
}

int main(){

    scanf("%d %d %d",&n,&m,&t);

    if(n == 1){
        printf("0\n");
        return 0;
    }

    for(int i = 1;i <= m;i++){
        train_t tmp;
        scanf("%d %d %d",&tmp.l,&tmp.r,&tmp.t);
        to_norm[tmp.l] = 1;
        to_norm[tmp.r] = 1;
        trains.push_back(tmp);
    }

    int lst = 0;

    for(auto &it:to_norm){
        it.second = ++lst;
    }

    build(1,1,lst);

    sort(trains.begin(),trains.end());

    int ans = inf;

    for(auto it:trains){
        if(it.l <= 1 && 1 <= it.r){
            update(1,1,lst,to_norm[it.r],1);
//            printf("adding1 %d %d %d with %d at %d\n",it.l,it.r,it.t,1,it.r);
            if(it.r == n && it.r - it.l + it.t <= t){
//                printf("deb %d %d %d\n",it.l,it.r,it.t);
                ans = min(ans,1);
            }
        }
        else{
            int tmp = query(1,1,lst,to_norm[it.l],to_norm[it.r]);
            if(tmp != inf){
                update(1,1,lst,to_norm[it.r],1 + tmp);
//                printf("adding2 %d %d %d with %d at %d\n",it.l,it.r,it.t,1 + tmp,it.r);
                if(it.r == n && it.r - it.l + it.t <= t){
                    ans = min(ans,1 + tmp);
//                    printf("deb %d %d %d\n",it.l,it.r,it.t);
                }
            }
        }
    }

    if(ans == inf){
        ans = -1;
    }

    printf("%d\n",ans);

    return 0;
}
