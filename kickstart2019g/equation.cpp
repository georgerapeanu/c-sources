#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int NMAX = 1e3;
const int LGMAX = 50;

int t;
int n;
long long m;
int cnt[LGMAX + 5][2];
long long min_sum[LGMAX + 5];

int main(){

    scanf("%d",&t);

    for(int test = 1;test <= t;test++){
        memset(cnt,0,sizeof(cnt));
        
        scanf("%d %lld",&n,&m);
        
        for(int i = 1;i <= n;i++){
            long long val;
            scanf("%lld",&val);
            for(int h = 0;h < LGMAX;h++){
                cnt[h][(val >> h) & 1]++;
            }
        }

        for(int h = 0;h < LGMAX;h++){
            min_sum[h] = (((long long)min(cnt[h][0],cnt[h][1]) << h)) + (h > 0 ? min_sum[h - 1]:0);
        }

        if(min_sum[LGMAX - 1] > m){
            printf("Case #%d: -1\n",test);
            continue;
        }

        long long pref_sum = 0;
        long long pref_ans = 0;

        for(int h = LGMAX - 1;h >= 0;h--){
            if(pref_sum + (((long long)cnt[h][0]) << h) + (h > 0 ? min_sum[h - 1]:0) <= m){
                pref_sum += (((long long)cnt[h][0]) << h);
                pref_ans |= (1LL << h);
            }
            else{
                pref_sum += (((long long)cnt[h][1]) << h);
            }
        }
        printf("Case #%d: %lld\n",test,pref_ans);
    }

    return 0;
}
