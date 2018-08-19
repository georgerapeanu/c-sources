#include <iostream>

using namespace std;
int pref[2005][3];
int suf[2005][3];
int N;
int V[2005];
int rez = 0;
int main(){
    cin >> N;
    for(int i = 1;i <= N;i++){
        cin >> V[i];
        pref[i][1] = pref[i - 1][1] + (V[i] == 1);
        pref[i][2] = pref[i - 1][2] + (V[i] == 2);
    }
    for(int i = N;i;i--){
        suf[i][1] = suf[i + 1][1] + (V[i] == 1);
        suf[i][2] = suf[i + 1][2] + (V[i] == 2);
        rez = max(rez,pref[i][1] + suf[i][2]);
    }
    for(int i = 1;i <= N;i++){
        int maxi = 0;
        for(int j = i;j <= N;j++){
            maxi = max(maxi,suf[j][1] + pref[j][2]);
            rez = max(rez,pref[i - 1][1] + suf[j + 1][2] + maxi - suf[j + 1][1] - pref[i - 1][2]);
        }
    }
    cout << rez;
    return 0;
}
