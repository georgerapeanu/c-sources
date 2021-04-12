#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int LGMAX = 10;
const int NMAX = 1000;

string s;

int t,n;
int suffix_array[NMAX + 5];
int pos[LGMAX + 1][NMAX + 5];
int gap;

bool cmp(int a,int b){
    if(pos[gap][a] != pos[gap][b]){
        return pos[gap][a] < pos[gap][b];
    }
    a += (1 << gap);
    b += (1 << gap);

    if(b > n || a > n){
        return a > b;
    }

    return pos[gap][a] < pos[gap][b];
}

void build_suffix_array(){
    for(int i = 1;i <= n;i++){
        suffix_array[i] = i;
        pos[0][i] = s[i] - 'A';
    }

    for(gap = 0;gap < LGMAX;gap++){
        sort(suffix_array + 1,suffix_array + 1 + n,cmp);
        pos[gap + 1][suffix_array[1]] = 0;
        for(int i = 2;i <= n;i++){
            pos[gap + 1][suffix_array[i]] = pos[gap + 1][suffix_array[i - 1]] + cmp(suffix_array[i - 1],suffix_array[i]);
        }
    }
}

int lcp(int a,int b){
    int ans = 0;
    for(int h = LGMAX;h >= 0 && a <= n && b <= n;h--){
        if(pos[h][a] == pos[h][b]){
            a += (1 << h);
            b += (1 << h);
            ans |= (1 << h);
        }
    }

    return ans;
}

int main(){
    cin >> t;

    while(t--){
        cin >> s;
        n = (int)s.size();
        s = " " + s;
        build_suffix_array();
        int ans = 0;
        for(int i = 1;i <= n;i++){
            ans += n - suffix_array[i] + 1;
            if(i > 1){
                ans -= lcp(suffix_array[i - 1],suffix_array[i]);
            }
        }

        cout << ans << "\n";
    }
    return 0;
}
