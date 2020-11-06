#include <bits/stdc++.h>

using namespace std;

int a[10];
int n;
int b[100005];

int main(){

    for(int i = 1;i <= 6;i++){
        scanf("%d",&a[i]);
    }

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&b[i]);
    }


    sort(a + 1,a + 1 + 6);
    multiset<pair<int,int> > s;

    for(int i = 1;i <= n;i++){
        s.insert({b[i] - a[6],6});
    }

    int ans = 2e9;

    while((int)s.size() >= n){
        ans = min(ans,s.rbegin()->first - s.begin()->first);
        pair<int,int> tmp = *s.begin();
        s.erase(s.begin());
        if(tmp.second > 1){
            tmp.first = tmp.first + a[tmp.second];
            tmp.second--;
            tmp.first = tmp.first - a[tmp.second];
            s.insert(tmp);
        }
    }

    printf("%d\n",ans);

    return 0;
}
