#include "testlib.h"
#include <vector>

using namespace std;
 
int main(int argc, char** argv){
  registerGen(argc, argv, 1);
  int n = opt<int>("n");
  int q = opt<int>("q");
  int vmax = opt<int>("vmax");
  int update_percent = opt<int>("u");
 
  vector<int> perm(1, 0);

  for(int i = 1;i <= n;i++){
    perm.push_back(i);
  }
  shuffle(perm.begin() + 1,perm.end());

  printf("%d\n", n);


  ///bucket * (bucket + 1) / 2 >= n
  ///bucket**2 + bucket - 2n >= 0
  ///delta = 1 + 8n
  ///bucket = (-1 + sqrt(1 + 8 * n)) / 2
  int bucket = (sqrt(1 + 8LL * n) - 1) / 2;
  while(bucket * (bucket + 1) / 2 < n){
    bucket++;
  }

  vector<pair<int, int> > edges;
  int first_node = 0;
  int last_node = 0;
  for(int i = 1;i <= bucket && last_node < n;i++){
    last_node++;
    if(first_node != 0){
      edges.push_back({first_node, last_node});
    }
    first_node = last_node;
    for(int j = 1;j <= bucket - i && last_node < n;j++){
      edges.push_back({last_node, last_node + 1});
      last_node++;
    }
  }

  while(last_node < n){
    ++last_node;
    edges.push_back({rnd.next(1, last_node - 1), last_node});
  }

  for(auto &it:edges){
    it.first = perm[it.first];
    it.second = perm[it.second];
    printf("%d %d %d\n", it.first, it.second, rnd.next(0, vmax));
  }

  printf("%d\n", q);
 
  while(q--){
    int t = rnd.next(0, 100);
    if(t <= update_percent){
      pair<int, int> edge = rnd.any(edges);
      int z = rnd.next(0, vmax);
      printf("0 %d %d %d\n", edge.first, edge.second, z);
    }else{
      int x = rnd.next(1, n);
      int y = rnd.next(1, n);
      printf("1 %d %d\n", x, y);
    }
  }
  return 0;
}

