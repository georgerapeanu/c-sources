#include <fstream>
#include <algorithm>

using namespace std;

ifstream f("secvzerounu.in");
ofstream g("secvzerounu.out");

int t;
string s;

int main() {

    f >> t;

    while(t--) {
        f >> s;
        if(s.size() == 1) {
            g << (s[0] == '0' ? "Da\n":"Nu\n");
        }
        else {
            g << ((s[0] == '0' && s[1] == '1') ? "Da\n":"Nu\n");
        }
    }

    f.close();
    g.close();

    return 0;
}
