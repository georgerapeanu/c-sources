#include <bits/stdc++.h>

using namespace std;

class DSU{
  vector<int> father;

public:

  DSU(int n): father(vector<int>(n + 1, 0)){
    ;
  }

  int get_root(int node){
    if(father[node] == 0){
      return node;
    }
    return father[node] = get_root(father[node]);
  } 

  bool unite(int x, int y) {
    x = get_root(x);
    y = get_root(y);

    if(x == y) {
      return false;
    }

    if(x > y){
      swap(x, y);
    }

    father[y] = x;

    return true;
  }
};

int ask(int node){
  cout << "? " << node << endl;
  int answer;
  cin >> answer;
  if(answer == -1){
    exit(0);
  }
  return answer;
}

void answer(const vector<int> &color){
  cout << "! ";
  for(int i = 1;i < (int)color.size();i++){
    cout << color[i] << " ";
  }
  cout << endl;
}

int main(){

  int t;

  cin >> t;

  while(t--){
    int n;
    
    cin >> n;

    vector<pair<int, int> > degrees(n + 1, make_pair(0, 0));

    for(int i = 1;i <= n;i++){
      cin >> degrees[i].first;
      degrees[i].second = i;
    }

    sort(degrees.begin() + 1, degrees.end(), greater<pair<int, int> >());
    
    DSU dsu(n);
    vector<int> visited(n + 1, false);

    for(int i = 1;i <= n;i++) {
      if(visited[degrees[i].second] == true){
        continue;
      }
      visited[degrees[i].second] = true;
      while(degrees[i].first--){
        int node = ask(degrees[i].second);
        
        dsu.unite(degrees[i].second, node);

        if(visited[node] == true){
          break;
        }
        visited[node] = true;
      }
    }

    vector<int> color(n + 1, 0);
    int last_color = 0;

    for(int i = 1;i <= n;i++) {
      if(i == dsu.get_root(i)){
        color[i] = ++last_color;
      }else{
        color[i] = color[dsu.get_root(i)];
      } 
    }

    answer(color);
  }

  return 0;
}
