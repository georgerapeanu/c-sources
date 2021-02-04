#include <bits/stdc++.h>
using namespace std;

struct Trie{
    map<string,Trie*> fiu;
    bool changed;

    Trie()
    {
        changed = true;
        fiu = map<string,Trie*>();
    }
};

Trie *T = new Trie;
int n;
char s[100005];

void adauga(Trie *nod, char *c, bool chan) {
    if ((*c) == '\0' || (*c) == '\n') {
        // gata
        nod->changed = chan;
        return;
    }

    string acum = "";
    char *i = c;
    i++;
    while ((*i) != '\0' && (*i) != '\n' && (*i) != '/') {
        acum += (*i);
        i++;
    }

    if (nod->fiu.count(acum) == 0) {
        nod->fiu[acum] = new Trie;
    }

    adauga(nod->fiu[acum], i, chan);
}

void chestie(Trie *nod) {
    if (nod->fiu.empty()) {
        // fisier 0
        return;
    }

    // merg in fii
    bool tot = 1;
    for (auto &it:nod->fiu) {
        chestie(it.second);
        nod->changed &= it.second->changed;
    }

}

string dfs_s = "/";
void afisare(Trie *nod) {
    
    if (nod->changed) {
        if(nod != T){
            dfs_s.pop_back();
        }
        cout << dfs_s << "\n";
        return;
    }

    for (auto &it:nod->fiu){
        int curr_size = dfs_s.size();
        dfs_s += it.first + "/";
        afisare(it.second);
        while(curr_size < (int)dfs_s.size()){
            dfs_s.pop_back();
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        bool val;
        cin >> val >> s;

        adauga(T, s, val);
    }

    chestie(T);

    afisare(T);


    return 0;
}
