#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

struct node_t{
    vector<int> vals;
    int lazy;

    node_t operator + (const node_t &other)const{
        node_t ans;
        for(auto it:this->vals){
            ans.vals.push_back(it);
        }
        for(auto it:other.vals){
            ans.vals.push_back(it);
        }
        sort(ans.vals.begin(),ans.vals.end());
        while((int)ans.vals.size() > 2){
            ans.vals.pop_back();
        }
        while((int)ans.vals.size() < 2){
            ans.vals.push_back(1e9);
        }
        ans.lazy = 0;
        return ans;
    }

    node_t(){
        vals = vector<int>();
        lazy = 0;
    }
};

class SegmentTreeBeats{
private:
    int n;
    vector<node_t> aint;
    
    void propag(int nod,int st,int dr){
        if(st == dr || aint[nod].lazy == 0){
            return ;
        }
        if(aint[nod * 2].vals[0] == aint[nod].vals[0]){
            aint[nod * 2].vals[0] = aint[nod].lazy;
            aint[nod * 2].lazy = aint[nod].lazy;
        }
        if(aint[nod * 2 + 1].vals[0] == aint[nod].vals[0]){
            aint[nod * 2 + 1].vals[0] = aint[nod].lazy;
            aint[nod * 2 + 1].lazy = aint[nod].lazy;
        }
        aint[nod].lazy = 0;
    }

    void build(int nod,int st,int dr){
        if(st == dr){
            aint[nod] = node_t();
            aint[nod].vals = {0,(int)1e9};
            return ;
        }

        int mid = (st + dr) / 2;

        build(nod * 2,st,mid);
        build(nod * 2 + 1,mid + 1,dr);
        
        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    bool update(int nod,int st,int dr,int l,int r,int val){
        propag(nod,st,dr);
        if(dr < l || st > r || aint[nod].vals[0] >= val){
            return 0;
        }
        if(l <= st && dr <= r && aint[nod].vals[1] > val){
            aint[nod].vals[0] = val;
            aint[nod].lazy = val;
            return 1;
        }
        int mid = (st + dr) / 2;

        bool ans = update(nod * 2,st,mid,l,r,val) | update(nod * 2 + 1,mid + 1,dr,l,r,val);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
        return ans;
    }

public:

    SegmentTreeBeats(int n){
        this->n = n;
        aint = vector<node_t>(4 * n + 5);
        build(1,1,n);
    }

    bool update(int st,int dr,int val){
        return update(1,1,n,st,dr,val);
    }
};

int n;
int a[NMAX + 5];
vector<int> pos[NMAX + 5];

int main(){

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        scanf("%d",&a[i]);
        pos[a[i]].push_back(i);
    }

    if((int)pos[1].size() == n){
        printf("1\n");
        return 0;
    }

    for(int i = 1;i <= n + 2;i++){
        pos[i].push_back(n + 1);
    }

    SegmentTreeBeats aint(n);

    for(int i = 1;i <= n + 2;i++){
        int lst = 0;
        bool ok = false;
        for(auto it:pos[i]){
            if(it <= n){
                ok |= aint.update(lst + 1,it,it);
            }
            else{
                ok |= aint.update(lst + 1,n,n + 1);
            }
            lst = it;
        }
        if(ok == false){
            printf("%d\n",i);
            return 0;
        }
    }

    return 0;
}
