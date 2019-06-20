#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

FILE *f = fopen("tri.in","r");
FILE *g = fopen("tri.out","w");

const int NMAX = 1e4;

int n;
pair<int,int> vertex[4];
pair<int,int> point[NMAX + 5];

int order_a[NMAX + 5];
int order_b[NMAX + 5];
int order_c[NMAX + 5];

int inv_a[NMAX + 5];
int inv_b[NMAX + 5];
int inv_c[NMAX + 5];

long long det(pair<int,int> a,pair<int,int> b,pair<int,int> c){
    return 1LL * a.first * (b.second - c.second) + 1LL * b.first * (c.second - a.second) + 1LL * c.first * (a.second - b.second);
}

bool cmp(int a,int b){
    return det(vertex[0],point[a],point[b]) > 0;
}

class AIB{
    int n;
    int active;
    int aib[NMAX + 5];

public:

    AIB(int n){
        this->n = n;
        active = 0;
        memset(aib,0,sizeof(aib));
    }
    
    void add(int pos){
        active++;
        for(;pos <= n;pos += (-pos) & pos){
            aib[pos]++;
        }
    }

    void rem(int pos){
        active--;
        for(;pos;pos <= n;pos += (-pos) & pos){
            aib[pos]--;
        }
    }

    int get_kth(int k){

        if(active < k){
            return -1;
        }

        int sum = 0;
        int pos = 0;
        
        for(int h = (1 << 14);h;h >>= 1){
            if((pos ^ h) <= NMAX && sum + aib[pos ^ h] < k){
                pos ^= h;
                sum += aib[pos];
            }
        }
        
        return pos + 1;
    }
};

int main(){

    for(int i = 1;i <= 3;i++){
        fscanf(f,"%d %d",&vertex[i].first,&vertex[i].second);
    }

    fscanf(f,"%d",&n);

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d %d",&point[i].first,&points[i].second);
        order_a[i] = i;
        order_b[i] = i;
        order_c[i] = i;
    }

    vertex[0] = vertex[1];
    sort(order_a + 1,order_a + 1 + n,cmp);

    vertex[0] = vertex[2];
    sort(order_b + 1,order_b + 1 + n,cmp);

    vertex[0] = vertex[3];
    sort(order_c + 1,order_c + 1 + n,cmp);
    reverse(order_c + 1,order_c + 1 + n,cmp);

    for(int i = 1;i <= n;i++){
        inv_a[order_a[i]] = i;
        inv_b[order_b[i]] = i;
        inv_c[order_c[i]] = i;
    }
    
    AIB a_aib(n);
    AIB c_aib(n);

    for(int i = 1;i <= n;i++){
        c_aib.add(i);
    }

    for(int i = 1;i <= n;i++){
        ///try to do it with point on C side
        int lc = c_aib.get_kth();
        ///try to do it with G = point[order_b[i]]
        ///try to do it with point on A side
    }

    fclose(f);
    fclose(g);

    return 0;
}
