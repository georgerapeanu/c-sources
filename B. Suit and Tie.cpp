#include <iostream>
#include <algorithm>

using namespace std;

int N;
int V[205];
int fst[105];
int lst[105];
int fr[105];

int main(){
	cin >> N;
	for(int i = 1;i <= 2 * N;i++){
		cin >> V[i];
		if(!fst[V[i]]){
			fst[V[i]] = i;
		}
		lst[V[i]] = i;
	}
	
	long long ans = 0;
	
	for(int j = 1;j <= N;j++){
		ans += lst[j] - fst[j] - 1;
		for(int i = fst[j];i <= lst[j];i++){
			if(V[i] < j){
				ans += (fr[V[i]] == 0 ? -1:1);
			}
			fr[V[i]]++;
		}
		
		for(int i = fst[j];i <= lst[j];i++){
			fr[V[i]]--;
		}
	}		
	
	cout << ans << "\n";
	
	return 0;
}