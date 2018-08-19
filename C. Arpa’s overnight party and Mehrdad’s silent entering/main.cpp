#include <iostream>
#include <vector>

using namespace std;

int N;
int BGF[200005];
int viz[200005];

vector< pair<int,int> > input;

void dfs(int nod,int tata){
    viz[nod] = 1 + viz[tata];
    if(!viz[(nod % 2 == 0 ? nod - 1 : nod % (2 * N) + 1)]){
        dfs((nod % 2 == 0 ? nod - 1 : nod % (2 * N) + 1),nod);
    }
    if(!viz[BGF[nod]]){
        dfs(BGF[nod],nod);
    }
}

int main(){
    cin >> N;
    for(int i = 1;i <= N;i++){
        int x,y;
        cin >> x >> y;
        BGF[x] = y;
        BGF[y] = x;
        input.push_back({x,y});
    }

    for(int i = 1;i <= 2 * N;i++){
        if(!viz[i]){
            dfs(i,0);
        }
    }

    for(int i = 1;i <= N;i++){
        cout << (viz[input[i - 1].first] & 1) + 1 << " " << (viz[input[i - 1].second] & 1) + 1 << "\n";
    }

    return 0;
}
