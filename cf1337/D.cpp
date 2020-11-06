#include <bits/stdc++.h>

using namespace std;

int t;
int r,g,b;

vector<pair<int,int> > chestie;

int nxt[int(3e5) + 5][3];
int ant[int(3e5) + 5][3];

long long get_cost(int i,int j,int k) {
    int a = chestie[i].first;
    int b = chestie[j].first;
    int c = chestie[k].first;

    return 1LL * (a - b) * (a - b) + 1LL * (b - c) * (b - c) + 1LL * (a - c) * (a - c);
}

int main() {


    scanf("%d",&t);

    while(t--) {
        chestie.clear();
        scanf("%d %d %d",&r,&g,&b);

        for(int i = 1; i <= r; i++) {
            int val;
            scanf("%d",&val);
            chestie.push_back({val,0});
        }

        for(int i = 1; i <= g; i++) {
            int val;
            scanf("%d",&val);
            chestie.push_back({val,1});
        }

        for(int i = 1; i <= b; i++) {
            int val;
            scanf("%d",&val);
            chestie.push_back({val,2});
        }

        sort(chestie.begin(),chestie.end());

        nxt[(int)chestie.size()][0] = 1e9;
        nxt[(int)chestie.size()][1] = 1e9;
        nxt[(int)chestie.size()][2] = 1e9;

        for(int i = (int)chestie.size() - 1; i >= 0; i--) {
            nxt[i][0] = nxt[i + 1][0];
            nxt[i][1] = nxt[i + 1][1];
            nxt[i][2] = nxt[i + 1][2];

            nxt[i][chestie[i].second] = i;
        }

        long long ans = 2e18;

        for(int i = 0; i < (int)chestie.size(); i++) {
            ant[i][0] = (i != 0 ? ant[i - 1][0]:1e9);
            ant[i][1] = (i != 0 ? ant[i - 1][1]:1e9);
            ant[i][2] = (i != 0 ? ant[i - 1][2]:1e9);
            ant[i][chestie[i].second] = i;
        }
        for(int i = 0; i < (int)chestie.size(); i++) {

            for(int j = 0; j < 3; j++) {
                if(j == chestie[i].second) {
                    continue;
                }
                int k = 0 ^ 1 ^ 2 ^ chestie[i].second ^ j;

                if(ant[i][j] != 1e9 && nxt[i][k] != 1e9) {
                    ans = min(ans,get_cost(i,ant[i][j],nxt[i][k]));
                }
            }
        }

        printf("%lld\n",ans);
    }

    return 0;
}
