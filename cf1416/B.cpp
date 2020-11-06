#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e4;

int t;
int n;
int a[NMAX + 5];

struct data_t{
    int i,j,x;
};

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d",&n);
        int s = 0;
        for(int i = 1;i <= n;i++){
            scanf("%d",&a[i]);
            s += a[i];
        }
        if(s % n != 0){
            printf("-1\n");
            continue;
        }
        s /= n;

        vector<data_t> op;

        for(int i = 2;i <= n;i++){
            if(a[i] % i != 0){
                op.push_back({1,i,i - (a[i] % i)});
                a[i] += (i - (a[i] % i));
            }
            op.push_back({i,1,a[i] / i});
        }

        for(int i = 2;i <= n;i++){
            op.push_back({1,i,s});
        }

        printf("%d\n",(int)op.size());

        for(auto it:op){
            printf("%d %d %d\n",it.i,it.j,it.x);
        }
    }

    return 0;
}
