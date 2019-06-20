#include <bits/stdc++.h>

using namespace std;

const int NMAX = 500;

int n,m;
string s[505];

int main(){

    cin >> n >> m;

    if(n <= 2 || m <= 2){
        cout << "NO";
        return 0;
    }

    int total = 0;

    for(int i = 1;i <= n;i++){
        cin >> s[i];
        s[i] = " " + s[i];
        for(auto &it:s[i]){
            total += (it == '*');
        }
    }

    for(int i = 2;i < n;i++){
        for(int j = 2;j < m;j++){
            if(s[i][j] == '*' &&
               s[i - 1][j] == '*' &&
               s[i][j + 1] == '*' &&
               s[i + 1][j] == '*' &&
               s[i][j - 1] == '*'){
                

                int cnt = -1;

                for(int k = i;k <= n && s[k][j] == '*';k++){
                    cnt ++;
                }
                for(int k = i - 1;k > 0 && s[k][j] == '*';k--){
                    cnt ++;
                }
                
                for(int k = j;k <= m && s[i][k] == '*';k++){
                    cnt ++;
                }

                for(int k = j - 1;k > 0 && s[i][k] == '*';k--){
                    cnt ++;
                }
                
                if(cnt == total){
                    cout << "YES";
                    return 0;
                }
                else{
                    cout << "NO";
                    return 0;
                }
            }
        }
    }
          
    cout << "NO";
    return 0;
}
