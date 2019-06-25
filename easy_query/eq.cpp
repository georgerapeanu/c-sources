#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("eq.in","r");
FILE *g = fopen("eq.out","w");

const int NMAX = 1e5 + 1;
const int MMAX = 13e4 + 1;

struct node_t{
    int y,z;
    int mi,ma;
    int y_without_mi;
    int y_without_pl;
    int z_without_mi;
    int z_without_pl;

    node_t operator + (const node_t &other)const{
        
        if(this->y == -(1 << 27)){
            return other;
        }
        
        if(other.y == -(1 << 27)){
            return *this;
        }

        node_t ans;
        
        ans.y = max(this->y,other.y);
        ans.z = min(this->z,other.z);
        ans.y = max(ans.y,this->ma - other.mi + other.ma);
        ans.z = min(ans.z,this->mi - other.ma + other.mi);
        ans.y = max(ans.y,this->y_without_mi - other.mi);
        ans.y = max(ans.y,this->y_without_pl + other.ma);
        ans.z = min(ans.z,this->z_without_mi - other.ma);
        ans.z = min(ans.z,this->z_without_pl + other.mi);

        ans.y_without_mi = max(this->y_without_mi,other.y_without_mi);
        ans.y_without_mi = max(ans.y_without_mi,this->ma + other.ma);

        ans.y_without_pl = max(this->y_without_pl,other.y_without_pl);
        ans.y_without_pl = max(ans.y_without_pl,this->ma - other.mi);
        
        ans.z_without_mi = min(this->z_without_mi,other.z_without_mi);
        ans.z_without_mi = min(ans.z_without_mi,this->mi + other.mi);

        ans.z_without_pl = min(this->z_without_pl,other.z_without_pl);
        ans.z_without_pl = min(ans.z_without_pl,this->mi - other.ma);
        
        ans.mi = min(this->mi,other.mi);
        ans.ma = max(this->ma,other.ma);
        
        return ans;
    }
};

int n,q;
int x[NMAX + 5];
node_t aint[4 * NMAX + 5];

void build(int nod,int st,int dr){
    if(st == dr){
        aint[nod].y = x[st];
        aint[nod].z = x[st];
        aint[nod].ma = x[st];
        aint[nod].mi = x[st];
        aint[nod].y_without_pl = 0;
        aint[nod].y_without_mi = 2 * x[st];
        aint[nod].z_without_pl = 0;
        aint[nod].z_without_mi = 2 * x[st];
        return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);

    aint[nod] = aint[nod * 2] + aint[2 * nod + 1];
}

node_t query(int nod,int st,int dr,int S,int D){
    if(S <= st && dr <= D){
        return aint[nod];
    }
    if(dr < S || st > D){
        return {-(1 << 27),(1 << 27),(1 << 27),-(1 << 27),0,0,0,0};
    }

    int mid = (st + dr) / 2;

    return query(nod * 2,st,mid,S,D) + query(nod * 2 + 1,mid + 1,dr,S,D);
}

int main(){

    fscanf(f,"%d %d",&n,&q);

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d",&x[i]);
    }
    
    build(1,1,n);

    for(int i = 1;i <= q;i++){
        int l,r;
        fscanf(f,"%d %d",&l,&r);
        node_t tmp = query(1,1,n,l,r);
        fprintf(g,"%d\n",tmp.y + tmp.z);
    }

    fclose(f);
    fclose(g);

    return 0;    
}
