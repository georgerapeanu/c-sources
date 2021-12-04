#include <bits/stdc++.h>

using namespace std;

const int VMAX = 1e4;

const int LEN = 1 << 12;
int ind = LEN - 1;
char buff[LEN];

int i32(){
  int ans = 0;
  while(buff[ind] < '0' || buff[ind] > '9'){
    if(++ind >= LEN){
      ind = 0;
      fread(buff,1,LEN,stdin);
    }
  }
  
  while(!(buff[ind] < '0' || buff[ind] > '9')){
    ans = ans * 10 + buff[ind] - '0';
    if(++ind >= LEN){
      ind = 0;
      fread(buff,1,LEN,stdin);
    }
  }

  return ans;
}


vector<int> stuff;
vector<int> :: iterator tmp;

int main(){
    
    int n;

    n = i32();

    vector<int> v(n);

    for(auto &it:v){
      it = i32();
      tmp = lower_bound(stuff.begin(),stuff.end(),it);
      if(tmp == stuff.end()){
        stuff.push_back(it);
      }else{
        *tmp = it;
      }
    }

    printf("%d\n",stuff.size());

    return 0;
}
