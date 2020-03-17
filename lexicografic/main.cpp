#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("lexicografic.in","r");
FILE *g = fopen("lexicografic.out","w");

const int NMAX = 250000;

struct node_t{
    pair<int,int> data;
    int active;

    node_t operator + (const node_t &other){
        node_t ans;
        ans.data = min(this->data,other.data);
        ans.active = this->active + other.active;
        return ans;
    }
};

node_t aint[4 * NMAX + 5];

void build(int nod,int st,int dr){
    if(st == dr){
        fscanf(f,"%d",&aint[nod].data.first);
        aint[nod].data.second = st;
        aint[nod].active = 1;
        return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

void deactivate(int nod,int st,int dr,const pair<int,int> &data,long long &active_left){
    if(st == dr){
        aint[nod].active = 0;
        aint[nod].data = {1e9,1e9};
        return ;
    }

    int mid = (st + dr) / 2;

    if(data.second <= mid){
        deactivate(nod * 2,st,mid,data,active_left);
    }
    else{
        active_left -= aint[nod * 2].active;
        deactivate(nod * 2 + 1,mid + 1,dr,data,active_left);
    }

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

pair<int,int> query(int nod,int st,int dr,long long cnt_active){
    if(cnt_active <= 0){
        return {1e9,1e9};
    }
    if(aint[nod].active <= cnt_active){
        return aint[nod].data;
    }
    int mid = (st + dr) / 2;
    return min(query(nod * 2,st,mid,cnt_active),query(nod * 2 + 1,mid + 1,dr,cnt_active - aint[nod * 2].active));
}

void afis(int nod,int st,int dr){
    if(st == dr){
        if(aint[nod].active == 1){
            fprintf(g,"%d ",aint[nod].data.first);
        }
        return ;
    }

    int mid = (st + dr) / 2;

    afis(nod * 2,st,mid);
    afis(nod * 2 + 1,mid + 1,dr);
}

int t;
int n;
long long k;

int main(){

    fscanf(f,"%d",&t);

    while(t--){
        fscanf(f,"%d %lld",&n,&k);
        build(1,1,n);
        while(k > 0 && aint[1].active > 0){
            pair<int,int> tmp = query(1,1,n,k + 1);
            fprintf(g,"%d ",tmp.first);
            deactivate(1,1,n,tmp,k);
        }

        afis(1,1,n);

        fprintf(g,"\n");
    }

    fclose(f);
    fclose(g);

    return 0;
}
