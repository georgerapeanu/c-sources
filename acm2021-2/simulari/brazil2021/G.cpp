#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

int main(){
    i64 n;

    scanf("%lld",&n);

    vector<i64> fib = {1,1};

    while(fib[(int)fib.size() - 2] + fib[(int)fib.size() - 1] <= n){
      fib.push_back(fib[(int)fib.size() - 2] + fib[(int)fib.size() - 1]);
    }

    queue<pair<i64,i64> > q;
    queue<pair<i64,i64> > tmp[2];
    q.push({1,0});

    bool found = false;
    for(int i = 2;i < (int)fib.size();i++){
      tmp[0].swap(q);

      while(tmp[0].empty() == false || tmp[1].empty() == false){
        if(tmp[0].empty() == false && (tmp[1].empty() || tmp[0].front().first < tmp[1].front().first)){
          if(q.empty() || q.back().first != tmp[0].front().first){
            q.push(tmp[0].front());
            found |= (tmp[0].front().first == n); 
          }
          if(tmp[0].front().first <= n / fib[i] && (n % (tmp[0].front().first * fib[i])) == 0){
            tmp[1].push({tmp[0].front().first * fib[i],i});
          }
          tmp[0].pop();
        }else{
          if(q.empty() || q.back().first != tmp[1].front().first){
            q.push(tmp[1].front());
            found |= (tmp[1].front().first == n); 
          }
          if(tmp[1].front().first <= n / fib[i] && (n % (tmp[1].front().first * fib[i])) == 0){
            tmp[1].push({tmp[1].front().first * fib[i],i});
          }
          tmp[1].pop();
        }
      }
    }
    if(found == false){
      printf("IMPOSSIBLE");
      return 0;
    }

    vector<pair<i64,i64> > vq;

    while(q.empty() == false){
      vq.push_back(q.front());
      q.pop();
    }


    for(int i = (int)vq.size() - 1;i > 0;i--){
      if(n == vq[i].first){
        for(int j = 1;j < vq[i].second;j++){
          printf("A");
        }
        printf("B");
        n /= fib[vq[i].second];
      }
    }

    return 0;
}
