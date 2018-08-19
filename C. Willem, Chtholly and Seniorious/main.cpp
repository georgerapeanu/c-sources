#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <cassert>
using namespace std;
int N,M,seed,vmax,op,l,r,x,y;
struct inter{
    int l,r;
    long long val;
    bool operator < (const inter &other)const{
        return l < other.l;
    }
};
set<inter> S;
int rnd(){
    int ret = seed;
    seed = (1LL * seed * 7 + 13) % 1000000007;
    return ret;
}
int lgpow(int b,int e,int MOD){
    int p = 1;
    while(e){
        if(e & 1){
            p = 1LL * p * b % MOD;
        }
        b = 1LL * b * b % MOD;
        e >>= 1;
    }
    return p;
}
bool cmp(inter a,inter b){
    return a.val < b.val;
}
void geninput(){
    op = rnd() % 4 + 1;
    l = rnd() % N + 1;
    r = rnd() % N + 1;
    if(r < l){
        swap(l,r);
    }
    if(op == 3){
        x = rnd() % (r - l + 1) + 1;
    }
    else {
        x = rnd() % vmax + 1;
    }
    if(op == 4){
        y = rnd() % vmax + 1;
    }
}
void maninput(){
    cin >> op >> l >> r >> x;
    if(op == 4)cin >> y;
}
int main(){
    cin >> N >> M >> seed >> vmax;
    for(int i = 1;i <= N;i++){
        int val;
        val = rnd() % vmax + 1;
        //cin >> val;
        S.insert({i,i,val});
    }
    for(int i = 1;i <= M;i++){
        geninput();
        vector<inter> tmp;
        set<inter> :: iterator it = S.lower_bound({l,r,0});
        if(it != S.begin() && (it == S.end() || it->l > l)){
            it--;
        }
        while(it != S.end() && it->l <= r){
            tmp.push_back(*it);
            set<inter> :: iterator aux = it;it++;
            S.erase(aux);
        }
        assert(!tmp.empty());
        if(tmp[0].l < l){
            S.insert({tmp[0].l,l-1,tmp[0].val});
            tmp[0].l = l;
        }
        if(tmp.back().r > r){
            S.insert({r + 1,tmp.back().r,tmp.back().val});
            tmp.back().r = r;
        }
        if(op == 2){
            S.insert({l,r,x});
        }
        else if(op == 3)
        {
            sort(tmp.begin(),tmp.end(),cmp);
            for(auto it:tmp){
                 if(x>0){
                    x -= it.r - it.l + 1;
                    if(x <= 0){
                        cout << it.val << "\n";
                    }
                }
                S.insert(it);
            }
        }
        else{
            int rez = 0;
            for(auto it:tmp){
                if(op == 1){
                    it.val += x;
                    S.insert(it);
                }
                else{
                    rez = (rez + 1LL * (it.r - it.l + 1) * lgpow(it.val % y,x,y)) % y;
                    S.insert(it);
                }
            }
            if(op == 4){
                cout << rez << "\n";
            }
        }
    }
    return 0;
}
