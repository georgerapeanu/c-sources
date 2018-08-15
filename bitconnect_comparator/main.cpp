#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <windows.h>

using namespace std;

int N;
bool ok = 1;

const int MAXOUTPUT = (1e5) * 3 + 20;
char A1[MAXOUTPUT];
char A2[MAXOUTPUT];
char B1[MAXOUTPUT];
char B2[MAXOUTPUT];

FILE *f;

void get(){
	f = fopen("bitconnect_bitMode.out","r");
	fread(B1,1,MAXOUTPUT,f);
	fclose(f);
	f = fopen("bitconnect_connectMode.out","r");
	fread(B2,1,MAXOUTPUT,f);
	fclose(f);
}

void verif(){
	system("gen.exe");

	bool ok1 = 1,ok2 = 1;

	system("Nlog^2N.exe");
	get();
	memcpy(A1,B1,sizeof(B1));
	memcpy(A2,B2,sizeof(B2));

	system("Nlog^3N.exe");
	get();
	ok1 &= (strcmp(A1,B1) == 0);
	ok2 &= (strcmp(A2,B2) == 0);

	system("N2.exe");
	get();
	ok1 &= (strcmp(A1,B1) == 0);
	ok2 &= (strcmp(A2,B2) == 0);

	system("N2logN.exe");
	get();
	ok1 &= (strcmp(A1,B1) == 0);
	ok2 &= (strcmp(A2,B2) == 0);
	cout << (ok1 ? "OK" : "WA") << " BITMODE ";
	cout << (ok2 ? "OK" : "WA") << " CONNECTMODE\n";
	while(!ok1 || !ok2);
}

int main(){
	while(1){
		verif();
	}
    return 0;
}
