#include <iostream>
#include <vector>
using namespace std;
int N,M,s;
vector<int> G[int(1e5) + 5];
bool d[int(1e5) + 5][2];
bool viz[int(1e5) + 5][2];
int where[int(1e5) + 5][2];
int numpasi[int(1e5) + 5][2];
void dfs(int nod,int wh,int tata){
    viz[nod][wh] = 1;
    if(G[nod].size() == 0){
        d[nod][0] = 1;
        return ;
    }
    for(auto it:G[nod]){
        if(!viz[it][!wh]){
            dfs(it,!wh,nod);
        }
        if(!d[it][!wh]){
            continue;
        }
        if(!d[nod][wh] || numpasi[it][!wh] + 1 < numpasi[nod][wh]){
            numpasi[nod][wh] = numpasi[it][!wh] + 1;
            where[nod][wh] = it;
            d[nod][wh] = 1;
        }
    }
}
int lvl[int(1e5) + 5];
bool active[int(1e5) + 5];
bool canDraw(int nod,int tata){
    active[nod] = 1;
    bool ans = 0;
    lvl[nod] = 1 + lvl[tata];
    for(auto it:G[nod]){
        if(!lvl[it]){
            ans |= canDraw(it,nod);
        }
        if(active[it] && (lvl[it] < lvl[nod] || it == nod)){
            ans = 1;
        }
    }
    active[nod] = 0;
    return ans;
}
int main()
{
    cin >> N >> M;
    for(int i = 1;i <= N;i++){
        int sz;
        cin >> sz;
        for(int j = 1;j <= sz;j++){
            int x;
            cin >> x;
            G[i].push_back(x);
        }
    }
    cin >> s;
    dfs(s,1,0);
    if(d[s][1]){
        cout << "Win\n";
        int wh = 1;
        while(where[s][wh]){
            cout << s << " ";
            s = where[s][wh];
            wh ^= 1;
        }
        cout << s;
    }
    else if(canDraw(s,0)){
        cout << "Draw\n";
    }
    else{
        cout << "Lose\n";
    }
    return 0;
}
