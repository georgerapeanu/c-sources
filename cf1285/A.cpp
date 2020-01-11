#include <bits/stdc++.h>

using namespace std;

int main() {

    int cntl = 0;
    int cntr = 0;

    string s;

    int n;

    cin >> n;

    cin >> s;

    for(auto it:s) {
        if(it == 'L') {
            cntl++;
        }
        else {
            cntr++;
        }
    }

    printf("%d\n",cntl + cntr + 1);

    return 0;
}
