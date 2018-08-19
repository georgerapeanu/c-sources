#include <iostream>

using namespace std;
int N;
int A[100005];
bool okst[100005];
bool okdr[100005];
bool eval(){
   for(int i = 2;i <= N;i++){
      if(A[i - 1] > A[i]){
         return 0;
      }
   }
   return 1;
}
int num,x = 1 << 30,y;
int up(int st,int dr){
   if(x > st){
      x = st;
      y = dr;
   }
   else if(st == x && y > dr){
      dr = y;
   }
}
int main() {
    cin >> N;
    for(int i = 1;i <= N;i++){
       cin >> A[i];
    }
    A[N + 1] = 1 << 30;
    int lastst = 0,lastdr = N;
    okst[0] = 1;
    for(int i = 1;i <= N;i++){
       okst[i] = okst[i - 1] & (A[i - 1] <= A[i]);
       if(okst[i]){
          lastst = i;
       }
    }
    okdr[N] = okdr[N + 1] = 1;
    for(int i = N - 1;i >= 0;i--){
       okdr[i] = okdr[i + 1] & (A[i] <= A[i + 1]);
       if(okdr[i]){
          lastdr = i;
       }
    }
    int st = 1,st2 = 1;
    for(int i = 1;i <= N;i++){
       if(A[i - 1] < A[i]){
          st = i;
       }
       while(st2 <= i && okdr[i + 1] && okst[st2] && A[st2] <= A[i + 1] && A[st2 - 1] <= A[i]){
          st2++;
       }
       if(okdr[i + 1] && okst[st - 1] && st < min(st2,lastst + 1)){
          num += min(st2,lastst + 1) - st;
          up(st,i);
       }
    }
    if(num == 0){
       cout << 0;
       return 0;
    }
    cout << num << "\n" << x << " " << y;
    return 0;
}
