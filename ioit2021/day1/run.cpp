#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int n;
int d[NMAX + 5];

int solve(int st,int dr){
    if(st == dr){
        return 1;
    }

    int mid = (st + dr) / 2;

    int ans = max(solve(st,mid),solve(mid + 1,dr));
    
    int _min = 1e9;
    int _max = -1e9;
    int rightmost_max = -1;
    int ind = mid + 1;

    int left_max = -1e9;
    int max_ind = mid;


    for(int i = mid;i >= st;i--){
        _min = min(_min,d[i]);
        left_max = max(left_max,d[i]);

        while(ind <= dr && d[ind] >= _min){
            if(_max <= d[ind]){
                _max = d[ind];
                rightmost_max = ind;
            }
            ind++;
        }
        if(_min == d[i] && left_max <= _max){
            ans = max(ans,rightmost_max - i + 1);
        }
    }

    return ans;
}

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&d[i]);
    }

    printf("%d\n",solve(1,n));

    return 0;
}

