#include <bits/stdc++.h>

using namespace std;

int ask(int pos) {
    int ans;
    cout << pos << endl;
    cin >> ans;
    return ans;
}

bool query(vector<int> b) {
    for(int i = 1; i < (int)b.size(); i++)cout << b[i];
    cout << endl;
    char c;
    cin >> c;
    return (c == 'Y');
}

int main() {
    int t;
    int n;
    cin >> t >> n;

    for(int x = 1; x <= t; x++) {
        vector<int> xors(n + 1,0);
        vector<int> lst(n + 1,0);

        for(int i = 1; i <= n / 2; i++) {
            lst[i] = ask(i);
            lst[n - i + 1] = ask(n - i + 1);
            xors[i] = lst[i] ^ lst[n - i + 1];
        }

        if(n == 10) {
            if(query(lst) == false) {
                return 0;
            }
            continue;
        }

        ///prepare the 2 halves;

        for(int fst = 1; fst <= n / 2; fst += 5) {
            vector<int> pos(2,-1);
            for(int i = fst; i < fst + 5; i++) {
                pos[xors[i]] = i;
            }
            if(pos[0] != -1) { ///reverse doesnt do anything, they can either be complemented or not
                int a = ask(pos[0]);
                if(a != lst[pos[0]]) { ///they are complemented in comparison with last time
                    for(int i = fst; i < fst + 5; i++) {
                        if(xors[i] == 0) {
                            lst[i] ^= 1;
                        }
                    }
                }
            }
            else {
                ask(1); /// just for filling
            }
            if(pos[1] != -1) { ///complement acts as reverse,so they can either be reversed or not
                int a = ask(pos[1]);
                if(a != lst[pos[1]]) { ///they are reversed
                    for(int i = fst; i < fst + 5; i++) {
                        if(xors[i] == 1) {
                            lst[i] ^= 1;
                        }
                    }
                }
            }
            else {
                ask(1); /// just for filling
            }
        }

        if(n == 20) { ///fill this up to 10 queries
            for(int i = 1; i <= 6; i++) {
                ask(1);
            }
        }

        ///sync the two halves

        for(int fst = 1; fst <= n / 2; fst += n / 4) {
            vector<int> pos(2,-1);
            for(int i = fst; i < fst + n / 4; i++) {
                pos[xors[i]] = i;
            }
            if(pos[0] != -1) { ///reverse doesnt do anything, they can either be complemented or not
                int a = ask(pos[0]);
                if(a != lst[pos[0]]) { ///they are complemented in comparison with last time
                    for(int i = fst; i < fst + n / 4; i++) {
                        if(xors[i] == 0) {
                            lst[i] ^= 1;
                        }
                    }
                }
            }
            else {
                ask(1); /// just for filling
            }
            if(pos[1] != -1) { ///complement acts as reverse,so they can either be reversed or not
                int a = ask(pos[1]);
                if(a != lst[pos[1]]) { ///they are reversed
                    for(int i = fst; i < fst + n / 4; i++) {
                        if(xors[i] == 1) {
                            lst[i] ^= 1;
                        }
                    }
                }
            }
            else {
                ask(1); /// just for filling
            }
        }

        for(int i = 1; i <= n / 2; i++) {
            lst[n + 1 - i] = lst[i] ^ xors[i];
        }

        if(query(lst) == false) {
            return 0;
        }
    }

    return 0;
}
