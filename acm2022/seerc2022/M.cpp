#include <bits/stdc++.h>
#ifdef LOCAL_DEFINE
#include <dbg.h>
#else
#define dbg(...)
#endif

using namespace std;

const long double eps = 1e-18;

// get (a + k) / (b + k) such that  (a + k + 1) / (b + k + 1) - (a + k) / (b + k) >= taget and k+1 is less
// k can be at most 1e9 + 1
//
// 
int getK(int a, long long b, long double target, const int m){
   int low = 0;
   int high = m + 2;

   while(high - low > 1){
    int mid = (low + high) / 2;
    long double fst = logl((a + mid + 1) / ((long double)b + mid + 1));
    long double snd = logl((a + mid) / ((long double)b + mid));
    dbg(mid, fst, snd, fst - snd, target);
    if(fst - snd >= target){
      low = mid;
    } else{
      high = mid;
    }
   }
   return low;
}

int count(const vector<pair<int, long long> > &v, const int m, long double target){
  int sum = 0;
  for(int i = 0;i < (int)v.size();i++){
    int extra = getK(v[i].first, v[i].second, target, m);
    dbg(i, v[i], target, extra);
    sum += extra;
    if(sum > m){
      return sum;
    }
  }
  return sum;
}

vector<int> getPath(const vector<vector<int> > &graph, int a, int b){
  vector<int> ant(graph.size(), -1);
  vector<int> q;

  q.push_back(a);
  ant[a] = -2;

  for(int i = 0;i < (int)q.size();i++){
    for(const auto &it:graph[q[i]]){
      if(ant[it] == -1){
        q.push_back(it);
        ant[it] = q[i];
      }
    }
  }
  vector<int> path = {b};

  while(ant[path.back()] != -2){
    path.push_back(ant[path.back()]);
  }
  reverse(path.begin(), path.end());
  return path;
}

int main(){
  ios::sync_with_stdio(true);
  cin.tie(0);
  cout.tie(0);
  
  int n, x;

  cin >> n >> x;
  vector<int> cheese(n, 0);

  for(auto &it:cheese){
    cin >> it;
  }

  vector<long long> sums(n, 0);

  vector<vector<int> > graph(n);
  for(int i = 1;i < n;i++){
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    sums[a] += cheese[b];
    sums[b] += cheese[a];
    graph[a].push_back(b);
    graph[b].push_back(a);
  }

  vector<int> path = getPath(graph, 0, n - 1);
  vector<pair<int, long long> > fractions;

  for(int i = 0;i + 1 < (int)path.size();i++){
    fractions.push_back({cheese[path[i + 1]], sums[path[i]] - (i > 0 ? cheese[path[i - 1]]:0)});
  }

  long double low = 0, high = 50;

  while(high - low > eps){
    long double mid = (high + low) / 2;

    if(count(fractions, x, mid) <= x){
      high = mid;
    } else {
      low = mid;
    }
  }
  dbg(high);
  vector<int> increases(n, 0);

  int cnt_low = x - count(fractions, x, high);
  for(int i = 0;i < (int)fractions.size();i++){
    increases[path[i + 1]] = getK(fractions[i].first, fractions[i].second, high, x);
    int tmp = getK(fractions[i].first, fractions[i].second, low, x);
    if(tmp != increases[path[i + 1]]){
      int tmp_increase = min(cnt_low, tmp - increases[path[i + 1]]);
      cnt_low -= tmp_increase;
      increases[path[i + 1]] += tmp_increase;
    }
  }

  for(auto it:increases){
    cout << it << " "; 
  }

  return 0;
}
