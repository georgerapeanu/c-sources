#include "testlib.h"
#include <vector>

using namespace std;
 
int main(int argc, char** argv){
  registerGen(argc, argv, 1);
  int n = opt<int>("n");
  int q = opt<int>("q");
  int h = opt<int>("h");
  int vmax = opt<int>("vmax");
  int update_percent = opt<int>("u");
 
  vector<int> perm(1, 0);

  for(int i = 1;i <= n;i++){
    perm.push_back(i);
  }
  shuffle(perm.begin() + 1,perm.end());

  printf("%d\n", n);

  vector<pair<int, int> > edges;
  vector<vector<int> > levels(h, vector<int>());
  
  for(int i = 1;i <= h;i++){
    levels[i - 1].push_back(perm[i]);
    if(i > 1){
      edges.push_back({perm[i - 1], perm[i]});
      printf("%d %d %d\n", perm[i - 1], perm[i], rnd.next(0, vmax));
    }
  }

  for(int i = h + 1;i <= n;i++){
    int target = rnd.next(0, h - 2);
    int x = rnd.any(levels[target]);
    int y = perm[i];
    int z = rnd.next(0, vmax);
    edges.push_back({x, y});
    levels[target + 1].push_back(y);
    printf("%d %d %d\n", x, y, z);
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

