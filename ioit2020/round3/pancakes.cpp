#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int VMAX = 1e6;
const int NMAX = 1e5;

int n;
int v[NMAX + 5];

int x,p;
bool not_prime[VMAX + 5];
int cost[10];

int get_cost(const vector<int> &val){
    int value = 0;
    int digit_product = 1;
    int digit_sum = 0;
    int ans = x;

    for(auto it:val){
        value = 10 * value + it;
        digit_product *= it;
        digit_sum += it;
        ans += cost[it];
    }

    if(not_prime[value] == false){
        ans += value;
        ans += p;
    }
    if(not_prime[digit_sum] == false){
        ans += digit_sum;
    }
    if(not_prime[digit_product] == false){
        ans += digit_product;
    }

    return ans;
}

int get_best_cost(int val){
    vector<int> v;

    while(val){
        v.push_back(val % 10);
        val /= 10;
    }

    reverse(v.begin(),v.end());

    int ans = 0;

    for(int i = 0;i < (int)v.size();i++){
        int tmp = v[i];
        for(int cf = (i == 0);cf < 10;cf++){
            v[i] = cf;
            ans = max(ans,get_cost(v));
        }
        v[i] = tmp;
    }

    return ans;
}

int main(){
    
    not_prime[0] = not_prime[1] = true;

    for(int i = 2;i <= VMAX;i++){
        if(not_prime[i]){
            continue;
        }

        for(int j = 2 * i;j <= VMAX;j += i){
            not_prime[j] = true;
        }
    }

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);
    }

    scanf("%d %d",&x,&p);

    scanf("%d %d %d %d",&cost[2],&cost[3],&cost[5],&cost[7]);

    long long ans = 0;

    for(int i = 1;i <= n;i++){
        ans += get_best_cost(v[i]);
    }

    printf("%lld\n",ans);

    return 0;
}
