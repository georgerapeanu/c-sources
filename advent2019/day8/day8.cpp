#include <bits/stdc++.h>

using namespace std;

int fr[10];

int image[30][30];

int main() {

    string s;

    int h;
    int w;

    cin >> h >> w;
    cin >> s;

    int mi0 = 1e9;
    int ans = 0;

    s = s + "2";

    fr[0] = 1e9;

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            image[i][j] = 2;
        }
    }

    for(int i = 0; i < (int)s.size(); i++) {
        if(i % (h * w) == 0) {
            if(mi0 > fr[0]) {
                mi0 = fr[0];
                ans = fr[1] * fr[2];
            }
            else if(mi0 == fr[0]) {
                ///shouldnt happen
            }
            memset(fr,0,sizeof(fr));
        }
        fr[s[i] - '0']++;
        if(image[(i % (h * w)) / w][(i % (h * w)) % w] == 2) {
            image[(i % (h * w)) / w][(i % (h * w)) % w] = s[i] - '0';
        }
    }

//    cout << ans;

    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            cout << (image[i][j] == 1 ? 'X':' ');
        }
        cout << "\n";
    }

    return 0;
}
