#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

FILE *f = fopen("agora.in","r");
FILE *g = fopen("agora.out","w");
//FILE *g2 = fopen("agora.ok","w");

int x,y,q;
int phi[7005];
bool p[7005];

int gcd(int a,int b){
    if(!b){
        return a;
    }

    return gcd(b,a % b);
}

vector<pair<int,int> > fact[7005];

vector< pair<int,int> > dublets;

int ans[100005];

struct query_t{
    int y,yy,x,id,sgn;
    bool operator < (const query_t &other)const{
        return x < other.x;
    }
};

void btr(int pas,int prod,int x){
    if(pas >= (int)fact[x].size()){
        int di = prod;
        int su = x * x / prod;
        if((su & 1) != (di & 1)){
            return ;
        }
        int y = (su - di) / 2;
        if(y < 0){
            y *= -1;
        }

        if(gcd(x,y) == 1 && y > 0 && y <= 7000){
            dublets.push_back({x,y});
        }
        return ;
    }

    for(int j = 0;j <= fact[x][pas].second;j++){
        btr(pas + 1,prod,x);
        prod *= fact[x][pas].first;
    }
}

vector<query_t> tmp;

int aib[7005];

void update(int pos,int val){
    for(;pos <= 7000;pos += (-pos) & pos){
        aib[pos] += val;
    }
}

int query(int pos){
    int sum = 0;
    for(;pos;pos -= (-pos) & pos){
        sum += aib[pos];
    }
    return sum;
}

int main(){
    for(int i = 2;i <= 7000;i++){
        if(p[i] == false){
            for(int j = i;j <= 7000;j += i){
                p[j] = true;
                int cj = j;
                int e = 0;
                while(cj % i == 0){
                    e += 2;
                    cj /= i;
                }
                fact[j].push_back({i,e});
            }
        }

        btr(0,1,i);
    }


    sort(dublets.begin(),dublets.end());
    dublets.resize(unique(dublets.begin(),dublets.end()) - dublets.begin());

    fscanf(f,"%d %d %d",&x,&y,&q);

    for(int i = 1;i <= q;i++){
        int x,y,xx,yy;
        fscanf(f,"%d %d %d %d",&x,&yy,&xx,&y);
        if(x > 0)tmp.push_back({y,yy,x - 1,i,-1});
        tmp.push_back({y,yy,xx,i,1});
    }

    sort(tmp.begin(),tmp.end());

    int ind = 0;

    for(auto it:tmp){
        while(ind < (int)dublets.size() && dublets[ind].first <= it.x){
            update(dublets[ind].second,1);
            ind++;
        }
        ans[it.id] += it.sgn * (query(it.yy) - (it.y > 0 ? query(it.y - 1):0));
    }

    for(int i = 1;i <= q;i++){
        fprintf(g,"%d\n",ans[i]);
    }

    return 0;
}
