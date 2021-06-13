#include <bits/stdc++.h>

using namespace std;

int n,v;
vector<int> events;
vector<int> vouchers;

int main(){

    scanf("%d %d",&n,&v);

    events = vector<int>(n,0);
    vouchers = vector<int>(v,0);

    for(auto &it:events){
        scanf("%d",&it);
    }
    
    for(auto &it:vouchers){
        scanf("%d",&it);
    }

    sort(events.begin(),events.end());
    sort(vouchers.begin(),vouchers.end());

    int ans = 0;

    for(auto it:vouchers){
        if(ans < (int)events.size() && events[ans] <= it){
            ans++;
        }
    }

    printf("%d\n",ans);

    return 0;
}
