#include <bits/stdc++.h>

using namespace std;


int main() {
  FILE *f = fopen("design.in","r");
  FILE *g = fopen("design.out","r");
  FILE *h = fopen("design.ok","r");
  
  int n;
  fscanf(f,"%d",&n);
  
  
  for(int i = 1;i <= n;i++){
	int a,b;
	fscanf(g,"%d",&a);
	fscanf(h,"%d",&b);
	if(a != b){
		printf("WA\n");
		while(1);
	}
  }
  
  printf("OK\n");
  
  return 0;
}
