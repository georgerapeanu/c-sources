#include <iostream>

using namespace std;

int main(){
	
	int z;	
	cin >> z;
	
	while(z--){
		int n,m,k;
		int ans = 0;
		string a,b;
		cin >> n >> m >> k;
		cin >> a >> b;
		a = " " + a;
		b = " " + b;
		
		
		for(int offset = 1;offset <= n;offset++){
			int lim = min(n - offset + 1,m);
			int last = 1,cnt = 0;
			for(int j = 1;j <= lim;j++){
				cnt += (a[offset + j - 1] != b[j]);
				while(cnt > k){
					cnt -= (a[offset + last - 1] != b[last]);
					last++;
				}
				ans = max(ans,j - last + 1);
			}
		}
		
		swap(a,b);
		swap(m,n);
		
		for(int offset = 1;offset <= n;offset++){
			int lim = min(n - offset + 1,m);
			int last = 1,cnt = 0;
			for(int j = 1;j <= lim;j++){
				cnt += (a[offset + j - 1] != b[j]);
				while(cnt > k){
					cnt -= (a[offset + last - 1] != b[last]);
					last++;
				}
				ans = max(ans,j - last + 1);
			}
		}
		
		cout << ans << "\n";
		
	}
	
	return 0;
}