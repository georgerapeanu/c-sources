#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <algorithm>

#include "floppy.h"

using namespace std;

const int LGMAX = 16;
const int NMAX = 40000;

class SegmentTree{

    struct node_t{
        int val;
        int pos;

        node_t operator + (const node_t &other)const{
            node_t ans;
            if(this->val < other.val){
                ans = *this;
            }
            else{
                ans = other;
            }
            return ans;
        }
    };
   
    int n;
    vector<node_t> aint;

    void build(int nod,int st,int dr,vector<int> &stuff){
        if(st == dr){
            aint[nod].val = stuff[st];
            aint[nod].pos = st;
            return ;
        }

        int mid = (st + dr) / 2;

        build(nod * 2,st,mid,stuff);
        build(nod * 2 + 1,mid + 1,dr,stuff);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    node_t query(int nod,int st,int dr,int l,int r){
        if(dr < l || st > r){
            return {int(1e9),0};
        }
        if(l <= st && dr <= r){
            return aint[nod];
        }

        int mid = (st + dr) / 2;

        return query(nod * 2,st,mid,l,r) + query(nod * 2 + 1,mid + 1,dr,l,r);
    }
public:

    SegmentTree(vector<int> &stuff){
        this->n = stuff.size();
        this->aint = vector<node_t>(4 * n + 5);
        build(1,0,n - 1,stuff);
    }

    int query(int l,int r){
        return query(1,0,n - 1,l,r).pos;
    }

};

string int_to_bin(int val,int pw2){
    string ans = "";

    for(int i = pw2;i >= 0;i--){
        ans += ((val >> i) & 1) + '0';
    }
    return ans;
}

void read_array(int subtask_id, const vector<int> &v) {
    string bits;

    vector<int> st;

    int n = v.size();

    for(auto it:v){
        while(st.empty() == false && st.back() < it){
            bits += '0';
            st.pop_back();
        }
        bits += '1';
        st.push_back(it);
    }

    save_to_floppy(bits);
}

int father[LGMAX + 1][NMAX + 5];
vector<int> solve_queries(int subtask_id, int n,
    const string &bits,
    const vector<int> &a, const std::vector<int> &b) {
    vector<int> answers;

    vector<int> pos;

    int lst = 1;

    for(auto it:bits){
        if(it == '1'){
            father[0][lst] = (pos.empty() ? 0:pos.back());
            pos.push_back(lst);
            lst++;
        }
        else{
            pos.pop_back();
        }
    }

    for(int i = 1;i <= LGMAX;i++){
        for(int j = 1;j < lst;j++){
            father[i][j] = father[i - 1][father[i - 1][j]];
        }
    }

    for(int i = 0;i < (int)a.size();i++){
        int ans = b[i] + 1;
        for(int h = LGMAX;h >= 0;h--){
            if(father[h][ans] >= a[i] + 1){
                ans = father[h][ans];
            }
        }
        answers.push_back(ans - 1);
    }

    return answers;
}
