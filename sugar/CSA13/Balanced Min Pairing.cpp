#include <iostream>
#include <algorithm>

using namespace std;

int n,t;
pair<int,int> fst[50005];
pair<int,int> snd[50005];
int ans[50005];

int main() {

    cin >> t;
    while(t--) {
        cin >> n;
        for(int i = 1; i <= n; i++) {
            cin >> fst[i].first;
            fst[i].second = i;
        }
        for(int i = 1; i <= n; i++) {
            cin >> snd[i].first;
            snd[i].second = i;
        }

        sort(fst + 1,fst + 1 + n);
        sort(snd + 1,snd + 1 + n);

        bool ok = true;

        for(int i = 1; i <= n / 2; i++) {
            ok &= (fst[i].first < snd[i + n / 2].first);
        }
        for(int j = 1; j <= n / 2; j++) {
            ok &= (snd[j].first < fst[j + n / 2].first);
        }
        if(!ok)cout << "-1\n";
        else {
            for(int i = 1; i <= n / 2; i++) {
                ans[fst[i].second] = snd[i + n / 2].second;
            }
            for(int i = n / 2 + 1; i <= n; i++) {
                ans[fst[i].second] = snd[i - n / 2].second;
            }
            for(int i = 1; i <= n; i++)cout << ans[i] << " ";
            cout << "\n";
        }
    }

    return 0;
}