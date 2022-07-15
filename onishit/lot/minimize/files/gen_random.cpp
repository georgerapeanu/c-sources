#include "testlib.h"
#include <vector>
using namespace std;
 
int main(int argc, char** argv){
  registerGen(argc, argv, 1);
  int n = opt<int>("n");
  int k = opt<int>("k");
  int vmax = opt<int>("vmax");
  int qm = opt<int>("qm");
  int qi = opt<int>("qi");
 
  printf("%d %d\n", n, k);
  for(int i = 1;i <= n;i++){
    printf("%d", rnd.next(0, vmax));
    if(i < n){
      printf(" ");
    }
  }
  printf("\n");
  printf("%d\n", qm + qi);
 
  vector <int> q;
  for (int i = 0; i < qm ; ++i)
    q.push_back(1);
  for (int i = 0; i < qi - 1 ; ++i)
    q.push_back(0);
 
  shuffle(q.begin(), q.end());
  q.push_back(0);
  
  for (auto it : q) {
      printf("%d", it);
      if (it == 1)
        printf(" %d %d", rnd.next(1, n), rnd.next(0, vmax));
      printf("\n");
  }
  return 0;
}
