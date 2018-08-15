#include <iostream>

using namespace std;

int N;
int fst[100005];
int lst[100005];
int V[100005];

int num;

int main(){
	long long rez = 0;
	
	cin >> N;
	
	for(int i = 1;i <= N;i++){
		int x;
		cin >> x;
		if(!fst[x]){
			num++;
			fst[x] = i;
		}
		lst[x] = i;
		V[i] = x;
	}
	
	for(int i = 1;i <= N;i++){
		num -= (lst[V[i]] == i);
		if(fst[V[i]] == i){
			rez += num;
		}
	}
	
	cout << rez;
	
	return 0;
}