#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string a,b;
int numA;
int numB;

vector< pair<int,int> > solve(char fst, char snd, int fst_fr, int snd_fr, int suf_first = (int)a.size(), int suf_second = (int)b.size()){
    if(suf_first == 0 && suf_second == 0){
        return vector< pair<int,int> >();
    }

    while(suf_first > 0 && a[suf_first - 1] == fst){
        suf_first--;
        fst_fr--;
    }
    while(suf_second > 0 && b[suf_second - 1] == snd){
        suf_second--;
        snd_fr--;
    }

    vector< pair<int,int> > tmp = solve(snd, fst, snd_fr, fst_fr, suf_first, suf_second);
    if(fst_fr || snd_fr){
        tmp.push_back({snd_fr, fst_fr});
    }
    return tmp;
}

vector< pair<int,int> > min(vector< pair<int,int> > a, vector< pair<int,int> > b){
    return a.size() < b.size() ? a : b;
}

vector< pair<int,int> > Try(char fst,char snd){
}

int main(){
    cin >> a >> b;

    for(auto it:a){
        numA += (it == 'a');
        numB += (it == 'b');
    }

    for(auto it:b){
        numA += (it == 'a');
        numB += (it == 'b');
    }

    vector< pair<int,int> > ans = min(solve('a', 'b', numA, numB), solve('b', 'a', numB, numA));

    cout << ans.size() << "\n";

    for(auto it:ans){
        cout << it.first << " " << it.second << "\n";
    }

    return 0;
}
