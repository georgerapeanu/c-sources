#include <bits/stdc++.h>

using namespace std;

int t;

int main() {

    scanf("%d",&t);

    while(t--) {
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        vector<int> v=  {a,b,c};
        sort(v.begin(),v.end());
        if(v[0] + v[1] + 1 >= v[2]) {
            printf("Yes\n");
        }
        else {
            printf("No\n");
        }
    }

    return 0;
}
