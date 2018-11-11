#include <cstdio>
#include <algorithm>
#include <deque>

using namespace std;

FILE *f = fopen("huffman.in","r");
FILE *g = fopen("huffman.out","w");

const int NMAX = 1e6;

int n;
pair<int,int> sons[2 * NMAX + 5];
pair<int,long long> ans[2 * NMAX + 5];
deque< pair<long long,int> > q[2];
int fr[NMAX + 5];

long long dfs(int nod,int len,long long val){
	if(nod <= n){
		ans[nod] = {len,val};
		return 1LL * len * fr[nod];
	}
	return dfs(sons[nod].first,len + 1,val * 2) + dfs(sons[nod].second,len + 1,val * 2 + 1);
}

int main(){
	
	fscanf(f,"%d",&n);
	
	for(int i = 1;i <= n;i++){
		int v;
		fscanf(f,"%d",&v);
		fr[i] = v;
		q[0].push_back({v,i});
	}
	
	for(int i = n + 1;i < 2 * n;i++){
		long long tmp = 1LL << 62;
		int x = -1,y = -1;
		
		if(!q[0].empty() && !q[1].empty() && q[0][0].first + q[1][0].first < tmp){
			tmp = q[0][0].first + q[1][0].first;
			x = 0;
			y = 1;
		}
		
		if((int)q[0].size() > 1 && q[0][0].first + q[0][1].first < tmp){
			tmp = q[0][0].first + q[0][1].first;
			x = y = 0;
		}
		
		if((int)q[1].size() > 1 && q[1][0].first + q[1][1].first < tmp){
			tmp = q[1][0].first + q[1][1].first;
			x = y = 1;
		}
		
		sons[i].first = q[x][0].second;
		q[x].pop_front();
		sons[i].second = q[y][0].second;
		q[y].pop_front();
		q[1].push_back({tmp,i});
	}
	
	fprintf(g,"%lld\n",dfs(2 * n - 1,0,0));
	for(int i = 1;i <= n;i++){
		fprintf(g,"%d %lld\n",ans[i].first,ans[i].second);
	}
	
	fclose(f);
	fclose(g);
	
	return 0;
}