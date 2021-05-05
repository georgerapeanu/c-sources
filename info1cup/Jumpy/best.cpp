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
    vector<int> paired;
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
            if(paired[it] == -1){
                paired[nod] = it;
                paired[it] = nod;
                return true;
            }
        }
        
        for(auto it:graph[nod]){
            if(pairup(paired[it])){
                paired[nod] = it;
                paired[it] = nod;
                return true;
            }
        }
        
        return false;
    }

public:

    BipartiteMatcher(int n,int m){
        this->n = n;
        this->m = m;
        paired = vector<int>(n + m, -1);
        graph = vector<vector<int> >(n + m,vector<int>());
        viz = vector<bool>(n + m,false);
        visited.reserve(n + m);
        ans = 0;
    }

    void add_edge(int a,int b){
        b += n;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    
    int match(){
        bool ok = true;

        while(ok){
            ok = false;
   
            while(!visited.empty()){
               viz[visited.back()] = false;
               visited.pop_back();
            }

            for(int i = 0;i < n;i++){
                if(paired[i] == -1){
                    if(pairup(i)){
                        ans++;
                        ok = true;
                    }
                }
            }
        }

        return ans;
    }

    bool has_alternating(int nod){
        if(viz[nod]){
            return false;
        }
        viz[nod] = true;
        visited.push_back(nod);
        if(paired[nod] == -1){
            return true;
        }
        for(auto it:graph[paired[nod]]){
            if(has_alternating(it)){
                return true;
            }
        }
        return false;
    }

    bool is_on_all_maximal_matchings(int nod,bool side){
        while(!visited.empty()){
           viz[visited.back()] = false;
           visited.pop_back();
        }

        return !has_alternating(nod + ((int)side) * n);
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
        if(solver.is_on_all_maximal_matchings(i,false)){
            vertical_state[i] = 1;
        }
    }
    
    for(int i = 0;i <= last_horizontal_group;i++){
        if(solver.is_on_all_maximal_matchings(i,true)){
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
