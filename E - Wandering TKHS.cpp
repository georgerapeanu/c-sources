#include <cstdio>
#include <vector>

using namespace std;

const int NMAX = 2e5;

int n;
int lvl[NMAX + 5];
int mars[NMAX + 5];
int ans[NMAX + 5];

vector<int> graph[NMAX + 5];


vector<int> path_to_root; 
vector<int> max_on_path;
int st[NMAX + 5];
int lin[NMAX + 5];
int fst[NMAX + 5];
int lst[NMAX + 5];
int len;

void predfs(int nod,int tata){
	lin[++len] = nod;
	fst[nod] = len;
	
	for(auto it:graph[nod]){
		if(it == tata){
			continue;
		}
		predfs(it,nod);
	}
	lst[nod] = len;
}

void dfs(int nod,int tata,int father_ancestor){
	path_to_root.push_back(nod);
	max_on_path.push_back(max(tata ? max_on_path.back():0,nod));
	lvl[nod] = 1 + lvl[tata];
	
	int st = 0,dr = path_to_root.size();
	
	while(dr - st > 1){
		int mid = (st + dr) / 2;
		
		if(max_on_path[mid] >= nod){
			dr = mid;
		}
		else{
			st = mid;
		}
	}
	
	int ancestor = path_to_root[min((int)path_to_root.size() - 1,dr + 1)];///the first ancestor from which i can merge and contribute
	ancestor = (lvl[father_ancestor] > lvl[ancestor] ? father_ancestor:ancestor);
		
	mars[fst[ancestor]] += 1;
	mars[lst[ancestor] + 1] -= 1;
	
	for(auto it:graph[nod]){
		if(it == tata){
			continue;
		}
		dfs(it,nod,ancestor);
	}
	
	path_to_root.pop_back();
	max_on_path.pop_back();
}

int main(){
	
	scanf("%d",&n);
	
	for(int i = 1;i < n;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		graph[x].push_back(y);
		graph[y].push_back(x);
	}
	
	predfs(1,0);
	dfs(1,0,1);
	
	for(int i = 1;i <= n;i++){
		mars[i] += mars[i - 1];
		ans[lin[i]] = mars[i];
	}
	
	for(int i = 2;i <= n;i++){
		printf("%d ",ans[i] - 1);
	}
	
	return 0;
}