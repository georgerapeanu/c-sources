#include <bits/stdc++.h>

using namespace std;

const int NMAX = 5e5;

int n,k;
int v[NMAX + 5];
vector<int> splits;

int aib[NMAX + 5];

int solve(int l,int r,int l_val,int r_val){
    l_val -= (l - 1);
    r_val -= (r + 1);

    if(l_val > r_val){
        return 1e9;
    }

    if(l > r){
        return 0;
    }

    for(int i = l;i <= r;i++){
        v[i] -= i;
    }

    vector<int> vmin = {-int(2e9 + 1)};

    for(int i = l;i <= r;i++){
        if(v[i] < l_val || v[i] > r_val){
            continue;
        }
        int st = -1;
        int dr = vmin.size();

        while(dr - st > 1){
            int mid = (st + dr) / 2;

            if(vmin[mid] <= v[i]){
                st = mid;
            }
            else{
                dr = mid;
            }
        }
        if(st == (int)vmin.size() - 1){
            vmin.push_back(0);
        }
        vmin[st + 1] = v[i];
    }


    return (r - l + 1) - (vmin.size() - 1);
}

int main(){

    scanf("%d %d",&n,&k);

    for(int i = 1;i <= n;i++){
        scanf("%d",&v[i]);
    }

    splits = {0};

    for(int i = 1;i <= k;i++){
        int tmp;
        scanf("%d",&tmp);
        splits.push_back(tmp);
    }

    splits.push_back(n + 1);

    v[0] = -2e9;
    v[n + 1] = 2e9;

    int ans = 0;

    for(int i = 0;i + 1 < (int)splits.size();i++){
        int tmp = solve(splits[i] + 1,splits[i + 1] - 1,v[splits[i]],v[splits[i + 1]]);
        if(tmp >= 1e9){
            printf("-1\n");
            return 0;
        }
        ans += tmp;
    }

    printf("%d\n",ans);
    return 0;
}
