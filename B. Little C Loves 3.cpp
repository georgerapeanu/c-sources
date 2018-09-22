#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 60;
const int MMAX = 60;
const int ELEM_MAX = NMAX * MMAX;

vector<int> graph[ELEM_MAX + 5];
int n,m;

int L[ELEM_MAX + 5];
int R[ELEM_MAX + 5];
bool viz[ELEM_MAX + 5];

bool pairup(int nod){
	if(viz[nod])return 0;
	viz[nod] = 1;
	for(auto it:graph[nod]){
		if(R[it] == 0){
			R[it] = nod;
			L[nod] = it;
			return 1;
		}
	}
	
	for(auto it:graph[nod]){
		if(pairup(R[it])){
			R[it] = nod;
			L[nod] = it;
			return 1;
		}
	}
	return 0;
}

int cuplaj(int n){
	int c = 0;
	bool ok = 1;
	memset(L,0,sizeof(L));
	memset(R,0,sizeof(R));
	while(ok){
		memset(viz,0,sizeof(viz));
		ok = 0;
		for(int i = 1;i <= n;i++){
			if(L[i] == 0 && pairup(i)){
				c += 2;
				ok = 1;
			}
		}
	}
	return c;
}

long long solve(int n,int m){
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			graph[(i - 1) * m + j].clear();
		}
	}
	
	for(int i = 1;i <= n;i++){
		for(int j = 1;j <= m;j++){
			for(int x = 1;x <= n;x++){
				for(int y = 1;y <= m;y++){
					if(abs(x - i) + abs(j - y) == 3){
						if((i + j) % 2 == 0){
							graph[(i - 1) * m + j].push_back((x - 1) * m + y);
						}
					}
				}
			}
		}
	}
	
	return cuplaj(n * m);
}

int base[] = {0,1,2,3,2,1};

int main(){
	
	scanf("%d %d",&n,&m);
	
	if(1LL * n * m > ELEM_MAX){
		if(n > m){
			swap(n,m);
		}
		if(n == 1)printf("%d",m - base[m % 6]);
		else      printf("%lld",1LL * n * m - (n % 2 == 1 && m % 2 == 1));
	}
	else{
		printf("%lld",solve(n,m));
	}
	
	
	return 0;
}