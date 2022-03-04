#include <bits/stdc++.h>

using namespace std;

const int BUCK = 600;
const int NMAX = 3e5;

int n;
int v[NMAX + 5];
map<int,int> fr;

int main(){
    
    int t;
    scanf("%d",&t);

    while(t--){
      fr.clear();
      scanf("%d", &n);

      for(int i = 1;i <= n;i++){
        int val;
        scanf("%d",&val);
        fr[val]++;
        v[i] = val;
      }

      for(int i = 1;i <= BUCK;i++){

      }
    }

    return 0;
}
