#include <cstdio>
#include <algorithm>

using namespace std;

const int NMAX = 1e5;

int n,m;
int vert[NMAX + 5];
int hor[NMAX + 5];

int main(){
	
	scanf("%d %d",&n,&m);
	
	for(int i = 1;i <= n;i++){
		scanf("%d",&vert[i]);
	}
	
	for(int i = 1;i <= m;i++){
		int x1,x2,y;
		scanf("%d %d %d",&x1,&x2,&y);
		if(x1 != 1){
			hor[i] = 0;
		}
		else{
			hor[i] = x2;
		}
	}
	
	sort(vert + 1,vert + 1 + n);
	sort(hor + 1,hor + 1 + m);
	
	int ind = 0;
	int ans = 1 << 30;
	
	for(int i = 0;i <= n;i++){
		while(ind < m && ((i == n && hor[ind + 1] != 1e9) || hor[ind + 1] < vert[i + 1])){
			ind++;
		}
		ans = min(ans,m - ind + i);
	}
	
	printf("%d",ans);
	
	return 0;
}