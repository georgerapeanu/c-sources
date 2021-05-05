#include <bits/stdc++.h>

using namespace std;

const int TMAX = 1;
const int NMAX = 10;
const int KMAX = 3;
const int XMAX = 20;
const int RMAX = 15;

int main(){
    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

    int t = TMAX;

    printf("%d\n",t);

    while(t--){
        int n = gen() % NMAX + 1;
        int k = KMAX;
        printf("%d %d\n",n,k);

        for(int i = 1;i <= k;i++){
            printf("%d ",int(gen() % RMAX + 1));
        }
        printf("\n");

        vector<int> p;
        
        for(int i = 1;i <= XMAX;i++){
            p.push_back(i);
        }

        shuffle(p.begin(),p.end(),gen);

        vector<int> pp;
        for(int i = 0;i < n;i++){
            pp.push_back(p[i]);
        }
        sort(pp.begin(),pp.end());

        for(auto it:pp){
            printf("%d ",it);
        }
        printf("\n");


        printf("\n");
    }
    
    return 0;
}
