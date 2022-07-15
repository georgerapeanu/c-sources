#include <bits/stdc++.h>

using namespace std;

const int BITS = 8;

int main(){
  
  int t;

  cin >> t;

  while(t--){
    bool ok = false;
    for(int i = 0; i < (1 << BITS);i++){
      int value = 0;
      if(i == 0){
        value = 0x00;
      }else if(i % 2 == 1){
        value = 0xff;
      }else if(i % 4 == 2){
        value = 0x55;
      }else if(i % 8 == 4){
        value = 0x33;
      }else if(i % 16 == 8){
        value = 0x11;
      }else if(i % 32 == 16){
        value = 0x0f;
      }else if(i % 64 == 32){
        value = 0x05;
      }else if(i % 128 == 64){
        value = 0x03;
      }else{
        value = 0x01;
      }
      for(int i = 0;i < BITS;i++){
        cout << ((value >> i) & 1);
      }
      cout << endl;
      int tmp;
      cin >> tmp;
      if(tmp == 0){
        ok = true;
        break;
      }
      if(tmp == -1){
        exit(0);
      }
    }
    if(!ok){
      exit(0);
    }
  }


  return 0;
}
