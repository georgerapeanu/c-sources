#include <bits/stdc++.h>

using namespace std;

int t;

int main() {
    
    scanf("%d",&t);

    while(t--){
        int n;
        scanf("%d",&n);

        vector<int> a(n,0);
        vector<int> b(n,0);
        vector<int> c(n,0);
        vector<int> p(n,0);

        for(int i = 0;i < n;i++){
            scanf("%d",&a[i]);
        }
        for(int i = 0;i < n;i++){
            scanf("%d",&b[i]);
        }
        for(int i = 0;i < n;i++){
            scanf("%d",&c[i]);
        }

        p[0] = a[0];

        for(int i = 1;i < n - 1;i++){
            if(p[i - 1] != a[i]){
                p[i] = a[i];
            }
            else{
                p[i] = b[i];
            }
        }

        if(a[n - 1] != p[n - 2] && a[n - 1] != p[0]){
            p[n - 1] = a[n - 1];
        }
        else if(b[n - 1] != p[n - 2] && b[n - 1] != p[0]){
            p[n - 1] = b[n - 1];
        }
        else{    
            p[n - 1] = c[n - 1];
        }
        
        for(auto it:p)printf("%d ",it);printf("\n");
    }


    return 0;
}
