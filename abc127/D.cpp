#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int n,m;
priority_queue<pair<int,int> > pq;

int main(){

    scanf("%d %d",&n,&m);

    for(long long i = 1;i <= n;i++){
        long long tmp;
        scanf("%lld",&tmp);
        pq.push({tmp,1});
    }

    for(long long i = 1;i <= m;i++){
        long long cnt,val;
        scanf("%lld %lld",&cnt,&val);
        pq.push({val,cnt});
    }

    long long sum = 0;

    for(int i = 1;i <= n;i++){
        auto tmp = pq.top();
        pq.pop();
        sum += tmp.first;
        tmp.second--;
        if(tmp.second > 0){
            pq.push(tmp);
        }
    }

    printf("%lld",sum);

    return 0;
}
