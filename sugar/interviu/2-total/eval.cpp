#include <iostream>
#include <fstream>

using namespace std;

ifstream f1("out");
ifstream f2("ok");

int main(){

	string a,b;

	while(f1 >> a && f2 >> b){
		if(a != b){
			cout << "WA\n";
			while(1);
		}
	}

    cout << "OK\n";

	f1.close();
	f2.close();

    return 0;
}
