#include <testlib.h>

using namespace std;

const int NMAX = 1e6;
const int VMAX = 1e9;

bool check_tree(int nod, int tata, const vector<vector<int> > &graph, vector<bool> &visited) {
  visited[nod] = true;
  for(auto it:graph[nod]){
    if(it == tata) {
      continue;
    }
    if(visited[it] == true){
      return false;
    }
    if(!check_tree(it, nod, graph, visited)){
      return false;
    }
  }
  return true;
}

int get_reachable(int nod, int tata, const vector< vector<int> > &graph) {
  int count = 1;

  for(auto it:graph[nod]) {
    if(it == tata){
      continue;
    }
    count += get_reachable(it, nod, graph);
  }
  return count;
}

int main(int argc, char** argv) {
  registerValidation(argc, argv);

  int n = inf.readInt(1, NMAX, "n");
  inf.readSpace();
  int k = inf.readInt(0, n, "k");
  inf.readEoln();

  for(int i = 1;i <= n;i++){
    int p_i = inf.readInt(0, VMAX, "p_i");
    if(i < n){
      inf.readSpace();
    } else {
      inf.readEoln();
    }
  }

  vector<vector<int> > graph(n + 1);

  for(int i = 1;i < n;i++){
    int u, v;
    u = inf.readInt(1, n);
    inf.readSpace();
    v = inf.readInt(1, n);
    inf.readEoln();
    inf.ensuref(u != v, "No self edges are allowed!");
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  inf.readEof();
  vector<bool> visited(n + 1, false);
  inf.ensuref(check_tree(1, 0, graph, visited), "Input should represent a tree"); 
  inf.ensuref(get_reachable(1, 0, graph) == n, "Input graph is not connex"); 

  return 0;
}
