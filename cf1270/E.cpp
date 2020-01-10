#include <bits/stdc++.h>

using namespace std;

int n;
pair<int,int> a[1005];

int get_mod(int val,int x) {
    return ((val % x) + x) % x;
}

vector<int> f[2][2];

int main() {

    scanf("%d",&n);

    for(int i = 1; i <= n; i++) {
        scanf("%d %d",&a[i].first,&a[i].second);
    }

    while(true) {
        for(int x = 0; x < 2; x++) {
            for(int y = 0; y < 2; y++) {
                f[x][y].clear();
            }
        }

        for(int i = 1; i <= n; i++) {
            f[get_mod(a[i].first,2)][get_mod(a[i].second,2)].push_back(i);
        }

        int sx = -1,sy = -1;

        for(int x = 0; x < 2; x++) {
            for(int y = 0; y < 2; y++) {
                if(f[x][y].size() == n) {
                    sx = x;
                    sy =y;
                }
            }
        }

        if(sx != -1 && sy != -1) {
            for(int i = 1; i <= n; i++) {
                a[i].first = (a[i].first - sx) / 2;
                a[i].second = (a[i].second - sy) / 2;
            }
            continue;
        }

        if(f[0][0].size() + f[1][1].size() > 0 && f[0][1].size() + f[1][0].size() > 0) {
            printf("%d\n",int(f[0][0].size() + f[1][1].size()));
            for(auto it:f[0][0]) {
                printf("%d ",it);
            }
            for(auto it:f[1][1]) {
                printf("%d ",it);
            }
            break;
        }
        else if(f[0][0].size() + f[1][1].size() > 0) {
            printf("%d\n",int(f[0][0].size()));
            for(auto it:f[0][0]) {
                printf("%d ",it);
            }
            break;
        }
        else {
            printf("%d\n",int(f[0][1].size()));
            for(auto it:f[0][1]) {
                printf("%d ",it);
            }
            break;
        }
    }

    return 0;
}
