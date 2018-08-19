#include <iostream>

using namespace std;
int N,M;
int V[1 << 17][20][20];
void propagUp(int val,int bit,int dif){
   V[val][bit][dif]++;
   if(bit <= 8){
      propagUp(val,bit + 1,dif);
      propagUp(val ^ (1 << bit),bit + 1,dif + 1);
   }
}
int propagDown(int val,int bit,int dif){
   if(bit <= 8){
      return V[val][bit][dif];
   }
   return propagDown(val,bit - 1,dif) + propagDown(val ^ (1 << bit),bit - 1,dif - 1);
}
int main() {
    cin >> N >> M;
    while(N--){
       int x;
       cin >> x;
       for(int y = 0;y <= M;y++){
          cout << propagDown(x,M,y) << " ";
       }
       cout << "\n";
       propagUp(x,0,0);
    }
    return 0;
}
