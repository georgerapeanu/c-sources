#include <iostream>
#include <cstdio>

using namespace std;

int f[200005];

void modif(int &a){
	a = 4;
}

int main(){

	int a = 5;
	int &b = a;
	
	modif(b);
	
	printf("%d\n",scanf("laba%d",&a));
	printf("%d",a);

	return 0;
}
