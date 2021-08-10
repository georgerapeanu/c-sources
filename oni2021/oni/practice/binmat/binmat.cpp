#include <cstdio>

using namespace std;

int main(){
    int n,k;
    scanf("%d %d",&n,&k);

    for(int i = 1;i <= n;i++){
        int l = i;
        int r = (n + i + k - 2) % n + 1;
        for(int j = 1;j <= n;j++){
            if((l <= j && j <= r) || (r < l && (j <= r || j >= l))){
                fputc('1',stdout);
            }else{
                fputc('0',stdout);
            }
        }
        fputc('\n',stdout);
    }
}
