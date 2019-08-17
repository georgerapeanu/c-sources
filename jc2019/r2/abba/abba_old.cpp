///helper script
#include <fstream>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

ifstream f("abba.in");
ofstream g("abba.out");

const int LVL = 1e6;
const int MOD = 1e9 + 7;

vector<int> bits;
bool solve(string &s,int lvl) {

    bits.clear();

    for(auto it:s) {
        if(it != 'a' && it != 'b') {
            return false;
        }
    }

    while(true) {
        if((int)s.size() == 1) {
            if(s[0] == 'b') {
                bits.push_back(lvl - 1);
            }
            break;
        }
        if(s == "ab") {
            bits.push_back(lvl - 2);
            break;
        }
        bool has_aa = false;
        bool has_bb = false;

        for(int i = 1; i < (int)s.size(); i++) {
            has_aa |= (s[i - 1] == 'a' && s[i] == 'a');
            has_bb |= (s[i - 1] == 'b' && s[i] == 'b');
        }

        if((has_aa ^ has_bb) == 0) {
            return false;
        }
        string ns = "";

        for(int i = 0; i < (int)s.size(); i++) {
            if(i < (int)s.size() - 1 && s[i] == 'a' && s[i + 1] == 'b') {
                ns = ns + (has_aa ? 'b':'a');
                i++;
            }
            else {
                ns = ns + s[i];
            }
        }

        if(s.size() == ns.size()) {
            return false;
        }

        if(has_bb == true) {
            bits.push_back(lvl - 2);
        }

        s = ns;
        lvl--;

    }

    return true;
}

int n;
string s;
int pw2[LVL + 5];

int main() {

    pw2[0] = 1;

    for(int i = 1; i <= LVL; i++) {
        pw2[i] = 2 * pw2[i - 1];
        if(pw2[i] >= MOD) {
            pw2[i] -= MOD;
        }
    }

    f >> n;

    while(n--) {
        f >> s;
        int wh = LVL;
        bool ok = solve(s,LVL);
        if(ok == false) {
            g << -1 << "\n";
        }
        else {
            sort(bits.begin(),bits.end());
            reverse(bits.begin(),bits.end());

            while((int)bits.size() > 1 && bits[(int)bits.size() - 2] == bits[(int)bits.size() - 1]) {
                int b = bits.back();
                bits.pop_back();
                bits.back() = b + 1;
            }

            int ans = 1;
            wh -= (bits.empty() == true ? wh - 1:bits.back());
            for(auto &it:bits) {
                it -= bits.back();
                ans += pw2[it];
                if(ans >= MOD) {
                    ans -= MOD;
                }
            }

            g << wh << " " << ans << "\n";
        }
    }

    f.close();
    g.close();

    return 0;
}
