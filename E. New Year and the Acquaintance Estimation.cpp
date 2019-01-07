#include <cstdio>
#include <stdexcept>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 5e5;

long long ans = 0;

int n;
vector<int> gr;
vector<long long> pref_sum;

bool solve(int n,vector<int> gr){
	sort(gr.begin(),gr.end());
	reverse(gr.begin(),gr.end());
	pref_sum.resize(n);
	pref_sum[0] = gr[0];
	
	for(int i = 1;i < n;i++){
		pref_sum[i] = pref_sum[i - 1] + gr[i];
	}
	
	int ind = n;
	
	for(int i = 0;i < n;i++){
		while(ind > 0 && gr[ind - 1] <= i + 1){
			ind--;
		}
		if(pref_sum[i] > 1LL * i * (i + 1) + (pref_sum[n - 1] - pref_sum[max(ind - 1,i)]) + 1LL * (i + 1) * max(0,ind - i - 1)){
			return false;
		}
	}
	return true;
}

int pseudosolve(int n,vector<int> gr){
		sort(gr.begin(),gr.end());
	reverse(gr.begin(),gr.end());
	pref_sum.resize(n);
	pref_sum[0] = gr[0];
	
	for(int i = 1;i < n;i++){
		pref_sum[i] = pref_sum[i - 1] + gr[i];
	}
	
	int ind = n;
	
	int liber = 0;
	
	for(int i = 0;i < n;i++){
		while(ind > 0 && gr[ind - 1] <= i + 1){
			ind--;
		}
		
		if(pref_sum[i] <= 1LL * i * (i + 1) + (pref_sum[n - 1] - pref_sum[max(ind - 1,i)]) + 1LL * (i + 1) * max(0,ind - i - 1)){
			;
		}
		else if(pref_sum[i] - (1LL * i * (i + 1) + (pref_sum[n - 1] - pref_sum[max(ind - 1,i)]) + 1LL * (i + 1) * max(0,ind - i - 1)) <= i + 1){
			liber = max(1LL * liber,pref_sum[i] - (1LL * i * (i + 1) + (pref_sum[n - 1] - pref_sum[max(ind - 1,i)]) + 1LL * (i + 1) * max(0,ind - i - 1)));
		}
		else{
			return -1;
		}
	}
	return liber;
}

const int LEN = 1e4;
char buff[LEN];
int ind = LEN - 1;

int i32(){
	int ans = 0;
	
	while(buff[ind] < '0' || buff[ind] > '9'){
		if(++ind >= LEN){
			ind = 0;
			fread(buff,1,LEN,stdin);
		}
	}
	
	while(!(buff[ind] < '0' || buff[ind] > '9')){
		ans = ans * 10 + buff[ind] - '0';
		if(++ind >= LEN){
			ind = 0;
			fread(buff,1,LEN,stdin);
		}
	}
	return ans;
}

int main(){
	
	scanf("%d",&n);
	
	gr.resize(n);
	
	long long sum = 0;
	
	for(int i = 0;i < n;i++){
		scanf("%d",&gr[i]);
		sum += gr[i];
	}
	
	int tmp = pseudosolve(n,gr);
	if(tmp == -1){
		printf("-1");
		return 0;
	}
	
	n++;
	
	if((sum + tmp) % 2 == 1){
		tmp++;
		gr.push_back(tmp);
		if(solve(n,gr)){
			gr.pop_back();
		}
		else{
			tmp -= 2;
			gr.back() = tmp;
			if(solve(n,gr)){
				gr.pop_back();
			}
			else{
				printf("-1");
				return 0;
			}
		}
		
	}
	
	int st = tmp,dr = tmp;
	for(int pas = 1 << 20;pas;pas >>= 1){
		if(dr + pas < n){
			gr.push_back(dr + pas);
			if(solve(n,gr)){
				dr += pas;
			}
			gr.pop_back();
		}			
		if(st - pas >= 0){
			gr.push_back(st - pas);
			
			if(solve(n,gr)){
				st -= pas;
			}
			gr.pop_back();
		}
	}
	
	if(st % 2 != tmp % 2){
		st++;
	}
	
	if(dr % 2 != tmp % 2){
		dr--;
	}
	
	if(st > dr){
		printf("-1");
		return 0;
	}		
	
	for(int i = st;i <= dr;i += 2){
		printf("%d ",i);
	}
	
	
	return 0;
}