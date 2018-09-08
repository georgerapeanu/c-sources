#include <iostream>

using namespace std;
int n;

int main() {

	cin >> n;
	for (int i = 1; i <= n; ++i) {
		long long n, m, k;
		cin >> n >> m >> k;
		long long diag = max(n, m), rez = 0;
		if (diag > k) {
			cout << -1 << '\n';
		}
 
		else {
			k -= min(n, m);
			rez += min(n, m);
			diag -= min(n, m);
			
			if(diag % 2 == 0){
				if(k % 2 == 0){
					rez += k;
				}
				else{
					rez += (k - 2);
				}
			}
			else{
				if(k % 2 == 0){
					rez += (k - 1);
				}
				else{
					rez += (k - 1);
				}
			}

			cout << rez << '\n';
		}
	}

	return 0;
}