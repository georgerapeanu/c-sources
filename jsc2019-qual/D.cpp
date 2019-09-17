#include <bits/stdc++.h>

using namespace std;

int n;
int ans[505][505];

void solve(int st,int dr,int col){
    if(st == dr){
        return ;
    }
    int mid = (st + dr) / 2;
    for(int i = st;i <= mid;i++){
        for(int j = mid + 1;j <= dr;j++){
            ans[i][j] = col;
        }
    }
    solve(st,mid,col + 1);
    solve(mid + 1,dr,col + 1);
}

int main() {
    cin >> n;
    
    solve(1,n,1);

    for(int i = 1;i <= n;i++){
        for(int j = i + 1;j <= n;j++){
            cout << ans[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
