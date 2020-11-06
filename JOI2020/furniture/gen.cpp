#include <cstdio>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;

int main(){

    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

    int n = gen() % 10 + 2;
    int m = gen() % 10 + 2;
    int q = gen() % (n * m - 2) + 1;

    printf("%d %d\n",n,m);

    vector<pair<int,int > > stuff;
    for(int i = 1;i <= n;i++){
        for(int j = 1;j <= m;j++){
            printf("0 ");
            if((i != 1 || j != 1) && (i != n || j != m)) stuff.push_back({i,j});
        }
        printf("\n");
    }

    printf("%d\n",q);

    shuffle(stuff.begin(),stuff.end(),gen);

    for(int i = 0;i < q;i++){
        printf("%d %d\n",stuff[i].first,stuff[i].second);
    }

    return 0;
}
