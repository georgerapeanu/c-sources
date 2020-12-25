#include <bits/stdc++.h>

using namespace std;

struct event_t{
    int x;
    int l,r;
    int type;
    int id;

    event_t(){
        x = l = r = type = id;
    }

    event_t(int x,int l,int r,int type,int id){
        this->x = x;
        this->l = l;
        this->r = r;
        this->type = type;
        this->id = id;
    }

    bool operator < (const event_t &other)const{
        if(this->x != other.x){
            return this->x < other.x;
        }
        return type < other.type;
    }
};

struct query_t{
    int x,y;
    int st,dr;
};


vector<int> ok(int query_size,vector<event_t> edges){

    sort(edges.begin(),edges.end());

    vector<int> ok(query_size,1);

    set<int> active;

    for(auto it:edges){
        if(it.type == -1){
            active.erase(it.l);
        }
        else if(it.type == 1){
            active.insert(it.l);
        }
        else{
            set<int> :: iterator it2 = active.lower_bound(it.l + 1);
            if(it2 != active.end() && *it2 < it.r){
                ok[it.id] = false;
            }
        }
    }

    return ok;
}

vector<int> solve(const vector<event_t> &x_edges,const vector<event_t> &y_edges,vector<query_t> &queries){
    while(true){
        bool done = true;
        for(auto it:queries){
            done &= (it.dr - it.st <= 1);
        }
        if(done == true){
            break;
        }
        vector<event_t> x = x_edges,y = y_edges;
        for(int i = 0;i < (int)queries.size();i++){
            query_t it = queries[i];
            int mid = (it.st + it.dr) / 2;
            x.push_back(event_t(it.x,it.y,it.y + mid,0,i));
            x.push_back(event_t(it.x + mid,it.y,it.y + mid,0,i));
            y.push_back(event_t(it.y,it.x,it.x + mid,0,i));
            y.push_back(event_t(it.y + mid,it.x,it.x + mid,0,i));
        }
        
        vector<int> ok_x = ok(queries.size(),x);
        vector<int> ok_y = ok(queries.size(),y);
    
        for(int i = 0;i < (int)queries.size();i++){
            if(ok_x[i] && ok_y[i]){
                queries[i].st = (queries[i].st + queries[i].dr) / 2;
            }
            else{
                queries[i].dr = (queries[i].st + queries[i].dr) / 2;
            }
        }
    }

    vector<int> ans;

    for(auto it:queries){
        ans.push_back(it.st);
    }
    return ans;
}

int main(){

    int n,m;
    vector<pair<int,int> > v;

    vector<event_t> x_edges;
    vector<event_t> y_edges;

    while(scanf("%d %d",&n,&m) != EOF){
        x_edges.clear();
        y_edges.clear();
        v.clear();

        for(int i = 0;i < n;i++){
            int x,y;
            scanf("%d %d",&x,&y);
            v.push_back({x,y});
        }

        for(int i = 0;i < n;i++){
            if(v[i].first == v[(i + 1) % n].first){
                y_edges.push_back({min(v[i].second,v[(i + 1) % n].second),v[i].first,-1,1,i});
                y_edges.push_back({max(v[i].second,v[(i + 1) % n].second),v[i].first,-1,-1,i});
            }
            else{
                x_edges.push_back({min(v[i].first,v[(i + 1) % n].first),v[i].second,-1,1,i});
                x_edges.push_back({max(v[i].first,v[(i + 1) % n].first),v[i].second,-1,-1,i});
            }
        }
        vector<query_t> queries(m);
        for(auto &it:queries){
            it.st = 0;
            it.dr = 2e8 + 5;
            scanf("%d %d",&it.x,&it.y);
        }

        vector<int> ans = solve(x_edges,y_edges,queries);

        for(auto it:ans){
            printf("%d\n",it);
        }
    }

    return 0;
}
