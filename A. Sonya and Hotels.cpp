#include <iostream>

using namespace std;

int N,d;
int V[105];

int main(){
	///N == 1
	cin >> N >> d;
	if(N == 1){cout << 2;return 0;}
	for(int i = 1;i <= N;i++){
		cin >> V[i];
	}
	
	int rez = 2 + (V[1] + d <= V[2] - d) + (V[N - 1] + d < V[N] - d);
	for(int i = 2;i < N;i++){
		if(V[i] - d > V[i - 1] + d){
			rez++;
		}
		if(V[i] + d <= V[i + 1] - d){
			rez++;
		}
	}
	
	cout << rez;
	
	return 0;
}