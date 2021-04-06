#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int t;
int n;
int v[105];

int main(){
    scanf("%d",&t);
    for(int test = 1;test <= t;test++){
        scanf("%d",&n);
        
        for(int i = 1;i <= n;i++){
            scanf("%d",&v[i]);
        }
        
        int ans = 0;
        
        for(int i = 1;i < n;i++){
            int idx = i;
            for(int j = i + 1;j <= n;j++){
                if(v[j] < v[idx]){
                    idx = j;
                }
            }
            reverse(v + i,v + 1 + idx);
            ans += idx - i + 1;
        }
        
        printf("Case #%d: %d\n",test,ans);
    }
    
    return 0;
}
