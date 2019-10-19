#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 20;

int t;
int n;
int h;
int a[NMAX + 5];
int b[NMAX + 5];
int confs_a[1 << NMAX];
int confs_b[1 << NMAX];

int main(){

    scanf("%d",&t);

    for(int test = 1;test <= t;test++){
        memset(confs_a,0,sizeof(confs_a));
        memset(confs_b,0,sizeof(confs_b));
        scanf("%d %d",&n,&h);
        
        for(int i = 0;i < n;i++){
            scanf("%d",&a[i]);
        }
        
        for(int i = 0;i < n;i++){
            scanf("%d",&b[i]);
        }

        for(int conf = 0;conf < (1 << n);conf++){
            int ans_a = 0;
            int ans_b = 0;
            for(int i = 0;i < n;i++){
                if((conf >> i) & 1){
                    ans_a = min(ans_a + a[i],h);
                    ans_b = min(ans_b + b[i],h);
                }
            }
            if(ans_a >= h){
                confs_a[conf] = 1;
            }
            if(ans_b >= h){
                confs_b[conf] = 1;
            }
        }

        for(int h = 0;h < n;h++){
            for(int conf = 0;conf < (1 << n);conf++){
                if(((conf >> h) & 1) == 0){
                    confs_a[conf] += confs_a[conf ^ (1 << h)];
                }
            }
        }

        long long ans = 0;

        for(int conf = 0;conf < (1 << n);conf++){
            if(confs_b[conf] == 1){
                ans += confs_a[((1 << n) - 1) ^ conf];
            }
        }

        printf("Case #%d: %lld\n",test,ans);

    }

    return 0;
}
