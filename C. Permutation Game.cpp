#include <cstdio>

using namespace std;

const int NMAX = 1e5;

int n;
int v[NMAX + 5];
int pos[NMAX + 5];
bool win[NMAX + 5];

int main(){
	
	scanf("%d",&n);
	
	for(int i = 1;i <= n;i++){
		scanf("%d",&v[i]);
		pos[v[i]] = i;
	}
	
	for(int i = n;i;i--){
		for(int j = i;j <= n;j += i){
			if(pos[i] + j <= n && v[pos[i] + j] > i && !win[v[pos[i] + j]]){
				win[i] = 1;
				break;
			}
			
			if(pos[i] - j >= 1 && v[pos[i] - j] >= i && !win[v[pos[i] - j]]){
				win[i] = 1;
				break;
			}
		}
	}
	
	for(int i = 1;i <= n;i++){
		printf("%c",(win[v[i]] ? 'A' : 'B'));
	}
	
	return 0;
}