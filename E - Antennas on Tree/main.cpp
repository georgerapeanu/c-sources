#include <iostream>
#include <vector>
using namespace std;
vector<int> G[100005];
int gr[100005];
int root;
int rez = 0;
int N;
bool dfs(int nod,int tata){
    if(G[nod].size() == (tata != 0)){
        return 0;
    }
    int tmp = 0;
    bool r = 0;
    for(auto it:G[nod]){
        if(it == tata){
            continue;
        }
        int f = dfs(it,nod);
        tmp += 1 - f;
        r |= f;
    }
    if(tmp > 1){
        r = 1;
        rez += tmp - 1;
    }
    return r;
}
int main()
{
    cin >> N;
    for(int i = 1;i < N;i++){
        int x,y;
        cin >> x >> y;
        x++;
        y++;
        G[x].push_back(y);
        G[y].push_back(x);
        gr[x]++;
        gr[y]++;
    }
    for(int i = 1;i <= N;i++){
        if(gr[i] >= 3){
            root = i;
        }
    }
    if(!root){
        rez = 1;
    }
    else{
        dfs(root,0);
    }
    cout << rez;
    return 0;
}
