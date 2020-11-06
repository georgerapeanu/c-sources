#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>

using namespace std;

const int NMAX = 1e5;
const int UMAX = 2e5;

const int DEBUG = 0;

int n,d,u,q;
int h[NMAX + 5];

struct node_t{
    vector<pair<int,int> > edges;
    vector<pair<int,int> > hsh_map;

    void add(pair<int,int> edge){
        edges.push_back({edge.first,h[edge.second]});
        edges.push_back({edge.second,h[edge.first]});
    }

    int fi(int x){
        int l = -1;
        int r = hsh_map.size();

        while(r - l > 1){
            int mid = (l + r) / 2;
            if(hsh_map[mid].first <= x){
                l = mid;
            }
            else{
                r = mid;
            }
        }
        if(l >= 0 && hsh_map[l].first == x){
            return hsh_map[l].second; 
        }
        return -1;
    }

    void push(int x,vector<int> &xx){
        if(DEBUG)printf("my edges are for %d\n",x);
        if(DEBUG)for(auto it:edges)printf("%d %d\n",it.first,it.second);
        int a = fi(x);
        if(a != -1){
            for(int i = a;i < (int)edges.size() && edges[i].first == x;i++){
                xx.push_back(edges[i].second);
            }
        }
    }

    void setup(){
        sort(edges.begin(),edges.end());
        for(int i = 0;i < (int)edges.size();i++){
            if(i == 0 || edges[i].first != edges[i - 1].first){
                hsh_map.push_back({edges[i].first,i});
            }
        }
    }
};


node_t aint[4 * UMAX + 5];

void add(int nod,int st,int dr,int l,int r,pair<int,int> edge){
    if(l <= st && dr <= r){
        aint[nod].add(edge);
        return ;
    }

    if(r < st || l > dr){
        return ;
    }

    int mid = (st + dr) / 2;

    add(nod * 2,st,mid,l,r,edge);
    add(nod * 2 + 1,mid + 1,dr,l,r,edge);
}

void gather_friends(int nod,int st,int dr,int pos,const int &x,const int &y,vector<int> &xx,vector<int> &yy){


    if(dr < pos || st > pos){
        return ;
    }

    if(DEBUG)printf("now in %d %d %d with %d %d %d\n",nod,st,dr,pos,x,y);
    aint[nod].push(x,xx);
    aint[nod].push(y,yy);

    if(st == dr){
        return ;
    }

    int mid = (st + dr) / 2;

    gather_friends(nod * 2,st,mid,pos,x,y,xx,yy);
    gather_friends(nod * 2 + 1,mid + 1,dr,pos,x,y,xx,yy);
}

void build(int nod,int st,int dr){
    aint[nod].setup();
    if(st == dr){
        return ;
    }

    int mid = (st + dr) / 2;

    build(nod * 2,st,mid);
    build(nod * 2 + 1,mid + 1,dr);
}

int solve(int x,int y,int v){
    vector<int> xx;
    vector<int> yy;

    gather_friends(1,1,u,v,x,y,xx,yy);


    if(DEBUG){
        printf("query %d %d %d\n",x,y,v);
        for(auto it:xx)printf("%d ",it);printf("\n");
        for(auto it:yy)printf("%d ",it);printf("\n");
    }

    sort(xx.begin(),xx.end());
    sort(yy.begin(),yy.end());

    int lst = -1;

    int ans = 1e9;

    for(auto it:xx){
        while(lst + 1 < (int)yy.size() && yy[lst + 1] <= it){
            lst++;
        }
        if(lst >= 0){
            ans = min(ans,it - yy[lst]);
        }
        if(lst + 1 < (int)yy.size()){
            ans = min(ans,yy[lst + 1] - it);
        }
    }

    return ans;
}

int main(){

    //if i get tle ill activate them, but i dont want them to interefere with the interaction
    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);

    cin >> n >> d >> u >> q;

    for(int i = 1;i <= n;i++){
        cin >> h[i];
    }

    map<pair<int,int>,int> mp;

    for(int i = 1;i <= u;i++){
        int a,b;
        cin >> a >> b;
        a++;
        b++;
        if(a > b){
            swap(a,b);
        }

        if(mp.count({a,b})){
            add(1,1,u,mp[{a,b}],i - 1,{a,b});
            if(DEBUG)printf("add edge %d %d from %d to %d\n",a,b,mp[{a,b}],i - 1);
            mp.erase({a,b});
        }
        else{
            mp[{a,b}] = i;
        }
    }

    for(auto it:mp){
        add(1,1,u,it.second,u,it.first);
        if(DEBUG)printf("add edge %d %d from %d to %d\n",it.first.first,it.first.second,it.second,u);
    }

    build(1,1,u);

    for(int i = 1;i <= q;i++){
        int x,y,v;
        cin >> x >> y >> v;
        x++;
        y++;
        cout << solve(x,y,v) << endl;
    }


    return 0;
}
