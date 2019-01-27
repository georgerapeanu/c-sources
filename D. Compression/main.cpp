#include <cstdio>
#include <algorithm>

using namespace std;

int n;
bool pos[6000];

int v[6000][6000];
char c[6000];

int main(){

    scanf("%d\n",&n);

    for(int i = 1;i <= n;i++){
        fgets(c + 1,6000,stdin);
        for(int j = 1;j <= n / 4;j++){
            int val = (c[j] >= 'A' ? 9 + c[j] - 'A' + 1 : c[j] - '0');
            for(int k = (j - 1) * 4 + 1;k <= j * 4;k++){
                v[i][k] = ((val >> (3 - (k - ((j - 1) * 4 + 1)))) & 1);
            }
        }
    }

    int ans = 1;

    for(int len = 2;len <= n;len++){
        if(pos[len] == true || n % len != 0){
            continue;
        }

        bool ok = true;

        for(int i = 1;i <= n && ok;i += len){
            for(int j = 1;j <= n && ok;j += len){
                int val = -1;
                for(int k = i;k < i + len && ok;k++){
                    for(int l = j;l < j + len && ok;l++){
                        if(val == -1){
                            val = v[k][l];
                        }
                        else if(val != v[k][l]){
                            ok = false;
                        }
                    }
                }
            }
        }

        if(ok){
            ans = max(ans,len);
        }
        else{
            for(int j = len;j < 6000;j += len){
                pos[j] = true;
            }
        }
    }

    printf("%d\n",ans);

    return 0;
}
