#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int NMAX = 2e5;

int n,k;
int v[NMAX + 5];

int main(){
	
	fscanf(stdin,"%d %d",&n,&k);

	vector<int> vals;
	
	vals.push_back(0);
	
	for(int i = 1;i <= n;i++){
		fscanf(stdin,"%d",&v[i]);
		v[i] ^= v[i - 1];
		int a = ((1 << k) - 1) ^ v[i];
		a = min(a,v[i]);
		vals.push_back(a);
	}
	
	sort(vals.begin(),vals.end());
	
	vals.push_back(-1);
	
	int fr = 0;
	int val = vals[0];
	
	long long ans = 0;
	
	for(int i = 0;i < (int)vals.size();i++){
		if(val == vals[i]){
			fr++;
		}
		else{
			int a = fr / 2;
			int b = fr - a;
			
			ans += 1LL * a * (a - 1) / 2 + 1LL * b * (b - 1) / 2;
			
			val = vals[i];
			fr = 1;
		}
	}
		
	ans = 1LL * n * (n + 1) / 2 - ans;
	
	fprintf(stdout,"%lld",ans);
	
	return 0;
}