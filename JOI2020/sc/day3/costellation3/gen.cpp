#include <bits/stdc++.h>

using namespace std;

int main(){

    mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());

    int n = gen() % 20 + 1;

    printf("%d\n",n);

    vector<int> a(n,0);

    for(int i = 1;i <= n;i++){
        a[i - 1] = gen() % n;
        printf("%d ",a[i - 1]);
    }


    vector<pair<int,int> > stuff;

    for(int i = 1;i <= n;i++){
        for(int j = a[i - 1] + 1;j <= n;j++){
            stuff.push_back({i,j});
        }
    }

    int m = gen() % int(stuff.size()) + 1;
    
    shuffle(stuff.begin(),stuff.end(),gen);

    printf("%d\n",m);
    for(int i = 0;i < m;i++){
        int x = stuff[i].first;
        int y = stuff[i].second;
        int c = gen() % 100 + 1;

        printf("%d %d %d\n",x,y,c);
    }

    return 0;
}

