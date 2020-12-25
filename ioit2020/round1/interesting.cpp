#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int n;
int val[NMAX + 5];

struct data_t{
    map<int,int> fr;
    set<pair<int,int> > inv_fr;

    void insert(int val){
        if(fr.count(val)){
            inv_fr.erase({fr[val],val});
        }
        fr[val]++;
        inv_fr.insert({fr[val],val});
    }

    void erase(int val){
        inv_fr.erase({fr[val],val});
        fr[val]--;
        if(fr[val] == 0){
            fr.erase(val);
        }
        else{
            inv_fr.insert({fr[val],val});
        }
    }

    int min_fr(){
        return inv_fr.begin()->first;
    }

    int max_fr(){
        return inv_fr.rbegin()->first;
    }

    long long compute(){
        return 1LL * inv_fr.begin()->first * inv_fr.rbegin()->first;
    }

    void afis(){
        for(auto it:fr)printf("fr %d %d\n",it.first,it.second);
        for(auto it:inv_fr)printf("inv_fr %d %d\n",it.first,it.second);
    }
};

long long solve(int l,int r,data_t &stuff,bool computed){
    if(l > r){
        return 0;
    }
    if(computed == 0){
        for(int i = l;i <= r;i++){
            stuff.insert(val[i]);
        }
    }

    long long ans = stuff.compute();

    int last = l - 1;

    vector<pair<int,int> > segm;

    for(int i = l;i <= r;i++){
        if(stuff.fr[val[i]] == stuff.min_fr()){
            segm.push_back({last + 1,i - 1});
            last = i;
        }
    }

    segm.push_back({last + 1,r});

    sort(segm.begin(),segm.end(),[&](const pair<int,int> &a,const pair<int,int> &b){
                return a.second - a.first > b.second - b.first;
            });

    for(int i = 1;i < (int)segm.size();i++){
        data_t tmp;
        ans = max(ans,solve(segm[i].first,segm[i].second,tmp,0));
    }

    for(int i = l;i < segm[0].first;i++){
        stuff.erase(val[i]);
    }
    
    for(int i = segm[0].second + 1;i <= r;i++){
        stuff.erase(val[i]);
    }

    ans = max(ans,solve(segm[0].first,segm[0].second,stuff,1));
    
    return ans;
}

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&val[i]);
    }

    data_t tmp;
    printf("%lld\n",solve(1,n,tmp,0));

    return 0;
}
