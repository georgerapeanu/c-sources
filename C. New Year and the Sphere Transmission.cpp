#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

long long solve(int n,int d){
	long long a = 2 + 1LL * (n / d - 1) * d;
	long long b = n / d;
	return a * b / 2;
}
	
int main(){
	int n;
	scanf("%d",&n);
	vector<long long> ans;
	for(int d = 1;1LL * d * d <= n;d++){
		if(n % d == 0){
			ans.push_back(solve(n,d));
			ans.push_back(solve(n,n / d));
		}
	}
	
	sort(ans.begin(),ans.end());
	ans.resize(unique(ans.begin(),ans.end()) - ans.begin());
	for(auto it:ans){
		printf("%lld ",it);
	}
	return 0;
}