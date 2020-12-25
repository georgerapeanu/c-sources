#include "monede.h"

using namespace std;

const Raport unu = Raport(1,1);
const Raport zero = Raport(0,1);

struct node_t{
    Raport first,second;

    node_t(Raport p){
        first = unu - p;
        second = p;
    }

    node_t operator * (node_t &other)const{
        node_t ans(zero);
        ans.first = first * other.first + second * other.second;
        ans.second = first * other.second + second * other.first;
        return ans;
    }
};

class SegmentTree{
private:

    int n;
    vector<node_t> aint;
public:

    SegmentTree(){
        ;
    }

    SegmentTree(int n,const Raport p[]){
        this->n = n;
        aint = vector<node_t>(2 * n + 5,node_t(zero));
        for(int i = 0;i < n;i++){
            aint[i + n] = node_t(p[i]);
        }
        for(int i = n - 1;i > 0;i--){
            aint[i] = aint[i<<1] * aint[i<<1|1];
        }
    }

    Raport query(int l,int r){
        r++;
        node_t tmp(zero);
        for(l += n,r += n;l < r;l >>= 1,r >>= 1){
            if(l & 1){
                tmp = tmp * aint[l++];
            }
            if(r & 1){
                tmp = tmp * aint[--r];
            }
        }
        return tmp.second;
    }
}aint;

void init(int N,const Raport p[]) {
    aint = SegmentTree(N,p);
}

Raport solve(int a, int b) {
    return aint.query(a,b);
}
