#include <fstream>
#include <algorithm>
#include <iostream>

using namespace std;

ifstream f("dupadealuri.in");
ofstream g("dupadealuri.out");

string s;
string t;

///(i - manacher[i],i + manacher[i])

int manacher[int(2e5) + 5];

int main() {

    f >> s;

    for(int i = 0; i < (int)s.size(); i++) {
        t += "#";
        t += s[i];
    }

    s = t + "#";

    int h = 0,r = 0;

    for(int i = 0; i < (int)s.size(); i++) {
        if(h + r > i) {
            manacher[i] = min(manacher[2 * h - i],h + r - i);
        }
        while(i - manacher[i] >= 0 && i + manacher[i] < (int)s.size() && s[i + manacher[i]] == s[i - manacher[i]]) {
            manacher[i]++;
        }
        if(h + r < i + manacher[i]) {
            h = i;
            r = manacher[i];
        }
    }

    int d = 0;
    long long ans = 1;


    for(int i = 1; i < (int)s.size() - 1; i++) {
        if(s[i] == s[(int)s.size() - 1 - i]) {
            d = i;
            if(s[i] != '#' && i + 1 < (int)s.size() - 1 - i - 1) {
                ans++;
            }
        }
        else {
            break;
        }
    }

    for(int i = 1; i < (int)s.size() - 1; i++) {
        if(i * 2 < (int)s.size() - 1) {
            int tmp = 0;
            if(i % 2 == 0) {
                ans += max(0,min(d - (i - manacher[i]) + 1,manacher[i])) / 2;
                tmp = max(0,min(d - (i - manacher[i]) + 1,manacher[i])) / 2;
            }
            else {
                ans += max(0,min(d - (i - manacher[i]) + 1,manacher[i] + 1)) / 2;
                tmp = max(0,min(d - (i - manacher[i]) + 1,manacher[i] + 1)) / 2;
            }
        }
    }

    reverse(s.begin(),s.end());
    reverse(manacher,manacher + s.size());
    for(int i = 1; i < (int)s.size() - 1; i++) {
        if(i * 2 < (int)s.size() - 1) {
            if(i % 2 == 0) {
                ans += max(0,min(d - (i - manacher[i]) + 1,manacher[i])) / 2;
            }
            else {
                ans += max(0,min(d - (i - manacher[i]) + 1,manacher[i] + 1)) / 2;
            }
        }
    }
    g << ans << "\n";



    f.close();
    g.close();

    return 0;
}
