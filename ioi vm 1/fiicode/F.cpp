#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

struct phone_t{
    int x,y,p;
    int id;

    phone_t(){
        x = 0;
        y = 0;
        p = 0;
        id = 0;
    }

    phone_t operator + (const phone_t &other)const{
        if(x < other.x && y < other.y){
            return other;
        }
        if(x > other.x && y > other.y){
            return *this;
        }
        return (p < other.p ? *this:other);
    }
};

struct node_t{
    phone_t best;
    phone_t best_left;
    int max_y;
};

const int NMAX = 1e5;

int n,m;
map<int,int> to_norm;

node_t aint[4 * 2 * NMAX + 5];

phone_t recalc(int nod,int st,int dr,int y){
    if(st == dr){
        if(y >= aint[nod].best.y){
            return phone_t();
        }
        return aint[nod].best;
    }
    int mid = (st + dr) / 2;
    if(aint[nod * 2 + 1].max_y <= y){
        return recalc(nod * 2,st,mid,y);
    }
    else{
        return aint[nod].best_left + recalc(nod * 2 + 1,mid + 1,dr,y);   
    }
}

void update(int nod,int st,int dr,int pos,phone_t phone){
    if(dr < pos || st > pos){
        return ;
    }
    
    if(st == dr){
        aint[nod].best = phone;
        aint[nod].best_left = phone_t();
        aint[nod].max_y = phone.y;
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,pos,phone);
    update(nod * 2 + 1,mid + 1,dr,pos,phone);
    
    aint[nod].max_y = max(aint[nod * 2].max_y,aint[nod * 2 + 1].max_y);
    aint[nod].best_left = recalc(nod * 2,st,mid,aint[nod * 2 + 1].max_y);
    aint[nod].best = aint[nod].best_left + aint[nod * 2 + 1].best;


}

int main(){

    scanf("%d %d",&n,&m);

    vector<phone_t> phones;

    for(int i = 1;i <= n + m;i++){
        phone_t tmp;
        scanf("%d %d %d",&tmp.x,&tmp.y,&tmp.p);
        tmp.id = i;
        phones.push_back(tmp);
        to_norm[tmp.x] = 1;
    }

    int lst = 0;

    for(auto &it:to_norm){
        it.second = ++lst;
    }

    for(auto &it:phones){
        it.x = to_norm[it.x];
    }

    for(int i = 0;i < n;i++){
        update(1,1,lst,phones[i].x,phones[i]);
    }

    for(int i = 1;i <= m;i++){
        printf("%d\n",aint[1].best.id);
        update(1,1,lst,aint[1].best.x,phone_t());
        update(1,1,lst,phones[n + i - 1].x,phones[n + i - 1]);
    }

    return 0;
}
