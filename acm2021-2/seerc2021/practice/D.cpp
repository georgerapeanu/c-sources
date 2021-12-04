#include <bits/stdc++.h>

using namespace std;

int main(){

  char c;
  bool onlyWhiteSpace = true;
  int cnt = 0;
  while(scanf("%c",&c) == 1){
    if(c == '\n'){
      cnt += onlyWhiteSpace;
      onlyWhiteSpace = true;
    }else if(c == '\t' || c == ' '){
      ;
    }else{
      onlyWhiteSpace = false;
    }
  }
  cnt += onlyWhiteSpace * (c != '\n');

  printf("%d\n",cnt);

  return 0;
}
