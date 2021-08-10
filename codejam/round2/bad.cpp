#include <bits/stdc++.h>

using namespace std;

int t;
int n,m,f,s;

const int NMAX = 10;

string a[NMAX + 5];
string b[NMAX + 5];
int v[NMAX + 5][NMAX + 5];


///1-indexed
class BipartiteMatcher{
public:
  
    vector<int> L,R;
    vector< vector<int> > graph;
  
private:
  
    vector<bool> viz;
    bool pair_up(int nod){
        if(viz[nod]){
            return 0;
        }
        viz[nod] = 1;
          
        for(auto it:graph[nod]){
            if(!R[it]){
                R[it] = nod;
                L[nod] = it;
                return 1;
            }
        }
          
        for(auto it:graph[nod]){
            if(pair_up(R[it])){
                R[it] = nod;
                L[nod] = it;
                return 1;
            }
        }
        return 0;
    }
      
public:
  
    BipartiteMatcher(int n,int m){
        graph.resize(n + 1);
        L.resize(n + 1);
        R.resize(m + 1);
        viz.resize(n + 1);
    }
      
    void add_edge(int u,int v){
        graph[u].push_back(v);
    }
      
	void reset_match(){
		fill(L.begin(),L.end(),0);
        fill(R.begin(),R.end(),0);
        fill(viz.begin(),viz.end(),0);
	}
	
	void reset_full(){
		fill(L.begin(),L.end(),0);
        fill(R.begin(),R.end(),0);
        fill(viz.begin(),viz.end(),0);
        fill(graph.begin(),graph.end(),vector<int>());
	}
	  
    int max_match(){
        int ans = 0;
        bool ok = 1;
        while(ok){
            ok = 0;
            fill(viz.begin(),viz.end(),0);
            for(int i = 1;i < (int)L.size();i++){
                if(!L[i] && pair_up(i)){
                    ans++;
                    ok = 1;
                }
            }
        }
        return ans;
    }
};

void add_edge(BipartiteMatcher &solver,int i,int j,int x,int y){
    if((i + j) & 1){
        return ;
    }

    solver.add_edge((i - 1) * m + j,(x - 1) * m + y);
}

const int dx[] = {-1,0,1,0};
const int dy[] = {0,1,0,-1};

int main(){

    cin >> t;

    for(int test = 1;test <= t;test++){
        
        cin >> n >> m >> f >> s;
        cout << "Case #" << test << ": ";

        for(int i = 1;i <= n;i++){
            cin >> a[i];
            a[i] = " " + a[i];
        }

        BipartiteMatcher solver(n * m,n * m);

        for(int i = 1;i <= n;i++){
            cin >> b[i];
            b[i] = " " + b[i];
        }

        int cnt = 0;
        
        for(int i = 1;i <= n;i++){
            for(int j = 1;j <= m;j++){
                cnt += (a[i][j] != b[i][j]);
                for(int k = 0;k < 4;k++){
                    int x = i + dx[k];
                    int y = j + dy[k];
                    if(1 <= x && x <= n && 1 <= y && y <= m){
                        if(a[i][j] != b[i][j] && a[x][y] != b[x][y] && a[i][j] == b[x][y] && b[i][j] == a[x][y]){
                            add_edge(solver,i,j,x,y);
                        }
                    }
                }
            }
        }
       
        int tmp = solver.max_match();

        cout << tmp * s + (cnt - tmp * 2) * f << "\n";

    }

    return 0;
}
