#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int n,k;
int a[NMAX + 5];

map<int,int> ans;

vector<int> stuff;

int main(){

    scanf("%d %d",&n,&k);

    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
        stuff.push_back(a[i]);
    }

    sort(stuff.begin(),stuff.end());

    int r = -1;
    int cnt = 0;
    long long cst = 0;

    for(int l = 0;l < (int)stuff.size();l++){
        if(r < l){
            r = l;
            cnt = 0;
            cst = k;
        }
        while(r < (int)stuff.size() && cst >= stuff[r] - stuff[l]){
            cst -= (stuff[r] - stuff[l]);
            cnt++;
            r++;
        }
        if(l == 0 || stuff[l - 1] != stuff[l]){
            ans[stuff[l]] = cnt;
        }
        cnt--;
        if(l + 1 < (int)stuff.size() && stuff[l] != stuff[l + 1]){
            cst += 1LL * (cnt) * (stuff[l + 1] - stuff[l]);
        }
    }

    for(int i = 1;i <= n;i++){
        printf("%d ",ans[a[i]]);
    }

    return 0;
}
