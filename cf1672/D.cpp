#include <bits/stdc++.h>

using namespace std;

int main(){

  int t;
  scanf("%d", &t);

  while(t--){
    int n;
    scanf("%d", &n);
    vector<pair<int, int>> a(n + 1, make_pair(0,0));
    vector<int> b(n + 1, 0);

    for(int i = 1;i <= n;i++){
      scanf("%d", &a[i].first);
      a[i].second = 1;
    }
    for(int i = 1;i <= n;i++){
     scanf("%d", &b[i]);
    }

    vector<int> last(n + 1, -1);
    vector<int> nxt(n + 1, -1);

    for(int i = n;i;i--){
      nxt[i] = last[a[i].first];
      last[a[i].first] = i;
    }

    int idx = 1;
    bool ok = true;
    for(int i = 1;i <= n;i++){
      int it = b[i];
      while(idx <= n && a[idx].first != it){
        if(nxt[idx] == -1 && a[idx].second > 0){
          idx = n + 1;
          break;
        }
        if(nxt[idx] != -1){
          a[nxt[idx]].second += a[idx].second;
        }
        a[idx].second = 0;
        idx++;
      }
      if(idx > n){
        ok = false;
        break;
      }
      a[idx].second--;
      if(a[idx].second == 0){
        idx++;
      }
    }
    printf(ok ? "YES\n":"NO\n");
  }

  return 0;
}
