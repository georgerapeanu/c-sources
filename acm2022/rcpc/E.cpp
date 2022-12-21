#include <bits/stdc++.h>

using namespace std;

bool check(int count[], int dists[]){
  if(dists[0] < 0 || dists[1] < 0){
    return false;
  }
  if(count[0] > dists[0] + dists[1]  || count[0] * 2 + 2 * count[1] < dists[0] + dists[1]){
    return false;
  }

  if(max(dists[0], dists[1]) > count[0] + count[1]){
    return false;
  }

  if(max(dists[0], dists[1]) - min(dists[0], dists[1]) > count[0]){
    return false;
  }
  return true;
}

int main(){

  int n, d;
  string a, b;
  cin >> n >> d;
  cin >> a >> b;

  int count[] = {0, 0};

  for(int i = 0;i < n;i++){
    count[a[i] == b[i]]++;
  }


  string c;

  int dists[] = {d, d};

  if(!check(count, dists)){
    cout << -1;
    return 0;
  }

  for(int i = 0;i < n;i++){
    /*
    cerr << dists[0] << " ";
    cerr << dists[1] << " ";
    cerr << count[0] << " ";
    cerr << count[1] << " ";
    cerr << check(count, dists) << " ";
    cerr << c << "\n";
    */
    if(a[i] == b[i]){
      count[1]--;
      if(check(count, dists) == true){
        c += a[i];
        continue;
      }
      dists[0]--;
      dists[1]--;
      if(check(count, dists) == true){
        c += (((a[i] - 'a' + 1) % ('z' - 'a' + 1)) + 'a');
        continue;
      }
      assert(false);
    }else{
      count[0]--;
      dists[0]--;
      if(check(count, dists) == true){
        c += b[i];
        continue;
      } 
      dists[0]++;
      
      dists[1]--;
      if(check(count, dists) == true){
        c += a[i];
        continue;
      }
      dists[1]++;

      dists[0]--;
      dists[1]--;
      if(check(count, dists) == true){
        c += a[i];
        while(c.back() == a[i] || c.back() == b[i]){
          c.back()++;
          if(c.back() > 'z'){
            c.back() = 'a';
          }
        }
        continue;
      }
      assert(false);
    }
  }

  cout << c;

  return 0;
}
