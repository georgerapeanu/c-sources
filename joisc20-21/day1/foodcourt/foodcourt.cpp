#include <cstdio>
#include <deque>
#include <vector>
#include <algorithm>

using namespace std;

class SegmentTree{
    struct node_t{
        long long a,b;///LEAVE a, JOIN b

        node_t operator + (const node_t &other)const{
            node_t ans;
            ans = *this;
            ans.b -= other.a;
            if(ans.b < 0){
                ans.a -= ans.b;
                ans.b = 0;
            }
            ans.b += other.b;
            return ans;
        }

        node_t(){
            a = b = 0;
        }

        node_t(long long a,long long b){
            this->a = a;
            this->b = b;
        }
    };

    int n;
    vector<node_t> aint;

    void propagate(int nod,int st,int dr){
        if(st == dr){
            return ;
        }

        aint[nod * 2] = aint[nod * 2] + aint[nod];
        aint[nod * 2 + 1] = aint[nod * 2 + 1] + aint[nod];
        aint[nod] = node_t();
    }
    
    void update(int nod,int st,int dr,int l,int r,node_t val){
        propagate(nod,st,dr);

        if(dr < l || st > r){
            return ;
        }

        if(l <= st && dr <= r){
            aint[nod] = aint[nod] + val;
            return ;
        }

        int mid = (st + dr) / 2;

        update(nod * 2,st,mid,l,r,val);
        update(nod * 2 + 1,mid + 1,dr,l,r,val);
    }

    node_t access(int nod,int st,int dr,int pos){
        propagate(nod,st,dr);
        if(dr < pos || st > pos){
            return node_t();
        }
        if(st == dr){
            return aint[nod];
        }

        int mid = (st + dr) / 2;

        return access(nod * 2,st,mid,pos) + access(nod * 2 + 1,mid + 1,dr,pos);
    }

public:

    SegmentTree(int n){
        this->n = n;
        this->aint = vector<node_t>(4 * n + 5);
    }

    void add(int l,int r,long long value){
        update(1,1,n,l,r,{0,value});
    }

    void remove(int l,int r,long long value){
        update(1,1,n,l,r,{value,0});
    }

    long long access(int pos){
        return access(1,1,n,pos).b;
    }
};

class FenwickTree{
    int n;
    vector<long long> aib;

    void update(int pos,long long value){
        for(;pos <= n;pos += (-pos) & pos){
            aib[pos] += value;
        }
    }

    long long query(int pos){
        long long ans = 0;

        for(;pos;pos -= (-pos) & pos){
            ans += aib[pos];
        }

        return ans;
    }

public:
 
    FenwickTree(int n){
        this->n = n;
        this->aib = vector<long long>(n + 1);
    }

    void add(int l,int r,long long value){
        update(l,value);
        update(r + 1,-value);
    }

    long long access(int pos){
        return query(pos);
    }
};

class SegmentTree2{///cause why not
    int n;
    vector<pair<long long,int> > aint;
    vector<long long> lazy;

    void propagate(int nod,int st,int dr){
        if(lazy[nod] == 0 || st == dr){
            return ;
        }

        lazy[nod * 2] += lazy[nod];
        lazy[nod * 2 + 1] += lazy[nod];
        aint[nod * 2].first += lazy[nod];
        aint[nod * 2 + 1].first += lazy[nod];
        lazy[nod] = 0;
    }

    void build(int nod,int st,int dr){
        if(st == dr){
            aint[nod] = {0,st};
            return ;
        }

        int mid = (st + dr) / 2;

        build(nod * 2,st,mid);
        build(nod * 2 + 1,mid + 1,dr);

        aint[nod] = min(aint[nod * 2],aint[nod * 2 + 1]);
    }

    void update_range(int nod,int st,int dr,int l,int r,long long value){
        propagate(nod,st,dr);

        if(r < st || l > dr){
            return ;
        }

        if(l <= st && dr <= r){
            aint[nod].first += value;
            lazy[nod] += value;
            return ;
        }

        int mid = (st + dr) / 2;

        update_range(nod * 2,st,mid,l,r,value);
        update_range(nod * 2 + 1,mid + 1,dr,l,r,value);

        aint[nod] = min(aint[nod * 2],aint[nod * 2 + 1]);
    }

    void update_set(int nod,int st,int dr,int pos,long long value){
        propagate(nod,st,dr);

        if(dr < pos || st > pos){
            return ;
        }

        if(st == dr){
            aint[nod].first = value;
            return ;
        }

        int mid = (st + dr) / 2;

        update_set(nod * 2,st,mid,pos,value);
        update_set(nod * 2 + 1,mid + 1,dr,pos,value);

        aint[nod] = min(aint[nod * 2],aint[nod * 2 + 1]);
    }

public:

    SegmentTree2(int n){
        this->n = n;
        aint = vector<pair<long long,int> >(4 * n + 5);
        lazy = vector<long long>(4 * n + 5);
        build(1,1,n);
    }

    void update_range(int l,int r,long long value){
        update_range(1,1,n,l,r,value);
    }

    void update_set(int pos,long long value){
        update_set(1,1,n,pos,value);
    }

    pair<long long,int> query(){
        return aint[1];
    }
};

const int NMAX = 250000;
const int MMAX = 250000;
const int QMAX = 250000;

int n,m,q;

struct query_t{
    int l,r,c;
    long long k;    
};

deque<pair<long long,int> > queries[NMAX + 5];
int answer[QMAX + 5];

const int LEN = 1 << 12;
char buff[LEN];
int ind = LEN - 1;

int i32(){
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9'){
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

    return ans;
}

long long i64(){
    long long ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9'){
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

    return ans;
}

int main(){

    n = i32();
    m = i32();
    q = i32();

    vector<query_t> query_list;

    SegmentTree aint(n);
    FenwickTree aib(n);

    for(int i = 1;i <= q;i++){
        int t;
        t = i32();

        if(t == 1){
            int l,r,c;
            long long k;
            l = i32();
            r = i32();
            c = i32();
            k = i64();
            aint.add(l,r,k);
            aib.add(l,r,k);
            query_list.push_back({l,r,c,k});
        }else if(t == 2){
            int l,r;
            long long k;
            l = i32();
            r = i32();
            k = i64();
            aint.remove(l,r,k);
        }else{
            int a;
            long long b;
            a = i32();
            b = i64();
            long long total = aib.access(a);
            long long cnt = aint.access(a);

            if(cnt >= b){
                queries[a].push_back({total - cnt + b,i});
            }else{
                answer[i] = -1;
            }
        }
    }

    SegmentTree2 aint2(n);

    for(int i = 1;i <= n;i++){
        sort(queries[i].begin(),queries[i].end());
        if(queries[i].empty()){
            aint2.update_set(i,1e18);
        }else{
            aint2.update_set(i,queries[i].front().first);
        }
    }
    
    for(auto it:query_list){
        aint2.update_range(it.l,it.r,-it.k);
        while(aint2.query().first <= 0){
            int pos = aint2.query().second;
            answer[queries[pos].front().second] = it.c;
            long long last = queries[pos].front().first;
            queries[pos].pop_front();
            if(queries[pos].empty()){
                aint2.update_set(pos,1e18);
            }else{
                aint2.update_range(pos,pos,queries[pos].front().first - last);
            }
        }
    }

    for(int i = 1;i <= q;i++){
        if(answer[i] != 0){
            printf("%d\n",(answer[i] == -1 ? 0:answer[i]));
        }
    }

    return 0;
}

