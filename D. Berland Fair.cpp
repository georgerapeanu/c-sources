#include <cstdio>
#include <algorithm>
#include <cmath>

using namespace std;

const int NMAX = 2e5;

int n;
long long t;

int v[NMAX + 5];

pair<long long,int> aib[NMAX + 5];

void update(int pos,pair<long long,int> val){
	for(;pos <= n;pos += (-pos) & pos){
		aib[pos].first += val.first;
		aib[pos].second += val.second;
	}
}

pair<long long,int> query(int pos){
	pair<long long,int> ans = {0,0};
	for(;pos;pos -= (-pos) & pos){
		ans.first += aib[pos].first;
		ans.second += aib[pos].second;
	}
	return ans;
}

pair<long long,int> find_next(int pos,long long &val){
	auto a = query(n);
	long long total_sum = a.first;
	int total_things = a.second;
	long long ans = 1LL * (val / total_sum) * total_things;
	auto init = query(pos);
		
	val %= total_sum;
	
	if(total_sum - init.first <= val){
		val -= (total_sum - init.first);
		ans += total_things - init.second;
		pos = 0;
		init = {0,0};
	}
	
	int np = 0;
	
	for(int step = 1 << 20;step;step >>= 1){
		if(np + step > n){
			continue;
		}
		auto tmp = query(np + step);
		if(tmp.first - init.first <= val){
			np += step;
		}
	}
			
	ans += query(np).second - query(pos).second;
	val -= query(np).first - query(pos).first;
	
	return {ans,np + 1};
	
}

int main(){
	
	scanf("%d %lld",&n,&t);
		
	for(int i = 1;i <= n;i++){
		scanf("%d",&v[i]);
		update(i,{v[i],1});
	}
	
	
	int pos = 0;
	long long ans = 0;
	
	for(int i = 1;i <= n;i++){
		auto tmp = find_next(pos,t);
		pos = tmp.second;
		ans += tmp.first;
		update(pos,{-v[pos],-1});
	}
	
	printf("%lld",ans);
	
	
	return 0;
}