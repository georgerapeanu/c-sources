#include <iostream>
#include <cstdlib>

using namespace std;

string a;

bool Try(int st,int dr){
	int low,up,dig;
	low = up = dig = 0;

	for(int i = 0;i < st;i++){
		low |= ('a' <= a[i] && a[i] <= 'z');
		up |= ('A' <= a[i] && a[i] <= 'Z');
		dig |= ('0' <= a[i] && a[i] <= '9');
	}

	for(int i = dr + 1;i < (int)a.size();i++){
		low |= ('a' <= a[i] && a[i] <= 'z');
		up |= ('A' <= a[i] && a[i] <= 'Z');
		dig |= ('0' <= a[i] && a[i] <= '9');
	}
	if(3 - low - up - dig <= dr - st + 1){
		if(!low){
			a[st++] = 'a';
		}
		if(!up){
			a[st++] = 'A';
		}
		if(!dig){
			a[st++] = '0';
		}
		return 1;
	}
	return 0;
}

int main(){
	int T;
	cin >> T;
	while(T--){
		cin >> a;
		for(int l = 0;l <= a.size();l++){
			for(int i = 0;i < (int)a.size() - l + 1;i++){
				int j = i + l - 1;
				if(Try(i,j)){
					cout << a << "\n";
					goto done1;
				}
			}
		}
		done1:;
	}
	return 0;
}