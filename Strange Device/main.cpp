#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int n;
long long a,b;

vector<pair<long long,int> > events;

long long gcd(long long a,long long b){
    if(b == 0){
        return a;
    }
    return gcd(b,a % b);
}

int main(){

    scanf("%d %lld %lld",&n,&a,&b);

    a /= gcd(a,b + 1);

    vector<pair<long long,long long> > segm;

    for(int i = 1;i <= n;i++){
        long long l,r;
        scanf("%lld %lld",&l,&r);

        if((r - l + 1) / a >= b){
            printf("%lld\n",a * b);
            return 0;
        }

        long long fst = (((l / b) % a) * (b) + (l % b));
        long long snd = (((r / b) % a) * (b) + (r % b));

        if(fst > snd){
            events.push_back({fst,1});
            events.push_back({(a - 1) * (b) + (b - 1) + 1,-1});
            events.push_back({0,1});
            events.push_back({snd + 1,-1});
        }
        else{
            events.push_back({fst,1});
            events.push_back({snd + 1,-1});
        }
    }

    sort(events.begin(),events.end());

    long long ans = 0;
    long long lst = -1;
    int cnt_active = 0;

    for(auto it:events){
        ans += ((long long)(cnt_active > 0)) * (it.first - lst);
        lst = it.first;
        cnt_active += it.second;
    }

    printf("%lld\n",ans);

    return 0;
}
