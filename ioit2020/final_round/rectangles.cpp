#include <bits/stdc++.h>

using namespace std;

struct query_t{
    long long x,y,xx,yy;
};

long long n,m,q,x,y;
vector<query_t> v;

int main(){

    scanf("%lld %lld %lld %lld %lld",&n,&m,&q,&x,&y);

    v = vector<query_t>(q);

    for(auto &it:v){
        scanf("%lld %lld %lld %lld",&it.x,&it.y,&it.xx,&it.yy);
    }

    reverse(v.begin(),v.end());

    for(auto it:v){
        if(it.x <= x && x <= it.xx && it.y <= y && y <= it.yy){
            x = (it.xx - it.x) - (x - it.x) + it.x;
            y = (it.yy - it.y) - (y - it.y) + it.y;
        }
    }

    x--;
    y--;
    printf("%lld\n",m * x + y);

    return 0;
}
