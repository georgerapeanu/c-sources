#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

const int NMAX = 500;
const int MOD = 998244353;

int n;
map<long long,int> composite;
map<long long,int> extracted_primes;
vector<long long> solo_primes;
vector<int> still_composite;

int lgpow(int a,int b){
	if(!b)return 1;
	if(b % 2) return 1LL * a * lgpow(1LL * a * a % MOD,b / 2) % MOD;
	return lgpow(1LL * a * a % MOD,b / 2) % MOD;
}

long long gcd(long long a,long long b){
	if(!b)return a;
	return gcd(b,a % b);
}

long long my_pow(long long base,long long exp){
	if(!exp) return 1;
	return base * my_pow(base,exp - 1);
}

bool process_root(long long val,int order){
	long long st = 1,dr;
	if(order == 2){
		dr = 2e9;
	}
	
	else if(order == 3){
		dr = 2e6;
	}
	
	else if(order == 4){
		dr = 40000;
	}
	
	while(dr - st > 1){
		long long mid = (st + dr) / 2;
		if(my_pow(mid,order) <= val){
			st = mid;
		}
		else{
			dr = mid;
		}
	}
	
	if(my_pow(st,order) != val){
		return false;
	}
	
	extracted_primes[st] += order;
	solo_primes.push_back(st);
	return true;
}

int main(){
	
	cin >> n;
	
	for(int i = 1;i <= n;i++){
		long long x;
		cin >> x;
		
		if(process_root(x,4)){
			continue;
		}
		
		if(process_root(x,3)){
			continue;
		}
		
		if(process_root(x,2)){
			continue;
		}
		composite[x]++;
	}
		
	while(composite.size()){
		long long val = composite.begin()->first;
		long long fr = composite.begin()->second;
		composite.erase(composite.begin());
		long long reduce = 0;
			
		
		if(val == 1 || fr == 0){
			continue;
		}
		
		for(auto it:composite){
			if(gcd(it.first,val) > 1){
				reduce = gcd(it.first,val);
			}
		}
		
		for(auto it:solo_primes){
			if(val % it == 0){
				reduce = it;
			}
		}
		
		if(reduce > 0){
			long long a = reduce;
			long long b = val / reduce;
			extracted_primes[a] += fr;
			extracted_primes[b] += fr;
			solo_primes.push_back(a);
			solo_primes.push_back(b);
					
			for(auto &it:composite){
				if(it.first % a == 0){
					extracted_primes[a] += it.second;
					extracted_primes[it.first / a] += it.second;
					solo_primes.push_back(it.first / a);
					it.second = 0;
				}
				else if(it.first % b == 0){
					extracted_primes[b] += it.second;
					extracted_primes[it.first / b] += it.second;
					solo_primes.push_back(it.first / b);
					it.second = 0;
				}
			}
		}
		else{
			still_composite.push_back(fr);
		}
	}
	
	int ans = 1;
	
	for(auto it:still_composite){
		ans = 1LL * (1LL * ans * (it + 1) % MOD) * (it + 1) % MOD;
	}
	
	for(auto it:extracted_primes){
		ans = 1LL * ans * (it.second + 1) % MOD;
	}
	
	cout << ans << endl;
	
	return 0;
}