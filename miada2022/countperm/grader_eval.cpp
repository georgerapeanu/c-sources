#include <bits/stdc++.h>

#define FIN "countperm.in"
#define FOUT "countperm.out"
#define FOK "countperm.ok"

using namespace std;

ifstream in, ok, out;
int Score_Test;

void Score() {
    cout << Score_Test << endl;
    in.close(); out.close(); ok.close();
    exit(0);
}

void Wrong() {
    cerr << "Răspuns greșit!" << endl;
    Score_Test = 0;
    Score();
}

void Correct() {
    cerr << "OK!" << endl;
    Score();
}

int main() {
    in.open(FIN);
    out.open(FOUT);
    ok.open(FOK);

    if(!in) {
      cerr << "Fișier de intrare lipsă!" << endl;
      Score();
    }
    if(!ok) {
      cerr << "Fișier ok lipsă!" << endl;
      Score();
    }

    if(!out) {
      cerr << "Fișier out lipsă!" << endl;
      Score();
    }

    ok >> Score_Test;
    string vok, vout;
    while (ok >> vok) {
        if (!(out >> vout) || vout != vok)
            Wrong();
    }

    Correct();
    return 0;
}
