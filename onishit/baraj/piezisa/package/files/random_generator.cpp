#include "testlib.h"

using namespace std;

int main(int argc, char** argv){
  registerGen(argc, argv, 1);
  int n = opt<int>("n");
  int vmax = opt<int>("vmax");
  int q = opt<int>("q");

  printf("%d\n", n);
  for(int i = 1;i <= n;i++){
    printf("%d", rnd.next(0, vmax));
    if(i < n){
      printf(" ");
    }
  }
  printf("\n");
  printf("%d\n", q);

  while(q--){
    int l = rnd.next(0, n - 1);
    int r = rnd.next(0, n - 1);

    if(l > r){
      swap(l, r);
    }
    printf("%d %d\n", l, r);
  }
  return 0;
}
