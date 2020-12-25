#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;
const int BUCK = 400;

int n;
int a[NMAX + 5];
vector<int> pos[NMAX + 5];

int nxt[NMAX + 5];
int ant[NMAX + 5];

int where[2 * NMAX + 5];

int brute(const vector<pair<int,int> > &v){
    where[NMAX + 0] = 0;
    int sum = NMAX;
    int ans = 0;
    for(int i = 0;i < (int)v.size();i++){
        sum += v[i].second;
        if(where[sum] == -1){
            where[sum] = v[i].first;
        }
        else{
            ans = max(ans,(i < (int)v.size() - 1 ? v[i + 1].first:n + 1) - 1 - where[sum]);
        }
    }

    sum = NMAX;
    where[NMAX + 0] = -1;
    for(int i = 0;i < (int)v.size();i++){
        sum += v[i].second;
        where[sum] = -1;
    }

    return ans;
}

int main(){

    for(int i = 0;i <= 2 * NMAX;i++){
        where[i] = -1;
    }

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
        pos[a[i]].push_back(i);
    }

    pair<int,int> bst = {-1,0};

    for(int i = 1;i <= n;i++){
        bst = max(bst,{pos[i].size(),i});
    }

    for(int i = 1;i <= n;i++){
        ant[i] = ant[i - 1];
        if(a[i - 1] == bst.second){
            ant[i] = i - 1;
        }
    }

    nxt[n] = n + 1;

    for(int i = n - 1;i;i--){
        nxt[i] = nxt[i + 1];
        if(a[i + 1] == bst.second){
            nxt[i] = i + 1;
        }
    }

    int ans = 0;

    for(int i = 1;i <= n;i++){

        if(i == bst.second || pos[i].empty()){
            continue;
        }

        if((int)pos[i].size() >= BUCK){
            vector<pair<int,int> > v;

            for(int j = 1;j <= n;j++){
                v.push_back({j,(a[j] == bst.second) - (a[j] == i)});
            }
            
            ans = max(ans,brute(v));
        }
        else{

            vector<pair<int,int> > v;
            
            for(auto it:pos[i]){
                int nod = it;
                int cnt = 1 + (int)pos[i].size();
                while(cnt > 0 && ant[nod] > 0){
                    nod = ant[nod];
                    cnt--;
                }
                while(nod < it){
                    if(v.empty() || v.back().first < nod){
                        v.push_back({nod,1});
                    }
                    nod = nxt[nod];
                }

                nod = it;
                cnt = 1 + (int)pos[i].size();

                while(cnt > 0 && nxt[nod] <= n){
                    nod = nxt[nod];
                    cnt--;
                    if(v.empty() || v.back().first < nod){
                        v.push_back({nod,1});
                    }
                }
            }

            vector<pair<int,int> > tmp;

            for(auto it:pos[i]){
                tmp.push_back({it,-1});
            }

            vector<pair<int,int> > real_v;

            merge(v.begin(),v.end(),tmp.begin(),tmp.end(),back_inserter(real_v));

            ans = max(ans,brute(real_v));
        }
    }

    printf("%d\n",ans);

    return 0;
}
