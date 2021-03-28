#include <cstdio>

using namespace std;

const int NMAX = 1e5;

int n;
int v[NMAX + 5];
int ans[2 * NMAX + 5];
int a,b;

int main(){
   
    freopen("permutare.in","r",stdin);
    freopen("permutare.out","w",stdout);

    scanf("%d",&n);

    for(int i = 1;i <= n + 1;i++){
        scanf("%d",&v[i]);
    }

    a = 1;
    b = 2 * n + 1;

    for(int i = n + 1;i > 1;i--){
        if(v[i] == -1){
            if(v[i - 1] == -1){
                ans[2 * i - 2] = a;
                ans[2 * i - 1] = a + 3; 
                a += 2;
            }else if(v[i - 1] == 0){
                ans[2 * i - 2] = a;
                ans[2 * i - 1] = b;
                a += 2;b--;
            }else{
                ans[2 * i - 2] = a;
                ans[2 * i - 1] = b - 1;
                a += 2;
            }
        }else if(v[i] == 0){
            if(v[i - 1] == -1){
                ans[2 * i - 2] = a + 1;
                ans[2 * i - 1] = b;
                b--;
            }else if(v[i - 1] == 0){
                ans[2 * i - 2] = a;
                ans[2 * i - 1] = b;
                a++;b--;
            }else{
                ans[2 * i - 2] = a;
                ans[2 * i - 1] = b - 1;
                a++;
            }
        }else{
            if(v[i - 1] == -1){
                ans[2 * i - 2] = a + 1;
                ans[2 * i - 1] = b;
                b -= 2;
            }else if(v[i - 1] == 0){
                ans[2 * i - 2] = a;
                ans[2 * i - 1] = b;
                a++;b -= 2;
            }else{
                ans[2 * i - 2] = b;
                ans[2 * i - 1] = b - 3;
                b -= 2;
            } 
        }
    }

    ans[1] = a;

    for(int i = 1;i <= 2 * n + 1;i++){
        printf("%d ",ans[i]);
    }

    return 0;
}
