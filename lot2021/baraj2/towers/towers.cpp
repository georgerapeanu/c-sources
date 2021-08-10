#include <bits/stdc++.h>

using namespace std;

const int NMAX = 5e5;
const int KMAX = 20;

int t;
int n,k;

int r[NMAX + 5];
int p[NMAX + 5];

vector<pair<int,int>> best_states[3];
vector<pair<int,int>> new_states[3];

bool cmp(pair<int,int> a,pair<int,int> b){
    return min(a.first,a.second) < min(b.first,b.second);
}

int main(){

    scanf("%d",&t);

    while(t--){
        scanf("%d %d",&n,&k);

        for(int i = 0;i < k;i++){
            scanf("%d",&r[i]);
        }

        for(int i = 1;i <= n;i++){
            scanf("%d",&p[i]);
        }

        for(int j = 0;j < k;j++){
            best_states[j] = {make_pair(0,0)};
        }

        p[0] = -1e8;

        for(int h = 1;h <= n;h++){
            for(int j = 0;j < k;j++){
                new_states[j].clear();
            }

            for(int j = 0;j < k;j++){
                for(auto it:best_states[j]){
                    int i = it.first;
                    int l = it.second;
                    if(p[h] - p[h - 1] >= r[j]){
                        new_states[j].push_back({i,l});
                    }
                    if(p[h] - p[i] >= r[(j + 1) % k]){
                        int x = l;
                        int y = (j + 1) % k;
                        new_states[y].push_back({x,h - 1});
                    }
                    if(p[h] - p[l] >= r[(j + 2) % k]){
                        int x = h - 1;
                        int y = (j + 2) % k;
                        new_states[y].push_back({x,i});
                    }
                }
            }

            for(int j = 0;j < k;j++){
                pair<int,int> best_first,best_second;
                best_first = best_second = make_pair(n + 1,n + 1);
                best_states[j] = new_states[j];
                sort(best_states[j].begin(),best_states[j].end(),cmp);
                best_states[j].resize(min((int)best_states[j].size(),KMAX));
            }
        }

        bool ok = false;
        for(int j = 0;j < k;j++){
            ok |= !best_states[j].empty();
        }

        printf("%d\n",ok);
    }

    return 0;
}

