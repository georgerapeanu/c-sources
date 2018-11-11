#include <cstdio>
#include <queue>
#include <algorithm>

using namespace std;

FILE *f = fopen("scandura.in","r");
FILE *g = fopen("scandura.out","w");

int n,m;

queue<long long> d[2];

int main(){
	
	fscanf(f,"%d %d",&n,&m);
	
	int tn = n;
	
	while((tn - 1) % (m - 1) != 0){
		d[0].push(0);
		tn++;
	}
	
	for(int i = 1;i <= n;i++){
		int val;
		fscanf(f,"%d",&val);
		d[0].push(val);
	}
	
	long long ans = 0;
	
	while((int)d[1].size() + (int)d[0].size() > 1){
		long long tmp = 0;
		for(int i = 1;i <= m;i++){
			long long Mi = 1LL << 62;
			int wq = 0;
			if(!d[0].empty() && d[0].front() < Mi){Mi = d[0].front();wq = 0;}
			if(!d[1].empty() && d[1].front() < Mi){Mi = d[1].front();wq = 1;}
			d[wq].pop();
			tmp += Mi;
		}			
		d[1].push(tmp);
		ans += tmp;
	}
	
	fprintf(g,"%lld",ans);
	
	return 0;
}