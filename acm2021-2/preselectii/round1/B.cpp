#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;

int t;
int a,b;

int prefixXors[NMAX + 5];

int main(){

    for(int i = 1;i <= NMAX;i++){
      prefixXors[i] = prefixXors[i - 1] ^ i;
    }

    scanf("%d",&t);

    while(t--){
      scanf("%d %d",&a,&b);
      if(prefixXors[a - 1] == b){
        printf("%d\n",a);
      }else if((prefixXors[a - 1] ^ b) == a){
        printf("%d\n",a + 2); 
      }else{
        printf("%d\n",a + 1);
      }
    }

    return 0;
}
