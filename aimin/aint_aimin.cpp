#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("aimin.in","r");
FILE *g = fopen("aimin.out","w");

const int NMAX = 2e5;
const int LMAX = 1e8;


int n;
int sz;
int height[NMAX + 5];
int st[NMAX + 5];
int dr[NMAX + 5];
pair<int,int> aint[2 * NMAX + 5];

void build(int sz){
    for(int i = 1;i <= sz;i++){
        aint[i + sz - 1] = {max(height[i + 1],height[i]),i};
    }
    for(int i = sz - 1;i;i--){
        aint[i] = min(aint[2 * i],aint[2 * i + 1]);
    }
}

void update(int pos,pair<int,int> val){
    for(aint[pos += sz - 1] = val;pos > 1;pos >>= 1){
        aint[pos >> 1] = min(aint[pos],aint[pos ^ 1]);
    }
}

int main(){

    fscanf(f,"%d",&n);
    
    for(int i = 1;i <= n;i++){
        fscanf(f,"%d",&height[i]);
    }

    sz = 1;
    while(sz < n){
        sz *= 2;
    }

    for(int i = n + 1;i <= sz + 1;i++){
        height[i] = (1 << 28);
    }

    for(int i = 1;i <= sz + 1;i++){
        st[i] = i;
        dr[i] = i;
    }

    build(sz);

    for(int i = 1;i < n;i++){
        int lvl = aint[1].first;
        int pos = aint[1].second;

        update(dr[pos] + 1,{(1 << 28),dr[pos] + 1});
        dr[pos] = dr[dr[pos] + 1];
        st[dr[pos]] = pos;
        height[pos] = lvl + 1;
        update(pos,{(1 << 28),pos});

        if(pos > 1){
            update(st[pos - 1],{max(height[pos],height[st[pos - 1]]),st[pos - 1]});
        }
        if(dr[pos] < n){
            update(pos,{max(height[pos],height[dr[pos] + 1]),pos});
        }
    }

    fprintf(g,"%d\n",height[1]);

    fclose(f);
    fclose(g);

    return 0;
}
