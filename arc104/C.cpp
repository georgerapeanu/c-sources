#include <bits/stdc++.h>

using namespace std;

int n;
int c[205];
int tp[205];
int active[205];

vector<pair<int,int> > v;
int dp[205];

int main() {

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        pair<int,int> tmp;
        scanf("%d %d",&tmp.first,&tmp.second);
        v.push_back(tmp);
        if(tmp.first != -1){
            tp[tmp.first] = 1;
            active[tmp.first] = i;
        }
        if(tmp.second != -1){
            tp[tmp.second] = 2;
            active[tmp.second] = i;
        }
    }

    dp[0] = true;

    for(int i = 0;i < 2 * n;i++){
        for(int j = i + 1;j <= 2 * n;j++){
            int k = (j - i) * 2 + i;
            if(k > 2 * n){
                continue;
            }
            bool ok = true;
            for(int it = i + 1;it <= j;it++){
                int other = it + (j - i);
                int fst = active[it];
                int snd = active[other];
                if(fst != 0 && snd != 0){
                    if(fst != snd){
                        ok = false;
                        break;
                    }
                }

                else if(fst != 0){
                    if(v[fst - 1].second != -1 && other != v[fst - 1].second){
                        ok = false;
                        break;
                    }
                }

                else if(snd != 0){
                    if(v[snd - 1].first != -1 && it != v[snd - 1].first){
                        ok = false;
                        break;
                    }
                }

                else if(tp[it] == 2 || tp[other] == 1 ){
                    ok = false;
                    break;
                }
            }
            if(ok){
                dp[k] |= dp[i];
            }
        }
    }

    printf(dp[2 * n] ? "Yes":"No");

    return 0;
}
