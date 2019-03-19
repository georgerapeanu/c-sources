#include <iostream>
#include <iomanip>

using namespace std;

const int NMAX = 5e5;

string s;
int SP[NMAX + 5];
long long SSP[NMAX + 5];

int main(){
    cin >> s;
    s = " " + s;

    for(int i = 1;i < (int)s.size();i++){
        SP[i] = SP[i - 1];
        if(s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U' || s[i] == 'Y'){
            SP[i]++;
        }
        SSP[i] = SP[i] + SSP[i - 1];
    }

    long double ans = 0;

    for(int l = 1;l < (int)s.size();l++){
        long long tmp = SSP[(int)s.size() - 1] - SSP[l - 1] - SSP[(int)s.size() - 1 - l];
        ans += tmp / (long double)l;
    }

    cout << fixed << setprecision(8) << ans << "\n";

    return 0;
}
