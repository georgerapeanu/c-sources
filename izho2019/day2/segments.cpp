#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 5e5;

int n;
int v[NMAX + 5];
long long sum[NMAX + 5];
int bst_pos[NMAX + 5];
int ans[NMAX + 5];

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);
        sum[i] = sum[i - 1] + v[i];
    }

    for(int i = 1;i <= n;i++){
        bst_pos[i] = max(bst_pos[i],bst_pos[i - 1]);
        ans[i] = ans[bst_pos[i]] + 1;
        int target = (lower_bound(sum + 1,sum + 1 + n,2 * sum[i] - sum[bst_pos[i]]) - sum);
        bst_pos[target] = max(bst_pos[target],i);
    }

    printf("%d\n",ans[n]);

    return 0;
}
