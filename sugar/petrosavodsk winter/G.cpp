#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;
const long double eps = 2e-6;

int n;
pair<int,int> v[NMAX + 5];

long double sums[NMAX + 5];
long double alpha[NMAX + 5];

int main(){

    scanf("%d",&n);

    for(int i = 0;i <= n;i++){
        scanf("%d %d",&v[i].first,&v[i].second);
    }

    for(int i = 1;i <= n;i++){
        sums[i] = ((long double)v[i].second - v[i - 1].second) / (v[i].first - v[i - 1].first);
    }

    if(1LL * (v[1].second - v[0].second) * (v[n].first - v[n - 1].first) != 
       1LL * (v[n].second - v[n - 1].second) * (v[0].first - v[1].first)){
        printf("No\n");
        return 0;
    }

    for(int i = 2;i <= n;i++){
        alpha[i - 1] = (sums[i] - sums[i - 1]) / 2;
    }

    bool ok = true;

    long double y = v[0].second;

    for(int i = 1;i < n;i++){
        y -= alpha[i] * (v[i].first - v[0].first);
    }

    if(-eps < y && y < eps){
        printf("Yes\n");
    }
    else{
        printf("No\n");
    }

    return 0;
}
