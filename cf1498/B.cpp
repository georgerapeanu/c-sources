#include <bits/stdc++.h>

using namespace std;

int t;
int n;
int w;

multiset<int> s;

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d %d",&n,&w);

        for(int i = 1;i <= n;i++){
            int val;
            scanf("%d",&val);
            s.insert(val);
        }

        int ans = 0;
        int space = 0;

        while(s.empty() == false){
            if(space < *s.begin()){
                space = w;
                ans++;
            }
            int value = *prev(s.lower_bound(space + 1));
            s.erase(s.find(value));
            space -= value;
        }

        printf("%d\n",ans);
    }

    return 0;
}
