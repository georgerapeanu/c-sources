#include <bits/stdc++.h>

using namespace std;

int n;
string s;
deque<pair<int,int>> coins[2];

int main(){
   
    cin >> n;
    cin >> s;

    for(int i = 0;i < n;i++){
        coins[s[i] != 'A'].push_back({1,i});
    }

    while(coins[0].empty() == false && coins[1].empty() == false){
        pair<int,int> a = coins[0].front();
        pair<int,int> b = coins[1].front();

        if(a < b){
            coins[0].push_back({a.first + 1,a.second});
        }else{
            coins[1].push_back({b.first + 1,b.second});
        }
        coins[0].pop_front();
        coins[1].pop_front();
    }

    if(coins[0].empty()){
        cout << "Paul" << endl;
    }else{
        cout << "Alex" << endl;
    }

    return 0;
}
