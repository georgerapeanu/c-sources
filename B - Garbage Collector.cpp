#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int BUCK = 2000;
const long long laba = 2e18;

struct samibagpula{
	long long val;
	
	samibagpula(){
		val = 0;
	}
	
	samibagpula(long long val){
		this->val = val;
	}
	
	samibagpula operator + (const samibagpula &other)const{
		samibagpula ans(0);
		if(laba - other.val <= this->val){
			ans.val = laba;
		}
		else{
			ans.val = this->val + other.val;
		}
		return ans;
	}
	
	samibagpula operator * (const samibagpula &other)const{
		samibagpula ans(0);
		if(laba / other.val <= this->val){
			ans.val = laba;
		}
		else{
			ans.val = this->val * other.val;
			if(ans.val > laba){
				ans.val = laba;
			}
		}
		return ans;
	}
	
	bool operator < (const samibagpula &other)const{
		return this->val < other.val;
	}
	
	samibagpula operator - (const samibagpula &other)const{
		samibagpula ans(0);
		if(laba == this->val){
			ans.val = laba;
		}
		else{
			ans.val = this->val - other.val;
		}
		return ans;
	}
};

int n,x;
int pos[(int)2e5 + 5];
samibagpula dp[(int)2e5 + 5];
samibagpula pre[(int)2e5 + 5];


int main(){
	
	scanf("%d %d",&n,&x);
	
	for(int i = 1;i <= n;i++){
		scanf("%d",&pos[i]);
	}
	
	for(int i = 1;i <= n;i++){
		dp[i] = samibagpula(laba);
		
		for(int j = 1;j <= BUCK + 4 && j <= i;j++){
			pre[j] = pre[j - 1] + samibagpula(pos[i - j + 1] - pos[i - j]) * (samibagpula(j + 1) * samibagpula(j + 1));
		}
		
		for(int j = i - 1;j >= i - BUCK && j >= 0;j--){
			samibagpula tmp = dp[j] + pos[i] + samibagpula(i - j + 1) * samibagpula(x);
			/*for(int k = i - 1;k >= j;k--){
				tmp += 1LL * (pos[k + 1] - pos[k]) * (1LL * (i - k + 1) * (i - k + 1));
			}
			tmp += 1LL * (pos[j]) * (1LL * (i - j + 1) * (i - j + 1));*/
			tmp = tmp + pre[i - j] + samibagpula(pos[j]) * (samibagpula(i - j + 1) * samibagpula(i - j + 1));
			dp[i] = min(dp[i],tmp);
		}
	}
	
	printf("%lld",dp[n].val);
	
	return 0;
}