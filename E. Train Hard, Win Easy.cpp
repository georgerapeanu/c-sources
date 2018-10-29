#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 3e5;

int n,k;
int x[NMAX + 5];
int y[NMAX + 5];

pair<int,int> v[NMAX + 5];
long long score[NMAX + 5];

int main(){
	
	scanf("%d %d",&n,&k);

	long long sum_x = 0;
	long long sum_y = 0;
	
	for(int i = 1;i <= n;i++){
		scanf("%d %d",&x[i],&y[i]);
		v[i] = {x[i] - y[i],i};
		sum_y += y[i];
	}

	sort(v + 1,v + 1 + n);

	for(int i = 1;i <= n;i++){
		sum_y -= y[v[i].second];
		score[v[i].second] += 1LL * y[v[i].second] * (i - 1);
		score[v[i].second] += 1LL * x[v[i].second] * (n - i);
		score[v[i].second] += sum_x;
		score[v[i].second] += sum_y;
		sum_x += x[v[i].second];
	}

	while(k--){
		int u,v;
		scanf("%d %d",&u,&v);
		int sc = min(x[u] + y[v],x[v] + y[u]);
		score[u] -= sc;
		score[v] -= sc;
	}

	for(int i = 1;i <= n;i++)printf("%lld ",score[i]);

	return 0;
}