#include <bits/stdc++.h>

using namespace std;

int t;
int n;
int fr[205];
int perm[205];
int answer[205];

map<pair<int,int>,int> memo;
int ask(int a,int b){
  if(a > b){
    swap(a,b);
  }
  if(memo[{a,b}] == 0){
    string s = "";
    for(int i = 0;i < n;i++){
      s += 'a';
    }
    string t = s;
    t[perm[a] - 1] = 'b';
    t[perm[b] - 1] = 'b';
    cout << "? " << s << " " << t << endl;
    int ans = 0;
    cin >> ans;
    if(ans == -1){
      exit(0);
    }
    memo[{a,b}] = ans + 1;
  }
  return memo[{a,b}];
}

void print_answer(){
  cout << "! ";
  for(int i = 1;i <= n;i++){
    cout << answer[i] << " ";
  }
  cout << endl;
}

int main(){

  cin >> t;

  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

  while(t--){
    cin >> n;
    memo.clear();
    for(int i = 1;i <= n;i++){
      perm[i] = i;
      answer[i] = 0;
    }
    //shuffle(perm + 1,perm + 1 + n,rng);
    
    int a = 1,b = 2;
    for(int i = 3;i <= n;i++){
      if(ask(a,b) < ask(a,i)){
        answer[perm[i]] = ask(a,i);
      }else if(ask(a,b) == ask(a,i)){
        answer[perm[a]] = ask(a,b);
        b = i;  
      }else{
        answer[perm[b]] = ask(a,b);
        a = i;
      }
    }

    int lst = 1;

    for(int i = 1;i <= n;i++){
      if(answer[i] == 0){
        answer[i] = lst++;
      }
    }
    
    print_answer();

  }

  return 0;
}
