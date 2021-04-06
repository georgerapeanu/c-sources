#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e2;
const int MMAX = 1e5;

int n,m;
int first_viz[MMAX + 5];
int last_viz[MMAX + 5];

int t;
long long x;
int y;

int nxt(int t,long long x,long long value){
    if(t == 1){
        value *= 1e5;
        value += x + 1e5 - 1;
        value /= 1e5;
    }else{
        value = (value * x + 1e5 - 1) / 1e5;
    }
    value = min(value,m + 1LL);
    return value;
}

int main(){

    scanf("%d %d",&n,&m);

    for(int i = 1;i <= m;i++){
        first_viz[i] = last_viz[i] = -1;
    }

    for(int i = 1;i <= n;i++){
        scanf("%d %lld %d",&t,&x,&y);

        for(int j = m;j >= 0;j--){
            if(last_viz[j] == i - 1){
                for(int value = j,_y = y;value <= m && _y >= 0;value = nxt(t,x,value),_y--){
                    if(last_viz[value] == i){
                        break;
                    }
                    last_viz[value] = i;
                    if(first_viz[value] == -1){
                        first_viz[value] = i;
                    }
                }
            }
        }
    }

    for(int j = 1;j <= m;j++){
        printf("%d ",first_viz[j]);
    }

    return 0;
}
