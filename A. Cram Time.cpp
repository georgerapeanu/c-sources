#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

long long a,b;

vector<int> fst;
vector<int> snd;

bool sw;

int main(){
	
	cin >> a >> b;
	
	vector<int> all;
	
	long long sum = 0;
	int ans = 0,last = 1;
	
	while(sum + last <= a + b){
		sum += last;
		ans++;
		
		all.push_back(last);
		
		last++;
	}
	
	for(int i = (int)all.size() - 1;i >= 0;i--){
		if(all[i] <= a){
			a -= all[i];
			fst.push_back(all[i]);
		}
		else{
			b -= all[i];
			snd.push_back(all[i]);
		}
	}
	
	if(b < 0){
		sort(snd.begin(),snd.end());
		while(b < 0){
			b += snd.back();
			snd.pop_back();
		}
	}
	
	cout << fst.size() << "\n";
	for(auto it:fst)cout << it << " ";cout << "\n";
	
	cout << snd.size() << "\n";
	for(auto it:snd)cout << it << " ";cout << "\n";
	
	return 0;
}