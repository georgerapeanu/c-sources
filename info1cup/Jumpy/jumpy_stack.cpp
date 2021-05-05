#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n,m;
vector<string> s;
vector<vector<int> > vertical_group;
vector<vector<int> > horizontal_group;

int last_vertical_group = -1;
int last_horizontal_group = -1;

vector<int> vertical_state;
vector<int> horizontal_state;

class BipartiteMatcher{
    int n,m;
    int ans;
    vector<int> l;
    vector<int> r;
    vector<vector<int> > graph;
    vector<bool> viz;
    vector<int> visited;

    bool pairup(int nod){
        if(viz[nod] == true){
            return false;
        }
        viz[nod] = true;
        visited.push_back(nod);

        for(auto it:graph[nod]){
            if(r[it] == -1){
                l[nod] = it;
                r[it] = nod;
                return true;
            }
        }
        
        for(auto it:graph[nod]){
            if(pairup(r[it])){
                l[nod] = it;
                r[it] = nod;
                return true;
            }
        }
        
        return false;
    }

public:

    BipartiteMatcher(int n,int m){
        this->n = n;
        this->m = m;
        l = vector<int>(n + 1,-1);
        r = vector<int>(m + 1, -1);
        graph = vector<vector<int> >(n + 1,vector<int>());
        viz = vector<bool>(n + 1,false);
        ans = 0;
    }

    void add_edge(int a,int b){
        graph[a].push_back(b);
    }
    
    int match(){
        bool ok = true;

        while(ok){
            ok = false;
    
            for(auto it:visited){
                viz[it] = false;
            }
            visited.clear();

            for(int i = 0;i < n;i++){
                if(l[i] == -1){
                    if(pairup(i)){
                        ans++;
                        ok = true;
                    }
                }
            }
        }

        return ans;
    }

    int match_without(int nod,bool side){
        int ans = 0;

        if(side == 0){
            if(l[nod] != -1){
                r[l[nod]] = -1;
                l[nod] = -1;
                this->ans--;
            }
            l[nod] = m;
            r[m] = nod;
            this->ans++;
            ans = this->match();
            l[nod] = -1;
            r[m] = -1;
            this->ans--;
        }else{
            if(r[nod] != -1){
                l[r[nod]] = -1;
                r[nod] = -1;
                this->ans--;
            }
            r[nod] = n;
            l[n] = nod;
            this->ans++;
            ans = this->match();
            l[n] = -1;
            r[nod] = -1;
            this->ans--;
        }
        
        return ans - 1;
    }
};

int main(){
    
    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);
    
    cin >> n >> m;


    s = vector<string>(n);
    horizontal_group = vector<vector<int> >(n,vector<int>());
    vertical_group = vector<vector<int> >(n,vector<int>());

    for(int i = 0;i < n;i++){
        cin >> s[i];
        horizontal_group[i] = vector<int>(m,0);
        vertical_group[i] = vector<int>(m,0);
    }

    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            if(s[i][j] == '#'){
                continue;
            }
            if(i == 0 || s[i - 1][j] == '#'){
                vertical_group[i][j] = ++last_vertical_group;
                vertical_state.push_back(0);
            }else{
                vertical_group[i][j] = vertical_group[i - 1][j];
            }
            if(j == 0 || s[i][j - 1] == '#'){
                horizontal_group[i][j] = ++last_horizontal_group;
                horizontal_state.push_back(0);
            }else{
                horizontal_group[i][j] = horizontal_group[i][j - 1];
            }
        }
    }

    BipartiteMatcher solver(last_vertical_group + 1,last_horizontal_group + 1);

    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            if(s[i][j] == '.'){
                solver.add_edge(vertical_group[i][j],horizontal_group[i][j]);                
            }
        }
    }

    int default_matching = solver.match();

    for(int i = 0;i <= last_vertical_group;i++){
        if(solver.match_without(i,false) < default_matching){
            vertical_state[i] = 1;
        }
    }
    
    for(int i = 0;i <= last_horizontal_group;i++){
        if(solver.match_without(i,true) < default_matching){
            horizontal_state[i] = 1;
        }
    }

    for(int i = 0;i < n;i++){
        for(int j = 0;j < m;j++){
            if(s[i][j] == '#'){
                cout << "#";
                continue;
            }
            int state = ((vertical_state[vertical_group[i][j]] << 1) | horizontal_state[horizontal_group[i][j]]);
            if(state == 0)     cout << "N";
            else if(state == 1)cout << "S";
            else if(state == 2)cout << "T";
            else               cout << "B";
        }
        cout << "\n";
    }
    
    return 0;
}
