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

int cnt_aa;
int cnt_bb;
vector<int> pos_ab;

int nxt[LVL + 5];
int ant[LVL + 5];
const int root = LVL + 4;
int len;

bool solve(string &s,int lvl) {

    bits.clear();

    cnt_aa = 0;
    cnt_bb = 0;
    pos_ab.clear();

    for(int i = 0; i < (int)s.size(); i++) {
        if(s[i] != 'a' && s[i] != 'b') {
            return false;
        }
        if(i < (int)s.size() - 1) {
            if(s[i] == 'a' && s[i + 1] == 'a') {
                cnt_aa++;
            }
            else if(s[i] == 'a' && s[i + 1] == 'b') {
                pos_ab.push_back(i);
            }
            else if(s[i] == 'b' && s[i + 1] == 'b') {
                cnt_bb++;
            }
        }
        nxt[i] = i + 1;
        ant[i + 1] = i;
    }

    len = s.size();
    nxt[len - 1] = root;
    ant[root] = len - 1;
    nxt[root] = 0;
    ant[0] = root;

    while(true) {
        if(len == 1) {
            if(s[nxt[root]] == 'b') {
                bits.push_back(lvl - 1);
            }
            break;
        }
        if(len == 2 && s[nxt[root]] == 'a' && s[nxt[nxt[root]]] == 'b') {
            bits.push_back(lvl - 2);
            break;
        }

        if((int)pos_ab.empty()) {
            return false;
        }

        bool has_aa = (cnt_aa > 0);
        bool has_bb = (cnt_bb > 0);

        if((has_aa ^ has_bb) == 0) {
            return false;
        }

        vector<int> new_pos_ab;

        if(has_bb) {
            bits.push_back(lvl - 2);
        }

        for(auto it:pos_ab) {
            if(ant[it] != root && s[ant[it]] == 'a') {
                cnt_aa--;
            }
            if(nxt[nxt[it]] != root && s[nxt[nxt[it]]] == 'b') {
                cnt_bb--;
            }

            nxt[it] = nxt[nxt[it]];
            ant[nxt[it]] = it;
            len--;

            if(has_aa) {
                s[it] = 'b';
                if(ant[it] != root && s[ant[it]] == 'b') {
                    cnt_bb++;
                }
                if(nxt[it] != root && s[nxt[it]] == 'b') {
                    cnt_bb++;
                }
                if(ant[it] != root && s[ant[it]] == 'a') {
                    new_pos_ab.push_back(ant[it]);
                }
            }
            else {
                s[it] = 'a';
                if(ant[it] != root && s[ant[it]] == 'a') {
                    cnt_aa++;
                }
                if(nxt[it] != root && s[nxt[it]] == 'a') {
                    cnt_aa++;
                }
                if(nxt[it] != root && s[nxt[it]] == 'b') {
                    new_pos_ab.push_back(it);
                }
            }
        }

        pos_ab = new_pos_ab;

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
