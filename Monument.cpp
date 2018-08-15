#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int p,q,r;
string S[155][155];
int dp[155][155][155];
int dp2[155][155][155];
int dp3[155][155][155];

int st[155];
int dr[155];

void update(vector<int> &heights,int &ans){
	stack<int> S,D;
	
	S.push(0);
	
	for(int i = 1;i < (int)heights.size() - 1;i++){
		while(heights[S.top()] >= heights[i]){
			S.pop();
		}
		st[i] = S.top();
		S.push(i);
	}
	
	D.push((int)heights.size() - 1);
	
	for(int i = (int)heights.size() - 2;i;i--){
		while(heights[D.top()] >= heights[i]){
			D.pop();
		}
		dr[i] = D.top();
		D.push(i);
	}

	for(int i = 1;i < (int)heights.size() - 1;i++){
		ans = max(ans,heights[i] * (dr[i] - st[i] - 1));
	}
	
}

int main(){///rotate things because bad problem
	cin >> p >> q >> r;
	
	for(int i = 1;i <= q;i++){
		for(int j = 1;j <= p;j++){
			cin >> S[j][i];
			S[j][i] = " " + S[j][i];
		}
	}
	
	for(int h = 1;h <= r;h++){
		for(int i = 1;i <= p;i++){
			for(int j = 1;j <= q;j++){
				if(S[i][j][h] == 'P'){
					continue;
				}
				dp[i][j][h] = min(dp[i - 1][j - 1][h],min(dp[i - 1][j][h],dp[i][j - 1][h])) + 1;
				dp2[i][j][h] = min(dp2[i - 1][j][h - 1],min(dp2[i - 1][j][h],dp2[i][j][h - 1])) + 1;
				dp3[i][j][h] = min(dp3[i][j - 1][h - 1],min(dp3[i][j - 1][h],dp3[i][j][h - 1])) + 1;
			}
		}
	}
	
	int ans = 0;
	
	for(int i = 1;i <= p;i++){
		for(int j = 1;j <= q;j++){
			vector<int> heights;
			heights.push_back(-1);
			for(int k = 1;k <= r;k++){
				heights.push_back(dp[i][j][k]);
			}
			heights.push_back(-1);
			update(heights,ans);
		}
	}
	
	for(int i = 1;i <= p;i++){
		for(int k = 1;k <= r;k++){
			vector<int> heights;
			heights.push_back(-1);
			for(int j = 1;j <= q;j++){
				heights.push_back(dp2[i][j][k]);
			}
			heights.push_back(-1);
			update(heights,ans);
		}
	}
	
	for(int j = 1;j <= q;j++){
		for(int k = 1;k <= r;k++){
			vector<int> heights;
			heights.push_back(-1);
			for(int i = 1;i <= p;i++){
				heights.push_back(dp3[i][j][k]);
			}
			heights.push_back(-1);
			update(heights,ans);
		}
	}
	
	cout << ans * 4;
	
	return 0;
}