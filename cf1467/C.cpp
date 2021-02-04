#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;

int n[4];
int a[4][NMAX + 5];
long long sum[4];

int main(){

    for(int k = 1;k <= 3;k++){
        scanf("%d",&n[k]);
    }
    long long total_sum = 0;
    vector<int> mins;
    for(int k = 1;k <= 3;k++){
        for(int i = 1;i <= n[k];i++){
            scanf("%d",&a[k][i]);
            total_sum += a[k][i];
            sum[k] += a[k][i];
        }
        sort(a[k] + 1,a[k] + 1 + n[k]);
        mins.push_back(a[k][1]);
    }
    sort(mins.begin(),mins.end());
    total_sum = max(total_sum - 2 * mins[0] - 2 * mins[1],max(total_sum - 2 * sum[1],max(total_sum - 2 * sum[2],total_sum - 2 * sum[3])));
    printf("%lld\n",total_sum);
    return 0;
}
