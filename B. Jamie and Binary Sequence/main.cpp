#include <iostream>
#include <map>
using namespace std;
map<int,int> fr;
long long N,K;
int main(){
	cin >> N >> K;
	for(int bit = 60;bit >= 0;bit--){
        if((N >> bit) & 1){
            fr[bit] = 1;
            K--;
        }
	}
	if(K < 0){
        cout << "No";
        return 0;
	}
	cout << "Yes\n";
	while(K >= fr.rbegin()->second){
        K -= fr.rbegin()->second;
        fr[fr.rbegin()->first - 1] += fr.rbegin()->second * 2;
        fr.erase(fr.rbegin()->first);
	}
	while(K--){
        fr.begin()->second--;
        fr[fr.begin()->first - 1] += 2;
	}
	for(map<int,int> :: reverse_iterator it = fr.rbegin();it != fr.rend();it++){
        while(it->second--){
            cout << it->first << " ";
        }
	}
	return 0;
}
