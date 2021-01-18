#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int t;
int n,m;

int main(){
    
    scanf("%d",&t);

    while(t--){
        scanf("%d %d",&n,&m);

        bool sw = (n > m);
        if(sw){
            swap(n,m);
        }

        vector<vector<int> > ans(n + 1,vector<int>(m + 1));

        int cnt_available = max(0,(n - 1) / 2) - 1;
        int lst = 1;
        int ans_sum = m;

        for(int i = 1;i <= n && cnt_available >= 0;i++){
            bool success = true;
            for(int j = 0;j < m / 2 + 1;j++){
                ans[i][lst] = 1;
                lst++;
                if(lst > m){
                    lst = 1;
                    cnt_available--;
                    if(cnt_available < 0 && j < m / 2){
                        success = false;
                        break;
                    }
                }
            }
            ans_sum += success;
        }

        if(sw){
            swap(n,m);
            vector<vector<int> > tmp(n + 1,vector<int>(m + 1));
            for(int i = 1;i <= n;i++){
                for(int j = 1;j <= m;j++){
                    tmp[i][j] = ans[j][i] ^ 1;
                }
            }
            ans = tmp;
        }
        
        printf("%d\n",ans_sum);
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                printf(ans[i][j] == 0 ? "-":"+");
            }
            printf("\n");
        }

    }

    return 0;
}
