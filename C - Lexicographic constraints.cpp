#include <iostream>

using namespace std;

const int NMAX = 2e5;

int n;
int a[NMAX + 5];
pair<int,int> st[NMAX + 5];
int len;

bool ok(int sz){
	len = 0;
	st[0] = {0,0};
	for(int i = 1;i <= n;i++){
		while(len && st[len].first > a[i]){
			len--;
		}
		if(len && st[len].first == a[i]){
			st[len].second++;
			while(len && st[len].second >= sz){
				st[len].second /= sz;
				st[len].first--;
				if(st[len].first == st[len - 1].first){
					st[len - 1].second += st[len].second;
					len--;
				}
			}
			
			if(len == 0 && st[0].second > 0){
				return false;
			}
		}
		else{
			st[++len] = {a[i],(a[i] <= a[i - 1])};
		}
		
	}
	return true;
}

int main(){
	
	cin >> n;
	
	bool special = true;
	
	for(int i = 1;i <= n;i++){
		cin >> a[i];
		special &= (a[i - 1] < a[i]);
	}
	
	if(special){
		cout << 1;
		return 0;
	}
	
	int st = 1;
	int dr = NMAX + 5;
	
	while(dr - st > 1){
		int mid = (st + dr) / 2;
		
		if(ok(mid)){
			dr = mid;
		}
		else{
			st = mid;
		}
	}
	
	cout << dr;
	
	return 0;
}