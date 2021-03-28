#include <cstdio>
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream f("hipersir.in");
ofstream g("hipersir.out");

const int MOD = 1e9 + 7;
const int inv2 = 500000004;
const int inv11 = 818181824;

int add(int a,int b){
    a += b;
    if(a >= MOD){
        a -= MOD;
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

class SegmentTree{
    int n;
    vector<int> aint;

    void build(int nod,int st,int dr,const string &s){
        /*for(int i = 1;i <= n;i++){
            aint[i] = mult(s[i - 1] - '0',mult(powers[3][i],powers[0][i]));
        }*/

        if(st == dr){
            aint[nod] = mult(s[st - 1] - '0',mult(lgpow(inv11,st),lgpow(2,st)));
            return ;
        }

        int mid = (st + dr) / 2;

        build(nod * 2,st,mid,s);
        build(nod * 2 + 1,mid + 1,dr,s);

        aint[nod] = add(aint[nod * 2],aint[nod * 2 + 1]);
    }
       
    void update(int nod,int st,int dr,int pos,int val){
        if(dr < pos || st > pos){
            return ;
        }

        if(st == dr){
            aint[nod] = val;
            return ;
        }

        int mid = (st + dr) / 2;

        update(nod * 2,st,mid,pos,val);
        update(nod * 2 + 1,mid + 1,dr,pos,val);

        aint[nod] = add(aint[nod * 2],aint[nod * 2 + 1]);
    }

    int query(int nod,int st,int dr,int l,int r){
        if(r < st || l > dr){
            return 0;
        }

        if(l <= st && dr <= r){
            return aint[nod];
        }

        int mid = (st + dr) / 2;

        return add(query(nod * 2,st,mid,l,r),query(nod * 2 + 1,mid + 1,dr,l,r));
    }

public:
    SegmentTree(const string &s){
        n = s.size();
        aint = vector<int>(4 * n + 5);
        build(1,1,n,s);
    }

    void update(int pos,int val){
        //aint[pos] = mult(val,mult(powers[3][pos],powers[0][pos]));
        update(1,1,n,pos,mult(val,mult(lgpow(inv11,pos),lgpow(2,pos))));
    }

    int query(int l,int r){
        int ans = query(1,1,n,l,r);

        /*for(int i = l;i <= r;i++){
            ans = add(ans,aint[i]);
        }*/

        ans = mult(ans,lgpow(11,r));
        ans = mult(ans,lgpow(inv2,l));

        return ans;
    }
};

int n,q;
string s;

int main(){
    
    f >> n >> q;
    f >> s;

    SegmentTree aint(s);

    while(q--){
        int t,l,r;
        f >> t >> l >> r;

        if(t == 1){
            aint.update(l,r);
        }else{
            g << aint.query(l,r) << "\n";
        }
    }

    f.close();
    g.close();

    return 0;
}
