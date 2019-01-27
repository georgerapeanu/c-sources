#include <iostream>
#include <algorithm>

using namespace std;

int n,k;
int a[(int)2e5 + 5];
string s;

int main(){
    cin >> n >> k;
    for(int i = 1;i <= n;i++){
        cin >> a[i];
    }
    cin >> s;
    s = " " + s;

    long long ans = 0;

    for(int i = 1;i <= n;){
        int j = i;
        while(j < (int)s.size() && s[i] == s[j]){
            j++;
        }

        sort(a + i,a + j);
        reverse(a + i,a + j);
        for(int l = 0;l < k && i + l < j;l++){
            ans += a[i + l];
        }
        i = j;
    }

    cout << ans;

    return 0;
}
