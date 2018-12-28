#include <iostream>
#include <iomanip>

using namespace std;

const int NMAX = 1e5;

int gr[NMAX + 5];
int s,n;

int main(){
	
	cin.sync_with_stdio(false);cin.tie(0);
	cout.sync_with_stdio(false);cout.tie(0);
	
	cin >> n >> s;
	
	for(int i = 1;i < n;i++){
		int x,y;
		cin >> x >> y;
		gr[x]++;
		gr[y]++;
	}
	
	int cnt = 0;
	
	for(int i = 1;i <= n;i++){
		cnt += (gr[i] == 1);
	}
	
	long double ans = 2 * ((long double)s) / cnt;
	
	cout << fixed << setprecision(10) << ans;
	
	return 0;
}