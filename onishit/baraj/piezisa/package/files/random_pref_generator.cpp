#include "testlib.h"

using namespace std;

int main(int argc, char** argv){
  registerGen(argc, argv, 1);
  int n = opt<int>("n");
  int vmax = opt<int>("vmax");
  int q = opt<int>("q");

  printf("%d\n", n);
  for(int i = 1;i <= n;i++){
		static int now = 0;

		int x = rnd.next(0, vmax);
    printf("%d", now ^ x);
		now = x;

    if(i < n){
      printf(" ");
    }
  }

  printf("\n");
  printf("%d\n", q);

	for (int i = 0; i + 1 < n && q > 0 ; ++i) {
		--q;
		printf("%d %d\n", i, i + 1);
	}
	

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

