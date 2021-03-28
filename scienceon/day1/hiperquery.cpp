#include <cstdio>
#include <map>
#include <unordered_map>
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream f("hiperquery.in");
ofstream g("hiperquery.out");

class SegmentTree{
    
    struct node_t{
        unordered_map<int,int> fr;

        node_t(){
            fr = unordered_map<int,int>();  
        }

        void add(int val,int sgn){
            fr[val] += sgn;
        }

        node_t operator + (const node_t &other)const{
            node_t ans;
            for(auto it:this->fr){
                ans.fr[it.first] += it.second;
            }
            for(auto it:other.fr){
                ans.fr[it.first] += it.second;
            }
            return ans;
        }
    };

    int n;
    vector<node_t> aint;

    void build(int nod,int st,int dr,const vector<int> &v){
        if(st == dr){
            aint[nod].add(v[st],1);
            return ;
        }

        int mid = (st + dr) / 2;

        build(nod * 2,st,mid,v);
        build(nod * 2 + 1,mid + 1,dr,v);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }
       
    void update(int nod,int st,int dr,int pos,int val,int sgn){
        if(dr < pos || st > pos){
            return ;
        }

        aint[nod].add(val,sgn);
        if(st == dr){
            return ;
        }

        int mid = (st + dr) / 2;

        update(nod * 2,st,mid,pos,val,sgn);
        update(nod * 2 + 1,mid + 1,dr,pos,val,sgn);
    }

    int query(int nod,int st,int dr,int l,int r,int x){
        if(r < st || l > dr){
            return 0;
        }

        if(l <= st && dr <= r){
            return aint[nod].fr[x];
        }

        int mid = (st + dr) / 2;

        return query(nod * 2,st,mid,l,r,x) + query(nod * 2 + 1,mid + 1,dr,l,r,x);
    }

public:
    SegmentTree(const vector<int> &v){
        n = v.size();
        aint = vector<node_t>(4 * n + 5);
        build(1,1,n,v);
    }

    void add(int pos,int val){
        update(1,1,n,pos,val,1);
    }
    
    void rem(int pos,int val){
        update(1,1,n,pos,val,-1);
    }

    int query(int l,int r,int x){
        int ans = query(1,1,n,l,r,x);

        return ans;
    }
};

int n,q;
vector<int> v;
int head = 1;

int main(){

    f >> n;
    
    v = vector<int>(n + 1);

    for(int i = 1;i <= n;i++){
        f >> v[i]; 
    }

    f >> q;

    SegmentTree aint(v);

    while(q--){
        int t;
        f >> t;

        if(t == 1){
            int pos,value;
            f >> pos >> value;
            pos = ((head + (pos - 1) - 1) % n) + 1;
            aint.rem(pos,v[pos]);
            v[pos] = value;
            aint.add(pos,v[pos]);
        }else if(t == 2){
            int shift;
            f >> shift;
            shift %= n;
            shift = (n - shift) % n;
            head = (head + shift - 1) % n + 1;
        }else{
            int l,r,x;
            f >> l >> r >> x;
            l = ((head + (l - 1) - 1) % n) + 1;
            r = ((head + (r - 1) - 1) % n) + 1;

            int ans = 0;

            if(l <= r){
                ans += aint.query(l,r,x);
            }else{
                ans += aint.query(1,r,x);
                ans += aint.query(l,n,x);
            }
            
            g << ans << "\n";
        }
    }
    
    f.close();
    g.close();

    return 0;
}
