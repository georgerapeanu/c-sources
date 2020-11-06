#include <bits/stdc++.h>
#include <chrono>

using namespace std;

int main(){

    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

    int n = gen() % 10 + 2;
    int m = gen() % (n * (n - 1) / 2) + 1;
    int q = gen() % 20 + 1;
    vector<pair<int,int> > edges;

    for(int i = 1;i <= n;i++){
        for(int j = i + 1;j <= n;j++){
            edges.push_back({i,j});
        }
    }

    shuffle(edges.begin(),edges.end(),gen);

    vector<int> ord;


    printf("%d %d %d\n",n,m,q);
    
    for(int i = 1;i <= n;i++){
        ord.push_back(i);
    }
    
    shuffle(ord.begin(),ord.end(),gen);

    for(auto it:ord)printf("%d ",it);printf("\n");

    ord.clear();


    for(int i = 1;i <= m;i++){
        ord.push_back(i);
        printf("%d %d\n",edges[i].first,edges[i].second);
    }


    shuffle(ord.begin(),ord.end(),gen);

    for(int i = 1;i <= q;i++){
        if(ord.empty() || (gen() % 2)){
            printf("1 %d\n",int(gen() % n + 1));
        }
        else{
            printf("2 %d\n",ord.back());
            ord.pop_back();
        }

    }

    return 0;
}
