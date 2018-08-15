#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 2e5;
const int BUCK_SIZE = 400;
int N,Q;
int V[200005];
long long AIB[200005];

void u(int x,int val){
    for(;x <= N;x += (-x) & x){
        AIB[x] += val;
    }
}

long long q(int x){
    long long S = 0;
    for(;x;x -= (-x) & x){
        S += AIB[x];
    }
    return S;
}

int find_pos(long long sum){
    int pos = 0;
    long long S = 0;
    for(int step = 1 << 20;step;step >>= 1){
        if(pos + step <= N && S + AIB[pos + step] < sum){
            pos += step;
            S += AIB[pos];
        }
    }

    return pos;
}

int exist(){
    long long sum = 0;
    int pos = 0;
    while(pos < N){
        if(sum == V[pos + 1]){
            return pos + 1;
        }
        pos++;
        sum += V[pos];
        pos = find_pos(2 * sum);
        sum = q(pos);
    }
    return -1;
}

int main(){
    V[0] = -1;
    scanf("%d %d",&N,&Q);
    for(int i = 1;i <= N;i++){
        scanf("%d",&V[i]);
        u(i,V[i]);
    }

    for(int i = 1;i <= Q;i++){
        int p,x;
        scanf("%d %d",&p,&x);
        u(p,x - V[p]);
        V[p] = x;
        printf("%d\n",exist());
    }
    return 0;
}
