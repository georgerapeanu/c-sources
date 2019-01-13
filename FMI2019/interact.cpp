#include <iostream>
#include <cstdlib>

using namespace std;

bool ask(const string &a) {
    int ans = 0;
    cout << "? " << a << endl;
    cin >> ans;
    return ans;
}

void answer(const string &a) {
    cout << "! " << a << endl;
    exit(0);
}

const int NMAX = 100;
const int SIGMA = 26;

string smen[30];

string get(char c) {
    int st = 0,dr = NMAX + 1;

    while(dr - st > 1) {
        int mid = (st + dr) / 2;

        if(ask(string(mid,c))) {
            st = mid;
        }
        else {
            dr = mid;
        }
    }

    return string(st,c);
}

string mer(string &a,string &b) {
    string pref = "";

    int y = 0;

    while(y < (int)b.size()) {
        string tmp = pref + b[y] + a;
        if(!ask(tmp)) {
            break;
        }
        pref += b[y];
        y++;
    }

    for(int i = 0; i < (int)a.size(); i++) {
        pref += a[i];
        while(y < (int)b.size()) {
            string tmp = pref + b[y] + a.substr(i + 1);
            if(!ask(tmp)) {
                break;
            }
            pref += b[y];
            y++;
        }
    }
    return pref;
}

int main() {

    for(int i = 0; i < SIGMA; i++) {
        smen[i] = get('a' + i);
    }

    for(int i = 1; i < SIGMA; i++) {
        smen[0] = mer(smen[0],smen[i]);
    }

    answer(smen[0]);

    return 0;
}
