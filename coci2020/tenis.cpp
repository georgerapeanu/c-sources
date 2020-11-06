#include <bits/stdc++.h>

using namespace std;

const int NMAX = 100005;

int n;
int ran[3][NMAX + 5];
int pos[3][NMAX + 5];

long long ans[3];

int appeared[NMAX + 5];
int fr[1 << 3];
int wh[NMAX + 5];
int wins[NMAX + 5];

int get_best(int a,int b) {
    pair<pair<int,int>,int> bst = {{1e9,1e9},1e9};

    for(int h = 0; h < 3; h++) {
        pair<pair<int,int>,int> tmp = {{min(pos[h][a],pos[h][b]),max(pos[h][a],pos[h][b])},h};
        bst = min(bst,tmp);
    }
    return bst.second;
}

int get_winner(int a,int b) {
    pair<pair<int,int>,int> bst = {{1e9,1e9},1e9};

    for(int h = 0; h < 3; h++) {
        pair<pair<int,int>,int> tmp = {{min(pos[h][a],pos[h][b]),max(pos[h][a],pos[h][b])},h};
        bst = min(bst,tmp);
    }
    return ran[bst.second][bst.first.first];
}

int bonus[NMAX + 5];

int main() {

    scanf("%d",&n);

    for(int h = 0; h <= 2; h++) {
        for(int i = 1; i <= n; i++) {
            scanf("%d",&ran[h][i]);
            pos[h][ran[h][i]] = i;
        }
    }

    for(int i = 1; i <= n; i++) {
        vector<int> noi;
        for(int h = 0; h <= 2; h++) {
            if(wh[ran[h][i]] == 0 || wh[ran[h][i]] == i) {
                if(wh[ran[h][i]] == 0) {
                    noi.push_back(ran[h][i]);
                    wh[ran[h][i]] = i;
                }
                appeared[ran[h][i]] |= 1 << h;
            }
        }
        for(auto it:noi) {
            for(int conf = 1; conf < (1 << 3); conf++) {
                pair<int,int> bst = {1e9,1e9};
                for(int h = 0; h < 3; h++) {
                    if((conf >> h) & 1) {
                        pair<int,int> tmp = {pos[h][it],h};
                        bst = min(bst,tmp);
                    }
                }
                ans[bst.second] += fr[conf];
            }
        }
        for(auto it:noi) {
            fr[appeared[it]]++;
        }
        for(int i = 0; i < (int)noi.size(); i++) {
            for(int j = i + 1; j < (int)noi.size(); j++) {
                ans[get_best(noi[i],noi[j])]++;
                wins[get_winner(noi[i],noi[j])]++;
            }
        }
        bonus[i - 1] += (int)noi.size();
    }

    for(int i = n; i >= 0; i--) {
        bonus[i] += bonus[i + 1];
    }

    for(int i = 1; i <= n; i++) {
        wins[i] += bonus[wh[i]];
    }

    for(int i = 0; i < 3; i++)printf("%lld ",ans[i]);
    printf("\n");
    for(int i = 1; i <= n; i++)printf("%d ",wins[i]);
    printf("\n");

    return 0;
}
