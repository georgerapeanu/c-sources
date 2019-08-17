#include <cstdio>

using namespace std;

FILE *f = fopen("namlei.in","r");
FILE *g = fopen("namlei.out","w");

const int NMAX = 3e4;
const int MOD = 997;

int n,k;
int x,y;

struct matrix_t{
    int n,m;
    int a[8][8];

    matrix_t operator * (const matrix_t &other)const{
        matrix_t ans;
        ans.n = this->n;
        ans.m = other.m;

        for(int i = 0;i < ans.n;i++){
            for(int j = 0;j < ans.m;j++){
                ans.a[i][j] = 0;
                for(int k = 0;k < this->m;k++){
                    ans.a[i][j] = (ans.a[i][j] + this->a[i][k] * other.a[k][j]) % MOD;
                }
            }
        }

        return ans;
    }
};

matrix_t aint[4 * NMAX + 5];
matrix_t base;
matrix_t v[NMAX + 5];

void build(int nod,int st,int dr){
    if(st == dr){
        aint[nod] = v[st];
        return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);

    aint[nod] = aint[nod * 2] * aint[nod * 2 + 1];
}

void update(int nod,int st,int dr,int pos,const matrix_t &val){
    if(dr < pos || st > pos){
        return;
    }

    if(st == dr){
        aint[nod] = val;
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,pos,val);
    update(nod * 2 + 1,mid + 1,dr,pos,val);

    aint[nod] = aint[nod * 2] * aint[nod * 2 + 1];
}

matrix_t query(int nod,int st,int dr,int l,int r){
    if(l <= st && dr <= r){
        return aint[nod];
    }
    
    int mid = (st + dr) / 2;
    
    if(r <= mid){
        return query(nod * 2,st,mid,l,r);
    }
    else if(l > mid){
        return query(nod * 2 + 1,mid + 1,dr,l,r);
    }
    else{
        return query(nod * 2,st,mid,l,r) * query(nod * 2 + 1,mid + 1,dr,l,r);
    }
}
int main(){
    fscanf(f,"%d %d",&n,&k);
    fscanf(f,"%d %d",&x,&y);

    x %= k;y %= k;

    base.n = base.m = k;
    for(int i = 0;i < k;i++)for(int j = 0;j < k;j++)base.a[i][j] = 1;

    for(int i = 1;i <= n;i++){
        v[i] = base;
        int cnt,j,l;
        fscanf(f,"%d %d %d",&cnt,&j,&l);
        for(int w = 1;w <= cnt;w++){
            v[i].a[j][l]++;
            int jp,lp;
            jp = (j * x + l * (w) * y) % k;
            lp = (j * x * (w) + l * y) % k;
            j = jp;
            l = lp;
        }
    }

    build(1,1,n);

    char t;

    fscanf(f,"\n");
    while(fscanf(f,"%c",&t) == 1){
        if(t == 'U'){
            int i,cnt,j,l;
            fscanf(f,"%d %d %d %d\n",&i,&cnt,&j,&l);
            i++;
            v[i] = base;
            for(int w = 1;w <= cnt;w++){
                v[i].a[j][l]++;
                int jp,lp;
                jp = (1LL * j * x + 1LL * l * (w) * y + 1) % k;
                lp = (1LL * j * x * (w) + 1LL * l * y +  1) % k;
                j = jp;
                l = lp;
            }
            update(1,1,n,i,v[i]);
        }
        else{
            int i,j,a,b;
            fscanf(f,"%d %d %d %d\n",&i,&a,&j,&b);
            i++;
            j++;
            fprintf(g,"%d\n",query(1,1,n,i,j - 1).a[a][b]);
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
