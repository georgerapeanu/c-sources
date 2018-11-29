#include <cstdio>
#include <iostream>
#include <iostream>
#include <algorithm>

using namespace std;

int n,c;
int fr[500005];
int rrrrr[500005];
int s_fr[500005];
int v[500005];

int solve(int st,int dr){
	if(st == dr){
		return 1 + s_fr[st - 1] + s_fr[n] - s_fr[dr];
	}
	
	int ans = 0;
	int mid = (st + dr) / 2;
	
	ans = max(solve(st,mid),solve(mid + 1,dr));
	int fr_max = 0;
	
	for(int i = mid + 1;i <= dr;i++){
		fr[v[i]]++;
		rrrrr[v[i]] = max(rrrrr[v[i]],fr[v[i]] + s_fr[n] - s_fr[i]);
		if(rrrrr[v[i]] > rrrrr[fr_max]){
			fr_max = v[i];
		}
	}

	for(int i = mid + 1;i <= dr;i++){
		fr[v[i]] = 0;
	}
	
	
	for(int i = mid;i >= st;i--){
		fr[v[i]]++;
		if(fr[fr_max] + rrrrr[fr_max] < fr[v[i]] + rrrrr[v[i]] ){
			fr_max = v[i];
		}
		ans = max(ans,s_fr[i - 1] + fr[fr_max] + rrrrr[fr_max]);
	}		
	
	for(int i = mid;i >= st;i--){
		fr[v[i]] = 0;
	}
	
	for(int i = mid + 1;i <= dr;i++){
		rrrrr[v[i]] = 0;
	}	
	
	return ans;
}

int main(){
	
	scanf("%d %d",&n,&c);
	
	for(int i = 1;i <= n;i++){
		scanf("%d",&v[i]);
		s_fr[i] = s_fr[i - 1] + (v[i] == c);
	}
	
	printf("%d",max(solve(1,n),s_fr[n]));
	
	return 0;
}