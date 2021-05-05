#include <bits/stdc++.h>

using namespace std;

const int NMAX = 25e4;

int n,k;

map<long long,int> to_norm;
pair<long long,long long> v[NMAX + 5];

class FenwickTree{
    vector<int> aib;
    int n;

public:

    FenwickTree(int n){
        this->n = n;
        this->aib = vector<int>(n + 1);
    }

    void update(int pos,int value){
        for(;pos <= n;pos += (-pos) & pos){
            aib[pos] += value;
        }
    }

    int query(int pos){
        int ans = 0;
        for(;pos;pos -= (-pos) & pos){
            ans += aib[pos];
        }
        return ans;
    }
    
    void reset(){
        for(auto &it:aib){
            it = 0;
        }
    }

}aib(0);

long long get_count(long long dist){
    aib.reset();
    int lst = 1;
    long long ans = 0;

    for(int i = 1;i <= n;i++){
        while(v[i].first - v[lst].first > dist){
            aib.update(to_norm[v[lst].second],-1);
            lst++;
        }

        int l = to_norm.lower_bound(v[i].second - dist)->second;
        map<long long,int> :: iterator it = to_norm.lower_bound(v[i].second + dist + 1);
        int r = (it == to_norm.end() ? n:it->second);
        
        ans += aib.query(r) - aib.query(l - 1);
        
        aib.update(to_norm[v[i].second],1);

    }

    return ans;
}

vector<long long> get_distances(long long dist){
    vector<long long> ans;
    int lst = 1;
    set<pair<long long,long long> > s;
    for(int i = 1;i <= n;i++){
        while(v[i].first - v[lst].first > dist){
            s.erase({v[lst].second,v[lst].first});
            lst++;
        }
        for(set<pair<long long,long long> > :: iterator it = s.lower_bound({v[i].second - dist,-2e9 - 10});it != s.end() && it->first <= v[i].second + dist;it++){
            ans.push_back(max(abs(v[i].first - it->second),abs(v[i].second - it->first)));
        }
        s.insert({v[i].second,v[i].first});
    }

    sort(ans.begin(),ans.end());
    return ans;
}

const int LEN = 1 << 12;
char buff[LEN];
int ind;

int i32(){
    int sgn = 1;
    int ans = 0;

    while((buff[ind] < '0' || buff[ind] > '9') && buff[ind] != '-'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    if(buff[ind] == '-'){
        sgn = -1;
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }
    
    while(!(buff[ind] < '0' || buff[ind] > '9')){
        ans = ans * 10 + buff[ind] - '0';
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    return ans * sgn;
}


int main(){
    
    n = i32();
    k = i32();

    aib = FenwickTree(n);

    for(int i = 1;i <= n;i++){
        int x,y;
        x = i32();
        y = i32();
        v[i] = {x + y,x - y};
        to_norm[v[i].second] = 1;
    }

    sort(v + 1,v + 1 + n);

    int lst = 0;

    for(auto &it:to_norm){
        it.second = ++lst;
    }

    long long l = 0;
    long long r = 4e9 + 5;

    while(r - l > 1){
        long long mid = (l + r) / 2;

        if(get_count(mid) < k){
            l = mid;
        }else{
            r = mid;
        }
    }

    vector<long long> ans = get_distances(l);

    while((int)ans.size() < k){
        ans.push_back(r);
    }

    for(auto it:ans){
        printf("%lld\n",it);
    }
    
    return 0;
}

