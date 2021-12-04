#include <bits/stdc++.h>

using namespace std;

int main(){
    
    char c;

    while(scanf("%c",&c) == 1){
      if('a' <= c && c <= 'z'){
        printf("%c", (((c - 'a') + 13) % 26) + 'a');
      }else if('A' <= c && c <= 'Z'){
        printf("%c", (((c - 'A') + 13) % 26) + 'A');
      }else{
        printf("%c",c);
      }
    }

    return 0;
}
