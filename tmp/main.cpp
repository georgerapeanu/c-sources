#include <ctime>
#include <cstdio>
#include <queue>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <vector>

using namespace std;
FILE *f = fopen("design.in","r");
FILE *g = fopen("design.out","w");

struct BipartiteMatcher {
    vector<vector<int>> g;
    vector<int> l, r, viz;

    BipartiteMatcher(int n, int m){
        g = vector< vector<int> >(n);
        l = vector<int>(n, -1);
        r = vector<int>(m, -1);
        viz = vector<int>(n);
    }

    void add_edge(int a, int b) {
        g[a].push_back(b);
    }

    bool match(int node) {
        if(viz[node])
            return false;
        viz[node] = true;

        for(auto vec : g[node]) {
            if(r[vec] == -1 || match(r[vec])) {
                l[node] = vec;
                r[vec] = node;
                return true;
            }
        }

        return false;
    }
    int solve() {
        bool ok = true;
        while(ok) {
            ok = false;
            fill(viz.begin(), viz.end(), 0);
            for(int i = 0; i < (int)l.size(); ++i)
                if(l[i] == -1)
                    ok |= match(i);
        }

        int ret = 0;
        for(int i = 0; i < (int)l.size(); ++i)
            ret += (l[i] != -1);
        return ret;
    }
};
const int NMAX = 500;
int n,k;
bool viz[NMAX + 5];
vector<int> graph[NMAX + 5];
int colors[NMAX + 5][7];
int tmp_colors[NMAX + 5][7];
int ans[NMAX + 5];
int dp[NMAX + 5][7][7];

bool check(int nod,int tata){
	vector<int> sons;
	vector<int> pos_cols;
	for(auto it:graph[nod]){
		if(it != tata){
			check(it,nod);
			sons.push_back(it);
		}
	}

	if(ans[nod]){
		pos_cols.push_back(ans[nod]);
	}
	else{
		for(int i = 1;i <= k;i++){
			pos_cols.push_back(i);
		}
	}

	bool ok = 0;

	if(tata){
		for(int cul_tata = 1;cul_tata <= k;cul_tata++){
			if(colors[nod][cul_tata] == 0){
				continue;
			}
			colors[nod][cul_tata]--;
			for(auto cul:pos_cols){

				BipartiteMatcher gg((int)sons.size() + 5,(int)sons.size() + 5);
				int wh = 0;
				for(int i = 0; i < (int)sons.size();i++){
					for(int col = 1;col <= k;col++){
						if(dp[sons[i]][cul][col]){
							for(int k = 1;k <= colors[nod][col];k++){
								wh++;
								gg.add_edge(i + 1,wh);
							}
						}
					}
				}

				dp[nod][cul_tata][cul] = (gg.solve() == (int)sons.size());
				ok |= dp[nod][cul_tata][cul];
			}
			colors[nod][cul_tata]++;
		}
	}
	else{
		for(auto cul:pos_cols){

			BipartiteMatcher gg((int)sons.size() + 5,(int)sons.size() + 5);
			int wh = 0;
			for(int i = 0; i < (int)sons.size();i++){
				for(int col = 1;col <= k;col++){
					if(dp[sons[i]][cul][col]){
						for(int k = 1;k <= colors[nod][col];k++){
							wh++;
							gg.add_edge(i + 1,wh);
						}
					}
				}
			}

			for(int i = 0;i < (int)gg.g.size();i++){
                for(auto it:gg.g[i]){
                    cout << i << " " << it << "\n";
                }
			}
            cout << "\n\n\n\n";
			dp[nod][0][cul] = (gg.solve() == (int)sons.size());
			ok |= dp[nod][0][cul];
		}
	}
	return ok;
}

bool ok(){
	memset(dp,0,sizeof(dp));
	return check(1,0);
}

void dfs(int nod,int tata){
    int child = -1;
    for(auto it:graph[nod]){
        if(it != tata){
            dfs(it,nod);
            if(!ans[it]){
                child = it;
            }
        }
    }

    if(child != -1){
        for(int i = 1;i <= k;i++){
            if(tmp_colors[child][i]){
                ans[nod] = i;
                for(auto it:graph[nod]){
                    tmp_colors[it][i]--;
                }
                break;
            }
        }
    }
}

int main(){
	fscanf(f,"%d %d",&n,&k);
	for(int i = 1;i <= n;i++){
		int sz;
		fscanf(f,"%d",&sz);
		for(int j = 1;j <= sz;j++){
			int col;
			fscanf(f,"%d",&col);
			colors[i][col]++;
			tmp_colors[i][col]++;
		}
		for(int j = 1;j <= sz;j++){
			int to;
			fscanf(f,"%d",&to);
			graph[i].push_back(to);
		}
	}

	dfs(1,0);

	for(int i = 1;i <= n;i++){
		if(ans[i]){
			continue;
		}
		for(int j = 1;j <= k;j++){
			ans[i] = j;
			if(ok()){
				break;
			}
		}
	}

	for(int i = 1;i <= n;i++){
		fprintf(g,"%d ",ans[i]);
	}

	printf("%.6f",(double)clock() / CLOCKS_PER_SEC);

	return 0;
}
