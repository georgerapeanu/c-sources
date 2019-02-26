#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

struct query_t{
    int t,l,r,v;
};

const int NMAX = 1e5;
const int no_lazy = -1;

int q;
query_t queries[NMAX + 5];

vector<int> events;
vector<int> weight;
map<int,int> norm;
set< pair<int,int> > active;

struct node_t{
    long long min_sum;
    long long sum;
    int total_weight;

    node_t operator + (const node_t &other)const{ // join operator
        node_t ans;
        ans.min_sum = min(this->min_sum,this->sum + other.min_sum);
        ans.sum = this->sum + other.sum;
        ans.total_weight  = this->total_weight + other.total_weight;
        return ans;
    }

    node_t operator + (const int &other)const{///join with val operator
        node_t ans;
        ans.total_weight = this->total_weight;
        ans.sum = 1LL * ans.total_weight * other;
        ans.min_sum = min(1LL * other,ans.sum);
        return ans;
    }
};

int lazy[4 * NMAX + 5];
node_t aint[4 * NMAX + 5];
int ST[4 * NMAX + 5];
int DR[4 * NMAX + 5];

void build(int nod,int st,int dr){
    lazy[nod] = no_lazy;

    ST[nod] = st;
    DR[nod] = dr;

    if(st == dr){
        aint[nod].min_sum = 0;
        aint[nod].sum = 0;
        aint[nod].total_weight = weight[st];
        return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);

    aint[nod] = aint[2 * nod] + aint[2 * nod + 1];
}

void propag(int nod,int st,int dr){
    if(st == dr || lazy[nod] == no_lazy){
        return ;
    }

    aint[2 * nod] = aint[2 * nod] + lazy[nod];
    aint[2 * nod + 1] = aint[2 * nod + 1] + lazy[nod];
    lazy[2 * nod] = lazy[nod];
    lazy[2 * nod + 1] = lazy[nod];

    lazy[nod] = no_lazy;
}

void update(int nod,int st,int dr,int S,int D,int val){
    propag(nod,st,dr);
    
    if(dr < S || st > D){
        return ;
    }

    if(S <= st && dr <= D){
        aint[nod] = aint[nod] + lazy[nod];
        lazy[nod] = val;
        return;
    }

    int mid = (st + dr) / 2;
    
    update(nod * 2,st,mid,S,D,val);
    update(nod * 2 + 1,mid + 1,dr,S,D,val);
    aint[nod] = aint[2 * nod] + aint[2 * nod + 1];
}

double query(int nod,int st,int dr,int l,int r,int v){
    if(v == 0){
        return l;
    }
    propag(nod,st,dr);
    while(st != l){
        int mid = (st + dr) / 2;
        if(l <= mid){
            dr = mid;
            nod = nod * 2;
        }
        else{
            st = mid + 1;
            nod = nod * 2 + 1;
        }
    }
    
    node_t initial;

    initial.sum = v;
    initial.min_sum = v;
    initial.total_weight = 0;

    initial = initial + aint[nod];

    if(initial.min_sum <= 0){
        int slope = aint[nod].sum / aint[nod].total_weight;
        long long sum = initial.sum;
        int weight = aint[nod].total_weight;
        return l + weight + (double)sum / slope;
    }

    while(1){
        if(nod % 2 == 0){
            nod /= 2;
            node_t tmp = initial + aint[nod * 2 + 1];
            if(tmp.min_sum < 0){
                nod = nod * 2 + 1;
                break;
            }
        }
        else{
            nod /= 2;
        }
    }

    st = ST[nod];
    dr = DR[nod];

    while(st != dr){
        node_t tmp = initial + aint[2 * nod];
        if(tmp.min_sum <= 0){
            nod = nod * 2;
        }
        else{
            initial = tmp;
            nod = nod * 2 + 1;
        }
        st = ST[nod];
        dr = DR[nod];
    }

    initial = initial + aint[nod];

    ///answer is st;
    int slope = aint[nod].sum / aint[nod].total_weight;
    long long sum = initial.sum;
    int weight = aint[nod].total_weight;

    return l + weight + (double)sum / slope;

}

int main(){

    scanf("%d",&q);

    for(int i = 1;i <= q;i++){
        scanf("%d",&queries[i].t);
        if(queries[i].t == 1){
            scanf("%d %d",&queries[i].l,&queries[i].r);
            events.push_back(queries[i].l);
        }
        else if(queries[i].t == 2){
            scanf("%d",&queries[i].l);
        }
        else{
            scanf("%d %d %d",&queries[i].l,&queries[i].r,&queries[i].v);
            events.push_back(queries[i].l);
            events.push_back(queries[i].r);
        }
    }

    sort(events.begin(),events.end());
    events.resize(unique(events.begin(),events.end()) - events.begin());
    
    vector<int> new_events;

    new_events.push_back(events[0]);
    weight.push_back(1);

    for(int i = 1;i < (int)events.size();i++){

        if(events[i] - 1 != events[i - 1]){
            new_events.push_back(events[i - 1] + 1);
            weight.push_back(events[i] - events[i - 1] - 1);
        }

        new_events.push_back(events[i]);
        weight.push_back(1);
    }
    new_events.push_back(events.back() + 1);
    weight.push_back(1);
    active.insert({events.back() + 1,20});

    events = new_events;

    for(int i = 0;i < (int)events.size();i++){
        norm[events[i]] = i;
    }

    build(1,0,(int)events.size() - 1);

    for(auto it:queries){
        if(it.t == 1){
            active.insert({norm[it.l],it.r});
            set<pair<int,int> > :: iterator it2 = active.lower_bound({norm[it.l] + 1,-20});
            update(1,0,(int)events.size() - 1,norm[it.l],it2->first - 1,it.r);
        }
        else if(it.t == 2){
            int st = norm[it.l];
            active.erase(active.lower_bound({norm[it.l],0}));
            set<pair<int,int> > :: iterator it2 =  active.lower_bound({norm[it.l],0});
            int dr = it2->first;
            int val = 0;
            if(it2 != active.begin()){
                it2--;
                val = it2->first;
            }
            update(1,0,(int)events.size() - 1,st,dr - 1,val);
        }
        else if(it.t == 3){
            printf("%.8f\n",query(1,0,(int)events.size() - 1,norm[it.l],norm[it.r],it.v));
        }
    }


    return 0;
}
