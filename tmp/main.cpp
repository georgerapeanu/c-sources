#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int f[200005];

void modif(int &a){
	a = 4;
}

void mod_vec(vector<string> v){
	v.push_back("fuck");
}

int main(){

	// int a = 5;
	// int &b = a;
	
	// modif(b);
	
	// printf("%d\n",scanf("laba%d",&a));
	// printf("%d",a);

	vector<string> a(2,"yes");
	
	mod_vec(a);
	
	for(auto it:a){
		cout << it << "\n";
	}
	
	return 0;
}
