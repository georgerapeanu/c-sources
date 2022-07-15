#include <bits/stdc++.h>

using namespace std;

FILE *f = fopen("in", "r");
FILE *f1 = fopen("out", "r");
FILE *f2 = fopen("ok", "r");

int main(){

  int n, a, b;

  fscanf(f, "%d", &n);

  for(int i = 0;i < n;i++){
    fscanf(f1, "%d", &a);
    fscanf(f2, "%d", &b);

    if(a != b){
      cout << "NO" << endl;
      return 0;
    }
  }

  cout << "OK";

  fclose(f);
  fclose(f1);
  fclose(f2);

  return 0;
}

