

#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

using ld = long double;

void generate_bad_brute(int n, int mx, int my){
  int x = rnd.next(-mx, my);
  int y = rnd.next(-mx, my);

  for(int i = 1;i <= n;i++){
      printf("%d %d\n", int((1LL * (i - 1) * mx * 2) / n + (x - mx)), y + my);
      printf("%d %d\n", x - mx, int((y - my) + (1LL * (i - 1) * my * 2) / n));
      printf("%d %d\n", int((x + mx) - (1LL * (i - 1) * mx * 2) / n), y - my);
      printf("%d %d\n", x + mx, int((y + my) - 1LL * (i - 1) * my * 2 / n));
  }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = opt<int>("n");
    int mx = opt<int>("mx");
    int my = opt<int>("my");

    printf("%d\n", n);

    generate_bad_brute(n, mx, my);
    

    return 0;
}


