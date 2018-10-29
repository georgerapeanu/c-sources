#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

int v[11][100005];

int n,m;
int t[100005];
int left[100005];

int main(){
	scanf("%d %d",&m,&n);

	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			scanf("%d",&v[i][j]);
		}
	}

	for(int j = 1;j <= m;j++){
		t[v[1][j]] = j;
	}

	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			v[i][j] = t[v[i][j]];
			left[j] = j;
		}
	}

	for(int i = 1;i <= n;i++){
		int len = 0;
		for(int j = 1;j <= m;j++){
			if(j == 1){
				len = 1;
			}
			else if(v[i][j] == v[i][j - 1] + 1){
				len++;
			}
			else{
				len = 1;
			}
			left[v[i][j]] = min(left[v[i][j]],len);
		}
	}

	long long ans = 0;

	for(int j = 1;j <= m;j++){
		ans += left[j];
	}

	printf("%lld",ans);

	return 0;
}