#include <iostream>
#include <iomanip>
#include <algorithm>

using namespace std;

int M,N;
int V[100005];

int main(){
	cin >> M >> N;
	
	for(int i = 1;i <= N;i++){
		char c;
		cin >> V[i] >> c;
	}
	
	sort(V + 1,V + 1 + N);
	
	for(int i = 2;i <= N;i += 2){
		V[i] = 2 * M - V[i];
	}
	
	sort(V + 1,V + 1 + N);
	
	double mi = 1e9,Ma = -(1e9),unit = (double)2 * M / N;
	
	for(int i = 0;i < N;i++){
		mi = min(mi,i * unit + V[1] - V[i + 1]);
		Ma = max(Ma,i * unit + V[1] - V[i + 1]);
	}
	
	cout << fixed << setprecision(10) << (Ma - mi) / 2;
	
	return 0;
}