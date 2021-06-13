#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;
const int VMAX = 3200;


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
	
	int max_match(){
		int ans = 0;
		bool ok = 1;
		fill(L.begin(),L.end(),0);
		fill(R.begin(),R.end(),0);
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

bool is_composite[VMAX + 5];
vector<int> primes;
vector<int> divs[NMAX + 5];

map<int,int> fr;
map<int,int> l;
map<int,int> r;

int n,k,x;
int ans[NMAX + 5];

int main(){

    for(int i = 2;i <= VMAX;i++){
        if(is_composite[i] == false){
            primes.push_back(i);
            for(int j = i + i;j <= VMAX;j += i){
                is_composite[j] = true;
            }
        }
    }

    scanf("%d %d %d",&n,&k,&x);

    for(int i = 1;i <= n;i++){
        int value;
        scanf("%d",&value);
        for(auto it:primes){
            if(value < it){
                break;
            }
            if(value % it == 0){
                divs[i].push_back(it);
                fr[it]++;
            }
            while(value % it == 0){
                value /= it;
            }
        }
        if(value > 1){
            divs[i].push_back(value);
            fr[value]++;
        }
    }

    int last_r = 0;
    int bst = -1,bst_fr = -1;

    for(auto it:fr){
        if(bst_fr < it.second){
            bst = it.first;
            bst_fr = it.second;
        }
        l[it.first] = last_r + 1;
        r[it.first] = last_r + min(it.second,x);
        last_r += min(it.second,x);
    }

    if(bst_fr < x){
        printf("IMPOSSIBLE\n");
        return 0;
    }

    BipartiteMatcher solver(n,last_r);

    for(int i = 1;i <= n;i++){
        for(auto p:divs[i]){
            int _l = l[p];
            int _r = r[p];
            for(int j = _l;j <= _r;j++){
                solver.add_edge(i,j);
            }
        }
    }

    if(solver.max_match() < k){
        printf("IMPOSSIBLE\n");
        return 0;
    }

    for(auto p:fr){
        int _l = l[p.first];
        int _r = r[p.first];
        for(int i = _l;i <= _r;i++){
            if(solver.R[i] == 0){
                break;
            }
            ans[solver.R[i]] = p.first;
        }
    }

    int fr_bst = 0;
    int cnt = 0;
    
    for(int i = 1;i <= n;i++){
        if(ans[i] == 0){
            ans[i] = -1;
        }else{
            cnt++;
        }
        if(ans[i] == bst){
            fr_bst++;
        }
    }

    for(int i = 1;fr_bst < x && i <= n;i++){
        if(ans[i] != -1 && ans[i] != bst){
            bool has_bst = false;
            for(auto it:divs[i]){
                if(bst == it){
                    has_bst = true;
                    break;
                }
            }
            if(has_bst){
                fr_bst++;
                ans[i] = bst;
            }
        }
    }


    for(int i = 1;i <= n;i++){
        if(ans[i] != -1 && ans[i] != bst && cnt > k){
            cnt--;
            ans[i] = -1;
        }
        printf("%d ",ans[i]);
    }

    return 0;
}
