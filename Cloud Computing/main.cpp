#include <iostream>
#include <vector>

using namespace std;

int n;
int v[100005];
vector<int> ans;
vector<int> pos[4];
int nv[100005];

int main() {
   cin >> n;

   for(int i = 1;i <= n;i++){
      cin >> v[i];
      pos[v[i]].push_back(i);
   }

   for(auto it:pos[3]){
      if(it == 1 || nv[it - 1]){
         cout << -1;
         return 0;
      }

      if(it == n || nv[it + 1]){
         cout << -1;
         return 0;
      }
      nv[it] = 3;
      ans.push_back(it);
      ans.push_back(it - 1);
      ans.push_back(it + 1);
      ans.push_back(it);
   }

   for(auto it:pos[2]){
      if((it == 1 || nv[it - 1]) + (it == n || nv[it + 1]) == 2){
         cout << -1;
         return 0;
      }
      else if((it == 1 || nv[it - 1])){
         nv[it] = 2;
         ans.push_back(it + 1);
         ans.push_back(it);
      }
      else{
         nv[it] = 2;
         ans.push_back(it - 1);
         ans.push_back(it);
      }
   }

   for(auto it:pos[1]){
      ans.push_back(it);
   }

   cout << (int)ans.size() << "\n";
   for(auto it:ans){
      cout << it << " ";
   }

   return 0;
}
