#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv){
	registerGen(argc, argv, 1);
	
	int n = opt<int>("n");
  int m = opt<int>("m");
	
  cout << n << " " << m << endl;

  return 0;
}

