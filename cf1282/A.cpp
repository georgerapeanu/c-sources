#include <bits/stdc++.h>

using namespace std;

int t;
int a,b,c,r;

int main() {

    scanf("%d",&t);

    while(t--) {
        scanf("%d %d %d %d",&a,&b,&c,&r);
        if(a > b) {
            swap(a,b);
        }
        int d = max(a,c - r);
        int e = min(b,c + r);

        printf("%d\n",(b - a) - max(0,e - d));
    }

    return 0;
}
