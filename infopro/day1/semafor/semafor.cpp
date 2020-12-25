#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 40000;
const int MMAX = 200000;

int n,m;
vector<int> graph[2 * NMAX + 5];

bool in_st[2 * NMAX + 5];
bool viz[2 * NMAX + 5];
int st[2 * NMAX + 5],len_st;
int id[2 * NMAX + 5];
int low[2 * NMAX + 5];
int lst_id;
int lst_ctc;
int ctc[2 * NMAX + 5];

bool ok_ctc[2 * NMAX + 5];

void dfs(int nod){
    st[++len_st] = nod;
    in_st[nod] = 1;
    viz[nod] = 1;
    id[nod] = low[nod] = ++lst_id;

    for(auto it:graph[nod]){
        if(viz[it] == 0){
            dfs(it);       
            low[nod] = min(low[nod],low[it]);
        }
        else if(in_st[it] == 1){
            low[nod] = min(low[nod],low[it]);
        }
    }

    if(low[nod] == id[nod]){
        lst_ctc++;
        while(len_st > 0 && st[len_st] != nod){
            ctc[st[len_st]] = lst_ctc;
            in_st[st[len_st]] = 0;
            len_st--;
        }
        ctc[st[len_st]] = lst_ctc;
        in_st[st[len_st]] = 0;
        len_st--;
    }
}

vector<pair<int,int> > edges;

int main(){

    scanf("%d %d",&n,&m);

    for(int i = 1;i <= m;i++){
        int a,b,c;
        scanf("%d %d %d",&a,&b,&c);
        if(c == 0){
            graph[a].push_back(b + n);
            edges.push_back({a,b + n});
        }
        else{
            graph[a + n].push_back(b);
            edges.push_back({a + n,b});
        }
    }

    for(int i = 1;i <= 2 * n;i++){
        if(viz[i] == 0){
            dfs(i);
        }
    }

    for(auto it:edges){
        if(ctc[it.first] == ctc[it.second]){
            ok_ctc[ctc[it.first]] = true;
        }
    }

    for(int i = 1;i <= n;i++){
        printf("%d",(ok_ctc[ctc[i]] | ok_ctc[ctc[i + n]]));
    }

    return 0;
}
