#include <iostream>

using namespace std;

bool ask(int x,int y) {
    cout << "? " << x << " " << y << endl;
    string ans;
    cin >> ans;
    return (ans == "x");
}

void answer(int ans) {
    cout << "! " << ans << endl;
}

string mess;

int main() {
    while(cin >> mess) {
        if(mess != "start") {
            return 0;
        }
        int ans = 0,mb = 0;
        for(int b = 0; b <= 30; b++) {
            if(ask(1 << b,1 << (b + 1))) {
                ans |= (1 << b);
                mb = b;
                break;
            }
        }

        for(int b = mb - 1; b >= 0; b--) {
            if(ask(ans + (1 << b),ans + (2 << b))) {
                ans |= (1 << b);
            }
        }

        if(ask(ans + 1,ans) == 0) {
            ans++;
        }

        answer(ans);
    }

    return 0;
}
