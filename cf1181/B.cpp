#include <bits/stdc++.h>

using namespace std;

int l;
string s;

class Bignum {
public:
    vector<int> digits;

public:

    Bignum() {
        digits.clear();
    }

    bool operator < (const Bignum &other)const {
        if(this->digits.size() != other.digits.size()) {
            return this->digits.size() < other.digits.size();
        }
        for(int i = (int)this->digits.size() - 1; i >= 0; i--) {
            if(this->digits[i] != other.digits[i]) {
                return this->digits[i] < other.digits[i];
            }
        }
        return 0;
    }

    Bignum operator + (const Bignum &other)const {
        Bignum ans;
        int t = 0;

        for(int i = 0; i < (int)this->digits.size() || i < (int)other.digits.size() || t; i++) {
            ans.digits.push_back((i < (int)this->digits.size() ? this->digits[i]:0) + (i < (int)other.digits.size() ? other.digits[i]:0) + t);
            t = ans.digits.back() / 10;
            ans.digits.back() %= 10;
        }

        return ans;
    }

    void afis() {
        for(int i = (int)this->digits.size() - 1; i >= 0; i--) {
            cout << this->digits[i];
        }

        cout << "\n";
    }
};

Bignum getnum(int st,int dr) {
    Bignum ans;
    for(int i = dr; i >= st; i--) {
        ans.digits.push_back(s[i] - '0');
    }
    return ans;
}

int main() {
    cin >> l;
    cin >> s;
    s = " " + s;

    int y = (1 + l) / 2;
    int x = y - 1;
    int z = y + 1;

    while(x > 0 && s[x] == '0') {
        x--;
    }

    while(z <= l && s[z] == '0') {
        z++;
    }

    bool found = false;

    Bignum ans;

    if(x > 1) {
        Bignum tmp = getnum(1,x - 1) + getnum(x,l);
        if(found == false || tmp < ans) {
            ans = tmp;
            found = true;
        }
    }

    if(1 < z && z <= l) {
        Bignum tmp = getnum(1,z - 1) + getnum(z,l);
        if(found == false || tmp < ans) {
            ans = tmp;
            found = true;
        }
    }

    if(y > 1 && s[y] != '0') {
        Bignum tmp = getnum(1,y - 1) + getnum(y,l);
        if(found == false || tmp < ans) {
            ans = tmp;
            found = true;
        }
    }

    ans.afis();

    return 0;
}
