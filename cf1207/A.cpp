#include <bits/stdc++.h>

using namespace std;

int main() {

    int t;

    scanf("%d",&t);

    while(t--){
        int b,p,f,h,c;
        scanf("%d %d %d",&b,&p,&f);
        scanf("%d %d",&h,&c);
        b /= 2;
        if(h < c){
            swap(h,c);
            swap(p,f);
        }

        printf("%d\n",min(b,p) * h + min(max(0,b - p),f) * c);
    }

    return 0;
}
