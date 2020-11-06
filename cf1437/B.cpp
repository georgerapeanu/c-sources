#include <bits/stdc++.h>

using namespace std;

int main(){

    int t;

    cin >> t;

    while(t--){

        string s;
        int n;
        cin >> n;
        cin >> s;

        int tmp = 0;

        for(int i = 1;i < n;i++){
            tmp += (s[i] == s[i - 1]);
        }
        tmp = (tmp + 1) / 2;
        printf("%d\n",tmp);
    }


    return 0;
}
