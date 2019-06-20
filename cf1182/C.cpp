#include <bits/stdc++.h>

using namespace std;

int n;
pair<pair<int,int>,int> a[100005];
bool taken[100005];
string s[100005];

int main(){

    cin >> n;

    for(int i = 1;i <= n;i++){
        cin >> s[i];

        for(auto it:s[i]){
            if(it == 'a' || it == 'e' || it == 'i' || it == 'o' || it == 'u'){
                a[i].first.first++;
                a[i].first.second = it;
            }
        }
        a[i].second = i;
    }

    sort(a + 1,a + 1 + n);

    vector<pair<int,int> > snd;

    for(int i = 2;i <= n;i++){
        if(taken[i - 1] == false && a[i].first == a[i - 1].first){
            taken[i] = true;
            taken[i - 1] = true;
            snd.push_back({a[i].second,a[i - 1].second});
        }
    }

    int l = 0;

    for(int i = 1;i <= n;i++){
        if(taken[i] == false){
            a[++l] = a[i];
        }
        taken[i] = false;
    }

    n = l;

    int nontaken_cnt = 0;

    vector<pair<int,int> > fst;

    for(int i = 2;i <= n;i++){
        if(a[i].first.first == a[i - 1].first.first && taken[i - 1] == false){
            taken[i] = true;
            taken[i - 1] = true;
            fst.push_back({a[i].second,a[i - 1].second});
        }
    }

    while((int)snd.size() > (int)fst.size()){
        fst.push_back(snd.back());
        snd.pop_back();
    }

    cout << min(fst.size(),snd.size()) << endl;

    for(int i = 0;i < (int)fst.size() && i < (int)snd.size();i++){
        cout << s[fst[i].first] << " " << s[snd[i].first] << "\n";
        cout << s[fst[i].second] << " " << s[snd[i].second] << "\n";
    }

    return 0;
}
