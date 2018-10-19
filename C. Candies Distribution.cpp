#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

const int NMAX = 1e3;

int n;
int l[NMAX + 5];
int r[NMAX + 5];

int solved;

int val[NMAX + 5];

int main(){
	
	cin >> n;
	
	for(int i = 1;i <= n;i++){
		cin >> l[i];
	}
	
	for(int i = 1;i <= n;i++){
		cin >> r[i];
	}
	
	queue<int> q;
	
	for(int i = 1;i <= n;i++){
		if(l[i] == 0 && r[i] == 0){
			val[i] = n;
			q.push(i);
		}
	}
	
	while(!q.empty()){
		solved++;
		int nod = q.front();
		q.pop();
		
		for(int i = nod + 1;i <= n;i++){
			if(val[i]){
				if(val[i] < val[nod]){
					cout << "NO\n";
					return 0;
				}
				continue;
			}
			
			l[i]--;
			
			if(l[i] == 0 && r[i] == 0){
				val[i] = val[nod] - 1;
				q.push(i);
			}
		}
		
		for(int i = nod - 1;i;i--){
			if(val[i]){
				if(val[i] < val[nod]){
					cout << "NO\n";
					return 0;
				}
				continue;
			}
			
			r[i]--;
			
			if(l[i] == 0 && r[i] == 0){
				val[i] = val[nod] - 1;
				q.push(i);
			}
		}
	}
	
	if(solved != n){
		cout << "NO\n";
		return 0;
	}
	
	cout << "YES\n";
	
	for(int i = 1;i <= n;i++){
		cout << val[i] << " ";
	}
	
	return 0;
}