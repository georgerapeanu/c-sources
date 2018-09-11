#include "combo.h"
#include <iostream>

using namespace std;

char get_first_char(){
	string a = "AB";
	
	int ans = press(a);
	
	if(ans == 0){
		a = "XY";
	}
	
	if(press(a.substr(1)) == 0){
		return a[0];
	}
	
	return a[1];
}

string guess_sequence(int N) {
	string prefix;
	string aval = "ABXY";
	
	prefix += get_first_char();
	
	if(N == 1){
		return prefix;
	}
	
	for(int i = 0;i < 4;i++){
		if(aval[i] == prefix[0]){
			swap(aval[i],aval[3]);
			aval.pop_back();
			break;
		}
	}
	
	for(int i = 1;i < N - 1;i++){
		string query = prefix + aval[0] + prefix + aval[1] + aval[0] + prefix + aval[1] + aval[1] + prefix + aval[1] + aval[2];
		int ans = press(query);
		if(ans == prefix.size()){
			prefix += aval[2];
		}
		else if(ans == prefix.size() + 1){
			prefix += aval[0];
		}
		else{
			prefix += aval[1];
		}
	}
	
	if(press(prefix + aval[0]) == N){
		return prefix + aval[0];
	}
	
	if(press(prefix + aval[1]) == N){
		return prefix + aval[1];
	}
	
	return prefix + aval[2];
}
