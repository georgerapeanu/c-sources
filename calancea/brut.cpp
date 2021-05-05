#include <cstdio>
#include <deque>

using namespace std;

const int NMAX = 1e6;

int n;
long long b;
int v[NMAX + 5];

long long sum = 0;
long long ans = 0;

int main(){
   
    freopen("calancea.in","r",stdin);
    freopen("calancea.ok","w",stdout);

    scanf("%d %lld",&n,&b);

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);
    }

    long long ans = 0;

    for(int i = 1;i <= n;i++){
        int _max = -NMAX - 5;
        long long sum = 0;

        for(int j = i;j <= n;j++){
            _max = max(v[j],_max);
            sum += _max - v[j];
            ans += (sum <= b);
        }
    }

    printf("%lld\n",ans); 

    return 0;
}

