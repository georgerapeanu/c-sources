#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

FILE *f = fopen("prieteni2.in","r");
FILE *g = fopen("prieteni2.out","w");

class SegmentTree{
    struct node_t{
        int best;
        int best_left;
        int best_right;
        bool active_right;
        bool whole_array;

        node_t(){
            best = best_left = best_right = 1;
            active_right = false;
            whole_array = true;
        }

        node_t operator + (const node_t &other)const{
            node_t ans;
            ans.best = max(this->best,other.best);
            if(this->active_right){
                ans.best = max(ans.best,this->best_right + other.best_left);
            }
            ans.best_left = this->best_left;
            if(this->whole_array && this->active_right){
                ans.best_left = max(ans.best_left,this->best_left + other.best_left);
            }
            ans.best_right = other.best_right;
            if(other.whole_array && this->active_right){
                ans.best_right = max(ans.best_right,this->best_right + other.best_right);
            }
            ans.active_right = other.active_right;
            if(this->active_right && this->whole_array && other.whole_array){
                ans.whole_array = 1;
            }
            else{
                ans.whole_array = 0;
            }
            return ans;
        }

        void flip(){
            this->active_right ^= 1;
        }

        void set(bool val){
            this->active_right = val;
        }

        void afis(){
            printf("%d %d %d %d %d\n",best,best_left,best_right,active_right,whole_array);
        }
    };

    int n;
    vector<node_t> aint;

    void build(int nod,int st,int dr){
        if(st == dr){
            aint[nod] = node_t();
            return ;
        }
        
        int mid = (st + dr) / 2;

        build(nod * 2,st,mid);
        build(nod * 2 + 1,mid + 1,dr);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    void update(int nod,int st,int dr,int pos,bool val){
        if(dr < pos || st > pos){
            return ;
        }
        if(st == dr){
            aint[nod].set(val);
            return ;
        }

        int mid = (st + dr) / 2;

        update(nod * 2,st,mid,pos,val);
        update(nod * 2 + 1,mid + 1,dr,pos,val);

        aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
    }

    node_t query(int nod,int st,int dr,int l,int r){
        if(l <= st && dr <= r){
            return aint[nod];
        }

        int mid = (st + dr) / 2;

        if(mid < l){
            return query(nod * 2 + 1,mid + 1,dr,l,r);
        }
        else if(l <= mid && mid + 1 <= r){
            return query(nod * 2,st,mid,l,r) + query(nod * 2 + 1,mid + 1,dr,l,r);
        }
        else{
            return query(nod * 2,st,mid,l,r);
        }
    }

    void afis(int nod,int st,int dr){
        printf("deb %d %d %d ",nod,st,dr);
        aint[nod].afis();

        if(st == dr){
            return ;
        }

        int mid = (st + dr) / 2;

        afis(nod * 2,st,mid);
        afis(nod * 2 + 1,mid + 1,dr);
    }

public:

    SegmentTree(int n){
        this->n = n;
        this->aint = vector<node_t>(4 * n + 5);
        this->build(1,1,n);
    }

    void update(int pos,bool val){
        this->update(1,1,n,pos,val);
    }

    int query(int l,int r){
        return query(1,1,n,l,r).best;
    }

    void afis(){
        this->afis(1,1,n);
    }
};

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;
    
    while(buff[ind] < '0' || buff[ind] > '9'){
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    
    while(!(buff[ind] < '0' || buff[ind] > '9')){
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN){
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }
    return ans;
}

const int NMAX = 2e5;
bool active[NMAX + 5];

int brut(int l,int r){
    int len = 1;
    int ans = 1;
    for(int i = l + 1;i <= r;i++){
        len = 1 + (active[i - 1] ? len:0);
        ans = max(ans,len);
    }
    return ans;
}

int main(){
    
    int n,q;

    n = i32();
    q = i32();

    SegmentTree aint(n);

    while(q--){
        int t;
        t = i32();
        if(t == 1){
            int pos;
            pos = i32();
            aint.update(pos,true);
            active[pos] = true;
        }else if(t == 2){
            int pos;
            pos = i32();
            aint.update(pos,false);
            active[pos] = false;
        }else{
            int l,r;
            l = i32();
            r = i32();
            fprintf(g,"%d\n",aint.query(l,r));
    //        printf("%d %d\n",aint.query(l,r),brut(l,r));
    //        assert(aint.query(l,r) == brut(l,r));
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
