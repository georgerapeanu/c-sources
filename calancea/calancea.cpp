///foarte explicit acel "monoton crescatoare"...

#include <cstdio>
#include <deque>

using namespace std;

const int NMAX = 1e6;

int n;
long long b;
int v[NMAX + 5];

deque<int> dq;
long long sum = 0;
long long ans = 0;

int main(){
   
    freopen("calancea.in","r",stdin);
    freopen("calancea.out","w",stdout);

    scanf("%d %lld",&n,&b);

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);
//        v[i] -= i;
    }

    int l = n,r = n;

    for(;r >= 1;r--){
        while(sum <= b && l > 0){
            while(dq.empty() == false && v[dq.front()] <= v[l]){
                int curr = dq.front();
                dq.pop_front();
                int nxt = (dq.empty() ? r + 1:dq.front());
                sum -= 1LL * (nxt - curr) * v[curr];
            }
            int nxt = (dq.empty() ? r + 1:dq.front());
            dq.push_front(l);
            sum += 1LL * (nxt - l) * v[l];
            sum -= v[l];
            l--;
        }
        ans += (r - l - (sum > b));
//        printf("deb %d %d %lld %d\n",l,r,sum,(r - l - (sum > b)));
//        for(auto it:dq)printf("%d ",it);printf("\n");
        sum -= v[dq.back()];
        sum += v[r];
        if(dq.back() >= r){
            dq.pop_back();
        }
    }

    printf("%lld\n",ans); 

    return 0;
}

