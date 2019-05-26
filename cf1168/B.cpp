#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <queue>

using namespace std;

const int TEST = 9;///any sequence longer than TEST has an interval like that

int ok(int conf,int lg){
    for(int x = 0;x < lg;x++){
        for(int s = 1;x + 2 * s < lg;s++){
            if(((conf >> x) & 1) == ((conf >> (x + s)) & 1) && ((conf >> x) & 1) == ((conf >> (x + 2 * s)) & 1)){
                return 1;
            }
        }
    }
    return 0;
}

string s;

int main(){

    cin >> s;

    long long ans = 0;

    for(int l = 0;l < (int)s.size();l++){
        ans += max(0,(((int)s.size() - 1) - (l + TEST) + 1));

        int conf = 0;

        for(int r = l;r < l + TEST && r < (int)s.size();r++){
            conf = (conf << 1) + (s[r] == '1');
            ans += ok(conf,r - l + 1);
        }
    }

    cout << ans;

    return 0;
}
