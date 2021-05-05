#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int t;
int m;
vector<pair<int,long long> > v;


int main(){
    
    scanf("%d",&t);

    for(int h = 1;h <= t;h++){
        v.clear();
        scanf("%d",&m);

        long long sum = 0;
        long long answer = 0;

        for(int i = 1;i <= m;i++){
            int p;
            long long e;
            scanf("%d %lld",&p,&e);
            v.push_back({p,e});
            sum += p * e;
        }

        for(int sum_taken = 0;sum_taken <= 60 * 500 && sum_taken < sum;sum_taken++){
            long long sum_others = sum - sum_taken;
            int sum_factors = 0;
            bool ok = true;
            for(auto it:v){
                int exp = 0;
                while(sum_others % it.first == 0){
                    exp++;
                    sum_others /= it.first;
                    sum_factors += it.first;
                }
                if(exp > it.second || sum_factors > sum_taken){
                    ok = false;
                    break;
                }
            }
            if(sum_others != 1 || sum_factors != sum_taken){
                ok = false;
            }
            if(ok){
                answer = sum - sum_taken;
                break;
            }
        }

        printf("Case #%d: %lld\n",h,answer);
    }

    return 0;
}
