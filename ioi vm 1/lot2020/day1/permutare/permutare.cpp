#include "permutare.h"

#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

struct node_t{
    int val;
    int fr;

    node_t operator + (const node_t &other){
        node_t ans = {0,0};
        if(this->val <= other.val){
            ans.val = this->val;
            ans.fr += this->fr;
        }
        if(this->val >= other.val){
            ans.val = other.val;
            ans.fr += other.fr;
        }
        return ans;
    }

    void propag(int lazy){
        val += lazy;
    }
};

class SegmentTree{
private:
    int n;
    vector<node_t> aint;
    vector<int> lazy;

    void propag(int nod,int st,int dr){
        if(st == dr || lazy[nod] == 0){
            return ;
        }
        aint[nod * 2].propag(lazy[nod]);lazy[nod * 2] += lazy[nod];
        aint[nod * 2 + 1].propag(lazy[nod]);lazy[nod * 2 + 1] += lazy[nod];
        lazy[nod] = 0;
    }

    void build(int nod,int st,int dr){
        lazy[nod] = 0;
        if(st == dr){
            aint[nod] = {0,1};
            return ;
        }
        int mid = (st + dr) / 2;
        
        build(nod * 2,st,mid);
        build(nod * 2 + 1,mid + 1,dr);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    void update(int nod,int st,int dr,int l,int r,int val){
        propag(nod,st,dr);
        if(dr < l || r < st){
            return ;
        }
        if(l <= st && dr <= r){
            lazy[nod] += val;
            aint[nod].propag(val);
//            printf("aint %d is now %d %d\n",nod,aint[nod].val,aint[nod].fr);
            return ;
        }

        int mid = (st + dr) / 2;

        update(nod * 2,st,mid,l,r,val);
        update(nod * 2 + 1,mid + 1,dr,l,r,val);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
//        printf("aint %d is now %d %d\n",nod,aint[nod].val,aint[nod].fr);
    }

    node_t query(int nod,int st,int dr,int l,int r){
        propag(nod,st,dr);
        if(dr < l || r < st){
            return {(int)1e9,0};
        }
        if(l <= st && dr <= r){
            return aint[nod];
        }

        int mid = (st + dr) / 2;

        return query(nod * 2,st,mid,l,r) + query(nod * 2 + 1,mid + 1,dr,l,r);
    }

public:
    SegmentTree(int n){
        this->n = n;
        aint = vector<node_t>(4 * n + 5,{(int)1e9,0});
        lazy = vector<int>(4 * n + 5,0);
        build(1,1,n);
    }

    void update(int l,int r,int val){
        this->update(1,1,n,l,r,val);
    }

    int query(int l,int r){///number of non-zero values
        node_t tmp = query(1,1,n,l,r);
    //    printf("query %d %d is %d %d\n",l,r,tmp.val,tmp.fr);
        return (r - l + 1) - (tmp.val == 0) * tmp.fr;
    }
}aint(1);

int n;
vector<int> perm;

int brut(const vector<int> &p){
    n = (int)p.size();
    int ma = 0;
    int cst = 0;

    for(int i = 0;i < (int)p.size();i++){
        ma = max(ma,p[i]);
        cst += (ma > i);
    }
    return cst;
}

void baga(int pos,int val,int sgn){
    if(val < pos){
  //      printf("adds %d %d %d\n",val,pos - 1,sgn);
        aint.update(val,pos - 1,sgn);
    }
}

int init(std::vector<int> p) {
    aint = SegmentTree((int)p.size());
    n = (int)p.size();

    perm.push_back(0);

    for(int i = 0;i < (int)p.size();i++){
        perm.push_back(p[i] + 1);
    }

    for(int i = 1;i < (int)perm.size();i++){
        baga(i,perm[i],1);
    }

    return aint.query(1,n);
}

int query(int x, int y) {
    x++;
    y++;

    baga(x,perm[x],-1);
    baga(y,perm[y],-1);

    swap(perm[x],perm[y]);
    
    baga(x,perm[x],1);
    baga(y,perm[y],1);

    return aint.query(1,n);
}
