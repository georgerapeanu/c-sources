#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;

int n;
int a[NMAX + 5];
int b[NMAX + 5];

int restr[NMAX + 5];///restrictions imposed by b
bool have[NMAX + 5];


int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
        have[a[i]] = true;
    }

    int pos = -1;

    for(int i = 1;i <= n;i++){
        scanf("%d",&b[i]);
        if(b[i] != 0){
            if(b[i] == 1){
                pos = i;
            }
            restr[b[i]] = i - b[i] + 2;
        }
    }

    bool ok = (pos > 0);

    for(int i = pos;i <= n;i++){
        ok &= (b[i] == i - pos + 1);
    }

    if(ok == false){
        int x = 1;
        for(int i = 1;i <= n;i++){
            x = max(x,restr[i]);
        }
        printf("%d",x + n - 1);
    }
    else{
        int lst = n - pos + 1;
        int x = 1;
        int ans = 1 << 30;
        for(int i = n;i;i--){
            x = max(x,restr[i]);
        }
        ans = min(ans,x + n - 1);

        bool ok = true;

        for(int i = 1;i < pos;i++){
            lst++;
            if(have[lst] == false){
                ok = false;
                break;
            }
            have[b[i]] = true;
        }

        if(ok){
            ans = min(ans,pos - 1);
        }

        printf("%d",ans);
    }

    return 0;
}
