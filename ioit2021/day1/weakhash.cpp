#include <bits/stdc++.h>

using namespace std;

const int MOD = 10000019;

int add(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
    }
    return a;
}

int scad(int a,int b){
    a -= b;
    if(a < 0){
        a += MOD;
    }
    return a;
}

int mult(int a,int b){
    return 1LL * a * b % MOD;
}

int lgpow(int b,int e){
    int p = 1;

    while(e){
        if(e & 1){
            p = mult(p,b);
        }

        b = mult(b,b);
        e >>= 1;
    }

    return p;
}

int n;
int h;
vector<pair<int,int> > fst;
vector<pair<int,int> > snd;
vector<pair<int,int> > tmp;

void solve(int st,int dr,vector<pair<int,int> > &ans){
    ans.push_back({1,1});

    for(int i = st;i <= dr;i++){
        tmp.clear();
        for(int cf = 1;cf <= 9;cf++){
            for(int j = 0;j < (int)ans.size();j++){
                tmp.push_back({mult(ans[j].first,cf),ans[j].second});
            }
        }
        sort(tmp.begin(),tmp.end());
        ans.clear();
        for(int i = 0;i < (int)tmp.size();i++){
            if(ans.empty() || ans.back().first != tmp[i].first){
                ans.push_back({tmp[i].first,0});
            }
            ans.back().second = add(ans.back().second,tmp[i].second);
        }
    }
}


int solve_snd(int value,int cnt){
    int inv_value = lgpow(value,MOD - 2);
    int snd_value = mult(inv_value,h);
    vector<pair<int,int> > :: iterator it = lower_bound(snd.begin(),snd.end(),make_pair(snd_value,0));
    if(it == snd.end() || it->first != snd_value){
        return 0;
    }
    return mult(cnt,it->second);
}

int main(){

    scanf("%d %d",&n,&h);

    int mid = (n + 1) / 2;

    solve(1,mid,fst);
    solve(mid + 1,n,snd);

    int ans = 0;

    for(int i = 0;i < (int)fst.size();i++){
        ans = add(ans,solve_snd(fst[i].first,fst[i].second));
    }

    printf("%d\n",ans);

    return 0;
}

