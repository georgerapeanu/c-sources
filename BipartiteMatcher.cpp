///tested on infoarena.ro/problema/cuplaj
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

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

int main(){
	
	FILE *f = fopen("cuplaj.in","r");
	FILE *g = fopen("cuplaj.out","w");
	
	int n,m,e;
	
	fscanf(f,"%d %d %d",&n,&m,&e);
	
	BipartiteMatcher matcher(n,m);
	
	while(e--){
		int x,y;
		fscanf(f,"%d %d",&x,&y);
		matcher.add_edge(x,y);
	}
	
	fprintf(g,"%d\n",matcher.max_match());
	for(int i = 1;i <= n;i++){
		if(matcher.L[i]){
			fprintf(g,"%d %d\n",i,matcher.L[i]);
		}
	}
	
	fclose(f);
	fclose(g);
	
	return 0;
}