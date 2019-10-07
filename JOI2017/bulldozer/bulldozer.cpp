#include <cstdio>
#include <algorithm>

using namespace std;

struct point_t{
    int x,y,c;

    bool operator < (const point_t &other)const{
        if(y != other.y){
            return y < other.y;
        }
        return x < other.x;
    }
};

struct line_t{
    int a,b;
    int i,j;
};

struct node_t{
    long long pref_sum;
    long long suff_sum;
    long long best_sum;
    long long total_sum;

    node_t(long long a = 0LL){
        pref_sum = max(a,0LL);
        suff_sum = max(a,0LL);
        total_sum = a;
        best_sum = max(a,0LL);
    }

    node_t operator + (const node_t &other)const{
        node_t ans;
        ans.pref_sum = max(this->pref_sum,this->total_sum + other.pref_sum);
        ans.suff_sum = max(other.suff_sum,other.total_sum + this->suff_sum);
        ans.total_sum = this->total_sum + other.total_sum;
        ans.best_sum = max(max(this->best_sum,other.best_sum),this->suff_sum + other.pref_sum);
        return ans;
    }
};

int n;
point_t v[2005];
int pos[2005];
line_t lines[2000 * 2000 + 5];
node_t aint[8005];

void build(int nod,int st,int dr){

    if(st == dr){
        aint[nod] = node_t(v[st].c);
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
        aint[nod] = node_t(val);
        return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,pos,val);
    update(nod * 2 + 1,mid + 1,dr,pos,val);

    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
}

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d %d %d",&v[i].x,&v[i].y,&v[i].c);
    }

    sort(v + 1,v + 1 + n);

    int len = 0;

    for(int i = 1;i <= n;i++){
        for(int j = i + 1;j <= n;j++){
            lines[++len] = {v[j].x - v[i].x,v[j].y - v[i].y,i,j};
        }
    }

    sort(lines + 1,lines + 1 + len,
            [&](line_t &a,line_t & b){
                if(1LL * a.a * b.b != 1LL * b.a * a.b){
                    return 1LL * a.a * b.b > 1LL * b.a * a.b;
                }
                if(a.i != b.i){
                    return a.i < b.i;
                }
                return a.j < b.j;
             });

    for(int i = 1;i <= n;i++){
        pos[i] = i;
    }

    build(1,1,n);

    long long ans = aint[1].best_sum;

    for(int i = 1;i <= len;i++){
        swap(pos[lines[i].i],pos[lines[i].j]);
        update(1,1,n,pos[lines[i].i],v[lines[i].i].c);
        update(1,1,n,pos[lines[i].j],v[lines[i].j].c);
        if(i == len || (1LL * lines[i].a * lines[i + 1].b > 1LL * lines[i + 1].a * lines[i].b)){
            ans = max(ans,aint[1].best_sum);
        }
    }

    printf("%lld\n",ans);

    return 0;
}
